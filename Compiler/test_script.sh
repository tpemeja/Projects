#!/bin/bash

#récupération du compilateur
cd src/
make -s
cd ..
cp src/lang .

#début des tests
#déclarations
cd test
path_decl="decl/"
path_aff="aff/"
path_cond="cond/"
path_ope="ope/"
path_return="return/"
path_struct="struct/"
files="${path_decl}test_simple_decl_int
       ${path_decl}test_simple_decl_float
       ${path_decl}test_double_decl_int
       ${path_decl}test_double_decl_float
       ${path_decl}test_double_decl_error
       ${path_aff}test_aff_int
       ${path_aff}test_aff_float
       ${path_aff}test_aff_error
       ${path_cond}test_if
       ${path_cond}test_if_else
       ${path_cond}test_while
       ${path_ope}test_plus_int
       ${path_ope}test_plus_float
       ${path_ope}test_minus_int
       ${path_ope}test_minus_float
       ${path_ope}test_mult_int
       ${path_ope}test_mult_float
       ${path_return}test_return_empty
       ${path_return}test_return_exp
       ${path_struct}test_struct_mult_float
       ${path_struct}test_struct_mult_int
       ${path_struct}test_struct_mult_mix
       ${path_struct}test_struct_simple_float
       ${path_struct}test_struct_simple_int
       ${path_struct}test_struct_dot
       ${path_struct}test_struct_dot_error
       ${path_struct}test_struct_arrow
       ${path_struct}test_struct_arrow_error"

names_decl="simple.int.declaration
       simple.float.declaration
       multiple.int.declaration
       multiple.float.declaration
       double.declaration.error"

names_aff="affection.int
           affection.float
           affection.error"

names_cond="cond.if
            cond.if.else
            cond.while"

names_ope="ope.plus.int
           ope.plus.float
           ope.minus.int
           ope.minus.float
           ope.mult.int
           ope.mult.float"

names_return="return.empty
           return.empty.exp"

names_struct="struct.mult.float
           struct.mult.int
           struct.mult.mix
           struct.simple.float
           struct.simple.int
           struct.dot.aff
           struct.dot.aff.error
           struct.arrow.aff
           struct.arrow.aff.error"

declare -a tab_result
count=0
i=0

#lancement des tests
for f in $files
do
    .././lang < $f.myc > $f.txt
    source test.sh $f.txt $f.rslt
    tab_result[count]=$?
    count=$(($count+1))
done

#affichage des résultats
if [ "$1" == "-d" ]; then
    echo "TEST FOR DECLARATION: $((${tab_result[0]}+${tab_result[1]}+${tab_result[2]}+${tab_result[3]}+${tab_result[4]}))/5"
    for n in $names_decl
    do
        echo -n "   $n:  "
        if [ ${tab_result[i]} -eq 1 ]; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
        i=$(($i+1))
    done
    echo "TEST FOR AFFECTATION: $((${tab_result[5]}+${tab_result[6]}+${tab_result[7]}))/3"
    for n in $names_aff
    do
        echo -n "   $n:  "
        if [ ${tab_result[i]} -eq 1 ]; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
        i=$(($i+1))
    done
    echo "TEST FOR CONDITION: $((${tab_result[8]}+${tab_result[9]}+${tab_result[10]}))/3"
    for n in $names_cond
    do
        echo -n "   $n:  "
        if [ ${tab_result[i]} -eq 1 ]; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
        i=$(($i+1))
    done
    echo "TEST FOR OPERATION: $((${tab_result[11]}+${tab_result[12]}+${tab_result[13]}+${tab_result[14]}+${tab_result[15]}+${tab_result[16]}))/6"
    for n in $names_ope
    do
        echo -n "   $n:  "
        if [ ${tab_result[i]} -eq 1 ]; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
        i=$(($i+1))
    done
    echo "TEST FOR RETURN: $((${tab_result[17]}+${tab_result[18]}))/2"
    for n in $names_return
    do
        echo -n "   $n:  "
        if [ ${tab_result[i]} -eq 1 ]; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
        i=$(($i+1))
    done
    echo "TEST FOR STRUCT: $((${tab_result[19]}+${tab_result[20]}+${tab_result[21]}+${tab_result[22]}+${tab_result[23]}+${tab_result[24]}+${tab_result[25]}+${tab_result[26]}+${tab_result[27]}))/9"
    for n in $names_struct
    do
        echo -n "   $n:  "
        if [ ${tab_result[i]} -eq 1 ]; then
            echo "PASSED"
        else
            echo "FAILED"
        fi
        i=$(($i+1))
    done
else
    echo "TEST FOR DECLARATION: $((${tab_result[0]}+${tab_result[1]}+${tab_result[2]}+${tab_result[3]}+${tab_result[4]}))/5"
    echo "TEST FOR AFFECTATION: $((${tab_result[5]}+${tab_result[6]}+${tab_result[7]}))/3"
    echo "TEST FOR CONDITION: $((${tab_result[8]}+${tab_result[9]}+${tab_result[10]}))/3"
    echo "TEST FOR OPERATION: $((${tab_result[11]}+${tab_result[12]}+${tab_result[13]}+${tab_result[14]}+${tab_result[15]}+${tab_result[16]}))/6"
    echo "TEST FOR RETURN: $((${tab_result[17]}+${tab_result[18]}))/2"
    echo "TEST FOR STRUCT: $((${tab_result[19]}+${tab_result[20]}+${tab_result[21]}+${tab_result[22]}+${tab_result[23]}+${tab_result[24]}+${tab_result[25]}+${tab_result[26]}+${tab_result[27]}))/9"
    echo "For more details use -d option"
fi

#sortie des tests
rm ${path_decl}*.txt ${path_cond}*.txt ${path_aff}*.txt ${path_ope}*.txt ${path_return}*.txt ${path_struct}*.txt
cd ..

#nettoyage des fichiers
rm lang
cd src/
make -s clean
cd ..


#rm $file_h $file_c
