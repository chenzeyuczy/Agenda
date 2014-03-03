CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lpthread -lgtest
SOURCES=User.cpp Date.cpp Meeting.cpp UserManage.cpp MeetingManage.cpp FileManage.cpp AgendaService.cpp AgendaController.cpp Agenda.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
