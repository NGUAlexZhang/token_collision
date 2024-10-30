.PHONY: all clean install
CC = g++
SRC_DIR = src/utils
INCLUDE_DIR = include
FLAGS = -O2 -I./include
LDFLAGS = -fPIC -shared
OBJ_DIR = obj
LIB_DIR = libs
BIN_DIR = bin

$(OBJ_DIR)/frequency.o: src/frequency.cc $(INCLUDE_DIR)/sam.hpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $< -c $(FLAGS) -o $@

$(OBJ_DIR)/pinyin.o: src/pinyin.cc $(INCLUDE_DIR)/acam.hpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $< -c $(FLAGS) -o $@

$(LIB_DIR)/libsam.so: $(SRC_DIR)/sam.cc $(INCLUDE_DIR)/sam.hpp
	@mkdir -p $(LIB_DIR)
	$(CC) $< $(FLAGS) $(LDFLAGS) -o $@

$(LIB_DIR)/libacam.so: $(SRC_DIR)/acam.cc $(INCLUDE_DIR)/acam.hpp
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

install:
	cp $(BIN_DIR)/frequency /usr/local/bin
	cp $(BIN_DIR)/pinyin /usr/local/bin
	cp $(LIB_DIR)/*.so /usr/lib
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)