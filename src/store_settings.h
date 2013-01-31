/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, store_settings.h , is part of tpad.
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
#ifndef STORE_SETTINGS_H
#define STORE_SETTINGS_H
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <libconfig.h>
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
                    );
#endif