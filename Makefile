CC=g++
CFLAGS=-Wall -g -O0 -std=c++11
TARGET_NAME=CalcPostFix
TARGET_TEST=test-CPF
SRC=src/main.cpp src/fonctions.cpp
SRC_TEST=
DEPS=-I inc/

default: run 

calculatrice:
	$(CC) -o $(TARGET_NAME) $(SRC) $(DEPS) $(CFLAGS)

test : 
	$(CC) -o $(TARGET_TEST) $(SRC_TEST) $(DEPS) $(CFLAGS)
	./$(TARGET_TEST)

clean:
	rm CalcPost* 

run:	calculatrice
	./$(TARGET_NAME)
