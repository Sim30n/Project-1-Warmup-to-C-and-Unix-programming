# Project-1-Warmup-to-C-and-Unix-programming
Käyttöjärjestelmät ja systeemiohjelmointi

gcc reverse.c -o reverse -Wall -std=c99 -pedantic

./reverse input.txt 

./reverse input.txt output.txt

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./reverse input.txt
