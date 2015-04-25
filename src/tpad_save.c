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
extern gboolean save_locked;
extern GtkWidget *window;
extern gchar* origfile;
extern int madetemp;
extern int nname;
extern int tpad_wach_thread_set;
extern gboolean disable_file_watch;
int nname=0;
gint save_watched(){
	gint response=0;
	GtkWidget *dialog;
	if( tpad_modbal_check_armed() && !nname) {
		dialog=gtk_message_dialog_new(GTK_WINDOW(window),
							GTK_DIALOG_DESTROY_WITH_PARENT,
							GTK_MESSAGE_QUESTION,
							GTK_BUTTONS_NONE,
							_ON_DISK_CHANGES);
		gtk_dialog_add_button(GTK_DIALOG(dialog),"Reload & Drop Unsaved Changes",2);
        	gtk_dialog_add_button(GTK_DIALOG(dialog),"Yes",1);
        	gtk_dialog_add_button(GTK_DIALOG(dialog),"No",0);
        	gtk_dialog_add_button(GTK_DIALOG(dialog),"Cancel",-1);
		response=gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);

		if(response == 2){
				nname=1;
				tpad_watch_exit();
				new_thread_tpad(tpad_fp_get_current());
				force_quit_program();
		}
		if(response == -1) return(-1);

		if(response == 0) tpad_modbal_set_zero();
			 
		if(response == 1) save_as();
;
	}
	return(1);
}
gint save_modified(){
        gint response=0;
	GtkWidget *dialog;	
	gint isw = 0;


	if(gtk_text_buffer_get_modified(GTK_TEXT_BUFFER(mBuff))==TRUE) 
	{
		
       	 	dialog= (GtkWidget *) gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,GTK_BUTTONS_NONE,_SAVE_CHANGES);
	
        	gtk_dialog_add_button(GTK_DIALOG(dialog),"Yes",1);
        	gtk_dialog_add_button(GTK_DIALOG(dialog),"No",0);
        	gtk_dialog_add_button(GTK_DIALOG(dialog),"Cancel",-1);
	
        	response=gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);

		if(response == 0) return(1);

        	if(response == 1) save_file();
	
		if(response == -1) return(0);

		return(1);
	}
  return(1);
}
void save_file(){	
    if(tpad_fp_get_current()) {
		if(!nname) save_watched();
		FILE *fp=NULL;
		if(madetemp==1)  fp=fopen(origfile, "w");
		else fp=fopen(tpad_fp_get_current(), "w");
		if(fp){
			GtkTextIter start,end;
			gtk_text_buffer_get_bounds( GTK_TEXT_BUFFER(mBuff),&start,&end);
			fprintf(fp,"%s",gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE));
			fclose(fp);
			if(nname) tpad_watch_exit();
			if(gtk_text_buffer_get_modified(GTK_TEXT_BUFFER(mBuff))==TRUE) {
			 tpad_modbal_set_neg();
			gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);
			}
				set_title();
				set_language();
				if(nname){
				tpad_modbal_set_neg();
				new_thread_tpad(tpad_fp_get_current());
				force_quit_program();
				}		



			/*if(nname){
			 new_thread_tpad(tpad_fp_get_current());
			exit(1)
			}
			else {
			*/

		//show_file(tpad_fp_get_current());
		//set_title();
    		//set_language();
			//}
		}
		else{
			gchar *c_error;
			if (tpad_fp_get_current()){
				if(str_size(tpad_fp_get_current()) >=2 && str_size(tpad_fp_get_current()) <=5000)  c_error=g_strconcat(_FAILED_SAVE_FILE,tpad_fp_get_current(),"\n",NULL);
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
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Save",
                                         GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),TRUE);
	if(tpad_fp_get_current()){

		if(tpad_modbal_check_armed()) {
		    time_t result = time(NULL);
    		if (result == ((time_t)-1))  exit(EXIT_FAILURE);

			char tbuff[2056];
			asctime(localtime(&result));
		
			sprintf(tbuff,"%d",(int)result);
	
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), (gchar*)g_strconcat((gchar*)get_currentfile_basename(),".backup.",tbuff,NULL));

		 gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(dialog),(const gchar *)g_strconcat((gchar*)tpad_fp_get_current(),".backup.",tbuff,NULL));
		nname=1;	
		} 
		else {
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), (gchar*)get_currentfile_basename());
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(dialog),(const gchar *)tpad_fp_get_current());
		}
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
		tpad_fp_set(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
	nname=1;
        save_file();
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}
