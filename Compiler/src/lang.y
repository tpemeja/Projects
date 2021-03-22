%code requires{
#include "Table_des_symboles.h"
#include "Attribute.h"
#include "display.h"
 }

%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();

void yyerror (char* s) {
  printf ("%s\n",s);

}


%}

%union {
	attribute val;
  char* s;
  pile p;
  int i;
}
%token <val> NUMI NUMF
%token TINT TFLOAT STRUCT
%token <val> ID
%token AO AF PO PF PV VIR
%token RETURN VOID EQ
%token <val> IF ELSE WHILE



%token <val> AND OR NOT DIFF EQUAL SUP INF
%token PLUS MOINS STAR DIV
%token DOT ARR

%type<val> exp
%type<s> vir
%type<p> vlist attr
%type<val> typename type
%type<val> pointer STAR
%type<val> if else bool_cond stat while while_cond
%type<p> params fun fun_head

%left DIFF EQUAL SUP INF       // low priority on comparison
%left PLUS MOINS               // higher priority on + -
%left STAR DIV                 // higher priority on * /
%left OR                       // higher priority on ||
%left AND                      // higher priority on &&
%left DOT ARR                  // higher priority on . and ->
%nonassoc UNA                  // highest priority on unary operator

%start prog



%%

prog : block                   {}
;

block:
decl_list inst_list            {}
;

// I. Declarations

decl_list : decl decl_list     {}
|                              {printf("\n");}
;

decl: var_decl PV              {printf(";\n");}
| struct_decl PV               {}
| fun_decl                     {}
;

// I.1. Variables
var_decl : type vlist          {if($1->type_val == TSTRUCT)
                                    get_symbol_value($1->name);
                                printf_decl($1,$2);}
;

// I.2. Structures
struct_decl : STRUCT ID struct {$2->type_val = TSTRUCT;
                                set_symbol_value($2->name,$2);}
;

struct : AO attr AF            {printf("struct %s{\n",$<val>0->name);
                                printf_struct($2,$<val>0);
                                printf("};\n");}
;

attr : type ID PV              {pile p = creer_pile();
                                empiler(p,$2);
                                empiler(p,$1);
                                $$ = p;}
| type ID PV attr              {empiler($4,$2);
                                empiler($4,$1);
                                $$ = $4;}

// I.3. Functions

fun_decl : type fun            {printf("}\n");
                                printf("\n");}
;

fun : fun_head fun_body        {}
;

fun_head : ID PO PF            {pile p = creer_pile();
                                pile p3 = creer_pile();
                                copie_pile(p,p3);
                                empiler(p,$1);
                                empiler(p,$<val>0);
                                pile p2 = creer_pile();
                                copie_pile(p,p2);
                                printf_fonction(p);
                                printf("\n");
                                printf_fonction_2(p2);
                                printf_pile(p3);}
| ID PO params PF              {pile p3 = creer_pile();
                                copie_pile($3,p3);
                                empiler($3,$1);
                                empiler($3,$<val>0);
                                pile p2 = creer_pile();
                                copie_pile($3,p2);
                                printf_fonction($3);
                                printf("\n");
                                printf_fonction_2(p2);
                                printf_pile(p3);}
;

params: type ID vir params     {empiler($4,$2);
                                empiler($4,$1);
                                $$ =$4;}
| type ID                      {pile pa = creer_pile();
                                empiler(pa,$2);
                                empiler(pa,$1);
                                $$ = pa;}

vlist: ID vir vlist            {empiler($3,$1);
                                $$ = $3;}
| ID                           {pile p = creer_pile();
                                empiler(p,$1);
                                $$ = p;}
;

vir : VIR                      {$$ = ",";}
;

fun_body : AO block AF         {}
;

// I.4. Types
type
: typename pointer             {$1->star_count = $2->star_count;
                                $$ = $1;}
| typename                     {$$ = $1;}
;

typename
: TINT                          {attribute new = new_attribute();
                                 new->type_val = INT;
                                 $$ = new;}
| TFLOAT                        {attribute new = new_attribute();
                                 new->type_val = FLOAT;
                                 $$ = new;}
| VOID                          {attribute new = new_attribute();
                                 new->type_val = TVOID;
                                 $$ = new;}
| STRUCT ID                     {attribute new = new_attribute();
                                 new->type_val = TSTRUCT;
                                 new->name = $2->name;
                                 $$ = new;}
;

pointer
: pointer STAR                 {$1->star_count++;
                                $$=$1;}
| STAR                         {attribute new = new_attribute();
                                new->star_count=1;
                                $$ = new;}
;


// II. Intructions

inst_list: inst PV inst_list   {}
| inst                         {}
|                              {}
;

inst:
exp                           {}
| AO block AF                 {}
| aff                         {}
| ret                         {printf(";\n");}
| cond                        {}
| loop                        {}
| PV                          {}
;


// II.1 Affectations

aff : ID EQ exp        {struct ATTRIBUTE* id = get_symbol_value($1->name);
                        switch($3->type_val){
                          case INT:
                            if ($3->name == "NUMI") {
                                if(id->type_val == FLOAT) {
                                    printf ("%s%i = (float)%i;\n", id->reg_name, id->reg_number,$3->int_val);
                                }else{
                                    printf ("%s%i = %i;\n", id->reg_name, id->reg_number,$3->int_val);
                                }
                            }else{
                                if(id->type_val == FLOAT) {
                                    printf ("%s%i = (float)%s%i;\n", id->reg_name, id->reg_number,$3->reg_name,$3->reg_number);
                                }else{
                                    printf ("%s%i = %s%i;\n", id->reg_name, id->reg_number,$3->reg_name,$3->reg_number);
                                }
                            }
                            break;
                          case FLOAT:
                            if (id->type_val == FLOAT) {
                              if ($3->name == "NUMF") {
                                printf ("%s%i = %f;\n", id->reg_name, id->reg_number,$3->float_val);
                              }else{
                                printf ("%s%i = %s%i;\n", id->reg_name, id->reg_number,$3->reg_name,$3->reg_number);
                              }
                            }else{
                              yyerror("type error: in affection: expected INT but given FLOAT");
                              exit(1);
                            }
                            break;
                          }
                       }
| STAR exp EQ exp {}
;


// II.2 Return
ret : RETURN exp              {printf("return ");printf_att($2);}
| RETURN PO PF                {printf("return()");}
;

// II.3. Conditionelles
cond :
if bool_cond stat else stat   {printf("%s%i: ",$2->reg_name,$2->reg_number);}
|  if bool_cond stat          {printf("%s%i: ",$1->reg_name,$1->reg_number);}
;

stat:
AO block AF                   {}
;
bool_cond: PO exp PF          {attribute label = new_attribute();
                               label->reg_name = "label";
                               label->reg_number = new_label_number();
                               printf(") goto %s%i;\n",$<val>0->reg_name,$<val>0->reg_number);
                               printf("\n");
                               printf("\n");
                               $$ = label;}

if : IF                       {attribute label = new_attribute();
                               label->reg_name = "label";
                               label->reg_number = new_label_number();
                               printf("if (! ");
                               $$ = label;}
;

else : ELSE                   {printf("goto %s%i;\n",$<val>-1->reg_name,$<val>-1->reg_number);
                               printf("%s%i: ", $<val>-2->reg_name,$<val>-2->reg_number);}
;

// II.4. Iterations

loop : while while_cond inst  {printf("goto %s%i; \n",$1->reg_name,$1->reg_number);
                               printf("%s%i: ",$2->reg_name,$2->reg_number);}
;

while_cond : PO exp PF        {attribute label = new_attribute();
                               label->reg_name = "label";
                               label->reg_number = new_label_number();
                               printf(") goto %s%i;\n",label->reg_name,label->reg_number);
                               printf("\n");
                               printf("\n");
                               $$ = label;}

while : WHILE                 {attribute label = new_attribute();
                               label->reg_name = "label";
                               label->reg_number = new_label_number();
                               printf("%s%i: if (! ",label->reg_name,label->reg_number);
                               $$ = label;}
;


// II.3 Expressions
exp
// II.3.0 Exp. arithmetiques
: MOINS exp %prec UNA         {}
| exp PLUS exp                {attribute new = new_attribute();
                               printf_exp('+',new,$1,$3);
                               $$ = new;}
| exp MOINS exp               {attribute new = new_attribute();
                               printf_exp('-',new,$1,$3);
                               $$ = new;}
| exp STAR exp                {attribute new = new_attribute();
                               printf_exp('*',new,$1,$3);
                               $$ = new;}
| exp DIV exp                 {attribute new = new_attribute();
                               printf_exp('/',new,$1,$3);
                               $$ = new;}
| PO exp PF                   {$$=$2;}
| ID                          {$$ = get_symbol_value($1->name);}
| NUMI                        {$1->name = "NUMI";
                               $$ = $1;}
| NUMF                        {$1->name = "NUMF";
                               $$ = $1;}

// II.3.1 Déréférencement

| STAR exp %prec UNA          {}

// II.3.2. Booléens

| NOT exp %prec UNA           {}
| exp INF exp                 {printf_bool(" < ",$1,$3);}
| exp SUP exp                 {printf_bool(" > ",$1,$3);}
| exp EQUAL exp               {printf_bool(" == ",$1,$3);}
| exp DIFF exp                {printf_bool(" != ",$1,$3);}
| exp AND exp                 {printf_bool(" && ",$1,$3);}
| exp OR exp                  {printf_bool(" || ",$1,$3);}

// II.3.3. Structures

| exp ARR ID                  {}
| exp ARR ID EQ exp           {printf_struct_aff("->",$1,$3);
                               controle_struct_type($3,$5);
                               printf_att($5);
                               printf(";\n");}
| exp DOT ID EQ exp           {printf_struct_aff(".",$1,$3);
                               controle_struct_type($3,$5);
                               printf_att($5);
                               printf(";\n");}
| app                         {}
;

// II.4 Applications de fonctions

app : ID PO args PF;

args :  arglist               {}
|                             {}
;

arglist : exp VIR arglist     {}
| exp                         {}
;



%%
int main () {
return yyparse ();
}
