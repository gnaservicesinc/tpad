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
#define _FP_BUFFER_SIZE 2056



gchar path_temp_file[ _FP_BUFFER_SIZE+1];
gchar path_swp_file[ _FP_BUFFER_SIZE+1];
gchar path_lock_file[ _FP_BUFFER_SIZE+1];
gint icurrentfile_size=0;
gint itempFilePathSize=0;
gint iswpFilePathSize=0;
gint ilockFilePathSize=0;
gint ihaveTemp=0;
gchar *get_currentfile_basename(){
	gchar *file_base_name=strrchr(g_strescape(tpad_fp_get_current(),"\\\?\'\""), '/');
	return(file_base_name ? file_base_name+1 : tpad_fp_get_current());
}
gchar *get_currentfile_dirname(){
		char cdirpath[icurrentfile_size +1];
	strncpy(cdirpath,tpad_fp_get_current(),icurrentfile_size );
	cdirpath[icurrentfile_size]= '\0';
	return(g_strdup(dirname(cdirpath)));
}


void tpad_open_guard_cln () {
 icurrentfile_size=0;
 itempFilePathSize=0;
 iswpFilePathSize=0;
 ilockFilePathSize=0;
 tpad_clear_char_array(path_temp_file);
 tpad_clear_char_array(path_swp_file);
 tpad_clear_char_array(path_lock_file);	
}

void tpad_clear_char_array(char arr[]){
	memset(&arr[0], 0, sizeof(arr));
}
gint tpad_open_guard_init(){
	tpad_open_guard_cln ();
	 icurrentfile_size=strlen(tpad_fp_get_current());
	 itempFilePathSize=icurrentfile_size + 1;
	 iswpFilePathSize=icurrentfile_size + 5;
	 ilockFilePathSize=icurrentfile_size + 8;
if(iswpFilePathSize >  _FP_BUFFER_SIZE) return(-1);
else{
	strncpy(path_temp_file,(gchar*) g_strconcat(tpad_fp_get_current(),"~",NULL),sizeof(path_temp_file));		
	strncpy(path_swp_file,(gchar*) g_strconcat((gchar*)get_currentfile_dirname(),"/.",g_strdup(get_currentfile_basename()),".swp",NULL),sizeof(path_swp_file));
	strncpy(path_lock_file,(gchar*) g_strconcat((gchar*)get_currentfile_dirname(),"/.~lock.",g_strdup(get_currentfile_basename()),"#",NULL),sizeof(path_lock_file));
	return(1);
	}
}


gboolean check_file_path_read (gchar* fp){
	if(access(fp, R_OK ) != -1)return(TRUE);
	else return(FALSE);
}

void tpad_open_guard_attack(gchar* fp){
	if (!gerror_openguard_popup(tpad_fp_get_current(), fp)){
			new_thread_tpad(NULL);
			exit(1);
	} 
}
int tpad_open_guard_check_ok(){
	int ireturn=0;
	tpad_open_guard_init();
	
	if(check_file_path_read (path_temp_file)) {
		tpad_open_guard_attack(path_temp_file);
		ireturn=1;
	}
	if (check_file_path_read(path_swp_file)) {
		tpad_open_guard_attack(path_swp_file);
		ireturn=1;
	}
	if(check_file_path_read (path_lock_file)){
		tpad_open_guard_attack (path_lock_file);
		ireturn=1;
	}
		return(ireturn);
}

void tpad_open_guard_remove_temp(){
if (ihaveTemp == 1)	remove(path_temp_file);
	tpad_open_guard_cln();
}

unsigned int tpad_get_file_size(char* filepath)
{
	unsigned int lSize;
	FILE * mFile;
	mFile = fopen (filepath,"rb");
	
	if(mFile == NULL) return(0);

	   
	fseek (mFile , 0 , SEEK_END);
	lSize = (unsigned int) ftell (mFile);
	rewind (mFile);
	fclose(mFile);
	return(lSize);
}

void tpad_open_guard_make_temp(){
if(ihaveTemp == 0 && tpad_fp_get_current() && path_temp_file) {
		FILE * origFile=NULL;
		long lSize = tpad_get_file_size(tpad_fp_get_current());
		char * buffer;
		size_t result;
		origFile = fopen (tpad_fp_get_current(),"rb");

		if (origFile==NULL) exit(1);
		
		buffer = (char*) malloc (sizeof(char)*lSize);	
		if (buffer == NULL)  exit (1);
		else{
			result = fread (buffer,1,lSize,origFile);
			if (result != lSize) exit(1);
		}

		FILE *fp=NULL;
		fp=fopen(path_temp_file, "wb");
		if(fp){  
			fwrite (buffer , sizeof(char), sizeof(char)*lSize, fp);
			fclose(fp);
			ihaveTemp=1;
		}
		else exit(1);
		
		fclose(origFile);
		free (buffer);
	}
}