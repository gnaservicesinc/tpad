/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, user_settings.h , is part of tpad.
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
#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <libconfig.h>
#include <unistd.h>
#include "store_settings.h"

typedef struct {
  config_t cfg;
  config_setting_t *root;
  config_setting_t *setting;
  config_setting_t *group;
  config_setting_t *UI;
  int show_line_numbers;
  int show_lang;
  int show_spelling_errors;
  int defualt_window_width;
  int default_window_height;
  int undo_level;
  int show_full_path;
  #ifdef AUTO_TAB_TOGGLE
  int auto_tab;
  #endif
  int gave_up;
} cfgSet;

cfgSet userCfg;
#ifdef AUTO_TAB_TOGGLE
void cfg_set_auto_tab(int opt);
int cfg_auto_tab();
int cfg_get_default_auto_tab(char *cfg_file);
#endif
void config_setup(char *cfg_file);
int cfg_file_test(const char *fname);
void cfg_read_in(char *cfg_file);
void cfg_set_default_width(int opt);
void cfg_set_default_height(int opt);
void cfg_set_show_lang(int opt);
void cfg_set_undo(int opt);
void cfg_set_show_spelling(int opt);
void cfg_set_show_line(int opt);
void cfg_set_show_full_path(int opt);
int cfg_line();
int cfg_show_full_path();
int cfg_spell();
int cfg_wWidth();
int cfg_wHeight();
int cfg_undo();
int cfg_gaveUp();
int cfg_lang();
int cfg_get_def_undo_level(char *cfg_file);
int cfg_get_show_line_numbers(char *cfg_file);
int cfg_get_check_spellcheck(char *cfg_file);
int cfg_get_default_window_width(char *cfg_file);
int cfg_get_default_window_height(char *cfg_file);
int cfg_get_default_show_lang(char *cfg_file);
int cfg_get_show_full_path(char *cfg_file);
int cfg_write();
void cfg_on_exit();
#endif