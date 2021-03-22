#include "test4.h"
int test(int d){
int ri0;
ri0 = d;
ri0 = 2;
if (! ri0 != 1) goto label0;
return ri0;
goto label1;
label0:
int ri1 = ri0 + 3;
return ri1;
label1: }
