#
# TODO: Add APPS for compiling executables from a different folder, skipping .o objects
# 

CC := clang++
SRCDIR := src
BUILDDIR := build
TESTDIR := test
BINTESTDIR := bin/test

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

TESTS := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
BINTESTS := $(patsubst $(TESTDIR)/%,$(BINTESTDIR)/%,$(TESTS:.$(SRCEXT)=.test))

CFLAGS := -std=c++1y -Wall
LIB := -L lib
INC := -I include

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Compiling..."
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BINTESTDIR)/%.test: $(TESTDIR)/%.$(SRCEXT) $(OBJECTS)
	@echo " Compiling test $@ "
	@mkdir -p $(BINTESTDIR)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

test: $(BINTESTS)
	@$(foreach test, $(BINTESTS), ./$(test))

.PHONY: test

clean:
	@echo " Cleaning..."
	@rm -rf $(BUILDDIR) $(BINTESTDIR)
