CC = g++
FLAGS = -Wall -std=c++11

S_OBJS = course.o csapp.o global.o s_main.o network.o person.o system.o server.o

C_OBJS = course.o global.o person.o system.o c_main.o network.o user_interface.o csapp.o

all: client server
.PHONY : all

server: $(S_OBJS)
	$(CC) $(FLAGS) $(S_OBJS) -o server

client: $(C_OBJS)
	$(CC) $(FLAGS) $(C_OBJS) -o client

csapp.o: csapp.cpp csapp.h
	$(CC) $(FLAGS) -c csapp.cpp

network.o: network.cpp network.hpp csapp.h
	$(CC) $(FLAGS) -c network.cpp

global.o: global.cpp global.hpp
	$(CC) $(FLAGS) -c global.cpp

s_main.o: s_main.cpp global.hpp
	$(CC) $(FLAGS) -c s_main.cpp

server.o: server.cpp csapp.h server.hpp system.hpp person.hpp network.hpp global.hpp
	$(CC) $(FLAGS) -c server.cpp

c_main.o: c_main.cpp csapp.h user_interface.hpp
	$(CC) $(FLAGS) -c c_main.cpp

user_interface.o: user_interface.cpp user_interface.hpp global.hpp csapp.h network.hpp
	$(CC) $(FLAGS) -c user_interface.cpp

person.o: person.cpp person.hpp global.hpp course.hpp system.hpp
	$(CC) $(FLAGS) -c person.cpp

course.o: course.cpp course.hpp system.hpp global.hpp
	$(CC) $(FLAGS) -c course.cpp

system.o: system.cpp system.hpp person.hpp course.hpp global.hpp
	$(CC) $(FLAGS) -c system.cpp

clean:
	rm -f *.o server client 
