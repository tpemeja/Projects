# source test.sh $1 $2

diff $1 $2 > temp.txt
t=temp.txt

if [ ! -e $t  ]; then
    echo "Erreur pendant diff $1 $2" #ne devrait pas se produire
fi
if [ -s $t ]; then
    rm temp.txt
    return 0 #KO !
else
    rm temp.txt
    return 1 #OK!
fi

rm temp.txt
