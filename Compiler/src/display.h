#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Attribute.h"
#include "Table_des_symboles.h"

void printf_att(attribute at);
void printf_exp(char symb, attribute at0, attribute at1, attribute at2);
void printf_bool(char* symb, attribute at0, attribute at1);
void printf_decl(attribute type, pile p);
void printf_fonction(pile p);
void printf_fonction_2(pile p);
void copie_pile(pile p,pile new_pile2);
void inversion_pile(pile p);
void printf_struct(pile p,attribute s);
void print_type(attribute type);
void printf_struct_aff(char* op, attribute s, attribute exp);
void printf_pile(pile p);
#endif
