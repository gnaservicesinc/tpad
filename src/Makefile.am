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
	../autogen.sh \
	error_warn.h \
	tpad_spawn.h \
	tpad_print.h \
	malloc.h \
	tpad_file.h \
	malloc.c \
	include.h \
	error_warn.c \
	tpad_file.c \
	tpad_print.c \
	tpad_spawn.c \
	tpad_logo.h \
	tpad_config.h \
	tpad_config.c \
	def.h \
	main.c \
	tpad_headers.h \
	tpad_doc.h \
	tpad_doc.c \
	tpad_pref.c \
	tpad_pref.h \
	tpad_save.c \
	tpad_save.h \
	tpad_string.c \
	tpad_string.h \
	tpad_textstats.c \
	tpad_textstats.h \
	tpad_open_guard.c \
	tpad_open_guard.h
	malloc.c\
	malloc.h\
	tpad_config.h\
	tpad_file.h\
	tpad_logo.h\
	tpad_print.h\
	tpad_spawn.h\
	tpad_string.h\
	error_warn.c\
	tpad_config.c\ 
	tpad_file.c\
	tpad_print.c\ 
	tpad_spawn.c\
	tpad_string.c\
	tpad_textstats.h\
	tpad_textstats.c\
	tpad_pref.h\
	tpad_pref.c\
	tpad_doc.h\
	tpad_doc.c\
	tpad_save.h\
	tpad_save.c

tpad_CFLAGS = -D_XOPEN_SOURCE=600 

tpad_LDFLAGS = 

tpad_LDADD = $(TPAD_LIBS) \
	-lpthread \
	-lm \
	-lmagic

