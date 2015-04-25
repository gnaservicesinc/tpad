/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_file.c , is part of tpad.
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
extern GtkWidget *window;
extern gboolean save_locked;
extern gchar *content;

gchar* unknownContents=NULL;

void open_file(){  
	gchar *newfile=NULL;
	gint response;
	GtkWidget *dialog;
    if(save_modified()){
        dialog = gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"Cancel",GTK_RESPONSE_CANCEL,"Open",GTK_RESPONSE_ACCEPT,NULL);
		gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
        response = gtk_dialog_run(GTK_DIALOG(dialog));
        if(response==GTK_RESPONSE_ACCEPT){
			save_locked=FALSE;
            newfile=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			if(tpad_fp_get_current()){
				if(newfile) new_thread_tpad((char*) g_strdup(g_strdup(newfile)));
			}
			else show_file(g_strdup(newfile));
			
        }
        gtk_widget_destroy(GTK_WIDGET(dialog));
    }
}
