/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, user_settings.c , is part of tpad.
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
#include "user_settings.h"

void cfg_on_exit(){
	config_destroy(&userCfg.cfg);
}

int cfg_show_full_path(){
	return(userCfg.show_full_path);
}
int cfg_lang(){
return(userCfg.show_lang);
}
int cfg_line(){
return(userCfg.show_line_numbers);
}
int cfg_spell(){
return(userCfg.show_spelling_errors);
}
int cfg_wWidth(){
return(userCfg.defualt_window_width);
}
int cfg_wHeight(){
return(userCfg.default_window_height);
}
int cfg_undo(){
return(userCfg.undo_level);
}
int cfg_gaveUp(){
return(userCfg.gave_up);
}
#ifdef AUTO_TAB_TOGGLE
int cfg_auto_tab(){
return(userCfg.auto_tab);
}
#endif
void cfg_set_show_line(int opt){
userCfg.show_line_numbers=opt;
}
void cfg_set_show_lang(int opt){
	userCfg.show_lang=opt;
}
void cfg_set_show_full_path(int opt){
	userCfg.show_full_path=opt;
}
void cfg_set_show_spelling(int opt){
userCfg.show_spelling_errors=opt;
}
void cfg_set_default_width(int opt){
userCfg.defualt_window_width=opt;
}
void cfg_set_default_height(int opt){
userCfg.default_window_height=opt;
}
void cfg_set_undo(int opt){
userCfg.undo_level=opt;
}
#ifdef AUTO_TAB_TOGGLE
void cfg_set_auto_tab(int opt){
userCfg.auto_tab=opt;
}
#endif
void config_setup(char *cfg_file){
	config_init(&userCfg.cfg);
	userCfg.root = config_root_setting(&userCfg.cfg);
	userCfg.show_line_numbers=1;
	userCfg.show_lang=0;
	userCfg.show_spelling_errors=0;
	userCfg.defualt_window_width=800;
	userCfg.default_window_height=900;
	userCfg.undo_level=0;
	userCfg.show_full_path=1;
	#ifdef AUTO_TAB_TOGGLE
	userCfg.auto_tab=0;
	#endif
	userCfg.gave_up=0;

	if(access(cfg_file, R_OK|W_OK ) != -1) cfg_read_in(cfg_file);
	else userCfg.gave_up=store_settings(cfg_file,
	                                    userCfg.show_line_numbers,
	                                    userCfg.show_lang,	                               
	                                    userCfg.show_spelling_errors,
	                                    userCfg.defualt_window_width,
	                                    userCfg.default_window_height,
	                                    userCfg.undo_level,
	                                    userCfg.show_full_path
	                                    #ifdef AUTO_TAB_TOGGLE
	                                    ,
	                                    userCfg.auto_tab
										#endif
	                                    );
										
}



void cfg_read_in(char *cfg_file){
	userCfg.show_line_numbers=cfg_get_show_line_numbers(cfg_file);	
	userCfg.show_spelling_errors=cfg_get_check_spellcheck(cfg_file);
	userCfg.show_lang=cfg_get_default_show_lang(cfg_file);
	userCfg.defualt_window_width=cfg_get_default_window_width(cfg_file);
	userCfg.default_window_height=cfg_get_default_window_height(cfg_file);	
	userCfg.undo_level=cfg_get_def_undo_level(cfg_file);
	userCfg.show_full_path=cfg_get_show_full_path(cfg_file);
	#ifdef AUTO_TAB_TOGGLE
	userCfg.auto_tab=cfg_get_default_auto_tab(cfg_file);
	#endif
}


int cfg_get_def_undo_level(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return(0);
	else {
		int DefaultUndo;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Interface_Settings");
		config_setting_lookup_int(userCfg.setting,"Undo_Level", &DefaultUndo);
		return DefaultUndo;
	}
}

int cfg_get_default_window_width(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return(800);	
	else {
		int DefaultWindowWidth;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Interface_Settings");
		config_setting_lookup_int(userCfg.setting,"Default_Window_Width", &DefaultWindowWidth);
		return DefaultWindowWidth;
	}
}

int cfg_get_default_window_height(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return(900);
	else {
		int DefaultWindowHeight;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Interface_Settings");
		config_setting_lookup_int(userCfg.setting,"Default_Window_Height", &DefaultWindowHeight);
	return DefaultWindowHeight;
	}
}

int cfg_get_check_spellcheck(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return (0);	
	else {
		int CheckSpelling;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Pref");
		config_setting_lookup_int(userCfg.setting,"Spelling", &CheckSpelling);
	return CheckSpelling;
	}
}

int cfg_get_show_line_numbers(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return (1);
	else {
		int ShowLineNumbers;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Pref");
		config_setting_lookup_int(userCfg.setting,"LineNumbers", &ShowLineNumbers);
	return ShowLineNumbers;
	}
}

int cfg_get_default_show_lang(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return(0);
	else {
		int DefaultShowLang;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Pref");
		config_setting_lookup_int(userCfg.setting,"ShowLang", &DefaultShowLang);
	return DefaultShowLang;
	}
}
int cfg_get_show_full_path(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return(1);
	else {
		int ShowFullPath;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Pref");
		config_setting_lookup_int(userCfg.setting,"Show_Full_Path", &ShowFullPath);
		return ShowFullPath;
	}
}
#ifdef AUTO_TAB_TOGGLE
int cfg_get_default_auto_tab(char *cfg_file){
	if(!config_read_file(&userCfg.cfg, (char*)cfg_file )) return(0);
	else {
		int DefaultAutoTab;	
		userCfg.setting = config_lookup(&userCfg.cfg,"User_Pref");
		config_setting_lookup_int(userCfg.setting,"Auto_Tab", &DefaultAutoTab);
		return DefaultAutoTab;
	}
}
#endif