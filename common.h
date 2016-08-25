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

#define info(...)	printf("INFO: "__FILE__":"STR_LINE" --- "__VA_ARGS__)
#define FILE_PATH_SIZE 2048
