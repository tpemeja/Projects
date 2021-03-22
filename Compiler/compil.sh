#CREATION DES FICHIERS .C ET .H
cd src/
make lang
cp ./lang ../
make clean
cd ..
file_name=$(basename $1 .myc)
file_c="$file_name.c"
file_h="$file_name.h"
in_h=1
./lang < $1 > $file_name.txt
echo "#ifndef $(echo $file_name | tr 'a-z' 'A-Z')_H" > $file_h
echo "#define $(echo $file_name | tr 'a-z' 'A-Z')_H" >> $file_h
while read line
do
  if [ -z "$line" ]; then
    in_h=0
    echo "#include \"$(echo $file_name).h\"" > $file_c
  else
    if [ ${in_h} -eq 1 ] ; then
      echo $line >> $file_h
    else
      echo $line >> $file_c
    fi
  fi
done < $file_name.txt
echo "#endif" >> $file_h
rm $file_name.txt
