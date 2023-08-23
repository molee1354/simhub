CC = clang
CFLAGS = -Wall -Wextra -g
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Find all "*.c" files within src/frontend/ and its subdirectories
SRC = $(wildcard $(SRCDIR)/frontend/**/*.c) $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
TARGET = $(BINDIR)/hwin

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile each "*.c" file to its corresponding location in OBJDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directory structure in OBJDIR
$(OBJDIR):
	@mkdir -p $(shell find $(SRCDIR)/frontend -type d | sed 's/$(SRCDIR)/$(OBJDIR)/')

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(TARGET) $(OBJDIR) $(BINDIR)

