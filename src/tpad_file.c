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

static gchar *cRpath=NULL;

gchar *clean_path(gchar *path){
	GError *error = NULL;
	gchar *buf_word=NULL;
	gchar *bwords=NULL;
	bwords=path;
	gint bwordsize=str_size(bwords);
	if (bwordsize >= (gint)1)
		{
		buf_word=g_strdup(g_convert(bwords, (gint) -1, (gchar*)"UTF-8", g_get_codeset(),NULL, NULL, &error));	
		if (error != NULL) 
			{
			print(g_strdup(error->message));
			return(NULL);
			}
			else return(g_strdup(buf_word));	
			}
	return(NULL);
}

gchar* link_resolve(gchar* file)
{
	gint path_max=0;
           #ifdef PATH_MAX
             path_max = PATH_MAX;
           #else
             path_max = pathconf(path, _PC_PATH_MAX);
             if (path_max <= 0) path_max = 4096;
           #endif
		 gchar* c_rpath=NULL;
		c_rpath=realpath(g_strdup(file),NULL);
	if(c_rpath == NULL)
	{
		static gchar *OutputError=NULL;
		if (errno){	
		OutputError=g_strconcat("Error resolving file path for:\n",
		                        file,"Reason:\n",
		                        g_strdup(strerror(errno)),"\n", NULL);
		}
		else{
		OutputError=g_strconcat("Error resolving file path for:\n",
		                        file,"Reason:\nUNK ERROR\n",NULL);
		}
		gerror_warn(OutputError,
		            "file_system.c->link_resolve->realpath: c_rpath == NULL",
		            TRUE,FALSE);
		return(NULL);
	}
	else return(g_strdup(c_rpath));	
}



gint get_file_type( gchar *file){
	struct stat buf;
	if (stat(file, &buf)== -1) {
			 print(g_strconcat("ERROR  Getting Information on file:  ",file,"\n",NULL));
			return(ERR);
          }  
	else{
			if (S_ISLNK(buf.st_mode)) return(LNK);
		    else if(S_ISDIR(buf.st_mode)) return(DIR);
			else if(S_ISREG(buf.st_mode)) return(REG);
			else return(ERR);
	}
}

gchar* getcRpath(void){

	if(cRpath!=NULL) return(g_strdup(cRpath));
	else return((gchar*)NULL);
}
 gchar* check_file(gchar *afile)
{
 static gchar* file=NULL;
 static gchar* nfile=NULL;

	file= g_strdup(clean_path( g_strdup(afile)));
	
switch(get_file_type(file))
	{
	case LNK:

					nfile= link_resolve( g_strdup(file));
					if(get_file_type( g_strdup(nfile)) == REG) {
						return(g_strdup(nfile));
					}
			       else  return((gchar*) NULL);
			break;
	case DIR:
			// Holding spot for now
			cRpath=g_strdup(file);
			return((gchar*) NULL);
			break;
	case REG:
				return(g_strdup(file));
			break;
	case ERR:
						// Holding spot for now
			return((gchar*) NULL);
			break;
	default:
							// Holding spot for now
			return((gchar*) NULL);
			break;

	}
	
}

int check_magic(gchar* file) {
		#ifdef HAVE_LIBMAGIC
		int ret =0;
		char *actual_file = (char*) file;
		const char *magic_full;
		magic_t magic_cookie;
		magic_cookie = magic_open(MAGIC_MIME); 
	if (magic_cookie == NULL) {
;
	        return(2);
		    }
	if (magic_load(magic_cookie, NULL) != 0) {
	     //   printf("cannot load magic database - %s\n", magic_error(magic_cookie));
	        magic_close(magic_cookie);
	        return(3);
	    }
	magic_full = magic_file(magic_cookie, actual_file);
	char* magic_string= (char*) magic_full;

	if(tpad_magic_test(magic_string,"text") == 0) ret =1;
	else ret =0;
	return(ret);
#endif
	#ifndef HAVE_LIBMAGIC
	return(1);
#endif
}

gint tpad_magic_test (gchar file_mime_string[], gchar check_mime_string[]){
	#ifdef HAVE_LIBMAGIC
	unsigned int slen=strlen(check_mime_string);
	gchar beg_string[slen];
	strncpy ( beg_string, file_mime_string, (int)slen );
	if(strncmp(beg_string,check_mime_string,slen) == 0) return(0);
	else return(1);
#endif
#ifndef HAVE_LIBMAGIC
	return(1);
#endif
}