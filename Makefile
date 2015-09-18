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
INCDIR := include

SRCEXT := cpp
HEADEXT := hpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TESTS := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
HEADERS := $(shell find $(INCDIR) -type f -name *.$(HEADEXT))

OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJECTS := $(patsubst %,$(BUILDDIR)/%,$(TESTS:.$(SRCEXT)=.o))

COMPILE := $(CC) $(CFLAGS) $(INC) -c 
MAKEDEPS := $(COMPILE) -MMD
LINKEDIT := $(CC) $(CFLAGS) $(LIB)

$(BUILDDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Compiling main object: $@"
	@mkdir -p $(BUILDDIR)/$(SRCDIR)
	@$(MAKEDEPS) -o $@ $<
	@$(COMPILE) -o $@ $<

$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@echo " Compiling test object: $@"
	@mkdir -p $(BUILDDIR)/$(TESTDIR)
	@$(MAKEDEPS) -o $@ $<
	@$(COMPILE) -o $@ $<

bin/test: $(TESTOBJECTS) $(OBJECTS)
	@echo " Linking test executable..."
	@$(LINKEDIT) -o $@ $^

test: bin/test
	@echo " Running tests..."
	@./bin/test

.PHONY: test

clean:
	@echo " Cleaning..."
	@rm -rf $(BUILDDIR) $(BINTESTDIR)

# Look at http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/ for further info on make deps and those included files
-include $(wildcard $(BUILDDIR)/**/*.d)
