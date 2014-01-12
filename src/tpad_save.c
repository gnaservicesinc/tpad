/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_save.c , is part of tpad.
 *
 *   tpad is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *   tpad is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with tpad.  If not, see <http://www.gnu.org/licenses/>.
 ********************************************************************************/
#include "tpad_headers.h"
extern GtkSourceBuffer *mBuff;
extern gchar *currentfile;
extern gboolean save_locked;
extern GtkWidget *window;
extern gchar* origfile;
extern int madetemp;

gint save_modified(){
	//ui_unity_urgent_on();
    gint response=0;
    if(gtk_text_buffer_get_modified(GTK_TEXT_BUFFER(mBuff))==TRUE) {
		GtkWidget *dialog;
        dialog=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,GTK_BUTTONS_NONE,_SAVE_CHANGES);
        gtk_dialog_add_button(GTK_DIALOG(dialog),GTK_STOCK_YES,1);
        gtk_dialog_add_button(GTK_DIALOG(dialog),GTK_STOCK_NO,0);
        gtk_dialog_add_button(GTK_DIALOG(dialog),GTK_STOCK_CANCEL,-1);
        response=gtk_dialog_run(GTK_DIALOG(dialog));
        if(response == 1) save_file();
        gtk_widget_destroy(dialog);
    }
	//ui_unity_urgent_off();
    if(response==-1) return(0);
    else return(1);
}
void save_file(){	
    if(currentfile) {
		FILE *fp=NULL;
		if(madetemp==1)  fp=fopen(origfile, "w");
		else fp=fopen(currentfile, "w");
		if(fp){
			GtkTextIter start,end;
			gtk_text_buffer_get_bounds( GTK_TEXT_BUFFER(mBuff),&start,&end);
			fprintf(fp,"%s",gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE));
			fclose(fp);
			gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);
			set_title();
    		set_language();
		}
		else{
			gchar *c_error;
			if (currentfile){
				if(str_size(currentfile) >=2 && str_size(currentfile) <=5000)  c_error=g_strconcat(_FAILED_SAVE_FILE,currentfile,"\n",NULL);
			}
			gerror_warn(c_error,"save_file->fopen->FAIL",TRUE,FALSE);
			g_free(c_error);
		}

    }
    else save_as();
}

void save_as(){
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new(_SAVE_FILE,GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_SAVE,
                                         GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),TRUE);
	if(currentfile){
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), (gchar*)get_currentfile_basename());
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(dialog),(const gchar *)currentfile);
	}
	else 
	{
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog),(const gchar *)_FALLBACK_SAVE_FILE_NAME);	
		
	    if (getcRpath() != NULL) gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(dialog),getcRpath());
		else {
					 struct passwd *pw = getpwuid(syscall(__NR_getuid));
			         gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(dialog),(gchar *)pw->pw_dir);
		}
	}
	
	if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT) {
		currentfile=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        save_file();
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}
