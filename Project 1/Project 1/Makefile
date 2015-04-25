ALLEGRO_DIR=~cdshaffer/allegro/lib
export PKG_CONFIG_PATH=$(ALLEGRO_DIR)/lib/pkgconfig
CFLAGS=$(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) && pkg-config --cflags allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5 allegro_dialog-5 allegro_primitives-5)
LDFLAGS=$(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) && pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5 allegro_dialog-5 allegro_primitives-5)

main: main.o sprite.o world.o
	g++ -o main main.o sprite.o world.o ${LDFLAGS}

main.o: main.C sprite.h world.h
	g++ -c main.C ${CFLAGS}

sprite.o: sprite.h sprite.C
	g++ -c sprite.C ${CFLAGS}

world.o: world.h sprite.h world.C
	g++ -c world.C ${CFLAGS}

clean:
	rm -f *.o main

