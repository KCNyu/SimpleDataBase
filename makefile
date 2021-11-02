OBJS1 = ./obj/server.o ./obj/AirManager.o
OBJS2 = ./obj/server_poll.o
OBJS3 = ./obj/server_epoll.o
OBJS4 = ./obj/client.o
inc_path = ./inc

myArgs = -Wall -g

All: server client server_poll server_epoll

server: $(OBJS1)
	g++ $^ -o $@ $(myArgs)
server_poll: $(OBJS2) ./obj/AirManager.o
	g++ $^ -o $@ $(myArgs)
server_epoll: $(OBJS3) ./obj/AirManager.o
	g++ $^ -o $@ $(myArgs)
client: $(OBJS4)
	g++ $^ -o $@ $(myArgs)
$(OBJS1): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)
$(OBJS2): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)
$(OBJS3): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)
$(OBJS4): ./obj/%.o: ./src/%.cpp
	g++ -c $< -o $@ $(myArgs) -I $(inc_path)
clean:
	rm -rf $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) server client server_poll server_epoll

.PHONY: ALL clean
