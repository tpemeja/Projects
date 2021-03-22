/*
 *  Attribute.h
 *
 *  Created by Janin on 10/2019
 *  Copyright 2018 LaBRI. All rights reserved.
 *
 *  Module for a clean handling of attibutes values
 *
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {INT, FLOAT, TVOID, TSTRUCT, TSTRUCT_ATTRIBUTE} type;

struct ATTRIBUTE {
  char * name;
  int int_val;
  float float_val;
  type type_val;
  char* struct_name;
  int star_count;
  int reg_number;
  char* reg_name;
  struct ATTRIBUTE* struct_attribute; // pour une structure, chaine des attributs

  /* other attribute's fields can goes here */

};

struct PELEM {
  struct ATTRIBUTE* a;
  struct PELEM* suivant;
};

struct PILE {
  struct PELEM* premier;
};

typedef struct ATTRIBUTE * attribute;
typedef struct PILE * pile;

#include "Table_des_symboles.h"
attribute new_attribute ();
/* returns the pointeur to a newly allocated (but uninitialized) attribute value structure */


attribute plus_attribute(attribute x, attribute y);
attribute mult_attribute(attribute x, attribute y);
attribute minus_attribute(attribute x, attribute y);
attribute div_attribute(attribute x, attribute y);
attribute neg_attribute(attribute x);
struct PILE* creer_pile();
struct ATTRIBUTE* depiler(struct PILE* p);
void empiler(struct PILE* p, struct ATTRIBUTE* a);
int new_Reg_Number(struct ATTRIBUTE* x);
int new_label_number();
int new_struct_reg_number();
void add_struct_attribute(attribute new, attribute s);
attribute struct_attribute_exist(attribute base, attribute test);
void controle_struct_type(attribute champ, attribute val);
#endif
