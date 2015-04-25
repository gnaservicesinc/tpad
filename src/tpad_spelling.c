/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_spelling.c , is part of tpad.
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
extern int spell_state;
extern GtkSpellChecker* doc_spelling;
extern GtkSourceView *view;

void init_spelling(){
	doc_spelling = gtk_spell_checker_new ();
	gtk_spell_checker_set_language (doc_spelling, _SPELL_LANG, NULL);
	gtk_spell_checker_attach (doc_spelling,GTK_TEXT_VIEW (view));
	spell_state=1;
	cfg_set_show_spelling(1);
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