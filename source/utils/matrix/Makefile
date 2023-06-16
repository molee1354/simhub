CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = src
TESTDIR = tests
BINDIR = bin

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SRC))
# TARGET = $(BINDIR)/main
TARGET = ./main $(BINDIR)/main

TEST_SRC = $(wildcard $(TESTDIR)/*.c)
TEST_OBJ = $(patsubst $(TESTDIR)/%.c,$(BINDIR)/%.o,$(TEST_SRC))
TEST_TARGET = $(BINDIR)/test

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(filter-out $(BINDIR)/main.o, $(OBJ)) | $(BINDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) $^ -o $@

$(BINDIR)/%.o: $(TESTDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)
