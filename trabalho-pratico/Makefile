CC = gcc
CFLAGS = -I. -Iinclude $(shell pkg-config --cflags glib-2.0) -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LIBS = $(shell pkg-config --libs glib-2.0)

SRC_DIR = src
OBJ_DIR = obj

MAIN_SRCS = $(SRC_DIR)/main.c
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRCS))
TARGET = programa-principal

all: $(TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) -g
	rm -rf $(OBJ_DIR) valgrind_output.txt
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind: $(TARGET)
	valgrind --leak-check=full -v ./$(TARGET) 2>&1 | tee valgrind_output.txt

clean:
	rm -rf $(TARGET) valgrind_output.txt
	rm -rf $(TARGET) Resultados/*
