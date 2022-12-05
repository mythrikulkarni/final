CC = g++ --std=c++17
CFLAGS = -I/opt/homebrew/include -g

LDFLAGS = -L/usr/include/jsoncpp -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC_CL = carClient.h carServer.h motorcycleServer.h motorcycleClient.h Passenger.h Person.h Dog.h Auto_V.h
OBJ	= car.o motorcycle.o Passenger.o Person.o Dog.o Auto_V.o

all: 	car motorcycle motorcycleR

carserver.h carclient.h:		sendData.json
	jsonrpcstub sendData.json --cpp-server=carServer --cpp-client=carClient

motorcycleserver.h motorcycleclient.h:		alert.json
	jsonrpcstub alert.json --cpp-server=motorcycleServer --cpp-client=motorcycleClient



Auto_V.o:	Auto_V.cpp Auto_V.h $(INC)
	$(CC) -c $(CFLAGS) Auto_V.cpp

Passenger.o:	Passenger.cpp Passenger.h $(INC)
	$(CC) -c $(CFLAGS) Passenger.cpp

Person.o:	Person.cpp Person.h $(INC)
	$(CC) -c $(CFLAGS) Person.cpp

Dog.o:	Dog.cpp Dog.h $(INC)
	$(CC) -c $(CFLAGS) Dog.cpp

motorcycle.o: motorcycle.cpp carclient.h motorcycleserver.h $(INC)
	$(CC) -c $(CFLAGS) motorcycle.cpp carclient.h motorcycleserver.h

motorcycleR.o: motorcycleR.cpp carclient.h motorcycleserver.h $(INC)
	$(CC) -c $(CFLAGS) motorcycleR.cpp carclient.h motorcycleserver.h

car.o: car.cpp motorcycleclient.h carserver.h $(INC)
	$(CC) -c $(CFLAGS) car.cpp motorcycleclient.h carserver.h

car: Auto_V.o car.o $(INC)
	$(CC) -o car car.o $(OBJ) $(LDFLAGS)

motorcycle: Auto_V.o motorcycle.o $(INC)
	$(CC) -o motorcycle motorcycle.o $(OBJ) $(LDFLAGS)

motorcycleR: Auto_V.o motorcycleR.o $(INC)
	$(CC) -o motorcycleR motorcycleR.o $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o *~ core carServer.h motorcycleServer.h