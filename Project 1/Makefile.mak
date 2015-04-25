ALLEGRO_DIR=C:/Allegro/lib
export PKG_CONFIG_PATH=$(ALLEGRO_DIR)/lib/pkgconfig
CFLAGS=$(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) && pkg-config --cflags allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5 allegro_dialog-5 allegro_primitives-5)
LDFLAGS=$(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) && pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5 allegro_dialog-5 allegro_primitives-5)

main: main.o sprite.o world.o tank.o vehicle.o shell.o Observer.o Subject.o TankGame.o
	g++ -o main main.o sprite.o world.o tank.o vehicle.o shell.o Observer.o Subject.o TankGame.o ${LDFLAGS}

main.o: main.cpp sprite.h world.h
	g++ -c main.C ${CFLAGS}

sprite.o: sprite.h sprite.cpp
	g++ -c sprite.C ${CFLAGS}

world.o: world.h sprite.h tank.h TankGame.h world.cpp
	g++ -c world.C ${CFLAGS}

tank.o:	tank.h vehicle.h shell.h sprite.h TankGame.h tank.cpp
	g++ -c tank.cpp ${CFLAGS}

vehicle.o:	vehicle.h Observer.h Subject.h  sprite.h vehicle.cpp
	g++ -c vehicle.cpp $ {CFLAGS}

shell.o:	shell.h Subject.h sprite.h TankGame.h shell.cpp
	g++ -c shell.cpp ${CFLAGS}
	
Observer.o:	Observer.h Observer.cpp
	g++ -c Observer.cpp ${CFLAGS}
	
Subject.o:	Subject.h Subject.cpp
	g++ -c Subject.cpp ${CFLAGS}
	
TankGame.o:	TankGame.h TankGame.cpp
	g++ -cTankGame.cpp ${CFLAGS}
	
clean:
	rm -f *.o main

