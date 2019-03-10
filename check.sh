#!/bin/bash
#//////////////////////////////////////////////////////
#	Created by Nan Mihai on 09.04.2017
#	Copyright (c) 2017 Nan Mihai. All rights reserved.
#	Checker Tema 2 - Structuri de date
#	Arbori de joc
#	Facultatea de Automatica si Calculatoare
#	Anul Universitar 2016-2017, Seria CC
#/////////////////////////////////////////////////////
result1=0
result2=0
result3=0
result=0
depunctari1=0
depunctari2=0
depunctari3=0
depunctari4=0
ZERO=0
VALGRIND="valgrind --leak-check=full --track-origins=yes -q --log-file=rezultat_valgrind.txt"
make build > /dev/null 2>&1
BEST=110
#Cerinta 1 - Construirea arborelui de joc
echo " _____________________________________________________________________"
echo "|               Cerinta 1 - Construirea arborelui de joc              |"					  
echo "|_____________________________________________________________________|"
for i in {1..10}
do
	fileIn="public_tests/task01/in/test"$i".in"
	fileOut="public_tests/task01/out/test"$i".out"
	fileRef="public_tests/task01/ref/test"$i".out"
	$VALGRIND ./minimax -c1 $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $fileRef > /dev/null
	EXIT_CODE=$?
	rm -rf $fileOut
	if [ $i -lt 10 ]
	then
		i=" "$i
	fi
	if [ $EXIT_CODE -eq $ZERO ] 
	then
		echo "GameTree_Test $i ................................................. PASS"
		((result=result+4))
		((result1=result1+4))
		if [[ -z $(cat rezultat_valgrind.txt) ]]; then
			printf "VALGRIND_Test $i ................................................. PASS\n"
		else
			printf "VALGRIND_Test $i ................................................. FAIL\n"
			((depunctari1=depunctari1+2))
			((result=result-2))
		fi
	else
		echo "GameTree_Test $i ................................................. FAIL"
	fi
done
#Cerinta 2 - Evaluarea arborelui SI/SAU
echo " _____________________________________________________________________"
echo "|                Cerinta 2 - Evaluarea arborelui SI/SAU               |"
echo "|_____________________________________________________________________|"
for i in {1..10}
do
	fileIn="public_tests/task02/in/test"$i".in"
	fileOut="public_tests/task02/out/test"$i".out"
	fileRef="public_tests/task02/ref/test"$i".out"
	$VALGRIND ./minimax -c2 $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $fileRef > /dev/null
	EXIT_CODE=$?
	rm -rf $fileOut
	if [ $i -lt 10 ]
	then
		i=" "$i
	fi
	if [ $EXIT_CODE -eq $ZERO ]
	then
		echo "AND/ORTree_Test $i ............................................... PASS"
		((result=result+2))
		((result2=result2+2))
		if [[ -z $(cat rezultat_valgrind.txt) ]]; then
			printf "VALGRIND_Test   $i ............................................... PASS\n"
		else
			printf "VALGRIND_Test   $i ............................................... FAIL\n"
			((depunctari2=depunctari2+1))
			((result=result-1))
		fi
	else
		echo "AND/ORTree_Test $i ............................................... FAIL"
	fi
done
#Cerinta 3 - Algoritmul Minimax
echo " _____________________________________________________________________"
echo "|                   Cerinta 3 - Algoritmul Minimax                    |"
echo "|_____________________________________________________________________|"
for i in {1..20}
do
	fileIn="public_tests/task03/in/test"$i".in"
	fileOut="public_tests/task03/out/test"$i".out"
	fileRef="public_tests/task03/ref/test"$i".out"
	$VALGRIND ./minimax -c3 $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $fileRef > /dev/null
	EXIT_CODE=$?
	rm -rf $fileOut
	if [ $i -lt 10 ]
	then
		i=" "$i
	fi
	if [ $EXIT_CODE -eq $ZERO ]
	then
		echo "Minimax_Test  $i ................................................. PASS"
		result=$(awk "BEGIN {print $result+1.5; exit}")
		result3=$(awk "BEGIN {print $result3+1.5; exit}")
		if [[ -z $(cat rezultat_valgrind.txt) ]]; then
			printf "VALGRIND_Test $i ................................................. PASS\n"
		else
			printf "VALGRIND_Test $i ................................................. FAIL\n"
			depunctari3=$(awk "BEGIN {print $depunctari3+0.25; exit}")
			result=$(awk "BEGIN {print $result-0.25; exit}")
		fi
	else
		echo "Minimax_Test  $i ................................................. FAIL"
	fi
done
#Bonus
bonus=0
#Cerinta 3 - Algoritmul Minimax cu Alpha-Beta Pruning
echo " _____________________________________________________________________"
echo "|                      Bonus - Alpha-Beta Pruning                     |"
echo "|_____________________________________________________________________|"
for i in {1..20}
do
	fileIn="public_tests/bonus/in/test"$i".in"
	fileOut="public_tests/bonus/out/test"$i".out"
	fileRef="public_tests/bonus/ref/test"$i".out"
	$VALGRIND ./minimax -b $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $fileRef > /dev/null
	EXIT_CODE=$?
	rm -rf $fileOut
	if [ $i -lt 10 ]
	then
		i=" "$i
	fi
	if [ $EXIT_CODE -eq $ZERO ]
	then
		echo "Alpha\Beta_Test $i ............................................... PASS"
		result=$(awk "BEGIN {print $result+1; exit}")
		bonus=$(awk "BEGIN {print $bonus+1; exit}")
		if [[ -z $(cat rezultat_valgrind.txt) ]]; then
			printf "VALGRIND_Test   $i ............................................... PASS\n"
		else
			printf "VALGRIND_Test   $i ............................................... FAIL\n"
			depunctari4=$(awk "BEGIN {print $depunctari4+0.1; exit}")
			result=$(awk "BEGIN {print $result-0.1; exit}")
		fi
	else
		echo "Alpha\Beta_Test $i ............................................... FAIL"
	fi
done
echo "Total - Cerinta 1 : "$result1
if [ $depunctari1 -ne 0 ]
then
	echo "Depunctari - Cerinta 1 : "$depunctari1
fi
echo "Total - Cerinta 2 : "$result2
if [ $depunctari2 -ne 0 ]
then
	echo "Depunctari - Cerinta 2 : "$depunctari2
fi
echo "Total - Cerinta 3 : "$result3
if [ $depunctari3 -ne 0 ]
then
	echo "Depunctari - Cerinta 3 : "$depunctari3
fi
echo "Total - Bonus     : "$bonus
if [ $depunctari4 -ne 0 ]
then
	echo "Depunctari - Bonus : "$depunctari4
fi
if [ "$result" -eq $BEST ]; then
	echo "Felicitari! Ai punctajul maxim: "$BEST"p! :)"
else
	echo "Ai acumulat "$result"p din maxim 110p! :("
fi
rm -rf out
rm -rf ref
make clean > /dev/null 2>&1
