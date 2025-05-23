EXE		    = ./bin/Minesweeper.exe
SRC         = $(wildcard src/*.c)
OBJ         = $(subst src, build, $(patsubst %.c, %.o, $(SRC)))

DBG         = # debug flags

INCLUDE     = -I ./include
LIB         = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSSGE
EXTRA       = -Werror -Wall -O3 -mwindows
STATIC      = # for static linking

all: create_dirs build_resources link

remake: clean all

build_resources:
	windres src/icon.rc -O coff -o build/icon.res

clean:
	erase $(subst build/, build\, $(OBJ))

create_dirs:
	if not exist bin mkdir bin
	if not exist build mkdir build

build/%.o: src/%.c
	gcc $(INCLUDE) -c src/$*.c -o build/$*.o $(DBG) $(EXTRA)

link: $(OBJ)
	gcc $(OBJ) -o $(EXE) $(LIB) $(STATIC) $(DBG) $(EXTRA) build/icon.res
	strip $(EXE)