/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2013 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_doc.c , is part of tpad.
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
extern GtkSourceBuffer *mBuff;
extern gchar *content;

void low_caps_document(){
	mod_doc(_METHOD_DOWNCAP);
}

void up_caps_document(){
	mod_doc(_METHOD_UPCAP);
}

void rev_document(){
	mod_doc(_METHOD_REVERSE);
}

void mod_doc(int method){

	if (method >= 0 && method <= _METHOD_MAX){
		GtkTextMark *  mark_start = (GtkTextMark *) gtk_text_mark_new ("mStart",TRUE);
		GtkTextMark *  mark_end = (GtkTextMark *) gtk_text_mark_new ("mEnd",FALSE);
	GtkTextIter start,end;
	gchar *RevBuff;
	if(gtk_text_buffer_get_has_selection (GTK_TEXT_BUFFER(mBuff))){
		if(gtk_text_buffer_get_selection_bounds( GTK_TEXT_BUFFER(mBuff),&start,&end))
			{
			gtk_text_buffer_begin_user_action(GTK_TEXT_BUFFER(mBuff));	
			RevBuff=NULL;
			switch(method)
			{
			case _METHOD_REVERSE: 	
				RevBuff=g_strdup(g_strreverse(gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE)));
			break;
			
			case _METHOD_UPCAP:
				RevBuff=g_ascii_strup(gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE),-1);
			break;

			case _METHOD_DOWNCAP:
				RevBuff=g_ascii_strdown (gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE),-1);
			break;

			default:
				gerror_warn(_ERROR_MOD_DOC_METHOD_VAL,(gchar*)__func__,TRUE,FALSE);
			break;
			
			}
			gtk_text_buffer_add_mark  (GTK_TEXT_BUFFER(mBuff),mark_start,&start);
			gtk_text_buffer_add_mark  (GTK_TEXT_BUFFER(mBuff),mark_end,&end);
			gtk_text_buffer_delete (GTK_TEXT_BUFFER(mBuff), &start, &end);
	 		gtk_text_buffer_insert (GTK_TEXT_BUFFER(mBuff), &start, g_strdup(RevBuff), -1);
			gtk_text_buffer_end_user_action (GTK_TEXT_BUFFER(mBuff));
			gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(mBuff),&start);		
					GtkTextIter mstart, mend;
			gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(mBuff),&mstart,mark_start);
			gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(mBuff),&mend,mark_end);
			gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &mstart, &mend);
			gtk_text_buffer_delete_mark (GTK_TEXT_BUFFER(mBuff), mark_start);
			gtk_text_buffer_delete_mark (GTK_TEXT_BUFFER(mBuff), mark_end);
		}
	}
	else {
	// Get buffer, reverse contents, and copy them into content.
	gtk_text_buffer_begin_user_action(GTK_TEXT_BUFFER(mBuff));
		
	gtk_text_buffer_get_bounds( GTK_TEXT_BUFFER(mBuff),&start,&end);
	//gtk_text_buffer_add_mark  (GTK_TEXT_BUFFER(mBuff),mark_start,&start);
    //gtk_text_buffer_add_mark  (GTK_TEXT_BUFFER(mBuff),mark_end,&end);
	content=NULL;
			switch(method)
			{
			case _METHOD_REVERSE: 	
				content=g_strdup(g_strreverse(gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE)));
			break;
			
			case _METHOD_UPCAP:
				content=g_ascii_strup(gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE),-1);
			break;

			case _METHOD_DOWNCAP:
				content=g_ascii_strdown (gtk_text_buffer_get_text(GTK_TEXT_BUFFER(mBuff),&start,&end,FALSE),-1);
			break;

			default:
				gerror_warn(_ERROR_MOD_DOC_METHOD_VAL,(gchar*)__func__,TRUE,FALSE);
			break;
			
			}
	

	// Flush Buffer
   //     gtk_text_buffer_set_text(GTK_TEXT_BUFFER(mBuff),"",-1);

	// Set Buffer
		
		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(mBuff),content,-1);
		g_free(content);
		gtk_text_buffer_end_user_action (GTK_TEXT_BUFFER(mBuff));
        gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(mBuff),TRUE);
        GtkTextIter iter;
        gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(mBuff),&iter);
        gtk_text_buffer_place_cursor(GTK_TEXT_BUFFER(mBuff),&iter);
		/*
		gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(mBuff),&start,mark_start);
		gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(mBuff),&end,mark_end);
		gtk_text_buffer_select_range (GTK_TEXT_BUFFER(mBuff), &start, &end);
		gtk_text_buffer_delete_mark (GTK_TEXT_BUFFER(mBuff), mark_start);
		gtk_text_buffer_delete_mark (GTK_TEXT_BUFFER(mBuff), mark_end);
		*/
	}
	}
}