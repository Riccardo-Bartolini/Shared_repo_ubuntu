CC = gcc
TARGET = main.elf
SRC = main.c function.c 
INCLUDE_PATH = ./include
CFLAGS = -I $(INCLUDE_PATH)
OBJ = $(SRC:.c=.o)

#first rule this will trigger $(TARGET) rule 
all: $(TARGET) cmp_size
#build the main.elf file
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

#Compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


cmp_size: 
	size $(TARGET:.elf=.o)
	size $(TARGET)


run: $(TARGET)
	./$(TARGET)



clean:
	rm -f $(OBJ) $(TARGET) 



