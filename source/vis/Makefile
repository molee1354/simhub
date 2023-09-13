CC = gcc
CFLAGS = -Wall -Wextra -fopenmp -g
SRCDIR = src
BINDIR = bin
OBJDIR = obj
DUMPSDIR = dumps
DUMPS = $(wildcard ./dump.*)
DEPS = require

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
TARGET = $(BINDIR)/main ./main

.PHONY: all clean deps

all: $(TARGET) | $(BINDIR)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

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

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) $(DUMPS); \
	rm -rf $(OBJDIR) $(BINDIR) $(DUMPSDIR)

deps:
	@while IFS= read -r line; do \
		TARG="$$(basename $${line})"; \
		rsync -a --exclude='main.c' "$$SIM_ROOT"/source/"$$line"src/* ./$(SRCDIR)/; \
		echo "...Copied dependency [$${TARG}] into ./$(notdir $(shell pwd))/$(SRCDIR)"; \
	done < $(DEPS)
