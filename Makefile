.PHONY: all clean
CC = g++
SRC_DIR = src/utils
FLAGS = -O2 
LDFLAGS = -fPIC -shared
OBJ_DIR = obj
LIB_DIR = libs
BIN_DIR = bin

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cc $(SRC_DIR)/sam.hpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $< -c $(FLAGS) -o $@

$(LIB_DIR)/libsam.so: $(SRC_DIR)/sam.cc $(SRC_DIR)/sam.hpp
	@mkdir -p $(LIB_DIR)
	$(CC) $< $(FLAGS) $(LDFLAGS) -o $@

$(BIN_DIR)/analyzer: $(OBJ_DIR)/main.o $(LIB_DIR)/libsam.so
	@mkdir -p $(BIN_DIR)
	$(CC) $< $(FLAGS) -L $(LIB_DIR) -lsam -o $@

all: $(BIN_DIR)/analyzer
ld_path:
	export LD_LIBRARY_PATH=./$(LIB_DIR)
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)