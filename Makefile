
PICDIR=/opt/pic32mx

CC=pic32-gcc
CXX=pic32-g++
UPDLOADER=ldpic32

TARGET=micro
SRCDIR=src
INCLUDEDIR=include
BINDIR=bin

SRCDIR=src
INCLUDEDIR=include
BINDIR=bin

CFLAGS=-O3 -I/opt/pic32mx/include -I$(INCLUDEDIR) -mprocessor=32MX795F512H

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%, $(BINDIR)/%, $(SOURCES:.c=.o))

TARGET:=$(BINDIR)/$(TARGET)

.PHONY: all upload clean format

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(PICDIR)/bin/pic32-bin2hex $(TARGET).elf
	

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -c -o $@ $< 

$(TARGET).elf: $(OBJECTS)
	$(PICDIR)/bin/pic32-ld  $(OBJECTS) -o $(TARGET).elf \
		-L$(PICDIR)/lib -L$(PICDIR)/lib/gcc/pic32mx/3.4.4 -ldetpic32 \
		-lgcc -lm -lc -lsupc++ -lxcpp -Map $(TARGET).map

upload: $(TARGET).hex
	ldpic32 -w $(TARGET).hex

clean:
	@- $(RM) $(BINDIR) -R

format:
	clang-format -style=file -i $(SRCDIR)/*.c
	clang-format -style=file -i $(INCLUDEDIR)/*.h