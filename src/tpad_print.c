
/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_print.c , is part of tpad.
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
#include "tpad_headers.h"

inline void print(gchar *s){
	#ifdef DEBUG_TOGGLE
	g_print("tpad(v.%s): %s\n",VERSION,s);
	#endif
}

inline void print_title(gchar* str){
	#ifdef DEBUG_TOGGLE
	gint ihHash=0, ihStr=0,ihTmp=0;
	register gint i=0;
	ihHash=(gint) ceil(HASH_PRINT_COUNT / 2);
	ihStr= (gint) ceil(str_size(str) / 2);
	ihTmp= (gint) ihHash - ihStr;
	if (ihTmp < 0) ihTmp = 0;
	for (i = 0; i < HASH_PRINT_COUNT; i++) {
		 printf("\x23");
	}
	printf("\n");
	for (i = 0; i < ihTmp; i++) {
		printf(" ");
	}
	printf("%s\n",str);
	for (i = 0; i < HASH_PRINT_COUNT; i++) {
		printf("\x23");
	}
	printf("\n");
	#endif
}