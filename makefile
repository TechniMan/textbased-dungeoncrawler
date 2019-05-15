IDIR=include
SDIR=src
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=lib

LIBS=

_DEPS = Logger.hpp Utilities.hpp Weapon.hpp Creature.hpp Player.hpp Enemy.hpp GAMESTATE.hpp Game.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Logger.o Utilities.o Weapon.o Creature.o Player.o Enemy.o Game.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) -std=c++11

cpp-cli-rpg: $(OBJ)
	mkdir -p bin
	$(CC) -g -o bin/$@.exec $^ $(CFLAGS) $(LIBS) -std=c++11

.PHONY: clean

clean:
	rm -rf $(ODIR) *~ core $(INCDIR)/*~ bin
