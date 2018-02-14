CC=gcc
CFLAGS=-Werror -Wall -O0 -g -lpthread
OBJ=main.o bathroom.o person.o
EXE=bathroomSim

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -lm -o bathroomSim
	echo "Compilation completed."
	
main.o: main.c
	$(CC) $(CFLAGS) -c *.h main.c -lm
	echo "main.o has been compiled."

bathroom.o: bathroom.c
	$(CC) $(CFLAGS) -c *.h bathroom.c -lm
	echo "bathroom.o has been compiled."
	
person.o: person.c
	$(CC) $(CFLAGS) -c *.h person.c -lm
	echo "bathroom.o has been compiled."

	
clean:
	rm -r $(EXE) $(OBJ)