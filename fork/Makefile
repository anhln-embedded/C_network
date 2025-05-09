# CC := /home/ngocanh/Desktop/make/toolchain/arm/usr/bin/arm-buildroot-linux-gnueabi-gcc
# LIB_PATH := /home/ngocanh/Desktop/make/toolchain/arm/usr/lib

CC := /home/ngocanh/Desktop/make/toolchain/misp/output/host/usr/bin/mips-buildroot-linux-uclibc-gcc
LIB_PATH := /home/ngocanh/Desktop/make/toolchain/misp/output/host/usr/lib

# CC := gcc  
# LIB_PATH := /usr/lib

# Name of the file to be generated
NAME_PROJECT := fork
PATH_OUTPUT := ./out


INC_DIRS := ./inc
SRC_DIRS := ./src

SRC_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
INC_FILES := $(foreach dir, $(INC_DIRS), $(wildcard $(dir)/*.h))
OBJ_FILES := $(patsubst $(SRC_DIRS)/%.c,$(PATH_OUTPUT)/%.o,$(SRC_FILES))


CFLAGS := -I$(INC_DIRS)

all: $(PATH_OUTPUT)/${NAME_PROJECT}
	@echo $(OBJ_FILES)

$(PATH_OUTPUT)/${NAME_PROJECT}: $(OBJ_FILES)
	@echo "Linking $@"
	@mkdir -p $(PATH_OUTPUT)
	LD_LIBRARY_PATH=$(LIB_PATH) $(CC) $^ -o $@

$(PATH_OUTPUT)/%.o: $(SRC_DIRS)/%.c $(INC_FILES)
	@echo "Compiling $< to $@"
	@mkdir -p $(PATH_OUTPUT)
	LD_LIBRARY_PATH=$(LIB_PATH) $(CC) -c $< -o $@ $(CFLAGS)

run: $(PATH_OUTPUT)/${NAME_PROJECT}
	@echo "Running $<"
	@LD_LIBRARY_PATH=$(LIB_PATH) ./$<

clean:
	@echo "Cleaning up..."
	rm -rf $(PATH_OUTPUT)/*