all : agenda clean

agenda : Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o \
	     Agenda.o
	g++ -std=c++11 -o agenda Date.o User.o Meeting.o Storage.o \
	AgendaService.o AgendaUI.o Agenda.o

Date.o : Date.h Date.cpp
	g++ --std=c++11 -c Date.cpp

User.o : User.h User.cpp
	g++ --std=c++11 -c User.cpp

Meeting.o : Meeting.h Meeting.cpp
	g++ --std=c++11 -c Meeting.cpp

Storage.o : Storage.h Storage.cpp
	g++ --std=c++11 -c Storage.cpp

AgendaService.o : AgendaService.h AgendaService.cpp
	g++ --std=c++11 -c AgendaService.cpp

AgendaUI.o : AgendaUI.h AgendaUI.cpp
	g++ --std=c++11 -c AgendaUI.cpp

Agenda.o : Agenda.cpp
	g++ --std=c++11 -c Agenda.cpp

clean :
	rm *.o
