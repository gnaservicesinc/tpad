/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, static.h , is part of tpad.
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
#ifndef STATIC_H
#define STATIC_H
static GtkWidget *window;
static GtkSourceView *view;
static GtkSourceBuffer *mBuff;
static GtkSpinButton *xSpinButton,*ySpinButton,*uSpinButton;
static GtkSpellChecker* doc_spelling;
static int spell_state=2;
static GtkWidget *findentry,*replaceentry;
static gchar *currentfile;
static GtkTextIter match_start,match_end;
static char *self_loc;
char *nFile[100000];
char *cfg_file[10000];
#endif