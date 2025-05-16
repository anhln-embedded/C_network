
export STAGING_DIR
CC := /home/ngocanh/Desktop/toolchain-arm_cortex-a7_gcc-5.2.0_musl-1.1.16_eabi/bin/arm-openwrt-linux-muslgnueabi-gcc
LIB_PATH := /home/ngocanh/Desktop/toolchain-arm_cortex-a7_gcc-5.2.0_musl-1.1.16_eabi/lib

# CC := gcc  
# LIB_PATH := /usr/lib


# Name of the file to be generated
NAME_PROJECT := agen_wan
PATH_OUTPUT := ./out


INC_DIRS := ./inc
SRC_DIRS := ./src

SRC_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
INC_FILES := $(foreach dir, $(INC_DIRS), $(wildcard $(dir)/*.h))
OBJ_FILES := $(patsubst $(SRC_DIRS)/%.c,$(PATH_OUTPUT)/%.o,$(SRC_FILES))


CFLAGS := -I$(INC_DIRS)
LDFLAGS := -lm -luci

all: $(PATH_OUTPUT)/${NAME_PROJECT}
	@echo $(OBJ_FILES)

$(PATH_OUTPUT)/${NAME_PROJECT}: $(OBJ_FILES)
	@echo "Linking $@"
	@mkdir -p $(PATH_OUTPUT)
	LDFLAGS=$(LIB_PATH) $(CC) $^ -o $@  ${LDFLAGS} 

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