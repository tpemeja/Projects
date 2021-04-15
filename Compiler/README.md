# Compiler creation 
Project realized in 2019 with Maxime ROSAY

## Project description
In this project, we created a compiler generating C code from a language specially created for this project and named "myC"

The complier supports the following actions :
- **declarations** (```int```, ```float```, ```struct```, ```void```, ```pointers```)
- **operators** (```+```,```-```,```*```) but not between pointers
- **assignments** (```int```,```float```,```struct```)
- **conditionals** (```if```, ```if else```, ```while```)
- **structures** (declaration, assignment) (see comments)
- **return** (no control over the output of the function)
- **function** (see comments)

## Compile .myc file

To generate ```.h``` and ```.c``` files from a ```.myc``` file:

```./compil.sh [nom.myc]```

## Test

We have unit tests, to run them:

```./test_script.sh [-d]```
(```-d``` gives more details about the tests performed)

To test the compiler that generates the .c and .h of the .myc in the ```test``` folder :
```./compil_test.sh```

For hand tests on the pseudo-compiler:
```
cd src/
make
./lang
```

```./lang``` opens the ```.myc``` code interpreter.

For more clarity, we have written some auxiliary functions that are mainly located in ```display.c```.

## Comments:
- Having misunderstood how the compiler should handle structures, i.e. for example ```return char var[8]``` for ```struct var{int x, int y}```
  We return the same structure as in C, which is the opposite of what we were supposed to do.
 
- The grammar does not seem to allow assigning a value to an attribute of a structure.
  For this we have added the rule line 322 ```exp ARR ID EQ exp``` to realize assignments of the type:
  
    ```variable->attribute = sth```
    
  But the rule generates warnings ```13 shift/reduce conflicts``` which we do not know how to solve.
  The code compiles and works with it now, so it doesn't seem to be a problem, but we specify it anyway.

- The assignment of the fields of a structure must strictly respect the equality of types (this is only for the structure, the explicit cast is implemented for the rest)

- The local attributes defined in the functions are not freed when we exit the functions in order to reuse them later.


## Lists of things not implemented:
- Structures in [Three-address code](https://en.wikipedia.org/wiki/Three-address_code) (implemented in C here)
- Check the return type of a function
- Test set for functions
