/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, def.h , is part of tpad.
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
////////////////////////////////////////////////////////////////////////
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#ifndef  _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef _FILE_OFFSET_BITS 
#define _FILE_OFFSET_BITS 64
#endif
#ifndef _FORTIFY_SOURCE
#define _FORTIFY_SOURCE 2
#endif
#ifndef __USE_FORTIFY_LEVEL
#define __USE_FORTIFY_LEVEL 2
#endif
////////////////////////////////////////////////////////////////////////
#ifndef  TPAD_STACKS_MAX
#define _TPAD_STACKS_MAX 9999
#endif
#ifndef UNDO_MAX
#define UNDO_MAX 3000
#endif
#ifndef THREAD_MAX 
#define THREAD_MAX 8
#endif
#ifndef _QUANTITY_OF_STACKS_DEFAULT
#define _QUANTITY_OF_STACKS_DEFAULT 100
#endif
#ifndef _INT_VAL_MAX
#define _INT_VAL_MAX 2147483647
#endif
#ifndef _DESKTOP_FILE_NAME
#define _DESKTOP_FILE_NAME "tpad.desktop"
#endif
#ifndef _FILE_IS_A_DIRECTORY
#define _FILE_IS_A_DIRECTORY 1
#endif
#ifndef  _FILE_IS_A_LINK
#define _FILE_IS_A_LINK 2
#endif
#ifndef _ERROR_FILE_GET_TYPE 
#define _ERROR_FILE_GET_TYPE 3
#endif
#ifndef _FILE_IS_A_REGRULAR_FILE
#define _FILE_IS_A_REGRULAR_FILE 4
#endif

#ifndef CONFIG_FILE_SUFFIX
#define CONFIG_FILE_SUFFIX "/.tpad.cfg"
#endif
#ifndef WIDTH_MAX
#define WIDTH_MAX 3920
#endif
#ifndef HEIGHT_MAX
#define HEIGHT_MAX 3920
#endif
#ifndef UNDOMAX
#define UNDOMAX 1000
#endif
#ifndef _DEFAULT_WINDOW_HEIGHT
#define _DEFAULT_WINDOW_HEIGHT 900
#endif
#ifndef _DEFAULT_WINDOW_WIDTH
#define _DEFAULT_WINDOW_WIDTH 800
#endif

////////////////////////////////////////
#if __STDC_VERSION__ < 199901L
	# if __GNUC__ >= 2
		#  define __func__ __FUNCTION__
     	# else
		#  define __func__ "<unknown>"
     	# endif
#endif
////////////////////////////////////////
#ifndef _FONT
#define _FONT gettext("Choose Font")
#endif
#ifndef _LINE_NUMBER
#define _LINE_NUMBER gettext("Show Line Numbers")
#endif
#ifndef _LANGUAGE
#define _LANGUAGE gettext("Show Language")
#endif
#ifndef _AUTOTAB
#define _AUTOTAB gettext("Auto Indent")
#endif
#ifndef _SPELLING
#define _SPELLING gettext("Spell Check")
#endif
#ifndef _SHOW_FULL_PATH
#define  _SHOW_FULL_PATH gettext("Show Full File Path")
#endif
#ifndef _UI_SETTINGS
#define _UI_SETTINGS gettext("Display UI Settings")
#endif
#ifndef _DEFAULT_WIDTH
#define _DEFAULT_WIDTH gettext("Default Window Width")
#endif
#ifndef _DEFAULT_HEIGHT
#define _DEFAULT_HEIGHT gettext("Default Window Height")
#endif
#ifndef _UNDO_LEVEL
#define _UNDO_LEVEL gettext("Set Maximum Undo Level (0 For Unlimited) :")
#endif
#ifndef _FIND_FIND_AND_REPLACE
#define _FIND_FIND_AND_REPLACE gettext("Find / Find & Replace Text")
#endif
#ifndef _SEARCH
#define _SEARCH_FOR gettext("Search Text For:")
#endif
#ifndef _ERROR_POPUP_TITLE
#define _ERROR_POPUP_TITLE gettext("Error!")
#endif
#ifndef _REPLACE_WITH
#define _REPLACE_WITH gettext("Replace Text With:")
#endif
#ifndef _FIND
#define _FIND gettext("Find")
#endif

#ifndef _REPLACE
#define _REPLACE gettext("Replace")
#endif
#ifndef _SAVE_CHANGES
#define _SAVE_CHANGES gettext("Text was modified!\nSave it?")
#endif
#ifndef _FIND_AND_REPLACE
#define _FIND_AND_REPLACE gettext("Find & Replace")
#endif
#ifndef _SPELL_LANG
#define _SPELL_LANG gettext("en_US")
#endif
#ifndef _KEEP_WIND_ABOVE
#define _KEEP_WIND_ABOVE gettext("Keep Window Above")
#endif
#ifndef _LINE_WP
#define _LINE_WP gettext("Wrap Lines")
#endif
#ifndef _CHECK_ON_OPEN
#define _CHECK_ON_OPEN gettext("Use Temp and  Check For (lock/tmp/swp)")
#endif
#ifndef _ABT_COMMENT
#define _ABT_COMMENT gettext("That simple, fast, and user friendly text editor you love.")
#endif
#ifndef _TRANSLATOR_CREDITS
#define _TRANSLATOR_CREDITS gettext("translator-credits")
#endif
#ifndef _CAN_NOT_READ_FILE
#define _CAN_NOT_READ_FILE gettext("Reading file failed!")
#endif
#ifndef _CONVERT_FAILED
#define _CONVERT_FAILED gettext("Conversion to UTF-8 FAILED! Is this a text document?")
#endif
#ifndef _FAILED_SAVE_FILE
#define _FAILED_SAVE_FILE gettext("WARNING: Saving File Failed! Unable to write to file: ")
#endif
#ifndef _SAVE_FILE
#define _SAVE_FILE gettext("Save File")
#endif
#ifndef _NEW_THREAD_FAILED
#define _NEW_THREAD_FAILED gettext("Thread could not be created")
#endif
#ifndef _WORD_COUNT
#define _WORD_COUNT gettext("Word Count")
#endif
#ifndef _WORD_COUNT_HEADING
#define _WORD_COUNT_HEADING gettext("Word Count:")
#endif
#ifndef _CHAR_COUNT_HEADING
#define _CHAR_COUNT_HEADING gettext("Char Count:")
#endif
#ifndef _LINE_COUNT_HEADING
#define _LINE_COUNT_HEADING gettext("Line Count:")
#endif
#ifndef _REVERSE_ALL_TEXT
#define _REVERSE_ALL_TEXT gettext("Reverse")
#endif
#ifndef _MAKE_UPPERCASE
#define _MAKE_UPPERCASE gettext("To upper case ")
#endif
#ifndef _BAD_CFG_REPLACE_FAIL
#define _BAD_CFG_REPLACE_FAIL gettext("Config file is invalid.\nFailed to remove bad config file.\nPlease manually remove it.")
#endif
#ifndef _CFG_FILE_INVALID
#define _CFG_FILE_INVALID gettext("Config file is invalid.")
#endif
#ifndef _REMOVED_INVALID_CFG_FILE
#define _REMOVED_INVALID_CFG_FILE gettext("Successfully removed bad config file.\nA new config file will be created.\nPress ok and tpad will restart...")
#endif
#ifndef _ERROR_SETTING_SETTING
#define _ERROR_SETTING_SETTING gettext("Error settings value out of range, change dropped.\nThe change will not be saved.\n However, you REALLY should save your work and exit tpad right now. Please report bug")
#endif
#ifndef _ERROR_TOO_SMALL
#define _ERROR_TOO_SMALL gettext("Error! The default window size must have a height of 50 or more and a width of 25 or more.")
#endif
#ifndef _QUANTITY_OF_STACKS_HEADING
#define _QUANTITY_OF_STACKS_HEADING gettext("Quantity of Stacks:")
#endif
#ifndef _MAKE_LOWERCASE
#define _MAKE_LOWERCASE gettext("To lower case")
#endif
#ifndef _FILE_MAY_BE_ALREADY_OPEN
#define _FILE_MAY_BE_ALREADY_OPEN gettext("File may alread be open in tpad or another program!")
#endif
#ifndef _FILE_MAY_BE_ALREADY_OPEN_DETAIL
#define _FILE_MAY_BE_ALREADY_OPEN_DETAIL gettext("Do you still want to open the file?\n------------------------------------\n\nDescription - File has a swap or temp file.\nPossible Causes --\n\n\t*File might be in-use already.\n\t*tpad or another program crashed or exited improperly while using this file.\n\t*other unknown reasons\n\nDetails --\n\nFile path:%s\n\nPath to tmp or swp file:%s\n")
#endif
#ifndef _ERROR_MOD_DOC_METHOD_VAL
#define _ERROR_MOD_DOC_METHOD_VAL gettext("Error invalid method. An error has occurred! Please save you work and exit tpad. Please report a bug!") 
#endif
#ifndef _ERROR_MAGIC_BAD
#define _ERROR_MAGIC_BAD gettext("File Is Not  A Text File -- BAD MAGIC")
#endif
#ifndef _ERROR_MAGIC_INIT
#define _ERROR_MAGIC_INIT gettext("Oh-No! I was unable to initialize magic the magic library\nSkipping magic!")
#endif
#ifndef _ERROR_MAGIC_DB
#define _ERROR_MAGIC_DB gettext("Uh-oh! I can not load the magic database\nSkipping!")
#endif

////////////////////////////////////////
