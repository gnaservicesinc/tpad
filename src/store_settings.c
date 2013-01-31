/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, store_settings.c , is part of tpad.
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
#include "store_settings.h"
 int store_settings(char *cfg_file,
                    int show_line_numbers,
                    int show_lang,
                    int show_spelling_errors,
                    int defualt_window_width,
                    int default_window_height,
                    int undo_level,
                    int show_full_path
                    #ifdef AUTO_TAB_TOGGLE
                    ,
                    int auto_tab
                    #endif
                    ){
	config_t cfg;
	config_setting_t *root, *setting, *group, *UI;
	config_init(&cfg);
	int ret=0;
	root = config_root_setting(&cfg);
	group = config_setting_add(root,"User_Pref", CONFIG_TYPE_GROUP);
	
	setting = config_setting_add(group,"LineNumbers", CONFIG_TYPE_INT);
	config_setting_set_int(setting, show_line_numbers);
	
	setting = config_setting_add(group,"Spelling", CONFIG_TYPE_INT);
	config_setting_set_int(setting, show_spelling_errors);

	setting = config_setting_add(group,"ShowLang", CONFIG_TYPE_INT);
	config_setting_set_int(setting, show_lang);
	#ifdef AUTO_TAB_TOGGLE 
	setting = config_setting_add(group,"Auto_Tab", CONFIG_TYPE_INT);
	config_setting_set_int(setting, auto_tab);
	#endif
	setting = config_setting_add(group,"Show_Full_Path", CONFIG_TYPE_INT);
	config_setting_set_int(setting, show_full_path);
	 
	UI = config_setting_add(root,"User_Interface_Settings", CONFIG_TYPE_GROUP);

	setting = config_setting_add(UI,"Default_Window_Width", CONFIG_TYPE_INT);
	config_setting_set_int(setting, defualt_window_width);

	setting = config_setting_add(UI,"Default_Window_Height", CONFIG_TYPE_INT);
	config_setting_set_int(setting, default_window_height);
	 
	setting = config_setting_add(UI,"Undo_Level", CONFIG_TYPE_INT);
	config_setting_set_int(setting, undo_level);
	 

	 
	if (! config_write_file(&cfg,(char*)cfg_file)) ret=0;
	else ret=1;
	config_destroy(&cfg);
	return(ret);
 }