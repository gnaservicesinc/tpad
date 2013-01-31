/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2013 Andrew Smith <andrew@gnaservicesinc.com>
 * 
 * Tpad is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Tpad is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "include.h"

int main(int argc,char *argv[]){
	#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
	#endif
	struct passwd *pw = getpwuid(syscall(__NR_getuid));
	strcpy ((char*)cfg_file,pw->pw_dir);
	strcat ((char*)cfg_file,"/.tpad.cfg");
	config_setup((char*)cfg_file); 
    GtkAccelGroup *accel_group;
    GtkWidget *menubar,*file,*filemenu,*newfile,*open,*save,*saveas,*quit,
	*search,*searchmenu,*find,*spelling,*replace,*redo,*undo,*settings,
	*settingsmenu,*selectfont,*linenumber,*help,*helpmenu,*about,*toolbar,
	*scrolled_window,*mainbox,*lang_chk,*ShowFullPath,*UIPrefs
		#ifdef AUTO_TAB_TOGGLE
		,*AutoTab
		#endif
		;
	GtkToolItem *toolnew,*toolopen,*toolsave,*toolsaveas,*toolredo,*toolundo,*toolquit,*toolspelling;
	currentfile=NULL;
	self_loc=argv[0];
	
    gtk_init(&argc,&argv);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Tpad");
	gtk_window_set_default_size(GTK_WINDOW(window),cfg_wWidth(),cfg_wHeight());
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(window),gdk_pixbuf_new_from_inline (-1, tpad_inline, FALSE, NULL));
	mainbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	
	menubar = gtk_menu_bar_new();	
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

    searchmenu=gtk_menu_new();

    search = gtk_menu_item_new_with_mnemonic("_Edit");
    find = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND,NULL);
    replace = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND_AND_REPLACE,NULL);   
    undo = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO,NULL);
    redo = gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO,NULL);
	
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(search), searchmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), find);
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), replace);
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), gtk_separator_menu_item_new() );
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), undo);
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), redo);
    gtk_menu_shell_append(GTK_MENU_SHELL(searchmenu), gtk_separator_menu_item_new() );
	
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
	UIPrefs =  gtk_menu_item_new_with_label(_UI_SETTINGS);

	(cfg_show_full_path()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ShowFullPath),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ShowFullPath),FALSE);
	(cfg_line()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(linenumber),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(linenumber),FALSE);
	(cfg_spell()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(spelling),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(spelling),FALSE);
	(cfg_lang()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(lang_chk),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(lang_chk),FALSE);                                           
	#ifdef AUTO_TAB_TOGGLE
	(cfg_auto_tab()) ? gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(AutoTab),TRUE) : gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(AutoTab),FALSE);
	#endif
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(settings), settingsmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), selectfont);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
    gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), linenumber);
    gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), spelling);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), lang_chk);
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), ShowFullPath);
	#ifdef AUTO_TAB_TOGGLE
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), AutoTab);
	#endif
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), gtk_separator_menu_item_new() );
	gtk_menu_shell_append(GTK_MENU_SHELL(settingsmenu), UIPrefs);
	
    helpmenu=gtk_menu_new();

    help = gtk_menu_item_new_with_mnemonic("_Help");
    about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT,NULL);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);	
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
    gtk_widget_add_accelerator(redo, "activate", accel_group,
                               GDK_KEY_r, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);	    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), search);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), settings);;
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
    gtk_box_pack_start(GTK_BOX(mainbox), menubar, FALSE, FALSE, 0);

	toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);

    toolquit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolquit),0);

	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(gtk_separator_tool_item_new ()),0);

	toolspelling  = gtk_tool_button_new_from_stock(GTK_STOCK_SPELL_CHECK);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(toolspelling),0);
		
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),GTK_TOOL_ITEM(gtk_separator_tool_item_new ()),0);
	
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

    gtk_box_pack_start(GTK_BOX(mainbox), toolbar, FALSE, FALSE, 0);

    mBuff=gtk_source_buffer_new(NULL);
	
	view=(GtkSourceView *)gtk_source_view_new_with_buffer(mBuff);
    (cfg_line()) ? gtk_source_view_set_show_line_numbers (view,TRUE) : gtk_source_view_set_show_line_numbers (view,FALSE) ;
    gtk_widget_modify_font(GTK_WIDGET(view), pango_font_description_from_string("DejaVu Sans Mono 12"));

	if(cfg_spell()) {
		doc_spelling = gtk_spell_checker_new ();
		gtk_spell_checker_set_language (doc_spelling, _SPELL_LANG, NULL);
		gtk_spell_checker_attach (doc_spelling,GTK_TEXT_VIEW (view));
		spell_state=1;
		cfg_set_show_spelling(1);
	}
	
    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window),GTK_WIDGET(view));
    gtk_box_pack_start(GTK_BOX(mainbox),GTK_WIDGET(scrolled_window),TRUE,TRUE,0);

    gtk_container_add(GTK_CONTAINER(window),mainbox);
	
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
	g_signal_connect(selectfont,"activate",G_CALLBACK(select_font),NULL);
    g_signal_connect(linenumber,"activate",G_CALLBACK(toggle_linenumber),NULL);
	g_signal_connect(spelling,"activate",G_CALLBACK(toggle_spelling),NULL);
	g_signal_connect(ShowFullPath,"activate",G_CALLBACK(toggle_show_full_path),NULL);	
	#ifdef AUTO_TAB_TOGGLE
	g_signal_connect(AutoTab,"activate",G_CALLBACK(toggle_auto_tab),NULL);
	#endif
	g_signal_connect(lang_chk,"activate",G_CALLBACK(toggle_show_lang),NULL);
	g_signal_connect(about,"activate",G_CALLBACK(show_about),NULL);
	g_signal_connect(UIPrefs,"activate",G_CALLBACK(show_ui_prefs),NULL);

    g_signal_connect(toolnew,"clicked",G_CALLBACK(runn),NULL);
    g_signal_connect(toolopen,"clicked",G_CALLBACK(open_file),NULL);
    g_signal_connect(toolsave,"clicked",G_CALLBACK(save_file),NULL);
    g_signal_connect(toolsaveas,"clicked",G_CALLBACK(save_as),NULL);
    g_signal_connect(toolundo,"clicked",G_CALLBACK(do_undo),NULL);
    g_signal_connect(toolredo,"clicked",G_CALLBACK(do_redo),NULL);
	g_signal_connect(toolspelling,"clicked",G_CALLBACK(toggle_spelling),NULL);
	g_signal_connect(toolquit,"clicked",G_CALLBACK(quit_program),NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
	
    new_file();
    if(argc > 1) show_file(g_strdup(argv[1]));

    gtk_main();
	
	cfg_on_exit();
	
	return (0);
}
void print(gchar *s){
   g_print("tpad(v.%s): %s\n",VERSION,s);
}

void toggle_show_lang(GtkWidget *caller){
    cfg_set_show_lang((cfg_lang()^1));
	set_language();
	gtk_widget_destroy(caller);
}

void do_UI_pref_update(GtkWidget *caller, gpointer dialog)
{
	cfg_set_default_width(gtk_spin_button_get_value_as_int (xSpinButton));
	cfg_set_default_height(gtk_spin_button_get_value_as_int (ySpinButton));
	cfg_set_undo(gtk_spin_button_get_value_as_int (uSpinButton));	
	set_language(); 
	gtk_widget_destroy((GtkWidget*) dialog);
}
void show_ui_prefs (){

	GtkWidget *dialog,*mainbox,*buttonbox,*xbox,*ybox,*ubox,*buttonAccept; 
	dialog=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(dialog),_UI_SETTINGS);
    gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(dialog),FALSE);
	g_signal_connect(dialog,"destroy",G_CALLBACK(gtk_widget_destroy),NULL);
	mainbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	xbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	ybox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	ubox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0); 
	buttonbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);  

	gtk_container_add(GTK_CONTAINER(dialog),mainbox);
	gtk_container_add(GTK_CONTAINER(mainbox),xbox);
    gtk_container_add(GTK_CONTAINER(mainbox),ybox);
	gtk_container_add(GTK_CONTAINER(mainbox),ubox);                     
	gtk_container_add(GTK_CONTAINER(mainbox),buttonbox);    

	gtk_box_pack_start (GTK_BOX (xbox),GTK_WIDGET (gtk_label_new(_DEFAULT_WIDTH)), TRUE, TRUE, 1); 
	xSpinButton=(GtkSpinButton*)gtk_spin_button_new_with_range(50,6000,10);
	gtk_spin_button_set_digits (xSpinButton,0);                     
	gtk_spin_button_set_value (xSpinButton,(gdouble)cfg_wWidth()); 
	gtk_spin_button_set_numeric (xSpinButton, TRUE);                   
	gtk_box_pack_start (GTK_BOX (xbox),GTK_WIDGET(xSpinButton),TRUE,TRUE,1);

	gtk_box_pack_start (GTK_BOX (ybox),GTK_WIDGET (gtk_label_new(_DEFAULT_HEIGHT)), TRUE, TRUE, 1); 
	ySpinButton=(GtkSpinButton*)gtk_spin_button_new_with_range(50,6000,10);
	gtk_spin_button_set_digits (ySpinButton,0);
	gtk_spin_button_set_numeric (ySpinButton, TRUE);                      
	gtk_spin_button_set_value (ySpinButton,(gdouble)cfg_wHeight()); 
	gtk_box_pack_start (GTK_BOX (ybox),GTK_WIDGET(ySpinButton),TRUE,TRUE,1);

	gtk_box_pack_start (GTK_BOX (ubox),GTK_WIDGET (gtk_label_new(_UNDO_LEVEL)), TRUE, TRUE, 1); 
	uSpinButton=(GtkSpinButton*)gtk_spin_button_new_with_range(0,UNDO_MAX,5);
	gtk_spin_button_set_digits (uSpinButton,0);
	gtk_spin_button_set_numeric (uSpinButton, TRUE);                      
	gtk_spin_button_set_value (uSpinButton,(gdouble)cfg_undo()); 
	gtk_box_pack_start (GTK_BOX (ubox),GTK_WIDGET(uSpinButton),TRUE,TRUE,1);
                  
    buttonAccept=gtk_button_new_from_stock(GTK_STOCK_APPLY);
	
	gtk_box_pack_start (GTK_BOX (buttonbox),GTK_WIDGET (buttonAccept), TRUE, TRUE, 1);
	
	g_signal_connect(buttonAccept,"clicked",G_CALLBACK(do_UI_pref_update),(gpointer) dialog); 
	
	gtk_widget_show_all(dialog);	
}
              
int save_modified(){
    GtkWidget *dialog;
    int response=0;
    if(gtk_text_buffer_get_modified(GTK_TEXT_BUFFER(mBuff))==TRUE) {
        dialog=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_QUESTION,GTK_BUTTONS_NONE,"Text was modified!\nSave it?");
        gtk_dialog_add_button(GTK_DIALOG(dialog),GTK_STOCK_YES,1);
        gtk_dialog_add_button(GTK_DIALOG(dialog),GTK_STOCK_NO,0);
        gtk_dialog_add_button(GTK_DIALOG(dialog),GTK_STOCK_CANCEL,-1);
        response=gtk_dialog_run(GTK_DIALOG(dialog));
        if(response == 1) save_file();
        gtk_widget_destroy(dialog);
    }
    if(response==-1) return(0);
    else return(1);
}

void * run_command(void *ptr){
	if(vfork() == 0) exit(execl("/bin/sh","sh","-c", self_loc, (char*) NULL));		
	return(0);
} 

void runn(){
	pthread_t thread;
	pthread_create( &thread, NULL,run_command, (void*)self_loc);
	pthread_join(thread, NULL);		
}

void new_file(){
    if(save_modified()) {
        gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(mBuff),"",-1);
        gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);
        currentfile=NULL;
        gtk_window_set_title(GTK_WINDOW(window),"Untitled");
      
    }
}

void open_file(){
    GtkWidget *dialog;
    gint response;
    gchar *newfile;
	
    if(save_modified()){
        dialog = gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,NULL);
        gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
        response = gtk_dialog_run(GTK_DIALOG(dialog));
        if(response==GTK_RESPONSE_ACCEPT){
            newfile=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			if(currentfile){
				strcpy ((char*)nFile,(char*)self_loc);
				strcat ((char*)nFile,(char*)" ");
				strcat ((char*)nFile,(char*)newfile);
				self_loc=(char*)nFile;
				runn();
			}
			else show_file(newfile);
        }
        gtk_widget_destroy(dialog);
    }
}

void toggle_show_full_path(){
cfg_set_show_full_path((cfg_show_full_path()^1));
if(currentfile) set_title();
}

char *get_currentfile_basename(){
char *file_base_name=strrchr(currentfile, '/');
return(file_base_name ? file_base_name+1 : currentfile);
}

void set_title(){
(cfg_show_full_path()) ? gtk_window_set_title(GTK_WINDOW(window),currentfile) : gtk_window_set_title(GTK_WINDOW(window),get_currentfile_basename());	
}

void show_file(gchar *newfile){
    gboolean response;
    gchar *content;
    response=g_file_get_contents(newfile,&content,NULL,NULL);
    if(response==TRUE) {
        gtk_source_buffer_begin_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(mBuff),content,-1);
        gtk_source_buffer_end_not_undoable_action(GTK_SOURCE_BUFFER(mBuff));
        gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);

        GtkTextIter iter;
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(mBuff),&iter);
        gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(mBuff),&iter);
		if(currentfile) g_free(currentfile);
        currentfile=g_strdup(newfile);
		set_title();
        set_language();
    }
}
#ifdef AUTO_TAB_TOGGLE
void toggle_auto_tab(GtkWidget *caller){
	gboolean state=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller));
	gtk_source_view_set_auto_indent(view,(gboolean)state);
	cfg_set_auto_tab((int) state);
}
#endif
void set_language(){
	if(cfg_lang()){
		long unsigned int i,pos;
		static char fil[sizeof(currentfile)/sizeof(currentfile[1])];
		GtkSourceLanguageManager *lm;
		GtkSourceLanguage *language = NULL;
		lm=gtk_source_language_manager_new();
		if(currentfile!=NULL){
    		pos = 0;
    		for(i=0; currentfile[i]; i++){
        		if(currentfile[i]=='\\') fil[pos++]='\\';
        		fil[pos++]=currentfile[i];
    		}
    		fil[pos]=0;
    		print(fil);
    		language=gtk_source_language_manager_guess_language(lm,fil,NULL);
    		gtk_source_buffer_set_language(mBuff,language);
			(language) ? gtk_source_buffer_set_highlight_syntax(mBuff,TRUE) : gtk_source_buffer_set_highlight_syntax(mBuff,FALSE);

		}
	}
	else {
		gtk_source_buffer_set_language(mBuff,NULL);
		gtk_source_buffer_set_highlight_syntax(mBuff,FALSE); 
	     }
	if(cfg_undo() >= 1 && cfg_undo() <= UNDO_MAX) gtk_source_buffer_set_max_undo_levels ((GtkSourceBuffer *)mBuff,(gint)cfg_undo());
	else {
		gtk_source_buffer_set_max_undo_levels ((GtkSourceBuffer *)mBuff,(gint)-1);
		cfg_set_undo(0);
	}
}

void save_file(){
    gchar *content;
    GtkTextIter start,end;
    if(currentfile) {
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(mBuff),&start);
        gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(mBuff),&end);
        content=gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE);
        g_file_set_contents(currentfile,content,-1,NULL);
        gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),FALSE);
        gtk_window_set_title(GTK_WINDOW(window),currentfile);
        set_language();
    }
    else save_as();
}

void save_as(){
    GtkWidget *dialog;
	
    dialog = gtk_file_chooser_dialog_new("Save File",GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_SAVE,
                                         GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_show_hidden (GTK_FILE_CHOOSER(dialog),TRUE);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),TRUE);
	if(currentfile) gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog),get_currentfile_basename());
	else gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog),"Untitled");
	if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT) {
		currentfile=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        save_file();
    }
    gtk_widget_destroy(dialog);
}

void do_find(GtkWidget *caller, GtkWidget *dialog){
    const gchar *findwhat;
    findwhat=gtk_entry_get_text(GTK_ENTRY(findentry));
    GtkTextIter iter;

    if(gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff)))
		gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(mBuff),
		                                  &iter,
		                                  gtk_text_buffer_get_selection_bound(GTK_TEXT_BUFFER(mBuff)));
	else 
		gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(mBuff),
                                           &iter,
                                           gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(mBuff)));

    if (gtk_text_iter_forward_search (&iter, findwhat, GTK_TEXT_SEARCH_TEXT_ONLY, &match_start, &match_end, NULL)) {
        gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(view),&match_end,0.0,FALSE,0,0);
        gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
    }
    else{
        GtkTextIter insert = iter;
        gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(mBuff), &iter);
        if (gtk_text_iter_forward_search (&iter, findwhat, GTK_TEXT_SEARCH_TEXT_ONLY, &match_start, &match_end, &insert))
        {
            gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(view),&match_end,0.0,FALSE,0,0);
            gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
        }
    }
}

void do_replace(GtkWidget *caller, GtkWidget *dialog){	
	do_find(caller,dialog);
	if(gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff))){
        gtk_text_buffer_delete (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
        gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &match_start, gtk_entry_get_text(GTK_ENTRY(replaceentry)), -1);
	}
		
}

void do_find_replace(GtkWidget *caller, GtkWidget *dialog){
	do_find(caller,dialog);
	while(gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff))){		
        gtk_text_buffer_delete (GTK_TEXT_BUFFER(mBuff), &match_start, &match_end);
        gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &match_start, gtk_entry_get_text(GTK_ENTRY(replaceentry)), -1);
		do_find(caller,dialog);
	}
}

void replace_dialog(){
    GtkWidget *dialog;
    GtkWidget *mainbox,*boxbutton,*findbox,*replacebox,*vseparator[2];
    GtkWidget *buttonfind,*buttonreplace,*buttonfindreplace;
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
	recived=gtk_clipboard_wait_for_text(S_Clip);
	findentry = gtk_entry_new();
	
	if(recived) gtk_entry_set_text(GTK_ENTRY(findentry),recived);

	gtk_box_pack_start (GTK_BOX (findbox),
                        GTK_WIDGET (findentry), TRUE, TRUE, 1);	
	gtk_box_pack_start (GTK_BOX (findbox),
	                    GTK_WIDGET(vseparator[0]),TRUE,TRUE,1);
	
    gtk_box_pack_start (GTK_BOX (replacebox),
                        GTK_WIDGET (gtk_label_new(_REPLACE_WITH)), TRUE, TRUE, 1);

    replaceentry = gtk_entry_new();	
    gtk_entry_set_max_length(GTK_ENTRY(replaceentry),65536);
	
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

    g_signal_connect(buttonfind,"clicked",G_CALLBACK(do_find), dialog);
    g_signal_connect(buttonreplace,"clicked",G_CALLBACK(do_replace), dialog);
    g_signal_connect(buttonfindreplace,"clicked",G_CALLBACK(do_find_replace), dialog);
    g_signal_connect(dialog,"destroy",G_CALLBACK(gtk_widget_destroy),NULL);
	
    gtk_widget_show_all(dialog);
}

void do_undo(){
    gtk_source_buffer_undo(GTK_SOURCE_BUFFER(mBuff));
}

void do_redo(){
    gtk_source_buffer_redo(GTK_SOURCE_BUFFER(mBuff));
}

void init_spelling(){
	doc_spelling = gtk_spell_checker_new ();
	gtk_spell_checker_set_language (doc_spelling, _SPELL_LANG, NULL);
	gtk_spell_checker_attach (doc_spelling,GTK_TEXT_VIEW (view));
	spell_state=1;
	cfg_set_show_spelling(1);
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

void toggle_linenumber(GtkWidget *caller){
	gboolean state=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(caller));
	gtk_source_view_set_show_line_numbers (view,(gboolean)state);
	cfg_set_show_line((int) state);
}

void show_about(){

    GtkWidget *dialog;
    dialog=gtk_about_dialog_new();
	
    gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG(dialog),(const gchar *)"Tpad");
    gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(dialog),(const gchar *)VERSION);
    gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG(dialog),(const gchar *)_ABT_COMMENT);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),(const gchar *)"Copyright © Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>");
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),(const gchar *)"https://gnaservicesinc.com");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(dialog),(const gchar *)"GNA Homepage");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog),gdk_pixbuf_new_from_inline (-1, tpad_inline, FALSE, NULL));
	
	gtk_window_set_position(GTK_WINDOW(GTK_ABOUT_DIALOG(dialog)),GTK_WIN_POS_CENTER);
    gtk_dialog_run(GTK_DIALOG(GTK_ABOUT_DIALOG(dialog)));
    gtk_widget_destroy(dialog);
 
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
}


void quit_program(){
	if (save_modified()){
		cfg_on_exit();
		if(!cfg_gaveUp())
			store_settings((char*)cfg_file,
			               cfg_line(),
			               cfg_lang(),
			               cfg_spell(),
			               cfg_wWidth(),
			               cfg_wHeight(),
			               cfg_undo(),
			               cfg_show_full_path()
						   #ifdef AUTO_TAB_TOGGLE
			               ,
			               cfg_auto_tab()
						   #endif
			               );

		if(currentfile) g_free(currentfile);
		gtk_main_quit();
		}
}
