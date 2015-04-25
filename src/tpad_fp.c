/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_string.c , is part of tpad.
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
#include "tpad_fp.h"

extern char* tpad_fp;
extern int tpad_fp_state;
void tpad_fp_calloc(size_t init_size);
void tpad_fp_recalloc(size_t new_size);

size_t cur = 0L;
	char* tpad_fp=NULL;
	int tpad_fp_state=_TPAD_FP_STATE_UNITIALIZED;


void tpad_fp_calloc(size_t init_size){
	if(tpad_fp_state==_TPAD_FP_STATE_UNITIALIZED){
	tpad_fp = (char*) calloc (init_size,sizeof(char));
	if (tpad_fp == NULL) {
		perror("malloc tpad_fp");
		free(tpad_fp);
		tpad_fp=NULL;
		exit(1);
		
	}
	cur=init_size;
	clear_char_array(tpad_fp,NULL);
	tpad_fp_state = _TPAD_FP_STATE_INITIALIZED;
	}
	else if (tpad_fp_state !=_TPAD_FP_STATE_FREE) tpad_fp_recalloc(init_size);
}
void tpad_fp_recalloc(size_t new_size){
	if (new_size > cur){
	size_t nsize;
	nsize=(new_size * sizeof(char));
	char *ptr_tpad_fp = (char*) realloc ( (void*)tpad_fp,nsize);
	
	if(ptr_tpad_fp != NULL){
	  tpad_fp=ptr_tpad_fp;
	}
	else {
		perror("realloc - ptr_tpad_fp");
		free (ptr_tpad_fp);
		free(tpad_fp);
		exit(1);
	}
	cur=nsize;
	}

	if (tpad_fp_state !=_TPAD_FP_STATE_FREE) clear_char_array(tpad_fp,NULL);

}
void tpad_fp_cleanup(){
	if (tpad_fp_state !=_TPAD_FP_STATE_FREE) clear_char_array(tpad_fp,NULL);
	if (tpad_fp_state == _TPAD_FP_STATE_INITIALIZED || tpad_fp_state == _TPAD_FP_STATE_SET){
 	free(tpad_fp);
	tpad_fp_state=_TPAD_FP_STATE_FREE;
}
	
}
char* tpad_fp_get_current(){
	if (_TPAD_FP_STATE_SET) return(g_strdup(tpad_fp));
	else return(NULL);
}
void tpad_fp_init(){
	
	tpad_fp_calloc( (size_t) _TPAD_FP_INIT_MEMSIZE);
	
}
void tpad_fp_set(char* fp){
	size_t nsize;
	size_t osize;
	char* lfp = (char*) fp;
	int fp_len = strlen(lfp);
	//if ( tpad_fp_state == _TPAD_FP_STATE_UNITIALIZED) tpad_fp_init();

	nsize= (size_t) ( (fp_len + 1) * sizeof(char) );

	tpad_fp_calloc(nsize);
	strcpy (tpad_fp,lfp);
	tpad_fp_state=_TPAD_FP_STATE_SET;

}