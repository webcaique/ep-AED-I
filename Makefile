# Nome do projeto
PROJ_NAME = ep-aed-1

# Coleta dos arquivos .c
C_SOURCE = $(wildcard *.c)

# Coleta dos arquivos .h
H_SOURCE = $(wildcard *.h)

# Armazenamento dos objetos
OBJ = $(C_SOURCE:.c=.o)

# Compilador
CC = gcc

# Flags para o compilador
CC_FLAGS = -c        \
           -W        \
		   -Wall     \
		   -pedantic \
		
# Compilação e links dos objetos com os arquivos c

all: $(PROJ_NAME) clean

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	@ rm *.o