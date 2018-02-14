CC=gcc
CFLAGS=-I. -Werror -Wall -O0 -g
OBJ=main.o person.o monitor.o
EXE=bathroomSim

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o bathroomSim
	echo "Compilation completed."
	
main.o: main.c
	$(CC) $(CFLAGS) main.c
	echo "main.o has been compiled."

bathroom.o: bathroom.c
	$(CC) $(CFLAGS) bathroom.c
	echo "bathroom.o has been compiled."
	
person.o: person.c
	$(CC) $(CFLAGS) person.c
	echo "person.c has been compiled."
	
clean:
	rm -r $(EXE) $(OBJ)