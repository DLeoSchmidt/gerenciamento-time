CC = gcc
TARGET = gerenciamentodotime
SOURCE = ./src
OBJETOS = ./objs

all: obj
	$(CC) $(OBJETOS)/nomes.o $(OBJETOS)/utils.o $(OBJETOS)/menus.o $(OBJETOS)/arquivos.o $(OBJETOS)/cadastros.o $(OBJETOS)/relatorios.o $(OBJETOS)/buscas.o $(OBJETOS)/main.o -o $(TARGET)

obj:
	$(CC) -c $(SOURCE)/nomes.c -o $(OBJETOS)/nomes.o
	$(CC) -c $(SOURCE)/utils.c -o $(OBJETOS)/utils.o
	$(CC) -c $(SOURCE)/menus.c -o $(OBJETOS)/menus.o
	$(CC) -c $(SOURCE)/arquivos.c -o $(OBJETOS)/arquivos.o
	$(CC) -c $(SOURCE)/cadastros.c -o $(OBJETOS)/cadastros.o
	$(CC) -c $(SOURCE)/relatorios.c -o $(OBJETOS)/relatorios.o
	$(CC) -c $(SOURCE)/buscas.c -o $(OBJETOS)/buscas.o
	$(CC) -c main.c -o $(OBJETOS)/main.o


clear:
	rm $(OBJETOS)/*.o
	rm $(TARGET)