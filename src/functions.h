/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, functions.h , is part of tpad.
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
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void do_redo();
void init_spelling();
inline int runcommand(const char *strCommand);
void really_do_replace(GtkWidget *caller, GtkWidget *dialog);
void open_file();
int save_modified();
void *launch_control( void *ptr );
void show_about();
void toggle_spelling();
void do_replace(GtkWidget *caller, GtkWidget *dialog);
void init_spelling();
void show_file(gchar *newfile);
void do_find(GtkWidget *caller, GtkWidget *dialog);
void show_about();
void save_file();
void set_language();
void toggle_linenumber(GtkWidget *caller);
void select_font();
void attach_spell();
void quit_program();
void replace_dialog();
void do_find_replace(GtkWidget *caller, GtkWidget *dialog);
void detach_spell();
void new_file();
void print(gchar *s);
void do_undo();
void runn();
void toggle_show_lang(GtkWidget *caller);
void save_as();
void toggle_show_full_path();
void set_title();
char *get_currentfile_basename();
#ifdef AUTO_TAB_TOGGLE
void toggle_auto_tab(GtkWidget *caller);
#endif
void show_ui_prefs();
#endif