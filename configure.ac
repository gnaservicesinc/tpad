dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(tpad, 2.8.8)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CC




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=tpad
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

AM_GLIB_GNU_GETTEXT

AC_HEADER_ASSERT
AC_ARG_ENABLE([autotab],
  AS_HELP_STRING([--enable-autotab],
    [enable a menu option to toggle auto indent])
)
AS_IF([test "x$enable_autotab" = "xyes"], [
            AC_DEFINE([AUTO_TAB_TOGGLE], [""],
            [Enable autotab toggle])
])
LT_INIT


PKG_CHECK_MODULES(GTKSPELL3,gtkspell3-3.0)

PKG_CHECK_MODULES(TPAD, libconfig
gtkspell3-3.0
[cairo gdk-pixbuf-2.0 cairo-gobject gucharmap-2.90 pangocairo gtk+-x11-3.0 gtk+-3.0 freetype2 pango gdk-3.0 gtksourceview-3.0 gio-2.0 pixman-1 gobject-2.0 gdk-x11-3.0 libpng12 atk glib-2.0 gtk+-unix-print-3.0 ])




AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
icons/Makefile
man/Makefile
])
