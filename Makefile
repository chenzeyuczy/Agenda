all : agenda install

agenda : Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o \
	     Agenda.o
	g++ -o agenda Date.o User.o Meeting.o Storage.o \
	AgendaService.o AgendaUI.o Agenda.o

Date.o : Date.h Date.cpp
	g++ -c Date.cpp

User.o : User.h User.cpp
	g++ -c User.cpp

Meeting.o : Meeting.h Meeting.cpp
	g++ -c Meeting.cpp

Storage.o : Storage.h Storage.cpp
	g++ -c Storage.cpp

AgendaService.o : AgendaService.h AgendaService.cpp
	g++ -c AgendaService.cpp

AgendaUI.o : AgendaUI.h AgendaUI.cpp
	g++ -c AgendaUI.cpp

Agenda.o : Agenda.cpp AgendaController.h
	g++ -c Agenda.cpp

clean :
	rm *.o *~ agenda
