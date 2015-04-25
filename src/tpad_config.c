/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013, 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_config.c , is part of tpad.
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
//////////////////////////////////////////////////////////////////////////
/***********************************DEC**********************************/
//////////////////////////////////////////////////////////////////////////

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static cfgSet userCfg;
static char* ccfile;
//////////////////////////////////////////////////////////////////////////
void cfg_read_in();
void set_conf_defaults();
void clean_userCfg();
inline int is_userCfg_valid();
inline void print_userCfg(char *fun);
void config_file();
int write_out();
void reset_config ();
void read_in();
void cfg_check(char CallingFunction[]);
void *do_write_out();
//////////////////////////////////////////////////////////////////////////
/***********************************PUB**********************************/
//////////////////////////////////////////////////////////////////////////
void cfg_on_exit(){
}
int cfg_show_full_path(){
	cfg_check((gchar*)__func__);
	return(userCfg.show_full_path);
}
int cfg_lang(){
	cfg_check((gchar*)__func__);
	return(userCfg.show_lang);
}
int cfg_line(){
	cfg_check((gchar*)__func__);
	return(userCfg.show_line_numbers);
}
char *cfg_id(){
	cfg_check((gchar*)__func__);
	char* cuid_string = (char*) calloc( 1024, sizeof( char ) );
	if (cuid_string == NULL) exit(1);

	uuid_unparse(userCfg.configID,cuid_string); 
	return(cuid_string);
}
int cfg_spell(){
	cfg_check((gchar*)__func__);
	return(userCfg.show_spelling_errors);
}
int cfg_sWidth(){
	cfg_check((gchar*)__func__);
	return(userCfg.screenWidth);
	//return(cfg_wWidth()); //Place Holder. 
}
int cfg_sHeight(){
	cfg_check((gchar*)__func__);
	return(userCfg.screenHeight);
	//return(cfg_wHeight()); //Place Holder. 
}
int cfg_wWidth(){
	cfg_check((gchar*)__func__);
	return(userCfg.defualt_window_width);
}
int cfg_wHeight(){
	cfg_check((gchar*)__func__);
	return(userCfg.default_window_height);
}
int cfg_undo(){
	cfg_check((gchar*)__func__);
	return(userCfg.undo_level);
}
int cfg_line_wrap(){
	cfg_check((gchar*)__func__);
	return(userCfg.line_wrap);
}
int cfg_use_stacks(){
	cfg_check((gchar*)__func__);
	return(userCfg.useStacks);
}
int cfg_stack_quantity(){
	cfg_check((gchar*)__func__);
	return(userCfg.StacksTotalQuantity);
}
int cfg_use_open_guard (){
	cfg_check((gchar*)__func__);
	return(userCfg.useOpenGuard);
}
#ifdef AUTO_TAB_TOGGLE
int cfg_auto_tab(){
	cfg_check((gchar*)__func__);
	return(userCfg.auto_tab);
}
#endif
///////////////////////////////////////////////////////
void cfg_set_show_line(int opt){
	if(opt >= 0 && opt <=1) userCfg.show_line_numbers=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_show_lang(int opt){
	if(opt >= 0 && opt <=1) userCfg.show_lang=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_show_full_path(int opt){
	if(opt >= 0 && opt <=1) userCfg.show_full_path=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_show_spelling(int opt){
	if(opt >= 0 && opt <=1) userCfg.show_spelling_errors=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_screen_width(int opt){
	#ifdef DEBUG_TOGGLE
	g_print("\nSet Screen Width\t=\t%i\n",opt);
	#endif
	if(opt > 0) userCfg.screenWidth=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_screen_height(int opt){
	#ifdef DEBUG_TOGGLE
	g_print("\nSet Screen Height\t=\t%i\n",opt);
	#endif
	if(opt > 0) userCfg.screenHeight=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_default_width(int opt){
	if(opt >= 25) userCfg.defualt_window_width=opt;
	else gerror_warn(_ERROR_TOO_SMALL,(gchar*)__func__,0,0);
}
void cfg_set_default_height(int opt){
	if(opt >= 50 || opt > _INT_VAL_MAX) userCfg.default_window_height=opt;
	else gerror_warn(_ERROR_TOO_SMALL,(gchar*)__func__,0,0);
}
void cfg_set_undo(int opt){
	if(opt >= 0 || opt > _INT_VAL_MAX) userCfg.undo_level=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_show_line_wrap(int opt){
	if(opt >= 0 && opt <=1) userCfg.line_wrap=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_use_stacks(int opt){
	if(opt >= 0 && opt <=1) userCfg.useStacks=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_stack_quantity(int opt){
	if(opt >= 0 && opt < _INT_VAL_MAX) userCfg.StacksTotalQuantity=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
}
void cfg_set_use_open_guard (int opt){
	if(opt >= 0 && opt <= 1) userCfg.useOpenGuard=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,(gchar*)__func__,0,0);
	
}
#ifdef AUTO_TAB_TOGGLE
void cfg_set_auto_tab(int opt){
	if(opt >= 0 && opt <=1) userCfg.auto_tab=opt;
	else gerror_warn(_ERROR_SETTING_SETTING,"cfg_set_auto_tab",0,0);
}
#endif
//////////////////////////////////////////////////////////////////////////

void config_setup(){
	config_file();
	set_conf_defaults();
	if(access(ccfile, R_OK|W_OK ) != -1) cfg_read_in();
	else cfg_save();
}
//////////////////////////////////////////////////////////////////////////
void cfg_save(){
	cfg_check((gchar*)__func__);
	write_out();
}

//////////////////////////////////////////////////////////////////////////
/***********************************PRI**********************************/
//////////////////////////////////////////////////////////////////////////
void cfg_check(char CallingFunction[]){
	if (!is_userCfg_valid()){
		print_userCfg((gchar*)&CallingFunction);
		clean_userCfg();
	}
}

void cfg_read_in(){
	read_in();
	cfg_check((gchar*)__func__);

}
//////////////////////////////////////////////////////////////////////////
void set_conf_defaults(){
	userCfg.show_line_numbers=1;
	userCfg.useOpenGuard=0;
	userCfg.show_lang=0;
	userCfg.show_spelling_errors=0;
	userCfg.defualt_window_width=_DEFAULT_WINDOW_WIDTH;
	userCfg.default_window_height=_DEFAULT_WINDOW_HEIGHT;
	userCfg.undo_level=0;
	userCfg.line_wrap=1;
	userCfg.show_full_path=1;
	userCfg.screenWidth=0;
	userCfg.screenHeight=0;
	uuid_generate(userCfg.configID);
	#ifdef AUTO_TAB_TOGGLE
	userCfg.auto_tab=0;
	userCfg.useStacks=TRUE;
	userCfg.StacksTotalQuantity=_QUANTITY_OF_STACKS_DEFAULT;
	#endif
}
//////////////////////////////////////////////////////////////////////////
inline void print_userCfg(char *fun){
	#ifdef DEBUG_TOGGLE
	print_title("WARNING - ERROR!");
	printf("\nINCLUDE THE FOLLOWING IN YOUR BUG REPORT:\n");
	print_title("BEGIN DEBUGGING INFO");
	printf("TPAD VERSION NUMBER:\t%s\n",VERSION);
	printf("PATH TO CONFIG FILE:\t%s\n",ccfile);
	printf("OUTOF RANGE / INVALID DATA IN: cfgSet userCfg\n");
	printf("IN FUNCTION:\t%s\n",fun);
	printf("%s =\t%i\n","userCfg.show_line_numbers",userCfg.show_line_numbers);
	printf("%s =\t%i\n","userCfg.show_lang",userCfg.show_lang);
	printf("%s =\t%i\n","userCfg.show_spelling_errors",userCfg.show_spelling_errors);
	printf("%s =\t%i\n","userCfg.defualt_window_width",userCfg.defualt_window_width);
	printf("%s =\t%i\n","userCfg.default_window_height",userCfg.default_window_height);
	printf("%s =\t%i\n","userCfg.undo_level",userCfg.undo_level);
	printf("%s =\t%i\n","userCfg.line_wrap",userCfg.line_wrap);
	printf("%s =\t%i\n","userCfg.show_full_path",userCfg.show_full_path);
	printf("%s =\t%i\n","userCfg.useStacks",userCfg.useStacks);
	printf("%s =\t%i\n","userCfg.StacksTotalQuantity",userCfg.StacksTotalQuantity);
	printf("%s =\t%i\n","	userCfg.useOpenGuardy",userCfg.useOpenGuard);
	#ifdef AUTO_TAB_TOGGLE
	printf("%s =\t%i\n","userCfg.auto_tab",userCfg.auto_tab);
	#endif
	print_title("END DEBUGGING INFO");	
	#endif
}
//////////////////////////////////////////////////////////////////////////
int is_userCfg_valid(){
        	if(userCfg.show_line_numbers < 0 || userCfg.show_line_numbers > 1) goto caseBad;
		if(userCfg.show_lang < 0 || userCfg.show_lang > 1) goto caseBad;
		if(userCfg.show_spelling_errors < 0 || userCfg.show_spelling_errors > 1) goto caseBad;
		if(userCfg.defualt_window_width < 10 || userCfg.defualt_window_width > WIDTH_MAX) goto caseBad;
		if(userCfg.default_window_height < 10 || userCfg.default_window_height > HEIGHT_MAX) goto caseBad;
		if(userCfg.undo_level < 0 || userCfg.undo_level > UNDOMAX) goto caseBad;
		if(userCfg.line_wrap < 0 || userCfg.line_wrap > 1) goto caseBad;
		if(userCfg.show_full_path < 0 || userCfg.show_full_path > 1) goto caseBad;
//	if(userCfg.useStacks < 0 && userCfg.useStacks > 1) goto caseBad;
		if(userCfg.useOpenGuard < 0 || userCfg.useOpenGuard > 1) goto caseBad;
		
		if(userCfg.StacksTotalQuantity < 0 || userCfg.StacksTotalQuantity > _INT_VAL_MAX) goto caseBad;
		#ifdef AUTO_TAB_TOGGLE
		if(userCfg.auto_tab < 0 || userCfg.auto_tab > 1) goto caseBad;
		#endif
		return(TRUE);
	caseBad:
		return(FALSE);
}
//////////////////////////////////////////////////////////////////////////
// Fix userCFG by replacing invalid values with default ones while
// preserving valid values (By range). 
//////////////////////////////////////////////////////////////////////////

void clean_userCfg(){
        if(userCfg.show_line_numbers < 0 || userCfg.show_line_numbers > 1) userCfg.show_line_numbers=1;
		if(userCfg.show_lang < 0 || userCfg.show_lang > 1) userCfg.show_lang=0;
		if(userCfg.show_spelling_errors < 0 || userCfg.show_spelling_errors > 1) userCfg.show_spelling_errors=0;
		if(userCfg.screenWidth > 0 ){
			if(userCfg.defualt_window_width > userCfg.screenWidth) userCfg.defualt_window_width=userCfg.screenWidth;
		}
		else{
			if(userCfg.defualt_window_width < 10 || userCfg.defualt_window_width > WIDTH_MAX) userCfg.defualt_window_width=_DEFAULT_WINDOW_WIDTH;
		}
		if (userCfg.screenHeight > 0 ){
			if(userCfg.default_window_height > userCfg.screenHeight) userCfg.default_window_height=userCfg.screenHeight;
		}
		else{
			if(userCfg.default_window_height < 10 || userCfg.default_window_height > HEIGHT_MAX) userCfg.default_window_height=_DEFAULT_WINDOW_HEIGHT;
		}
		
		if(userCfg.StacksTotalQuantity < 0 || userCfg.StacksTotalQuantity >= _INT_VAL_MAX) userCfg.StacksTotalQuantity=_QUANTITY_OF_STACKS_DEFAULT;
		if(userCfg.useStacks < 0 && userCfg.useStacks > 1) userCfg.useStacks=1;
		if(userCfg.undo_level < 0 || userCfg.undo_level > UNDOMAX) userCfg.undo_level=0;
		if(userCfg.line_wrap < 0 || userCfg.line_wrap > 1) userCfg.line_wrap=1;
		if(userCfg.useOpenGuard< 0 || 	userCfg.useOpenGuard > 1) 	userCfg.useOpenGuard=0;
		if(userCfg.show_full_path < 0 || userCfg.show_full_path > 1) userCfg.show_full_path=1;
		#ifdef AUTO_TAB_TOGGLE
		if(userCfg.auto_tab < 0 || userCfg.auto_tab > 1) userCfg.auto_tab=0;
		#endif
}
//////////////////////////////////////////////////////////////////////////
void config_file(){
	struct passwd *pw = getpwuid(syscall(__NR_getuid));
	ccfile = g_strconcat((gchar *)pw->pw_dir,(gchar *)CONFIG_FILE_SUFFIX,NULL);
}
//////////////////////////////////////////////////////////////////////////
int write_out(){
	int rc;
	pthread_t thread;
	if( (rc=pthread_create( &thread, NULL, do_write_out, NULL)) ){
    	return(1);
	}
	else {
	 pthread_join( thread, NULL);
	 return(0);
	}
}
//////////////////////////////////////////////////////////////////////////
void reset_config (){
	 if (remove(ccfile) != 0 ){
		gerror_warn(_BAD_CFG_REPLACE_FAIL,ccfile,1,1); 
	 }
	 else gerror_warn(_CFG_FILE_INVALID,_REMOVED_INVALID_CFG_FILE,1,1);
		 
}
//////////////////////////////////////////////////////////////////////////
void read_in()
{
	FILE *ptr_cfg;
	ptr_cfg=fopen(ccfile,"rb");
	if (!ptr_cfg) {
		reset_config ();
	}
	else {
		//Success opening, read data into the struct 
		fseek(ptr_cfg, sizeof(cfgSet), SEEK_END);
		rewind(ptr_cfg);
		size_t result;
		long lSize =1;
		result=fread(&userCfg,sizeof(cfgSet),1,ptr_cfg);
		if (result != lSize){
			reset_config ();
		}
		fclose(ptr_cfg);
	}
}
//////////////////////////////////////////////////////////////////////////	
void *do_write_out()
{
	FILE *ptr_cfg;
	pthread_mutex_lock( &mutex );
	
	ptr_cfg=fopen(ccfile,"wb");
	
	if(!ptr_cfg) reset_config ();
	else {
		fwrite(&userCfg, sizeof(cfgSet),1,ptr_cfg);
		fclose(ptr_cfg);
		}
	pthread_mutex_unlock( &mutex );
	return(0);
}

//////////////////////////////////////////////////////////////////////////
