all: server client

client: client.cpp
	g++ -o client client.cpp
server: server.o AirManager.o
	g++ -o server server.o AirManager.o
server.o: server.cpp AirManager.h
	g++ -c server.cpp
AirManager.o: AirManager.hpp AirManager.h
	g++ -c AirManager.hpp

clean:
	rm server client *.o
