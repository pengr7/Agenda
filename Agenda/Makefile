CC=g++ -c -std=c++0x
all=User.o Date.o Meeting.o Storage.o AgendaService.o AgendaUI.o Agenda.cpp
target:$(all)
	g++ -std=c++0x $(all)
User.o:User.h User.cpp
	$(CC) User.cpp
Date.o:Date.h Date.cpp
	$(CC) Date.cpp
Meeting.o:Meeting.h Meeting.cpp
	$(CC) Meeting.cpp
Storage.o:Storage.h Storage.cpp
	$(CC) Storage.cpp
AgendaService.o:AgendaService.h AgendaService.cpp
	$(CC) AgendaService.cpp
AgendaUI.o:AgendaUI.h AgendaUI.cpp
	$(CC) AgendaUI.cpp
clean:
	rm *.o *.out
