# CC := gcc  
# LIB_PATH := /usr/lib

# CC := /home/ngocanh/Desktop/make/toolchain/usr/bin/arm-buildroot-linux-gnueabi-gcc
# LIB_PATH := /home/ngocanh/Desktop/make/toolchain/usr/lib

NAME_PROJECT := agen_wan
PATH_OUTPUT := ./out

INC_DIRS := ./inc
SRC_DIRS := ./src

SRC_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
INC_FILES := $(foreach dir, $(INC_DIRS), $(wildcard $(dir)/*.h))
OBJ_FILES := $(patsubst $(SRC_DIRS)/%.c,$(PATH_OUTPUT)/%.o,$(SRC_FILES))

CFLAGS := $(foreach dir, $(INC_DIRS), -I$(dir))

all: $(PATH_OUTPUT)/${NAME_PROJECT}
	@echo $(OBJ_FILES)

$(PATH_OUTPUT)/${NAME_PROJECT}: $(OBJ_FILES)
	@echo "Linking $@"
	@mkdir -p $(PATH_OUTPUT)
	LD_LIBRARY_PATH=$(LIB_PATH) $(CC) $^ -o $@ $(LDFLAGS)

$(PATH_OUTPUT)/%.o: $(SRC_DIRS)/%.c $(INC_FILES)
	@echo "Compiling $< to $@"
	@mkdir -p $(PATH_OUTPUT)
	$(CC) -c $< -o $@ $(CFLAGS)

run: $(PATH_OUTPUT)/${NAME_PROJECT}
	@echo "Running $<"
	LD_LIBRARY_PATH=$(LIB_PATH) ./$(PATH_OUTPUT)/${NAME_PROJECT}

clean:
	@echo "Cleaning up..."
	rm -rf $(PATH_OUTPUT)/*.o $(PATH_OUTPUT)/$(NAME_PROJECT)

# ==== Toolchain and paths ====

# CC := gcc  
# LIB_PATH := /usr/lib
# INCLUDE_PATH := /usr/include


# CC := /home/ngocanh/Desktop/make/toolchain/usr/bin/arm-buildroot-linux-gnueabi-gcc
# LIB_PATH := /home/ngocanh/Desktop/make/toolchain/usr/lib
# INCLUDE_PATH := /home/ngocanh/Desktop/make/toolchain/usr/include

# # ==== Project info ====
# NAME_PROJECT := agen_wan
# PATH_OUTPUT := ./out
# SRC_DIR := ./src
# INC_DIR := ./inc

# # ==== File discovery ====
# SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
# OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(PATH_OUTPUT)/%.o,$(SRC_FILES))

# # ==== Flags ====
# CFLAGS := -I$(INC_DIR) -I$(INCLUDE_PATH)
# LDFLAGS := -L$(LIB_PATH) -lcJSON

# # ==== Default target ====
# all: $(PATH_OUTPUT)/$(NAME_PROJECT)

# # ==== Link ====
# $(PATH_OUTPUT)/$(NAME_PROJECT): $(OBJ_FILES)
# 	@echo "Linking $@"
# 	@mkdir -p $(PATH_OUTPUT)
# 	$(CC) $^ -o $@ $(LDFLAGS)

# # ==== Compile ====
# $(PATH_OUTPUT)/%.o: $(SRC_DIR)/%.c
# 	@echo "Compiling $< -> $@"
# 	@mkdir -p $(PATH_OUTPUT)
# 	$(CC) -c $< -o $@ $(CFLAGS)

# # ==== Run binary (on local, for x86 test only) ====
# run: $(PATH_OUTPUT)/$(NAME_PROJECT)
# 	@echo "Running $(NAME_PROJECT)..."
# 	LD_LIBRARY_PATH=$(LIB_PATH) ./$(PATH_OUTPUT)/$(NAME_PROJECT)

# # ==== Clean ====
# clean:
# 	@echo "Cleaning..."
# 	rm -rf $(PATH_OUTPUT)/*.o $(PATH_OUTPUT)/$(NAME_PROJECT)
