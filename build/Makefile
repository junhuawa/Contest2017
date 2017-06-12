all: test5 
#test1: ../src/question1.c
#	gcc -o test1 $^ -Wall

test2: ../src/question2.c
	gcc -o test2 $^ -Wall -I../include/

#test3: ../src/question3.c
#	gcc -o test3 $^ -Wall -I../include/

test4: ../src/question4.cpp
	gcc -o test4 $^ -Wall -I../include/ -lstdc++

test5: ../src/question5.c
	gcc -o test5 $^ -Wall -I../include/

.PHONY: clean
clean: 
	rm -rf test*
