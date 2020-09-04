project: user-interface.o llist.o
	g++ -o project  user-interface.cpp llist.o

project.o: user-interface.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -c user-interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp

projectdebug: projectdebug.o llistdebug.o
	g++ -o projectdebug project2.o llist.o

projectdebug.o: user-interface.cpp
	g++ -D DEBUG -ansi -pedantic-errors -Wall -c user-interface.cpp

llistdebug.o: llist.cpp
	g++ -D DEBUG -ansi -pedantic-errors -Wall -c llist.cpp





