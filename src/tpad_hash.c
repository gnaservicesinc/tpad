/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_hash.c , is part of tpad.
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
#define _Space_ 32



char *file2sha512(){
	char* file = tpad_hash_get_file();
	if(file == NULL) return("--\n");	

	if(strlen(file) <=2) return("--\n");	

		

	unsigned char* ichr = (unsigned char*)calloc(64,sizeof(unsigned char));
	if(ichr == NULL) exit(1);
	
	sha512_file(file,ichr,0);

    	return (data_to_hex(ichr));

}
char *file2sha256(){
	char* file = tpad_hash_get_file();
	if(file == NULL) return("--\n");	

	if(strlen(file) <=2) return("--\n");	

	if(access(file, R_OK|W_OK ) == -1) return("--\n");	

	unsigned char* ichr = (unsigned char*)calloc(32,sizeof(unsigned char));
	if(ichr == NULL) exit(1);
	
	sha256_file(file,ichr,0);

    	return (data_to_hex(ichr));

}

char *file2md5(){
	char* file = tpad_hash_get_file();
	if(file == NULL) return("--\n");	

	if(strlen(file) <=2) return("--\n");	

	if(access(file, R_OK|W_OK ) == -1) return("--\n");	

	unsigned char* ichr = (unsigned char*)calloc(16,sizeof(unsigned char));
	if(ichr == NULL) exit(1);
	
	md5_file(file,ichr);

    	return (data_to_hex(ichr));

}

char *str2sha512(const char *str) {
	if(str == NULL) return("--\n");	

	if(strlen(str) <=1) return("--\n");	
	int n = 0;
	unsigned char* ichr = (unsigned char*)calloc(64,sizeof(unsigned char));
	if(ichr == NULL) exit(1);
	
	
	sha512(str,strlen(str),ichr,0);

    	return (data_to_hex(ichr));
}
char *str2sha256(const char *str) {
		if(str == NULL) return("--\n");	
	if(strlen(str) <=1) return("--\n");
	
	int n = 0;
	unsigned char* ichr = (unsigned char*)calloc(32,sizeof(unsigned char));
	if(ichr == NULL) exit(1);
	
	

	sha256(str,strlen(str),ichr,0);

    	return (data_to_hex(ichr));
}
char *str2md5(const char *str) {
		if(str == NULL) return("--\n");	

	if(strlen(str) <=1) return("--\n");	
	int n = 0;
	unsigned char* ichr = (unsigned char*)calloc(16,sizeof(unsigned char));
	if(ichr == NULL) exit(1);
	
	if(strlen(str) <=1) return("--'\0'\n");

	md5(str,strlen(str),ichr);

    	return (data_to_hex(ichr));
}

char* tpad_hash_read_in_file(char* fp){

 if(access(fp, R_OK ) == -1) return("--\n"); 

  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;

  pFile = fopen ( fp , "rb" );
  if (pFile==NULL) return("--\n");

  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  buffer = (char*) calloc (lSize+1,sizeof(char));
  if (buffer == NULL) return("--\n");

  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) return("--\n");

  fclose (pFile);
  return (buffer);
}
char *strFrombase64(const char *str) {
	if(str == NULL) return("--\n");	

	if(strlen(str) <=1) return("--\n");
	
	size_t ssize = strlen(str) + 1;	
	size_t dlen=0;
	int ret = 0;
	ret=base64_decode(NULL,&dlen,str,ssize-1);

	char* ichr = (char*) calloc(dlen + 1,sizeof(char));

	if(ichr == NULL) exit(1);
	
	ret = base64_decode(ichr,&dlen,str,ssize-1);
	//If Invalid Char for base 64 detected, encode instead. 
	if(ret == POLARSSL_ERR_BASE64_INVALID_CHARACTER){
		return(str2base64(str));
	}

	if(ret == 0) return (ichr);
	else return("--\n");
}
char *str2base64(const char *str) {
	if(str == NULL) return("--\n");	

	if(strlen(str) <=1) return("--\n");
	
	size_t ssize = strlen(str) + 1;
		
	int n = 0;
	size_t dlen=0;
 	base64_encode(NULL,&dlen,str,ssize);

	char* ichr = (char*)calloc(dlen+1,sizeof(char));
	if(ichr == NULL) exit(1);
	
	int ret = base64_encode(ichr,&dlen,str,ssize);

    	//return (data_to_hex(ichr));
	if(ret == 0) return (ichr);
	else return("--\n");
}
char* tpad_hash_get_file(){
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("File hash to clipboard",GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Hash File",
                                         GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),FALSE);
	if(tpad_fp_get_current()){
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), (gchar*)get_currentfile_basename());
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER(dialog),(const gchar *)tpad_fp_get_current());
	}
		char *ptrStr=NULL;

	
	//if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_CANCEL) {
//		return(NULL);
//	}

	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_ACCEPT:
		ptrStr = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			int oLen=0;
	if(ptrStr == NULL) return("'\0'");
	oLen=strlen(ptrStr);
	oLen++;
	char* out= (char*) calloc(oLen,sizeof(char));
	if(out == NULL) exit(1);
	memcpy(out,ptrStr,oLen);
		gtk_widget_destroy(GTK_WIDGET(dialog));
		return(out);
	break;

	case GTK_RESPONSE_CANCEL:
		gtk_widget_destroy(GTK_WIDGET(dialog));
		ptrStr = NULL;
		return("-\n");
	default:
		gtk_widget_destroy(GTK_WIDGET(dialog));
		ptrStr = NULL;
		return("-\n");
	break;
	}
    
}
char *data_to_hex(unsigned char* data){

	if(data == NULL) return("--\n");	

	size_t strLen =strlen(data);
	size_t data_len = 0;
	if( strLen < sizeof(data) / sizeof(data[0]) ){
		data_len=sizeof(data) / sizeof(data[0]) +1;
	}
	else data_len=strLen+1;



	int n = 0;
	char* out = (char*) calloc(data_len * 3,sizeof(char));

	if(out == NULL) exit(1);

	for (n = 0; n < data_len; ++n) {
        if (( unsigned int) data[n] > 0 && ( unsigned int) data[n] <= 255 )snprintf(&(out[n*2]), data_len * 2, "%02x", (unsigned int)data[n]);
    }

    return (out);
}
char* tpad_hash_choose_file_and_get_contents(){
	return(tpad_hash_read_in_file(tpad_hash_get_file()));
}


char *file2base64(){
 return( (char *) str2base64((char *)tpad_hash_choose_file_and_get_contents()) );
}
char *filefrombase64(){
 return( (char *) strFrombase64((char *) tpad_hash_choose_file_and_get_contents()) );
}