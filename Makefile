#
# TODO: Add APPS for compiling executables from a different folder, skipping .o objects
# 

CC := clang++
CFLAGS := -std=c++1y -Wall
LIB := -L lib
INC := -I include

SRCDIR := src
BUILDDIR := build
TESTDIR := test
SRCEXT := cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TESTS := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))

OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJECTS := $(patsubst %,$(BUILDDIR)/%,$(TESTS:.$(SRCEXT)=.o))

$(BUILDDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Compiling main object: $@"
	@mkdir -p $(BUILDDIR)/$(SRCDIR)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@echo " Compiling test object: $@"
	@mkdir -p $(BUILDDIR)/$(TESTDIR)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<


bin/test: $(TESTOBJECTS) $(OBJECTS)
	@echo " Linking test executable..."
	@$(CC) $(CFLAGS) $(LIB) -o bin/test $^

test: bin/test
	@echo " Running tests..."
	@./bin/test

.PHONY: test

clean:
	@echo " Cleaning..."
	@rm -rf $(BUILDDIR) $(BINTESTDIR)
