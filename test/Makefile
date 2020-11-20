NAME = Lab3

ZZ = zircon
ZZFLAGS = -cfile
ZZOUTPUT = $(NAME).h

CC = clang
OPT = -march=native -O2
#VERSION = -std=c89
OUTPUT = a.out

#FLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
WARNINGS = -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-format-extra-args -Wno-return-type
REMOVE_WARN =
HEADERS =
LIBS =

ZZINPUT = $(NAME).zc
CCINPUT = $(NAME).spec.c

all: compiler

compiler:
	./$(ZZ) $(ZZFLAGS) $(ZZINPUT)
	$(CC) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) -o $(OUTPUT) $(CCINPUT)
	@echo
	./$(OUTPUT)

clean:
	rm -rf $(OUTPUT) $(ZZOUTPUT) Object.h
