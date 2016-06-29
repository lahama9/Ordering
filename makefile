#makefile for HW 4
hw4: main.o Customer.o Order.o
	gcc -o hw4 main.o Customer.o Order.o

main.o: main.c Customer.h
	gcc -c main.c

Customer.o: Customer.c Customer.h
	gcc -c Customer.c

Order.o: Order.c Order.h
	gcc -c Order.c
