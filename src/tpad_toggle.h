/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_hconnect.h , is part of tpad.
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

#ifndef TPAD_TOGGLE_H
#define  TPAD_TOGGLE_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "tpad_headers.h"
void toggle_line_wrap(GtkWidget *caller);
void toggle_linenumber(GtkWidget *caller);
void toggle_use_open_guard(GtkWidget *caller);
void toggle_show_full_path();
void toggle_keep_above(GtkWidget *caller);
#ifdef AUTO_TAB_TOGGLE
void toggle_auto_tab(GtkWidget *caller);
#endif
void toggle_covt (GtkWidget *caller);
void toggle_case_sarch (GtkWidget *caller);
#endif