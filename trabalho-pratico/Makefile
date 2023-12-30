CC = gcc
CFLAGS = -lncurses -O3 -march=native -mtune=native -I.

SRC_DIR = src
OBJ_DIR = obj
OBJ_DIR_T = $(OBJ_DIR)/Tools
OBJ_DIR_DS = $(OBJ_DIR)/DataStructures
OBJ_DIR_IO = $(OBJ_DIR)/IO
OBJ_DIR_C = $(OBJ_DIR)/Catalogs
OBJ_DIR_Q = $(OBJ_DIR)/Queries
OBJ_DIR_I = $(OBJ_DIR)/IO/Interactive
OBJ_DIR_TESTS = $(OBJ_DIR)/Tests



SRC_MAIN = $(SRC_DIR)/main.c
SRC_TESTS = $(wildcard $(SRC_DIR)/Tests/*.c)

SRCS_TOOLS = $(wildcard $(SRC_DIR)/Tools/*.c)
SRCS_DATA = $(wildcard $(SRC_DIR)/DataStructures/*.c)
SRCS_CATALOG = $(wildcard $(SRC_DIR)/Catalogs/*.c)
SRCS_QUERY = $(wildcard $(SRC_DIR)/Queries/*.c)
SRCS_IO = $(wildcard $(SRC_DIR)/IO/*.c)
SRCS_INTERACTIVE = $(wildcard $(SRC_DIR)/IO/Interactive/*.c)



OBJS_TOOLS = $(patsubst $(SRC_DIR)/Tools/%.c, $(OBJ_DIR_T)/%.o, $(SRCS_TOOLS)) 
OBJS_DATA = $(patsubst $(SRC_DIR)/DataStructures/%.c, $(OBJ_DIR_DS)/%.o, $(SRCS_DATA))
OBJS_CATALOG = $(patsubst $(SRC_DIR)/Catalogs/%.c, $(OBJ_DIR_C)/%.o, $(SRCS_CATALOG))
OBJS_QUERY = $(patsubst $(SRC_DIR)/Queries/%.c, $(OBJ_DIR_Q)/%.o, $(SRCS_QUERY))
OBJS_INTERACTIVE = $(patsubst $(SRC_DIR)/IO/Interactive/%.c, $(OBJ_DIR_I)/%.o, $(SRCS_INTERACTIVE))
OBJS_IO = $(patsubst $(SRC_DIR)/IO/%.c, $(OBJ_DIR_IO)/%.o, $(SRCS_IO))

OBJS_TESTS = $(patsubst $(SRC_DIR)/Tests/%.c, $(OBJ_DIR_TESTS)/%.o, $(SRC_TESTS))
OBJS_MAIN = $(patsubst $(SRC_DIR)/main.c, $(OBJ_DIR)/main.o, $(SRC_MAIN))

TARGET = programa-principal programa-testes

all: $(TARGET)

programa-principal: $(OBJS_MAIN) $(OBJS_TOOLS) $(OBJS_DATA) $(OBJS_CATALOG) $(OBJS_QUERY) $(OBJS_INTERACTIVE) $(OBJS_IO)
	$(CC) -o $@ $^ $(CFLAGS) -g

programa-testes: $(OBJS_TESTS) $(OBJS_TOOLS) $(OBJS_DATA) $(OBJS_CATALOG) $(OBJS_QUERY) $(OBJS_INTERACTIVE) $(OBJS_IO)
	$(CC) -o $@ $^ $(CFLAGS) -g
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_T)
	rm -rf $(OBJ_DIR_TESTS)
	rm -rf $(OBJ_DIR_DS)
	rm -rf $(OBJ_DIR_C)
	rm -rf $(OBJ_DIR_Q)
	rm -rf $(OBJ_DIR_I)
	rm -rf $(OBJ_DIR_IO)
	rm -rf $(OBJ_DIR)


$(OBJ_DIR_TESTS):
	mkdir -p $(OBJ_DIR_TESTS)

$(OBJ_DIR_T):
	mkdir -p $(OBJ_DIR_T)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_DS):
	mkdir -p $(OBJ_DIR_DS)

$(OBJ_DIR_C):
	mkdir -p $(OBJ_DIR_C)

$(OBJ_DIR_Q):
	mkdir -p $(OBJ_DIR_Q)

$(OBJ_DIR_I):
	mkdir -p $(OBJ_DIR_I)

$(OBJ_DIR_IO):
	mkdir -p $(OBJ_DIR_IO)





$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_TESTS)/%.o: $(SRC_DIR)/Tests/%.c | $(OBJ_DIR_TESTS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_T)/%.o: $(SRC_DIR)/Tools/%.c | $(OBJ_DIR_T)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_DS)/%.o: $(SRC_DIR)/DataStructures/%.c | $(OBJ_DIR_DS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_C)/%.o: $(SRC_DIR)/Catalogs/%.c | $(OBJ_DIR_C)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_Q)/%.o: $(SRC_DIR)/Queries/%.c | $(OBJ_DIR_Q)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_IO)/%.o: $(SRC_DIR)/IO/%.c | $(OBJ_DIR_IO)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR_I)/%.o: $(SRC_DIR)/IO/Interactive/%.c | $(OBJ_DIR_I)
	$(CC) -c -o $@ $< $(CFLAGS)

valgrind: $(TARGET)
	valgrind --leak-check=full -v ./$(TARGET) 2>&1 | tee valgrind_output.txt

clean:
	rm -rf $(TARGET) Resultados/*