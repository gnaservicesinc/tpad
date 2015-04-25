/********************************************************************************* 
 *     COPYRIGHT NOTICE:
 *     Copyright © 2014 Andrew Smith (GNA SERVICES INC) <Andrew@GNAServicesInc.com>
 *     All Rights Reserved.
 *
 *   This file, tpad_hconnect.c , is part of tpad.
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


extern gboolean searchCase;
extern gboolean doCOVT;


		void h512_connector(GtkWidget *caller){
			gchar *recived;
	recived=NULL;
	recived=str2sha512(gtk_clipboard_wait_for_text(GTK_CLIPBOARD(gtk_clipboard_get(GDK_SELECTION_PRIMARY))));
		if(strlen(recived) > 2) gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
		void h256_connector(GtkWidget *caller){
					gchar *recived;
	recived=NULL;
	recived=str2sha256(gtk_clipboard_wait_for_text(GTK_CLIPBOARD(gtk_clipboard_get(GDK_SELECTION_PRIMARY))));
		if(strlen(recived) > 2) gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
		void hmd5_connector(GtkWidget *caller){
					gchar *recived;
	recived=NULL;
	recived=str2md5(gtk_clipboard_wait_for_text(GTK_CLIPBOARD(gtk_clipboard_get(GDK_SELECTION_PRIMARY))));
		if(strlen(recived) > 2) gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
	void base64_connector(GtkWidget *caller){
					gchar *recived;
	recived=NULL;
	recived=(char*) str2base64(gtk_clipboard_wait_for_text(GTK_CLIPBOARD(gtk_clipboard_get(GDK_SELECTION_PRIMARY))));
		if(strlen(recived) > 2) gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
		void fbase64_connector(GtkWidget *caller){
					gchar *recived;
	recived=NULL;
	recived=(char*) strFrombase64(gtk_clipboard_wait_for_text(GTK_CLIPBOARD(gtk_clipboard_get(GDK_SELECTION_PRIMARY))));
		if(strlen(recived) > 2) gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
		void base64_file_connector(GtkWidget *caller){
	char* recived= (char*) file2base64();
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
		void fbase64_file_connector(GtkWidget *caller){
	char* recived= (char*) filefrombase64();
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}

		void h512_file_connector(GtkWidget *caller){
		char* recived= (char*) file2sha512();
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
		
	}
		void h256_file_connector(GtkWidget *caller){
	char* recived= (char*) file2sha256();
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
		void hmd5_file_connector(GtkWidget *caller){
		char* recived= (char*) file2md5();
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD),recived ,strlen(recived));
	gtk_clipboard_store (gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
	}
