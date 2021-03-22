#include "display.h"

void printf_att(attribute at){ //Affiche attribut
  // Affiche le nom du registre ou la valeur de l'attribut
  if(strcmp(at->name,"NUMI") == 0){
    printf("%i",at->int_val);
  }else{
    if(strcmp(at->name,"NUMF") == 0){
      printf("%f",at->float_val);
    }else{
      printf("%s%i",at->reg_name,at->reg_number);
    }
  }
}


void printf_exp(char symb, attribute at0, attribute at1, attribute at2){ //Affiche affectation d'une expression;
// Création d'un nouveau registre
at0->type_val = INT;
at0->reg_name = "ri";
if (at1->type_val == FLOAT || at2->type_val == FLOAT) { //conversion type
  at0->type_val = FLOAT;
  at0->reg_name = "rf";
  if (at1->type_val == INT && at2->type_val == FLOAT) {
    attribute conv = new_attribute();
    conv->type_val = FLOAT;
    conv->reg_name = "rf";
    conv->reg_number = new_Reg_Number(conv);
    print_type(conv);
    printf(" ");
    printf_att(conv);
    printf(" = (float)");
    printf_att(at1);
    printf(";\n");
    at1 = conv;
  }
  if (at1->type_val == FLOAT && at2->type_val == INT) {
    attribute conv = new_attribute();
    conv->type_val = FLOAT;
    conv->reg_name = "rf";
    conv->reg_number = new_Reg_Number(conv);
    print_type(conv);
    printf(" ");
    printf_att(conv);
    printf(" = (float)");
    printf_att(at2);
    printf(";\n");
    at2 = conv;
  }
}
switch(at0->type_val) {
  case INT:
  printf("int ");
  break;
  case FLOAT:
  printf("float ");
  break;
}
at0->reg_number = new_Reg_Number(at0);

// Affichage affectation
printf_att(at0); printf(" = ");    printf_att(at1); printf(" %c ",symb); printf_att(at2); printf(";\n");
};

void printf_bool(char* symb, attribute at0, attribute at1){ //Affiche expression booleenes
  // Affichage expression
  printf_att(at0); printf(" %s ",symb); printf_att(at1);
};

void print_type(attribute type) {
  switch(type->type_val) {
    case INT:
    printf("int");
    break;
    case FLOAT:
    printf("float");
    break;
    case TVOID:
    printf("void");
    break;
    case TSTRUCT:
    printf("struct %s",type->name);
    break;
    default:
    printf("undefined type error\n");
    exit(1);
  }
}
void print_star(attribute type) {
  int count = type->star_count;
  while(count > 0) {
    printf("*");
    count--;
  }
  printf(" ");
}

void printf_decl(attribute type, pile p) {
    //affichage du type à déclarer
    print_type(type);
    print_star(type);
    // affichage de tous les symboles à convertir en registre
    while(p->premier->suivant != NULL){
        attribute a = depiler(p);
        if (get_symbol_value(a->name) != NULL) {
            printf("declaration error: double declaration of %s\n", a->name);
            exit(1);
        }
        switch(type->type_val) {
            case INT:
                a->type_val = INT;
                a->reg_name = "ri";
                a->reg_number = new_Reg_Number(a);
                a->star_count = type->star_count;
                set_symbol_value(a->name,a);
                printf("ri%i, ",a->reg_number);
                break;
            case FLOAT:
                a->type_val = FLOAT;
                a->reg_number = new_Reg_Number(a);
                a->reg_name = "rf";
                a->star_count = type->star_count;
                set_symbol_value(a->name,a);
                printf("rf%i, ",a->reg_number);
                //printf("test type: %i\n",a->type_val);
                break;
            case TSTRUCT:
                a->type_val = TSTRUCT;
                a->reg_name = "rs";
                a->reg_number = new_struct_reg_number();
                a->struct_name = type->name;
                a->star_count = type->star_count;
                set_symbol_value(a->name,a);
                printf("rs%i,",a->reg_number);
                break;
        }
    }
    // le dernier élément n'affiche pas de , mais un ;
    attribute a = depiler(p);
    if (get_symbol_value(a->name) != NULL) {
        printf("declaration error: double declaration of %s\n", a->name);
        exit(1);
    }
    switch(type->type_val) {
        case INT:
            a->type_val = INT;
            a->reg_name = "ri";
            a->reg_number = new_Reg_Number(a);
            a->star_count = type->star_count;
            set_symbol_value(a->name,a);
            printf("ri%i",a->reg_number);
            break;
        case FLOAT:
            a->type_val = FLOAT;
            a->reg_name = "rf";
            a->reg_number = new_Reg_Number(a);
            a->star_count = type->star_count;
            set_symbol_value(a->name,a);
            printf("rf%i",a->reg_number);
            break;
        case TSTRUCT:
            a->type_val = TSTRUCT;
            a->reg_name = "rs";
            a->reg_number = new_struct_reg_number();
            a->struct_name = type->name;
            a->star_count = type->star_count;
            set_symbol_value(a->name,a);
            printf("rs%i",a->reg_number);
            break;
    }
  free(p);
}

void printf_struct(pile p,attribute s) {
  // affichage des attributs d'une structure
  // dans la pile sont stockés des couples (ID,type)
  s->struct_attribute=NULL;
  while(p->premier != NULL) {
    attribute type = depiler(p);
    attribute id = depiler(p);
    id->type_val=type->type_val;
    add_struct_attribute(id,s);
    printf("\t");
    print_type(type);
    print_star(type);
    printf("%s;\n",id->name);
  }
}

void printf_struct_aff(char* op, attribute s, attribute id) {
    int cmp = 0;
    if (strcmp(op,"->") == 0) {
        cmp = 1;
    }
    if (strcmp(op,".") == 0) {
        cmp = 2;
    }
    attribute champs = NULL;
    switch(cmp) {
        case 1:
            champs = struct_attribute_exist(s,id);
            if (s->star_count != 1) {
                printf("struct error: in arrow affection: %s is not a single-pointer\n",s->name);
                exit(1);
            }
            if (champs != NULL && s->star_count == 1){
                printf_att(s);
                printf("->");
                printf("%s",id->name);
                printf(" = ");
            }else{
                printf("struct error: in affection: this attribute doesn't exist\n");
                exit(1);
            }
            break;
        case 2:
            champs = struct_attribute_exist(s,id);
            if (s->star_count != 0){
                printf("struct error: in dot affection: %s is a pointer\n",s->name);
                exit(1);
            }
            if (champs != NULL && s->star_count == 0){
                printf_att(s);
                printf(".");
                printf("%s",id->name);
                printf(" = ");
            }else{
                printf("struct error: in affection: this attribute doesn't exist\n");
                exit(1);
            }
            break;
    }
}

void printf_fonction(pile p) {
  // affichage des attributs d'une structure
  // dans la pile sont stockés des couples (ID,type)
  if(p->premier != NULL){
    attribute type = depiler(p);
    attribute id = depiler(p);
    print_type(type);
    print_star(type);
    printf("%s(",id->name);
  }
  while(p->premier != NULL && p->premier->suivant != NULL && p->premier->suivant->suivant != NULL) {
    attribute type = depiler(p);
    attribute id = depiler(p);
    print_type(type);
    print_star(type);
    printf("%s,",id->name);
  }
  if(p->premier != NULL){
    attribute type = depiler(p);
    attribute id = depiler(p);
    print_type(type);
    print_star(type);
    printf("%s",id->name);
  }
  printf(");\n");
  free(p);
}

void inversion_pile(pile p){
  pile new_pile = creer_pile();
  while(p->premier != NULL) {
    attribute att = depiler(p);
    empiler(new_pile,att);
  }
  *p = *new_pile;
  free(new_pile);
}

void copie_pile(pile p,pile new_pile2){
  pile new_pile1 = creer_pile();
  while(p->premier != NULL) {
    attribute att = depiler(p);
    empiler(new_pile1,att);
    empiler(new_pile2,att);
  }
  inversion_pile(new_pile1);
  inversion_pile(new_pile2);
  *p = *new_pile1;
  free(new_pile1);
}


void printf_fonction_2(pile p) {
  // affichage des attributs d'une structure
  // dans la pile sont stockés des couples (ID,type)
  if(p->premier != NULL){
    attribute type = depiler(p);
    attribute id = depiler(p);
    print_type(type);
    print_star(type);
    printf("%s(",id->name);
  }
  while(p->premier != NULL && p->premier->suivant != NULL && p->premier->suivant->suivant != NULL) {
    attribute type = depiler(p);
    attribute id = depiler(p);
    print_type(type);
    print_star(type);
    printf("%s,",id->name);
  }
  if(p->premier != NULL){
    attribute type = depiler(p);
    attribute id = depiler(p);
    print_type(type);
    print_star(type);
    printf("%s",id->name);
  }
  printf("){\n");
  free(p);
}


void printf_pile(pile p){
  while(p->premier != NULL && p->premier->suivant != NULL){
    attribute type = depiler(p);
    print_type(type);
    print_star(type);
    attribute a = depiler(p);
    char* name = a->name;
    switch(type->type_val) {
      case INT:
      a->type_val = INT;
      a->reg_name = "ri";
      a->reg_number = new_Reg_Number(a);
      set_symbol_value(a->name,a);
      printf("ri%i;\n",a->reg_number);
      printf("ri%i = ",a->reg_number);
      break;
      case FLOAT:
      a->type_val = FLOAT;
      a->reg_number = new_Reg_Number(a);
      a->reg_name = "rf";
      set_symbol_value(a->name,a);
      printf("rf%i;\n",a->reg_number);
      printf("rf%i = ",a->reg_number);
      //printf("test type: %i\n",a->type_val);
      break;
      case TSTRUCT:
      a->type_val = TSTRUCT;
      a->reg_name = "rs";
      a->reg_number = new_struct_reg_number();
      a->struct_name = type->name;
      set_symbol_value(a->name,a);
      printf("rs%i;\n",a->reg_number);
      printf("rs%i = ",a->reg_number);
      break;
    }
    printf("%s;\n",name);
  }
  free(p);
}
