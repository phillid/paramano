#include <stdarg.h>

int  get_int_value_from_filef(const char* format, ...);
int  vget_int_value_from_filef(const char* format, va_list args);
int  get_int_value_from_file(const char* filename);
void chomp(char *string);
int  get_int(const char* string);

/* <ew> Stringification of line number */
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define STR_LINE STRING(__LINE__)
/* </ew> */

#define info(format, ...)	printf("INFO : "__FILE__"@%s():"STR_LINE": "format, __func__ __VA_OPT__(,) __VA_ARGS__)

#ifdef DEBUG
#define debug(format, ...)	fprintf(stderr, "DEBUG: "__FILE__"@%s():"STR_LINE": "format, __func__ __VA_OPT__(,) __VA_ARGS__)
#else
#define debug(...)
#endif

#define debug_entry()	debug("entry\n")
#define debug_exit()	debug("exit\n")

#define FILE_PATH_SIZE 2048
#define CPU_TRAY_UPDATE_INTERVAL 2000
#define BAT_TRAY_UPDATE_INTERVAL 10000
