cd src/
make lang
cp ./lang ../
make clean
cd ..
cd test
for f in `ls *myc | tr -d '.myc'`
do
  in_h=0
  #echo $f
  ./../lang < $f.myc > $f.txt
  echo "#ifndef $(echo $f | tr 'a-z' 'A-Z')_H" > $f.h
  echo "#define $(echo $f | tr 'a-z' 'A-Z')_H" >> $f.h
  echo "#include \"$(echo $f).h\"" > $f.c

  while read line
  do
    if [ -z "$line" ]; then
      in_h=$((in_h+1))

    else
      if [ $(($in_h%3)) -eq 0 ] ; then
        echo $line >> $f.h
      else
        echo $line >> $f.c
      fi
    fi
  done < $f.txt
  echo "#endif" >> $f.h
  rm $f.txt

done
cd ..
