/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
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
extern gchar *currentfile;
extern gboolean save_locked;
extern GtkWidget *window;
extern gchar *content;
extern gchar* origfile;
extern gchar path_temp_file[];
extern int setModified;
extern int madetemp;
////////////////////////////////////////////////////////////////////////
GtkWidget *window;
GtkSourceView *view;
G_LOCK_DEFINE (mBuff);

GtkSourceBuffer *mBuff;

GtkSpinButton *xSpinButton,*ySpinButton,*uSpinButton;
GtkSpellChecker* doc_spelling;
int spell_state=2;
GtkWidget *findentry,*replaceentry;
gchar *currentfile;
GtkTextIter match_start,match_end;
gchar *content;
gchar* origfile;
gboolean save_locked;
gchar *unknownContents;
int setModified=0;
int madetemp=0;
GdkDisplay* Display;
int sdone=0;
int run_count_update=1;
gboolean searchCase=FALSE;
gboolean doCOVT=FALSE;
////////////////////////////////////////////////////////////////////////
//#ifdef HAVE_LIBUNITY
//#define _DESKTOP_FILE_NAME "tpad.desktop"
//static int urgent_toggle=0;
//static UnityLauncherEntry *entry;
//#endif
////////////////////////////////////////////////////////////////////////
int new_thread_tpad (char *file);
void do_redo();
void init_spelling();
void set_buffer();
void submit_buff( );
void really_do_replace(GtkWidget *caller, GtkWidget *dialog);
void open_file();
void *launch_control( void *ptr );
void show_about();
void toggle_spelling();
void do_replace();
void init_spelling();
void show_file(gchar *nfile);
void do_find(GtkWidget *caller, GtkWidget *dialog);
void show_about();
void set_language();
void toggle_linenumber(GtkWidget *caller);
void select_font();
void attach_spell();
void quit_program();
void replace_dialog();
void detach_spell();
void new_file();
void do_undo();
void runn();
void toggle_use_open_guard(GtkWidget *caller);
void toggle_show_lang(GtkWidget *caller);
void toggle_show_full_path();
void set_title();
void toggle_line_wrap(GtkWidget *caller);
gchar *get_currentfile_basename();
void toggle_keep_above(GtkWidget *caller);
#ifdef AUTO_TAB_TOGGLE
void toggle_auto_tab(GtkWidget *caller);
#endif
void show_ui_prefs();
void toggle_covt (GtkWidget *caller);
gboolean is_separator (gchar cChar);
gpointer current_data = NULL;
void ui_unity_init();
int ui_unity_urgent_on ();
int ui_unity_urgent_off ();
void ui_unity_destroy ();
////////////////////////////////////////////////////////////////////////
const static char COPPYRIGHT_NOTICE[78] = {"Copyright (C) 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>"};
const static char LICENSE_NOTICE[695] = {"Copyright (C) 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>\n\ntpad is free software: you can redistribute it and/or modify it\nunder the terms of the GNU General Public License as published by the\nFree Software Foundation, either version 3 of the License, or\n(at your option) any later version.\n\ntpad is distributed in the hope that it will be useful, but\nWITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along\nwith this program.  If not, see <http://www.gnu.org/licenses/>.\n"};
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
	set_path_self(g_strdup(argv[0]));
	currentfile=NULL;
	////////////////////////////////////////////////////////////////////////
	/* GTK INIT */
	////////////////////////////////////////////////////////////////////////
	gtk_init(&argc,&argv);
  	////////////////////////////////////////////////////////////////////////
	/* CONFIG Setup */
	////////////////////////////////////////////////////////////////////////
	config_setup();
	ui_unity_init();
	////////////////////////////////////////////////////////////////////////
	/* Declare some var for use in the main window for menus, tool bar, etc. */
	////////////////////////////////////////////////////////////////////////
	GtkAccelGroup *accel_group;
    	GtkWidget *menubar,*file,*filemenu,*newfile,*open,*save,*saveas,*quit,*checkOnOpen,
	*search,*searchmenu,*find,*replace,*redo,*undo,*reverse, *capsup,*capsdown, *settings,*spelling,
	*settingsmenu,*selectfont,*linenumber,*help,*helpmenu,*about,*toolbar,*DocStats,
	*scrolled_window,*mainbox,*lang_chk,*ShowFullPath,*lineWp,*keepAbove,*UIPrefs
		#ifdef AUTO_TAB_TOGGLE
		,*AutoTab
		#endif
		;
	GtkToolItem *toolnew,*toolopen,*toolsave,*toolsaveas,*toolredo,*toolundo,*toolquit;
	gint idisplayNumber=0,mwidth=0,mheight=0;
	////////////////////////////////////////////////////////////////////////
	// Get information on the display for use with config. 
	////////////////////////////////////////////////////////////////////////
	Display=gdk_display_manager_get_default_display (gdk_display_manager_get());
	idisplayNumber = gdk_display_get_n_screens (Display);
	int i=0;
	for (i=0;i < idisplayNumber; i++){
		GdkScreen* Screen;
		Screen=gdk_display_get_screen(Display,i);
		mwidth+=gdk_screen_get_width(Screen);
		mheight+=gdk_screen_get_height(Screen);
	}
	cfg_set_screen_width(mwidth);
	cfg_set_screen_height(mheight); 
	////////////////////////////////////////////////////////////////////////
	// Main Window Setup
	////////////////////////////////////////////////////////////////////////
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Tpad");
	gtk_window_set_default_size(GTK_WINDOW(window),cfg_wWidth(),cfg_wHeight());
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(window),gdk_pixbuf_new_from_inline (-1, tpad_inline, FALSE, NULL));
	mainbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
 	////////////////////////////////////////////////////////////////////////
	// Menu bar setup 
	////////////////////////////////////////////////////////////////////////
	menubar = gtk_menu_bar_new();
 	////////////////////////////////////////////////////////////////////////
	//Setup file menu
 	////////////////////////////////////////////////////////////////////////
    	filemenu = gtk_menu_new();

	file = gtk_menu_item_new_with_mnemonic("_File");
    	newfile = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
    	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
    	save = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
    	saveas = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS,NULL);
    	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,NULL);
   	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), newfile);
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveas);
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), gtk_separator_menu_item_new() );
    	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	////////////////////////////////////////////////////////////////////////
	//Setup search menu
 	////////////////////////////////////////////////////////////////////////
	searchmenu=gtk_menu_new();

    	search = gtk_menu_item_new_with_mnemonic("_Edit");
    	find = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND,NULL);
    	replace = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND_AND_REPLACE,NULL);   
    	undo = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO,NULL);
    	redo = gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO,NULL);
		reverse= gtk_menu_item_new_with_label((const gchar*)_REVERSE_ALL_TEXT);
		capsup=gtk_menu_item_new_with_label((const gchar*)_MAKE_UPPERCASE);
		capsdown=gtk_menu_item_new_with_label((const gchar*)_MAKE_LOWERCASE);
	
    	gtk_menu_item_set_submenu(GTK_MENU_ITEM(search), searchmenu);
    	gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), find);
    	gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), replace);
    	gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), gtk_separator_menu_item_new() );
    	gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), undo);
    	gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), redo);
    	gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), gtk_separator_menu_item_new() );
		gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), reverse);
		gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), capsup);
		gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), capsdown);
	////////////////////////////////////////////////////////////////////////
	//Setup settings menu
	////////////////////////////////////////////////////////////////////////
	settingsmenu=gtk_menu_new();
	
	settings = gtk_menu_item_new_with_mnemonic("_Settings");
    	selectfont = gtk_image_menu_item_new_from_stock(GTK_STOCK_SELECT_FONT,NULL);
    	linenumber = gtk_check_menu_item_new_with_label (_LINE_NUMBER);
	lang_chk = gtk_check_menu_item_new_with_label (_LANGUAGE);
	#ifdef AUTO_TAB_TOGGLE
	AutoTab = gtk_check_menu_item_new_with_label (_AUTOTAB);
	#endif
	spelling= gtk_check_menu_item_new_with_label(_SPELLING);
	ShowFullPath = gtk_check_menu_item_new_with_label(_SHOW_FULL_PATH);
	UIPrefs = gtk_image_menu_item_new_from_stock(GTK_STOCK_PREFERENCES,NULL);
	DocStats =gtk_menu_item_new_with_label((const gchar*)_WORD_COUNT);
	keepAbove = gtk_check_menu_item_new_with_label(_KEEP_WIND_ABOVE);
	lineWp = gtk_check_menu_item_new_with_label(_LINE_WP);
	checkOnOpen=gtk_check_menu_item_new_with_label(_CHECK_ON_OPEN);
	// Set items active state in settings menu to match config state
	////////////////////////////////////////////////////////////////////////
	(cfg_line_wrap()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(lineWp),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(lineWp),FALSE);
	(cfg_show_full_path()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ShowFullPath),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ShowFullPath),FALSE);
	(cfg_line()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(linenumber),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(linenumber),FALSE);
	(cfg_spell()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(spelling),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(spelling),FALSE);
	(cfg_lang()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(lang_chk),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(lang_chk),FALSE);       
	(cfg_use_open_guard ()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(checkOnOpen),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(checkOnOpen),FALSE);       
	#ifdef AUTO_TAB_TOGGLE
	(cfg_auto_tab()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(AutoTab),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(AutoTab),FALSE);
	#endif
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(settings), settingsmenu);
	#ifdef AUTO_TAB_TOGGLE
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), AutoTab);
	#endif
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), lineWp);
    	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), linenumber);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), spelling);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), lang_chk);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), ShowFullPath);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), keepAbove); 
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), selectfont);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), UIPrefs);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), DocStats);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), checkOnOpen);
	
	////////////////////////////////////////////////////////////////////////
	//Set up help menu
	////////////////////////////////////////////////////////////////////////
	helpmenu=gtk_menu_new();

    	help = gtk_menu_item_new_with_mnemonic("_Help");
    	about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT,NULL);
   	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
   	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);

	////////////////////////////////////////////////////////////////////////
	//Setup some accels 
 	////////////////////////////////////////////////////////////////////////
	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
	
	gtk_widget_add_accelerator(newfile, "activate", accel_group,
                               GDK_KEY_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(open, "activate", accel_group,
                               GDK_KEY_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(save, "activate", accel_group,
                               GDK_KEY_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(quit, "activate", accel_group,
                               GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(find, "activate", accel_group,
                               GDK_KEY_f, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(replace, "activate", accel_group,
                               GDK_KEY_h, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(undo, "activate", accel_group,
                               GDK_KEY_z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(reverse, "activate", accel_group,
                               GDK_KEY_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    	gtk_widget_add_accelerator(capsup, "activate", accel_group,
                               GDK_KEY_u, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	    	gtk_widget_add_accelerator(capsdown, "activate", accel_group,
                               GDK_KEY_l, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(redo, "activate", accel_group,
	                           GDK_KEY_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	#ifdef AUTO_TAB_TOGGLE
	gtk_widget_add_accelerator(AutoTab, "activate", accel_group,
                               GDK_KEY_F7, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	#endif
	gtk_widget_add_accelerator(lineWp, "activate", accel_group,
                               GDK_KEY_F6, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(linenumber, "activate", accel_group,
                               GDK_KEY_F5, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(lang_chk, "activate", accel_group,
                               GDK_KEY_F4, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(spelling, "activate", accel_group,
                               GDK_KEY_F3, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(ShowFullPath, "activate", accel_group,
                               GDK_KEY_F2, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_add_accelerator(keepAbove, "activate", accel_group,
                               GDK_KEY_F1, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);	
	////////////////////////////////////////////////////////////////////////
	// Put all of these menus into the main menu menu bar 
	////////////////////////////////////////////////////////////////////////
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), search);
    	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), settings);
    	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

	gtk_box_pack_start(GTK_BOX(mainbox), menubar, FALSE, FALSE, 0);
	////////////////////////////////////////////////////////////////////////
	// Set up toolbar
	////////////////////////////////////////////////////////////////////////
	toolbar = gtk_toolbar_new();
    	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);

    	toolquit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolquit),0);

	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(gtk_separator_tool_item_new ()),0);

	//toolspelling  = gtk_tool_button_new_from_stock(GTK_STOCK_SPELL_CHECK);
	//gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolspelling),0);
		
   	// gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(gtk_separator_tool_item_new ()),0);
	
	toolredo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);	
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolredo),0);
	
   	 toolundo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolundo),0);
	
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(gtk_separator_tool_item_new ()),0);
	
    	toolsaveas = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE_AS);
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolsaveas),0);

    	toolsave = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolsave),0);

    	toolopen = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolopen),0);

    	toolnew = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolnew),0);
	////////////////////////////////////////////////////////////////////////
	// Add the tool bar to the box main box
	////////////////////////////////////////////////////////////////////////
    	gtk_box_pack_start(GTK_BOX(mainbox), toolbar, FALSE, FALSE, 0);
	////////////////////////////////////////////////////////////////////////
	// Set up GTKSourceView with a buffer
	////////////////////////////////////////////////////////////////////////
	mBuff=gtk_source_buffer_new(NULL);
	
	view=(GtkSourceView *)gtk_source_view_new_with_buffer(mBuff);
    	(cfg_line()) ? gtk_source_view_set_show_line_numbers (view,TRUE) : gtk_source_view_set_show_line_numbers (view,FALSE) ;
    	gtk_widget_modify_font(GTK_WIDGET(view), pango_font_description_from_string("DejaVu Sans Mono 12"));

	gtk_source_view_set_smart_home_end(GTK_SOURCE_VIEW(view),GTK_SOURCE_SMART_HOME_END_BEFORE);
	////////////////////////////////////////////////////////////////////////
	// If the setting for spell checking is enabled, setup spell checking
	////////////////////////////////////////////////////////////////////////
		if(cfg_spell()) {
		doc_spelling = gtk_spell_checker_new ();
		gtk_spell_checker_set_language (doc_spelling, _SPELL_LANG, NULL);
		gtk_spell_checker_attach (doc_spelling,GTK_TEXT_VIEW (view));
		spell_state=1;
		cfg_set_show_spelling(1);
	}
	////////////////////////////////////////////////////////////////////////
	// Put our source view into a scrolled window and added it to box mainbox
	////////////////////////////////////////////////////////////////////////
	scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    	gtk_container_add(GTK_CONTAINER(scrolled_window),GTK_WIDGET(view));
    	gtk_box_pack_start(GTK_BOX(mainbox),GTK_WIDGET(scrolled_window),TRUE,TRUE,0);
	////////////////////////////////////////////////////////////////////////
	// Add box mainbox to main window, window 
	gtk_container_add(GTK_CONTAINER(window),mainbox);
	////////////////////////////////////////////////////////////////////////
	// Connect signals from above to callbacks 
	g_signal_connect(window,"delete_event",G_CALLBACK(quit_program),NULL);
    g_signal_connect(newfile,"activate",G_CALLBACK(runn),NULL);
    g_signal_connect(open,"activate",G_CALLBACK(open_file),NULL);
    g_signal_connect(save,"activate",G_CALLBACK(save_file),NULL);
    g_signal_connect(saveas,"activate",G_CALLBACK(save_as),NULL);
    g_signal_connect(quit,"activate",G_CALLBACK(quit_program),NULL);
	g_signal_connect(find,"activate",G_CALLBACK(replace_dialog),NULL);
    g_signal_connect(replace,"activate",G_CALLBACK(replace_dialog),NULL);
    g_signal_connect(undo,"activate",G_CALLBACK(do_undo),NULL);
	g_signal_connect(redo,"activate",G_CALLBACK(do_redo),NULL);
	g_signal_connect(capsup,"activate",G_CALLBACK(up_caps_document),NULL);
	g_signal_connect(capsdown,"activate",G_CALLBACK(low_caps_document),NULL);
    g_signal_connect(reverse,"activate",G_CALLBACK(rev_document),NULL);
	g_signal_connect(lineWp,"activate",G_CALLBACK(toggle_line_wrap),NULL);
	g_signal_connect(selectfont,"activate",G_CALLBACK(select_font),NULL);
    g_signal_connect(linenumber,"activate",G_CALLBACK(toggle_linenumber),NULL);
	g_signal_connect(spelling,"activate",G_CALLBACK(toggle_spelling),NULL);
	g_signal_connect(ShowFullPath,"activate",G_CALLBACK(toggle_show_full_path),NULL);	
	#ifdef AUTO_TAB_TOGGLE
	g_signal_connect(AutoTab,"activate",G_CALLBACK(toggle_auto_tab),NULL);
	#endif
	g_signal_connect(lang_chk,"activate",G_CALLBACK(toggle_show_lang),NULL);
	g_signal_connect(keepAbove,"activate",G_CALLBACK(toggle_keep_above),NULL);
	g_signal_connect(about,"activate",G_CALLBACK(show_about),NULL);
	g_signal_connect(UIPrefs,"activate",G_CALLBACK(show_ui_prefs),NULL);
	g_signal_connect(DocStats,"activate",G_CALLBACK(get_text_stats),NULL);
	g_signal_connect(checkOnOpen,"activate",G_CALLBACK(toggle_use_open_guard),NULL);
	

    	g_signal_connect(toolnew,"clicked",G_CALLBACK(runn),NULL);
    	g_signal_connect(toolopen,"clicked",G_CALLBACK(open_file),NULL);
    	g_signal_connect(toolsave,"clicked",G_CALLBACK(save_file),NULL);
    	g_signal_connect(toolsaveas,"clicked",G_CALLBACK(save_as),NULL);
    	g_signal_connect(toolundo,"clicked",G_CALLBACK(do_undo),NULL);
    	g_signal_connect(toolredo,"clicked",G_CALLBACK(do_redo),NULL);
	
	//g_signal_connect(toolspelling,"clicked",G_CALLBACK(toggle_spelling),NULL);
	g_signal_connect(toolquit,"clicked",G_CALLBACK(quit_program),NULL);
	////////////////////////////////////////////////////////////////////////
	/* GTK WIDGET SHOW ALL */
	////////////////////////////////////////////////////////////////////////
	gtk_widget_show_all(GTK_WIDGET(window));
	new_file();
    	//////////////////////////////////////////////////////////////////////// 
	// handle cl arguments
	////////////////////////////////////////////////////////////////////////
	if (argc > 2){
		int i=0;
		for (i = 2; i < argc; i += 1) new_thread_tpad ( g_strdup(argv[i]));
	}
	if(argc > 1) {
		show_file(g_strdup(argv[1]));
	}
	////////////////////////////////////////////////////////////////////////
	/* GTK MAIN */
	////////////////////////////////////////////////////////////////////////
    	gtk_main();
	////////////////////////////////////////////////////////////////////////
	return (0);
}


void show_about(){
    GtkWidget *dialog;
    dialog=gtk_about_dialog_new();
    gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG(dialog),(const gchar *)"Tpad");
    gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(dialog),(const gchar *)VERSION);
    gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG(dialog),(const gchar *)_ABT_COMMENT);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),(const gchar *)"Copyright 2012, 2013, 2014 © Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>");
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),(const gchar *)"https://gnaservicesinc.com");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog),(const gchar *)"GNA Homepage");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog),gdk_pixbuf_new_from_inline (-1, tpad_inline, FALSE, NULL));
	gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(dialog), _TRANSLATOR_CREDITS);
	gtk_window_set_position(GTK_WINDOW(GTK_ABOUT_DIALOG(dialog)),GTK_WIN_POS_CENTER);
    gtk_dialog_run(GTK_DIALOG(GTK_ABOUT_DIALOG(dialog)));
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

void do_find(GtkWidget *caller, GtkWidget *dialog){
    const gchar *findwhat;
	if(doCOVT)findwhat=g_strcompress(gtk_entry_get_text(GTK_ENTRY(findentry)));
	else findwhat=gtk_entry_get_text(GTK_ENTRY(findentry));
	
    GtkTextIter iter;
			GtkTextIter start,end;
			gtk_text_buffer_get_bounds( GTK_TEXT_BUFFER(mBuff),&start,&end);
	if(searchCase){
    if( gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff)) ) gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(mBuff), &iter, gtk_text_buffer_get_selection_bound (GTK_TEXT_BUFFER(mBuff)) );
    else gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(mBuff), &iter, gtk_text_buffer_get_insert (GTK_TEXT_BUFFER(mBuff)) );

    if (gtk_text_iter_forward_search (&iter, findwhat, GTK_TEXT_SEARCH_TEXT_ONLY, &match_start, &match_end, NULL)) {
        gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(view),&match_end,0.0,FALSE,.5,.1);
        gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
    }
    else{	
		
        GtkTextIter insert = iter;
        gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(mBuff), &iter);
        if (gtk_text_iter_forward_search (&iter, findwhat, GTK_TEXT_SEARCH_TEXT_ONLY, &match_start, &match_end, &insert))
        {
            gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(view),&match_end,0.0,FALSE,.5,.1);
            gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
        }
			sdone++;
		
    }
  }
else{
    if( gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff)) ) gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(mBuff), &iter, gtk_text_buffer_get_selection_bound (GTK_TEXT_BUFFER(mBuff)) );
    else gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(mBuff), &iter, gtk_text_buffer_get_insert (GTK_TEXT_BUFFER(mBuff)) );

    if (gtk_text_iter_forward_search (&iter, findwhat, GTK_TEXT_SEARCH_CASE_INSENSITIVE, &match_start, &match_end, NULL)) {
        gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(view),&match_end,0.0,FALSE,.5,.1);
        gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
    }
    else{
        GtkTextIter insert = iter;
        gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(mBuff), &iter);
        if (gtk_text_iter_forward_search (&iter, findwhat,GTK_TEXT_SEARCH_CASE_INSENSITIVE, &match_start, &match_end, &insert))
        {
            gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(view),&match_end,0.0,FALSE,.5,.1);
            gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
        }
			sdone++;
		
    }
  }

}

void toggle_covt (GtkWidget *caller){
doCOVT=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller));
}

void toggle_case_sarch (GtkWidget *caller){
 searchCase=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller));
}

void do_replace(GtkWidget *caller, GtkWidget *dialog){	
	do_find(caller,dialog);
	if(gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff))){
        gtk_text_buffer_delete (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
		if(doCOVT)gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &match_start, g_strcompress(gtk_entry_get_text(GTK_ENTRY(replaceentry))), -1);
		else gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &match_start,gtk_entry_get_text(GTK_ENTRY(replaceentry)), -1);		
	}
		
}


void do_find_replace(GtkWidget *caller, GtkWidget *dialog){
	sdone=0;
	gtk_text_buffer_begin_user_action(GTK_TEXT_BUFFER(mBuff));
	do_find(caller,dialog);
	while(gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff))){
		if(sdone >= 2) break;	
        gtk_text_buffer_delete (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
		if(doCOVT)gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &match_start, g_strcompress(gtk_entry_get_text(GTK_ENTRY(replaceentry))), -1);
		else gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &match_start, gtk_entry_get_text(GTK_ENTRY(replaceentry)), -1);
		do_find(caller,dialog);
	}
	gtk_text_buffer_end_user_action (GTK_TEXT_BUFFER(mBuff));
}
void replace_dialog(){
	sdone=0;
    GtkWidget *dialog;
    GtkWidget *mainbox,*boxbutton,*findbox,*replacebox,*vseparator[3];
    GtkWidget *buttonfind,*buttonreplace,*buttonfindreplace;
	GtkWidget *checkbutton, *convtbutton;
	GtkClipboard *S_Clip;
    dialog=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	vseparator[0]=gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	vseparator[1]=gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	vseparator[2]=gtk_separator_new(GTK_ORIENTATION_VERTICAL);
    gtk_window_set_title(GTK_WINDOW(dialog),_FIND_FIND_AND_REPLACE);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(dialog),FALSE);

    g_signal_connect(dialog,"destroy",G_CALLBACK(gtk_widget_destroy),NULL);

    mainbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    findbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    replacebox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    boxbutton=gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);

    gtk_container_add(GTK_CONTAINER(dialog),mainbox);
    gtk_container_add(GTK_CONTAINER(mainbox),findbox);
    gtk_container_add(GTK_CONTAINER(mainbox),replacebox);
    gtk_container_add(GTK_CONTAINER(mainbox),boxbutton);

    gtk_box_pack_start (GTK_BOX (findbox),
                        GTK_WIDGET (gtk_label_new(_SEARCH_FOR)), TRUE, TRUE, 1);
	
	S_Clip=gtk_clipboard_get(GDK_SELECTION_PRIMARY);
	gchar *recived;
	recived=NULL;
	recived=gtk_clipboard_wait_for_text(GTK_CLIPBOARD(S_Clip));
	findentry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(findentry),65536);
	gtk_entry_set_input_purpose (GTK_ENTRY(findentry),GTK_INPUT_PURPOSE_FREE_FORM);
	if(recived) gtk_entry_set_text(GTK_ENTRY(findentry),g_strescape(recived,"\?\\\'\""));

	gtk_box_pack_start (GTK_BOX (findbox),
                        GTK_WIDGET (findentry), TRUE, TRUE, 1);	
	gtk_box_pack_start (GTK_BOX (findbox),
	                    GTK_WIDGET(vseparator[0]),TRUE,TRUE,1);
	
    gtk_box_pack_start (GTK_BOX (replacebox),
                        GTK_WIDGET (gtk_label_new(_REPLACE_WITH)), TRUE, TRUE, 1);

    replaceentry = gtk_entry_new();	
    gtk_entry_set_max_length(GTK_ENTRY(replaceentry),65536);
	gtk_entry_set_input_purpose (GTK_ENTRY(replaceentry),GTK_INPUT_PURPOSE_FREE_FORM);
    gtk_box_pack_start (GTK_BOX (replacebox),
                        GTK_WIDGET (replaceentry), TRUE, TRUE, 1);
	gtk_box_pack_start (GTK_BOX (replacebox),
	                    GTK_WIDGET(vseparator[1]),TRUE,TRUE,1);
	
    buttonfind=gtk_button_new_with_label(_FIND);
    gtk_box_pack_start (GTK_BOX (boxbutton),
                        GTK_WIDGET (buttonfind), TRUE, TRUE, 1);

    buttonreplace=gtk_button_new_with_label(_REPLACE);
    gtk_box_pack_start (GTK_BOX (boxbutton),
                        GTK_WIDGET (buttonreplace), TRUE, TRUE, 1);
	
	gtk_box_pack_start (GTK_BOX (boxbutton),
	                    GTK_WIDGET(vseparator[2]),TRUE,TRUE,1);
                    
    buttonfindreplace=gtk_button_new_with_label(_FIND_AND_REPLACE);
    gtk_box_pack_start (GTK_BOX (boxbutton),
                        GTK_WIDGET (buttonfindreplace), TRUE, TRUE, 1);

	checkbutton = gtk_check_button_new_with_label((const gchar*)"Match case"); 
		    gtk_box_pack_start (GTK_BOX (boxbutton),
                        GTK_WIDGET (checkbutton), TRUE, TRUE, 1);

	convtbutton = gtk_check_button_new_with_label((const gchar*)"COVT"); 
	 gtk_box_pack_start (GTK_BOX (boxbutton),
                        GTK_WIDGET (convtbutton), TRUE, TRUE, 1);
	doCOVT=TRUE;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(convtbutton),doCOVT);
	g_signal_connect(convtbutton, "clicked",G_CALLBACK(toggle_covt),NULL );
	g_signal_connect(checkbutton, "clicked",G_CALLBACK(toggle_case_sarch),NULL );


    g_signal_connect(buttonfind,"clicked",G_CALLBACK(do_find), GTK_WINDOW(dialog));
    g_signal_connect(buttonreplace,"clicked",G_CALLBACK(do_replace),GTK_WINDOW(dialog));
    g_signal_connect(buttonfindreplace,"clicked",G_CALLBACK(do_find_replace),GTK_WINDOW(dialog));
    g_signal_connect(dialog,"destroy",G_CALLBACK(gtk_widget_destroy),NULL);
	
    gtk_widget_show_all(dialog);
}
///////////////////////////////////////////////////////////////////////////
void runn(){
	new_thread_tpad(NULL);
}
////////////////////////////////////////////////////////////////////
void toggle_use_open_guard(GtkWidget *caller){
    cfg_set_use_open_guard ((int)gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller)));
	cfg_save();
}
////////////////////////////////////////////////////////////////////
void toggle_show_lang(GtkWidget *caller){
    cfg_set_show_lang((int)gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller)));
	gtk_source_buffer_set_highlight_matching_brackets (mBuff, gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller)));
	set_language();
	cfg_save();
}
////////////////////////////////////////////////////////////////////


void new_file(){
	
    if(save_modified()) {
        gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(mBuff),"",-1);
        gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);
        currentfile=NULL;
        gtk_window_set_title(GTK_WINDOW(window),_FALLBACK_SAVE_FILE_NAME);
		save_locked=FALSE;
    }
	
}

void open_file(){  
	gchar *newfile=NULL;
	gint response;
	GtkWidget *dialog;
    if(save_modified()){
        dialog = gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,NULL);
        gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
        response = gtk_dialog_run(GTK_DIALOG(dialog));
        if(response==GTK_RESPONSE_ACCEPT){
			save_locked=FALSE;
            newfile=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			if(currentfile){
				if(newfile) new_thread_tpad((char*) g_strdup(g_strdup(newfile)));
			}
			else show_file(g_strdup(newfile));
			
        }
        gtk_widget_destroy(GTK_WIDGET(dialog));
    }
}
void toggle_line_wrap(GtkWidget *caller){
	(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller))) ? gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view),GTK_WRAP_WORD) : gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view),GTK_WRAP_NONE);
	(gtk_text_view_get_wrap_mode (GTK_TEXT_VIEW (view))) ? cfg_set_show_line_wrap(1) : cfg_set_show_line_wrap(0);
	cfg_save();
}

void set_title(){
(cfg_show_full_path()) ? gtk_window_set_title(GTK_WINDOW(window),g_strescape(currentfile,"\\\?\'\"")) : gtk_window_set_title(GTK_WINDOW(window),get_currentfile_basename());	
}
void set_buffer(){
	    gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(mBuff),content,-1);
	    g_free(content);
        gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);
        GtkTextIter iter;
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(mBuff),&iter);
        gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(mBuff),&iter);
}
void show_file(gchar *nfile){

	static gchar *newfile=NULL;

	
	newfile= g_strdup(check_file(nfile));

		if (newfile == NULL){
	//	ui_unity_urgent_on();
		print("Can't open file:");
		print(nfile);
	}
	else{
	int mcheck=check_magic(newfile);
		
		if(mcheck == 0){
			printf("tpad(v.%s):%s\n",VERSION,_ERROR_MAGIC_BAD);
			}
	else{

	 if (mcheck == 2){
	printf("tpad(v.%s):%s\n",VERSION,_ERROR_MAGIC_INIT);
		}
		if (mcheck == 3){
	   printf("%s\n",_ERROR_MAGIC_DB);
		}
					if(cfg_use_open_guard()){
										currentfile=NULL;
				currentfile=g_strdup(newfile);	

	
					if(tpad_open_guard_check_ok()){
						 setModified=1;
					}
					else{

						tpad_open_guard_make_temp();
						madetemp=1;
						origfile=g_strdup((gchar*) newfile);
						newfile=g_strdup((gchar*) path_temp_file);
						
					}
				}

	gsize length;
    GError *err = NULL;
	content=NULL;
	unknownContents=NULL;
	if(g_file_get_contents (newfile, &unknownContents, &length,&err))
	{
		if (err != NULL){
			 ui_unity_urgent_on();
			gerror_warn(err->message,_CAN_NOT_READ_FILE,TRUE,TRUE);
			g_error_free (err);
			
		}
		else{
			GError *error = NULL;	
			content=g_strdup(g_convert(unknownContents, length, "UTF-8", g_get_codeset(),NULL, NULL, &error));
			g_free(unknownContents);
			if (error != NULL)
       		{
			    ui_unity_urgent_on();
				gerror_warn(error->message,_CONVERT_FAILED,TRUE,TRUE);
   				g_error_free (error);
       		}
 	   		else{
				set_buffer();
				//if(currentfile) g_free(currentfile);
				currentfile=NULL;
				currentfile=g_strdup(newfile);	
				set_title();
				set_language();
										if(cfg_use_open_guard() &&  setModified==1){
					        gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
    						gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),TRUE);
  							gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
							}
			} 
		}
	}
  }
}
}
void toggle_show_full_path(GtkWidget *caller){
 (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller))) ? cfg_set_show_full_path(1) : cfg_set_show_full_path(0);	
if(currentfile) set_title();
}

#ifdef AUTO_TAB_TOGGLE

void toggle_auto_tab(GtkWidget *caller){
	gboolean state=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller));
	gtk_source_view_set_auto_indent(GTK_SOURCE_VIEW(view),(gboolean)state);
	cfg_set_auto_tab((int) state);
	cfg_save();
}
#endif

void set_language(){
	if(cfg_lang()){
			GtkSourceLanguageManager *lm;
			lm=gtk_source_language_manager_new();
			if(currentfile!=NULL){
				long unsigned int i= 0,pos= 0;
				static char fil[sizeof(currentfile)/sizeof(currentfile[1])];
    			for(i=0; currentfile[i]; i++){
        			if(currentfile[i]=='\\') fil[pos++]='\\';
        			fil[pos++]=currentfile[i];
    				}
    			fil[pos]=0;
				gboolean result_uncertain;
				gchar *content_type;
				content_type = g_content_type_guess (fil, NULL, 0, &result_uncertain);
				if (result_uncertain){
					g_free (content_type);
					content_type = NULL;
					}
				GtkSourceLanguage *lang = NULL;
				lang = gtk_source_language_manager_guess_language (lm, fil, content_type);
				gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(mBuff),GTK_SOURCE_LANGUAGE(lang));
				gtk_source_buffer_set_highlight_matching_brackets (GTK_SOURCE_BUFFER(mBuff), (gboolean) cfg_lang());
				if(cfg_lang()) (lang) ? gtk_source_buffer_set_highlight_syntax(GTK_SOURCE_BUFFER(mBuff),TRUE) : gtk_source_buffer_set_highlight_syntax(GTK_SOURCE_BUFFER(mBuff),FALSE);	
				if(content_type) g_free (content_type);
		}
	}
	else {
		gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(mBuff),NULL);
		gtk_source_buffer_set_highlight_syntax(GTK_SOURCE_BUFFER(mBuff),FALSE); 
	     }
	if(cfg_undo() >= 1 && cfg_undo() <= UNDO_MAX) gtk_source_buffer_set_max_undo_levels ((GtkSourceBuffer *)mBuff,(gint)cfg_undo());
	else {
		gtk_source_buffer_set_max_undo_levels ((GtkSourceBuffer *)mBuff,(gint)-1);
		cfg_set_undo(0);
	}
		(cfg_line_wrap()) ? gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view),GTK_WRAP_WORD) : gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view),GTK_WRAP_NONE);
}



void select_font(){
    gint response;
    GtkWidget *dialog = gtk_font_chooser_dialog_new(_FONT,NULL);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
	
    response = gtk_dialog_run(GTK_DIALOG(dialog));
	
    if (response == GTK_RESPONSE_OK || response == GTK_RESPONSE_APPLY) {
        PangoFontDescription *font_desc;
        gchar *fontname = gtk_font_chooser_get_font(GTK_FONT_CHOOSER(dialog));
        g_print("%s",fontname);
        font_desc = pango_font_description_from_string(fontname);
        gtk_widget_modify_font(GTK_WIDGET(view), font_desc);
        pango_font_description_free(font_desc);
        g_free(fontname);
    }
    gtk_widget_destroy(dialog);
}



void do_undo(){
   if(gtk_source_buffer_can_undo(GTK_SOURCE_BUFFER(mBuff))) gtk_source_buffer_undo(GTK_SOURCE_BUFFER(mBuff));
}


void do_redo(){
  if(gtk_source_buffer_can_redo(GTK_SOURCE_BUFFER(mBuff)))  gtk_source_buffer_redo(GTK_SOURCE_BUFFER(mBuff));
}



void init_spelling(){
	doc_spelling = gtk_spell_checker_new ();
	gtk_spell_checker_set_language (doc_spelling, _SPELL_LANG, NULL);
	gtk_spell_checker_attach (doc_spelling,GTK_TEXT_VIEW (view));
	spell_state=1;
	cfg_set_show_spelling(1);
}

void toggle_linenumber(GtkWidget *caller){
	gboolean state=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller));
	gtk_source_view_set_show_line_numbers (view,(gboolean)state);
	cfg_set_show_line((int) state);
	cfg_save();
}

void detach_spell(){
	g_object_ref(doc_spelling);
	gtk_spell_checker_detach (doc_spelling);
	spell_state=0;
	cfg_set_show_spelling(0);
}


void attach_spell(){
	gtk_spell_checker_attach(doc_spelling, GTK_TEXT_VIEW (view));
	g_object_unref(doc_spelling);
	spell_state=1;
	cfg_set_show_spelling(1);
}


void toggle_spelling(){
	switch(spell_state)
	{
	case 0: attach_spell();
		break;
	case 1: detach_spell();
		break;
	case 2: init_spelling();
		break;
	}
	cfg_save();
}

void toggle_keep_above(GtkWidget *caller){
	gtk_window_set_keep_above (GTK_WINDOW(window),gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller)));
	cfg_save();
}

void quit_program(){
	if (save_modified()){
		tpad_open_guard_remove_temp();
		run_count_update=0;
		set_path_self_cleanup();
		g_free(currentfile);
		ui_unity_destroy();
		gtk_main_quit();
		exit(0);
		}
}


#ifdef HAVE_LIBUNITY
void ui_unity_init(void){
	/*if (!entry)
		entry = unity_launcher_entry_get_for_desktop_file( _DESKTOP_FILE_NAME );
*/
}

void ui_unity_destroy (void)
{
	/*
if (entry) {
		unity_launcher_entry_set_count_visible (entry, FALSE);
		g_main_context_iteration(NULL, FALSE);
	}
*/
}
int ui_unity_urgent_on (void)
{
	/*
	if (!entry) ui_unity_init();

	
	if (entry) {
			unity_launcher_entry_set_urgent(entry,TRUE);
			return(TRUE);
	}
	else return(FALSE);
	*/
	return(TRUE);
}

int ui_unity_urgent_off (void)
{
	/*
	if (!entry) ui_unity_init();

	
	if (entry) {
			unity_launcher_entry_set_urgent(entry,FALSE);
			return(TRUE);
	}
	else return(FALSE);
		*/
	return(TRUE);
}
#else
void ui_unity_init(void) {}
int ui_unity_urgent_on (void) {}
int ui_unity_urgent_off (void) {}
void ui_unity_destroy (void) {}
#endif  /* HAVE_LIBUNITY */
