# Makefile for the Bank program
CC = g++ -pthread
CFLAGS = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
CCLINK = $(CXX)
OBJS = Bank.o main.o
RM = rm -f
TARGET = Bank
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) -o Bank $(OBJS)
# Creating the object files
main.o: main.cpp Bank.h
Bank.o: Bank.cpp Bank.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*
