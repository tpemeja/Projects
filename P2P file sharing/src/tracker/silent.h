#ifndef SILENT__H
#define SILENT__H
#include <stdio.h>

/* active le mode silencieux */
void set_silent_mode();
/* renvoie 1 si le mode silencieux est activé, 0 sinon*/
int check_silent_mode();
/* fonction permettant de réduire la duplication de code */
void silent_print(char *to_print);
#endif
