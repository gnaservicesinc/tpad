/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, error_warn.h , is part of tpad.
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
#ifndef ERROR_WARN_H
#define ERROR_WARN_H
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <syslog.h>
#include <unistd.h>
#include <libintl.h>
#include <glib/gi18n.h>
#define _ERROR_INFO gettext("Error Deatils:")
#define _ERROR_OCCURED gettext("An error has occured: %s")
#define _ERROR_MSG gettext("An error has occured and the program may abort.\nAny unsaved work may be lost.\nIf you belive that a bug in tpad is the root cause report a bug at\nhttps://bugs.launchpad.net/tpad-project \nThe following message may help you determine the cause\n\n%s\n")
void gerror_log(gchar *c_msg);
void gerror_popup(gchar *c_msg);
void gerror_warn(gchar *c_msg, gchar *extra_information, gboolean slog, gboolean abort);
gint gerror_openguard_popup(gchar *c_fileName, gchar * foundFilePath);
#endif