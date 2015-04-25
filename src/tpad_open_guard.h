#ifndef _TPAD_OPEN_GUARD_
#define _TPAD_OPEN_GUARD_
#include "include.h"
extern gchar path_temp_file[];
extern gchar path_swp_file[];
extern gchar path_lock_file[];
extern  gint icurrentfile_size;
extern gint  itempFilePathSize;
extern gint iswpFilePathSize;
extern gint ilockFilePathSize;
gchar *get_currentfile_basename();
gchar *get_currentfile_dirname();
gint tpad_open_guard_init();
void tpad_clear_char_array(char arr[]);
void tpad_open_guard_cln ();
gboolean check_file_path_read (gchar* fp);
int tpad_open_guard_check_ok();
void tpad_open_guard_attack(gchar* fp);
void tpad_open_guard_make_temp();
void tpad_open_guard_remove_temp();
unsigned int tpad_get_file_size(char* filepath);
#endif