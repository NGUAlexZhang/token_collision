.PHONY: all clean
CC = g++
SRC_DIR = src/utils
FLAGS = -O2 
LDFLAGS = -fPIC -shared
OBJ_DIR = obj
LIB_DIR = libs
BIN_DIR = bin

$(OBJ_DIR)/frequency.o: src/frequency.cc $(SRC_DIR)/sam.hpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $< -c $(FLAGS) -o $@

$(OBJ_DIR)/pinyin.o: src/pinyin.cc $(SRC_DIR)/acam.hpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $< -c $(FLAGS) -o $@

$(LIB_DIR)/libsam.so: $(SRC_DIR)/sam.cc $(SRC_DIR)/sam.hpp
	@mkdir -p $(LIB_DIR)
	$(CC) $< $(FLAGS) $(LDFLAGS) -o $@

$(LIB_DIR)/libacam.so: $(SRC_DIR)/acam.cc $(SRC_DIR)/acam.hpp
	@mkdir -p $(LIB_DIR)
	$(CC) $< $(FLAGS) $(LDFLAGS) -o $@

$(BIN_DIR)/frequency: $(OBJ_DIR)/frequency.o $(LIB_DIR)/libsam.so
	@mkdir -p $(BIN_DIR)
	$(CC) $< $(FLAGS) -L $(LIB_DIR) -lsam -o $@

$(BIN_DIR)/pinyin: $(OBJ_DIR)/pinyin.o $(LIB_DIR)/libacam.so
	@mkdir -p $(BIN_DIR)
	$(CC) $< $(FLAGS) -L $(LIB_DIR) -lacam -o $@

all: $(BIN_DIR)/frequency $(BIN_DIR)/pinyin
ld_path:
	export LD_LIBRARY_PATH=./$(LIB_DIR)
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)