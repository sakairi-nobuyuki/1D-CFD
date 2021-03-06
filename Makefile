CC=g++
CFLAGS=-Wall -O3 -vtree-vectorize 

all:main

#main:main.o cfd2d.o cfd1d.o volume.o boundary.o Mechanics.o functions.o
#	$(CC) $(CFLAGS) main.o cfd2d.o cfd1d.o volume.o boundary.o Mechanics.o functions.o -o main -lm
main:main.o cfd1d.o volume.o boundary.o functions.o
	$(CC) $(CFLAGS) main.o cfd1d.o volume.o boundary.o functions.o -o main -lm


#object
main.o:main.cpp
volume.o:volume.cpp
boundary.o:boundary.cpp
functions.o:functions.cpp
#Mechanics.o:Mechanics.cpp
cfd1d.o:cfd1d.cpp
#cfd2d.o:cfd2d.cpp

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@