CC = gcc
INCLUDE = $(shell pkg-config --cflags sdl2)
CFLAGS = -Wall -Wextra -g -fopenmp $(INCLUDE)
LDFLAGS = $(shell pkg-config --libs sdl2)
SRCDIR = src
BINDIR = bin
OBJDIR = obj
DUMPSDIR = dumps
DUMPS = $(wildcard ./dump.*)
DEPS = require

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
TARGET = $(BINDIR)/main

.PHONY: all run clean deps cleandeps

all: $(TARGET) | $(BINDIR)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR): $(DUMPSDIR)
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(DUMPSDIR):
	mkdir -p $(DUMPSDIR)

run: $(TARGET) | $(BINDIR)
	$(TARGET)

save: $(TARGET) | $(BINDIR)
	$(TARGET) save

clean: cleandeps
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) $(DUMPS); \
	rm -rf $(OBJDIR) $(BINDIR) $(DUMPSDIR)

deps:
	@while IFS= read -r line; do \
		TARG="$$(basename $${line})"; \
		for f in "$${SIM_ROOT}"/source/"$${line}"src/*; \
		do \
			file="$$(basename $${f})"; \
			if [[ $${file} == "main.c" ]]; \
			then \
				continue; \
			fi; \
			if [[ -n $$(echo $${file} | grep "_commonincl.h") ]]; \
			then \
				cp $$f ./$(SRCDIR)/$${file}; \
				continue; \
			fi; \
			cp $$f ./$(SRCDIR)/$${TARG}_$${file}; \
		done; \
		echo "...Copied dependency [$${TARG}] into ./$(notdir $(shell pwd))/$(SRCDIR)"; \
	done < $(DEPS)

cleandeps:
	@while IFS= read -r line; do \
		TARG="$$(basename $${line})"; \
		rm -f ./$(SRCDIR)/$${TARG}* ; \
		echo "...Cleaned dependency [$${TARG}] from ./$(notdir $(shell pwd))/$(SRCDIR)"; \
	done < $(DEPS)
