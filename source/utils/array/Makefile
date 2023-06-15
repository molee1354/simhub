CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = src
TESTDIR = tests
BINDIR = bin
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
# TARGET = $(BINDIR)/main
TARGET = ./main $(BINDIR)/main

TEST_SRC = $(wildcard $(TESTDIR)/*.c)
TEST_OBJ = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TEST_SRC))
TEST_TARGET = $(BINDIR)/test

.PHONY: all test clean

all: $(TARGET) | $(BINDIR)

$(TARGET): $(OBJ) | $(OBJDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET) | $(BINDIR)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(filter-out $(OBJDIR)/main.o, $(OBJ)) | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) $^ -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)
