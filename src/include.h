/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, include.h , is part of tpad.
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
#ifndef INCLUDE_H
#define INCLUDE_H
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#define _FORTIFY_SOURCE 2
#define UNDO_MAX 3000
#define _FONT gettext("Choose Font")
#define _LINE_NUMBER gettext("Show Line Numbers")
#define _LANGUAGE gettext("Show Language")
#define _AUTOTAB gettext("Auto Indent")
#define _SPELLING gettext("Spell Check")
#define _SHOW_FULL_PATH gettext("Show Full File Path")
#define _UI_SETTINGS gettext("Display UI Settings")
#define _DEFAULT_WIDTH gettext("Default Window Width")
#define _DEFAULT_HEIGHT gettext("Default Window Height")
#define _UNDO_LEVEL gettext("Set Maximum Undo Level (0 For Unlimited) :")
#define _FIND_FIND_AND_REPLACE gettext("Find / Find & Replace Text")
#define _SEARCH_FOR gettext("Search Text For:")
#define _REPLACE_WITH gettext("Replace Text With:")
#define _FIND gettext("Find")
#define _REPLACE gettext("Replace")
#define _FIND_AND_REPLACE gettext("Find & Replace")
#define _SPELL_LANG gettext("en_US")
#define _ABT_COMMENT gettext("That simple, fast, and user friendly text editor you love.")
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gtkspell/gtkspell.h>
#include <gdk/gdkkeysyms.h>
#include <gtksourceview/gtksourcemark.h>
#include <gtksourceview/gtksourceview.h>
#include <gtksourceview/gtksourcebuffer.h>
#include <gtksourceview/gtksourcelanguage.h>
#include <gtksourceview/gtksourcelanguagemanager.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <libconfig.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <libintl.h>
#include <glib/gi18n.h>
#include "static.h"
#include "functions.h"
#include "user_settings.h"
#include "store_settings.h"
#include "tpad_logo.h"
#endif