CC = gcc
CFLAGS = -I. -Iinclude $(shell pkg-config --cflags glib-2.0) -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LIBS = $(shell pkg-config --libs glib-2.0)

SRC_DIR = src
OBJ_DIR = obj
OBJ_DIR_DS = $(OBJ_DIR)/DataStructures
OBJ_DIR_C = $(OBJ_DIR)/Catalogs

SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS_DATA = $(wildcard $(SRC_DIR)/DataStructures/*.c)
SRCS_CATALOG = $(wildcard $(SRC_DIR)/Catalogs/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS)) 
OBJS_DATA = $(patsubst $(SRC_DIR)/DataStructures/%.c, $(OBJ_DIR_DS)/%.o, $(SRCS_DATA))
OBJS_CATALOG = $(patsubst $(SRC_DIR)/Catalogs/%.c, $(OBJ_DIR_C)/%.o, $(SRCS_CATALOG))
TARGET = programa-principal

all: $(TARGET)

$(TARGET): $(OBJS) $(OBJS_DATA) $(OBJS_CATALOG)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) -g
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_DS)
	rm -rf $(OBJ_DIR_C)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_DS):
	mkdir -p $(OBJ_DIR_DS)

$(OBJ_DIR_C):
	mkdir -p $(OBJ_DIR_C)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_DS)/%.o: $(SRC_DIR)/DataStructures/%.c | $(OBJ_DIR_DS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_C)/%.o: $(SRC_DIR)/Catalogs/%.c | $(OBJ_DIR_C)
	$(CC) -c -o $@ $< $(CFLAGS)

valgrind: $(TARGET)
	valgrind --leak-check=full -v ./$(TARGET) 2>&1 | tee valgrind_output.txt

clean:
	rm -rf $(TARGET) Resultados/*