UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CC := clang++
else
	CC := g++
endif

SRCDIR := src
LIBDIR := lib
BUILDDIR := build
TARGETDIR := bin
INSTALLBINDIR := /usr/local/bin
TARGET := bin/raspberry-pi-fpv-visor

# All CPP files
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -c

ifeq ($(UNAME_S),Linux)
	CFLAGS += -std=gnu++14 -O2 # -fPIC
else
	CFLAGS += -std=c++14 -stdlib=libc++ -O2
endif

LIB := -pthread $(shell pkg-config gtkmm-3.0 opencv --libs)
INC := -I include $(shell pkg-config gtkmm-3.0 opencv --cflags)

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	@echo " Installing...";
	@echo " cp $(TARGET) $(INSTALLBINDIR)"; cp $(TARGET) $(INSTALLBINDIR)

distclean:
	@echo " Un-Installing...";
	@echo " rm /usr/local/bin/CoralSeaServer"; rm /usr/local/bin/CoralSeaServer

.PHONY: clean
