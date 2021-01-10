all: server client

client: client.cpp
	g++ -o client client.cpp
server: server.cpp AirManager.hpp
	g++ -o server server.cpp AirManager.hpp
clean:
	rm server client
