#!/bin/bash

result=0
input=tests/test_main_entrada_saida.in

for input in tests/entradas/*; do

  echo "Testando $input"

  if [[ ${input: -1} == 'a' ]]; then
    rm -f registros
  fi

  number=${input##*/teste}
  number=${number%?}

  # if number bigger than 05
  if [[ $number == "06" ]]; then
    sed -i 's/#define MAXNUMREGS 11/#define MAXNUMREGS 13/' src/main.c
  fi

  output=tests/saidas/s${input##*/teste}
  
  gcc -o main src/main.c
  ./main < $input > test.out

  diff -w -u3 --color=auto --palette='ad=1;3;38;5;154:de=1;3;38;5;9' test.out $output && echo "OK" || result=1

done

sed -i 's/#define MAXNUMREGS 13/#define MAXNUMREGS 11/' src/main.c
rm registros
rm -f test.out
rm -f main
exit $result