CC=gcc
COMMON_DIR = ../common/
COMMON_DEPS = canvas.c plot.c functype.c calculus.c
COMMON_DEPS_HEAD = $(addsuffix .h,$(basename $(COMMON_DEPS)) )
COMMON_OBJS = $(addsuffix .o,$(basename $(COMMON_DEPS)) )

MAIN = main.c
OBJ = main.o


BUILD_DIR=./build/

CFLAGS=-g -I. -I$(COMMON_DIR)


$(BUILD_DIR)%.o: $(addprefix $(COMMON_DIR), %.c) 
	$(CC) -c  $< $(CFLAGS) -o $@

$(BUILD_DIR)%.o: %.c
	$(CC) -c  $< $(CFLAGS) -o  $@

exercise:$(addprefix $(BUILD_DIR), $(OBJ) $(COMMON_OBJS)) 
	gcc $^ $(CFLAGS) -o $@

build::
	mkdir  $(BUILD_DIR)
.PHONY: test,clean
test:
	@echo $(CC)
	@echo 
clean:
	del exercise.exe
	cd $(BUILD_DIR) &&\
	del *.o

