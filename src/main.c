/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, main.c , is part of tpad.
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
 ******************************************************************************/
////////////////////////////////////////////////////////////////////////
#include "tpad_headers.h"
//#include "tpad_string.h"
extern GtkSourceBuffer *mBuff;
extern gboolean save_locked;
extern GtkWidget *window;
//extern gchar *content;
extern gchar* origfile;
extern GtkSourceView *view;
extern gchar path_temp_file[];
extern int setModified;
extern int madetemp;
extern gboolean disable_file_watch;
extern int tpad_wach_thread_set;
extern int spell_state;
extern int run_count_update;
extern unsigned int gbid;
extern GtkSpellChecker* doc_spelling;
//extern gboolean searchCase;
//extern gboolean doCOVT;
////////////////////////////////////////////////////////////////////////
GtkWidget *window=NULL;
GtkSourceView *view=NULL;
G_LOCK_DEFINE (mBuff);
GtkSourceBuffer *mBuff;

int spell_state=2;
GtkSpinButton *xSpinButton,*ySpinButton,*uSpinButton;
unsigned int gbid=0;

//gchar *currentfile;

gchar *content;
gchar* origfile;
gboolean save_locked;
int tpad_wach_thread_set=0;

int setModified=0;
int madetemp=0;


int run_count_update=1;

gboolean disable_file_watch = FALSE;
////////////////////////////////////////////////////////////////////////
//#ifdef HAVE_LIBUNITY
//#define _DESKTOP_FILE_NAME "tpad.desktop"
//static int urgent_toggle=0;
//static UnityLauncherEntry *entry;
//#endif
////////////////////////////////////////////////////////////////////////
//int new_thread_tpad (char *file);

gpointer current_data = NULL;
////////////////////////////////////////////////////////////////////////
const static char COPPYRIGHT_NOTICE[78] = {"Copyright (C) 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>"};
const static char LICENSE_NOTICE[695] = {"Copyright (C) 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>\n\ntpad is free software: you can redistribute it and/or modify it\nunder the terms of the GNU General Public License as published by the\nFree Software Foundation, either version 3 of the License, or\n(at your option) any later version.\n\ntpad is distributed in the hope that it will be useful, but\nWITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along\nwith this program.  If not, see <http://www.gnu.org/licenses/>.\n"};
////////////////////////////////////////////////////////////////////////
/* MAIN  */ 
////////////////////////////////////////////////////////////////////////
int main(int argc,char *argv[])
{

	////////////////////////////////////////////////////////////////////////
	// Native Language Support Int
	////////////////////////////////////////////////////////////////////////
	#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
	#endif
	////////////////////////////////////////////////////////////////////////
	char* fchar = (char*) argv[1];
	set_path_self(argv[0]);
	////////////////////////////////////////////////////////////////////////
	/* GTK INIT */
	////////////////////////////////////////////////////////////////////////
	gtk_init(&argc,&argv);
 	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	/* PATH SELF SET */
	////////////////////////////////////////////////////////////////////////
	//set_path_self(g_strdup(argv[0])); 
 	////////////////////////////////////////////////////////////////////////

	
	////////////////////////////////////////////////////////////////////////
	/* CONFIG Setup */
	////////////////////////////////////////////////////////////////////////
	config_setup();
	ui_unity_init();
	
	tpad_fp_init();
	gtk_widget_show_all(GTK_WIDGET(tpad_new_ui()));	
	new_file();
    	//////////////////////////////////////////////////////////////////////// 
	// handle cl arguments
	////////////////////////////////////////////////////////////////////////
	if (argc > 2){
		int i=0;
		for (i = 2; i < argc; i += 1) new_thread_tpad ( g_strdup(argv[i]));
	}
	if(argc > 1) {
		show_file(g_strdup(fchar));
	}
	////////////////////////////////////////////////////////////////////////
	/* GTK MAIN */
	////////////////////////////////////////////////////////////////////////
    	gtk_main();
	////////////////////////////////////////////////////////////////////////
	return (0);
}