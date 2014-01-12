/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
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
#include "malloc.h"
#include "tpad_logo.h"
#include "tpad_string.h"
#include "error_warn.h"
#include "tpad_config.h"
#include "tpad_file.h"
#include "tpad_print.h"
#include "tpad_spawn.h"
#include "tpad_textstats.h"
#include "tpad_pref.h"
#include "tpad_save.h"
#include "tpad_doc.h"
#include "tpad_open_guard.h"