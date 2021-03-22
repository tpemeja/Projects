#include "Attribute.h"



attribute new_attribute () {
  attribute r;
  r  = malloc (sizeof (struct ATTRIBUTE));
  r->name="";
  return r;
};


// chaine un attribute new à un autre s
void add_struct_attribute(attribute new, attribute s) {
    if (s->struct_attribute == NULL) {
        s->struct_attribute = new;
    } else {
        new->struct_attribute = s->struct_attribute;
        s->struct_attribute = new;
    }
}
// renvoie true si champ et val sont de même type
void controle_struct_type(attribute champ, attribute val) {
    if (champ->type_val != val->type_val) {
        printf("struct affectation: type conflict\n");
        exit(1);
    }
}

// Retourne l'attribute contenant l'attribut si l'attribut contenu dans "test" est bien un attribut du type
// de "base", NULL sinon
attribute struct_attribute_exist(attribute base, attribute test) {
    attribute att = NULL;
    attribute type = get_symbol_value(base->struct_name);
    while (type->struct_attribute != NULL) {
        attribute att = type->struct_attribute;
        if (strcmp(att->name,test->name) == 0) {
            return att;
        }
        type = att;
    }
    return att;
}


int new_struct_reg_number() {
    static int num_struct = 0;
    return num_struct++;
}

int new_label_number() {
    static int num_label = 0;
    return num_label++;
}

int new_Reg_Number(struct ATTRIBUTE* x) {
  static int num_int = 0;
  static int num_float = 0;
  if (x->type_val == INT) {
    return num_int++;
  }else{
          return num_float++;
      }
  printf("new register number error: cannot create for this attribute\n");
  exit(1);
}

void empiler(struct PILE* p, struct ATTRIBUTE* a) {
  struct PELEM* nouveau = malloc(sizeof(*nouveau));
  if (p == NULL || nouveau == NULL) {
    exit(EXIT_FAILURE);
  }
  nouveau->a = a;
  nouveau->suivant = p->premier;
  p->premier = nouveau;
}

struct ATTRIBUTE* depiler(struct PILE* p) {
  if (p == NULL) {
    exit(EXIT_FAILURE);
  }
  struct ATTRIBUTE* a = NULL;
  struct PELEM* elemDepile = p->premier;
  if (p != NULL && p->premier != NULL) {
    a = elemDepile->a;
    p->premier = elemDepile->suivant;
    free(elemDepile);
  }
  return a;
}

struct PILE* creer_pile(){
  struct PILE* nouveau = malloc(sizeof(struct PILE));
  nouveau->premier = NULL;
  return nouveau;
}

attribute plus_attribute(attribute x, attribute y) {
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val + y -> int_val;
  return r;
};

attribute mult_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val * y -> int_val;
  return r;
};

attribute minus_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val - y -> int_val;
  return r;
};

attribute div_attribute(attribute x, attribute y){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = x -> int_val % y -> int_val;
  return r;
};

attribute neg_attribute(attribute x){
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  r -> int_val = -(x -> int_val);
  return r;
};
