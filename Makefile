# Nome do projeto
PROJ_NAME = ep-aed-1

# Coleta dos arquivos .c
C_SOURCE = $(wildcard src/*.c)

# Coleta dos arquivos .h
H_SOURCE = $(wildcard src/*.h)

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

%.o: src/%.c src/%.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: src/main.c src/$(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	@ rm src/*.o