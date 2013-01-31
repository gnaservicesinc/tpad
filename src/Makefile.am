## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(TPAD_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = tpad

tpad_SOURCES = \
	main.c \
	include.h \
	static.h \
	functions.h \
	user_settings.h \
	user_settings.c \
	store_settings.h \
	store_settings.c \
	tpad_logo.h

tpad_LDFLAGS = 

tpad_LDADD = $(TPAD_LIBS) \
	-lpthread \
	-lconfig

