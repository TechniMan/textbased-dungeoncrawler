IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = Logger.hpp Utilities.hpp Weapon.hpp Creature.hpp Player.hpp Enemy.hpp GAMESTATE.hpp Game.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Logger.o Utilities.o Weapon.o Creature.o Player.o Enemy.o Game.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cpp-cli-rpg: $(OBJ)
	$(CC) -g -o ../bin/$@.exec $^ $(CFLAGS) $(LIBS) -std=c++11

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
