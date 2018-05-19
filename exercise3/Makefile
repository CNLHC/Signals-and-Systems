CC=gcc

BUILD_DIR=./build/
CUSTOM_DEPS = main.c

CFLAGS=-g -I. -I$(COMMON_DIR)

COMMON_DIR = ../common/
COMMON_DEPS = canvas.c plot.c functype.c calculus.c
COMMON_DEPS_ABS = $(addprefix $(COMMON_DIR), $(COMMON_DEPS))
COMMON_DEPS_HEAD = $(addsuffix .h,$(basename $(COMMON_DEPS)) )

DEPS = $(CUSTOM_DEPS) $(COMMON_DEPS_ABS)
OBJS = $(addsuffix .o,$(basename $(DEPS)))


main:$(addprefix $(BUILD_DIR), $(notdir $(OBJS)))
	gcc $^ $(CFLAGS) -o $@

$(BUILD_DIR)%.o: $(addprefix $(COMMON_DIR), %.c) 
	$(CC) -c  $< $(CFLAGS) -o $@

$(BUILD_DIR)%.o: %.c
	$(CC) -c  $< $(CFLAGS) -o $@



build::
	mkdir  $(BUILD_DIR)
.PHONY: test,clean

test:
	@echo $(DEPS)
	@echo $(addprefix $(BUILD_DIR),$(notdir $(OBJS)))
clean:
	del exercise.exe
	cd $(BUILD_DIR) &&\
	del *.o

