# Makefile for the Bank program
CXX = g++ -pthread
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
CCLINK = $(CXX)
OBJS = Bank.o main.o atm.o lock.o
RM = rm -f
TARGET = Bank
# Creating the  executable
Bank: $(OBJS)
	$(CCLINK) -o Bank $(OBJS)
# Creating the object files
main.o: main.cpp Bank.h atm.h
Bank.o: Bank.cpp Bank.h lock.h
atm.o: atm.h atm.cpp Bank.h lock.h
lock.o: lock.h lock.cpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*
