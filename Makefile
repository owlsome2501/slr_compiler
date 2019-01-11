CC := g++
SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGETDIR := .

EXECUTABLE := pl0_parser
TARGET := $(TARGETDIR)/$(EXECUTABLE)

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -std=c++11
INC := -I $(INCDIR)

LEXSRCEXT := l
LEXSOURCES := $(shell find $(SRCDIR) -type f -name *.$(LEXSRCEXT))
LEXTARGET := $(BUILDDIR)/lex.yy.cc
LEXOBJECTS := $(BUILDDIR)/lex.yy.o

$(TARGET): $(LEXOBJECTS) $(OBJECTS)
	$(CC) $^ -o $(TARGET)

$(LEXTARGET): $(LEXSOURCES)
	@mkdir -p $(BUILDDIR)
	flex++ --outfile=$(LEXTARGET) $(LEXSOURCES)

$(LEXOBJECTS): $(LEXTARGET)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY:clean
clean:
	rm -r $(BUILDDIR) $(TARGET)
