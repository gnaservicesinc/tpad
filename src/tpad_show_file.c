/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_show_file.c , is part of tpad.
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
extern int setModified;
extern int madetemp;
extern gchar *unknownContents;
extern gchar* origfile;
extern GtkSourceBuffer *mBuff;
extern GtkSourceView *view;

extern int tpad_wach_thread_set;

void show_file(gchar *nfile){
//new_file();
	static gchar *newfile=NULL;

	
	newfile= g_strdup(check_file(nfile));

		if (newfile == NULL){
		print("Can't open file:");
		print(nfile);
	}
	else{
	int mcheck=check_magic(newfile);
		
		if(mcheck == 0){
			printf("tpad(v.%s):%s\n",VERSION,_ERROR_MAGIC_BAD);
			}
	else{

	 if (mcheck == 2){
	printf("tpad(v.%s):%s\n",VERSION,_ERROR_MAGIC_INIT);
		}
	if (mcheck == 3){
	   printf("%s\n",_ERROR_MAGIC_DB);
		}
	if(cfg_use_open_guard()){	
				tpad_fp_set(newfile);

	
					if(tpad_open_guard_check_ok()){
						 setModified=1;
					}
					else{

						tpad_open_guard_make_temp();
						madetemp=1;
						origfile=g_strdup((gchar*) newfile);
						
				 		
					}
				}

	gsize length;
    GError *err = NULL;
	content=NULL;
	unknownContents=NULL;
	if(g_file_get_contents (newfile, &unknownContents, &length,&err))
	{
		if (err != NULL){
			 ui_unity_urgent_on();
			gerror_warn(err->message,_CAN_NOT_READ_FILE,TRUE,TRUE);
			g_error_free (err);
			
		}
		else{
			GError *error = NULL;	
			content=g_strdup(g_convert(unknownContents, length, "UTF-8", g_get_codeset(),NULL, NULL, &error));
			g_free(unknownContents);
			if (error != NULL)
       		{
			    ui_unity_urgent_on();
				gerror_warn(error->message,_CONVERT_FAILED,TRUE,TRUE);
   				g_error_free (error);
       		}
 	   		else{
				set_buffer();
				tpad_fp_set(newfile);	
				set_title();
				set_language();
				if(tpad_wach_thread_set) tpad_watch_exit();
				tpad_modbal_set_zero();
				tpad_watch_fname(tpad_fp_get_current());
										if(cfg_use_open_guard() &&  setModified==1){
					        gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
    						gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),TRUE);
  							gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
							}
			} 
		}
	}
  }
}

/*
	new_file();
	gchar* unknownContents=NULL;
	static gchar *newfile=NULL;

	
	newfile= g_strdup(check_file(nfile));

		if (newfile == NULL){
		print("Can't open file:");
		print(nfile);
	}
	else{
	int mcheck=check_magic(newfile);
		
		if(mcheck == 0){
			printf("tpad(v.%s):%s\n",VERSION,_ERROR_MAGIC_BAD);
			}
	else{

	 if (mcheck == 2){
	printf("tpad(v.%s):%s\n",VERSION,_ERROR_MAGIC_INIT);
		}
	if (mcheck == 3){
	   printf("%s\n",_ERROR_MAGIC_DB);
		}
	if(cfg_use_open_guard()){	
				tpad_fp_set(newfile);

	
					if(tpad_open_guard_check_ok()){
						 setModified=1;
					}
					else{

						tpad_open_guard_make_temp();
						madetemp=1;
						origfile=g_strdup((gchar*) newfile);
						
				 		
					}
				}

	gsize length;
    GError *err = NULL;
	content=NULL;
	unknownContents=NULL;
	
	if(g_file_get_contents (newfile, &unknownContents, &length,&err))
	{
		if (err != NULL){
			// ui_unity_urgent_on();
			gerror_warn(err->message,_CAN_NOT_READ_FILE,TRUE,TRUE);
			g_error_free (err);
			
		}
		else{
			GError *error = NULL;	
			content=g_strdup(g_convert(unknownContents, length, "UTF-8", g_get_codeset(),NULL, NULL, &error));
			g_free(unknownContents);
			if (error != NULL)
       		{
			//    ui_unity_urgent_on();
				gerror_warn(error->message,_CONVERT_FAILED,TRUE,TRUE);
   				g_error_free (error);
       		}
 	   		else{
				
				
				set_buffer();
				tpad_fp_set(newfile);	
				set_title();
				set_language();
				if(tpad_wach_thread_set) tpad_watch_exit();
				tpad_modbal_set_zero();
				tpad_watch_fname(tpad_fp_get_current());
										if(cfg_use_open_guard() &&  setModified==1){
					        gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
    						gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),TRUE);
  							gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
							}
			} 
		}
	}
  }
}
*/
}
