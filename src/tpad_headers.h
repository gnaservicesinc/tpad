/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013, 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_headers.c , is part of tpad.
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
#include "def.h"
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "include.h"
#ifndef _EXT_CONTENT_DEC_
#define _EXT_CONTENT_DEC_
extern gchar *content;
#endif


#include "malloc.h"
#include "tpad_logo.h"
#include "main.h"
#include "tpad_string.h"
#include "error_warn.h"
#include "tpad_config.h"
#include "tpad_buff.h"
#include "tpad_file.h"
#include "tpad_new_file.h"
#include "tpad_open_file.h"
#include "tpad_unity.h"
#include "tpad_show_file.h"
#include "tpad_quit.h"
#include "tpad_find.h"
#include "tpad_about.h"
#include "tpad_find_and_replace.h"
#include "tpad_magic.h"
#include "tpad_font.h"
#include "tpad_print.h"
#include "tpad_ui.h"
#include "tpad_title.h"
#include "tpad_find.h"
#include "tpad_spawn.h"
#include "tpad_textstats.h"
#include "tpad_pref.h"
#include "tpad_toggle.h"
#include "tpad_save.h"
#include "tpad_spelling.h"
#include "tpad_history.h"
#include "tpad_hconnect.h"
#include "tpad_doc.h"
#include "tpad_open_guard.h"
#include "tpad_fp.h"
#include "tpad_hash.h"
#include "tpad_tree.h"
#include "tpad_watch.h"
#include "tpad_modbal.h"
#include "tpad_lang.h"
#include "polarssl/check_config.h"
#include "polarssl/config.h"
#include "polarssl/md5.h"
#include "polarssl/platform.h"
#include "polarssl/sha256.h"
#include "polarssl/sha512.h"
#include "polarssl/base64.h"
#include "polarssl/threading.h"
#include "polarssl/timing.h"
#include "polarssl/version.h"