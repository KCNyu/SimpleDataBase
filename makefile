all: server client

client: client.cpp
	g++ -o client client.cpp
server: server.o AirManager.o
	g++ -o server server.o AirManager.o
server.o: server.cpp AirManager.h
	g++ -c server.cpp
AirManager.o: AirManager.cpp AirManager.h
	g++ -c AirManager.cpp

clean:
	rm server client *.o
