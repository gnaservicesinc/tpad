/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013, 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_config.h , is part of tpad.
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
/ ********************************************************************************/

#ifndef TPAD_CONFIG_H
#define  TPAD_CONFIG_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <libintl.h>
#include <wchar.h>
#include <pthread.h>
#include <math.h>
#include <glib/gi18n.h>
#include <uuid/uuid.h>

typedef struct {
  int show_line_numbers;
  int show_lang;
  int line_wrap;
  int show_spelling_errors;
  int defualt_window_width;
  int default_window_height;
  int undo_level;
  int show_full_path;
  #ifdef AUTO_TAB_TOGGLE
  int auto_tab;
  #endif
  int screenWidth;
  int screenHeight;
  int useStacks;
  int StacksTotalQuantity;
  int useOpenGuard;
  uuid_t configID;
} cfgSet;

#ifdef AUTO_TAB_TOGGLE
void cfg_set_auto_tab(int opt);
int cfg_auto_tab();
int cfg_get_default_auto_tab(char *cfg_file);
#endif

void config_setup();
void cfg_save();
void cfg_set_use_open_guard(int opt);
void cfg_set_screen_width(int opt);
void cfg_set_screen_height(int opt);
void cfg_set_default_width(int opt);
void cfg_set_default_height(int opt);
void cfg_set_show_lang(int opt);
void cfg_set_undo(int opt);
void cfg_set_show_spelling(int opt);
void cfg_set_show_line(int opt);
void cfg_set_show_full_path(int opt);
void cfg_set_show_line_wrap(int opt);
void cfg_set_use_stacks(int opt);
void cfg_set_stack_quantity(int opt);

int cfg_line();
int cfg_line_wrap();
int cfg_show_full_path();
int cfg_spell();
int cfg_sWidth();
int cfg_sHeight();
int cfg_wWidth();
char *cfg_id();
int cfg_wHeight();
int cfg_undo();
int cfg_gaveUp();
int cfg_use_open_guard();
int cfg_lang();
int cfg_use_stacks();
int cfg_stack_quantity();

#endif
