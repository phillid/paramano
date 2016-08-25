#include <stddef.h>

void         gf_init();
int          gf_current(int core);
int          gf_available(int core, char* out, int size);
void         gf_get_frequency_label(char* buffer, size_t max_size, int freq);
char*        gf_freqa(int core, int index);
int          gf_freqi(int core, int index);
unsigned int gf_number();
