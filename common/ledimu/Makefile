include make/clang.mk

BUILD_DIR = ../../build
OBJ_DIR = $(BUILD_DIR)/objs
SRC = $(wildcard src/[a-zA-Z]*.cpp)
OBJ = $(subst src/,$(OBJ_DIR)/, $(subst .cpp,.o, $(SRC)))
TARGET = $(BUILD_DIR)/ledimu.a

CFLAGS += -DSD_EMU_H -g

all: $(TARGET) test

$(TARGET): $(OBJ_DIR) $(BUILD_DIR) $(OBJ)
	ar rcs $(TARGET) $(OBJ)

test: $(TARGET)
	(cd test && make)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR)/%.o: src/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) *.gch
