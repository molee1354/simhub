CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = src
BINDIR = bin
OBJDIR = obj
DEPS = deps

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
TARGET = $(BINDIR)/main ./main

.PHONY: all clean get_deps

all: $(TARGET) | $(BINDIR)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c get_deps | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

run: $(TARGET) | $(BINDIR)
	$(TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

get_deps:
	@while IFS= read -r line; do \
		echo "$$line"; \
		rsync -a --exclude='main.c' "$$line"src/* ./src/; \
	done < $(DEPS)
