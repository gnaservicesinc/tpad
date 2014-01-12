/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_spawn.c , is part of tpad.
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

static gchar* path_self=NULL;

void set_path_self_cleanup() {
	path_self=NULL;
}

void set_path_self( gchar *c_self_path){
				//	if(path_self) g_free(path_self);
	            path_self=NULL;
				path_self=g_strdup(c_self_path);	
}

void *tpad_spawn_command(void *ptr){
	gchar *file_open_new_path=NULL;
	file_open_new_path = (gchar *) g_strdup((gchar*)ptr);
	if(fork() == 0)exit(execl("/bin/sh","sh","-c", (gchar*) g_strconcat(path_self," ",file_open_new_path,NULL), (gchar*) NULL));
	return(0);
}
gint new_thread_tpad (gchar *file){
	pthread_t thread;
	gint  iThreadReturn;
	iThreadReturn = pthread_create(&thread,
	                               NULL,
	                               tpad_spawn_command,
	                               (void*) file);
	pthread_join(thread, NULL);
	return(iThreadReturn);
}