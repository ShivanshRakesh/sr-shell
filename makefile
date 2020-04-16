MODULE_DIR = modules
INCLUDE_DIR = header_files
OBJECT_DIR = obj
CC = gcc 
CFLAGS = -Wall -I$(INCLUDE_DIR)

_DEPS = utils.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJECTS = command.o print_dialogues.o process.o prompt.o 
OBJECTS = $(patsubst %,$(OBJECT_DIR)/%,$(_OBJECTS))

sr-shell: $(OBJECTS) main.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJECT_DIR)main.o: main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJECT_DIR)/%.o: $(MODULE_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


.PHONY: clean

clean:
	rm -rf $(OBJECT_DIR)/*.o *~ core $(INCLUDE_DIR)/*~