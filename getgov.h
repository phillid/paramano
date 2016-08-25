#include <stdbool.h>

void         gg_init();
bool         gg_current(int core, char* out, int size);
bool         gg_available(int core, char* out, int size);
char*        gg_gov(int core, int index);
unsigned int gg_number();
