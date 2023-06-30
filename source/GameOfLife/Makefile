CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = src
BINDIR = bin
OBJDIR = obj
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

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

run: $(TARGET) | $(BINDIR)
	$(TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) $(DUMPS)

deps:
	@while IFS= read -r line; do \
		TARG="$$(basename $${line})"; \
		rsync -a --exclude='main.c' ../source/"$$line"src/* ./$(SRCDIR)/; \
		echo "...Copied dependency [$${TARG}] into ./$(notdir $(shell pwd))/$(SRCDIR)"; \
	done < $(DEPS)
