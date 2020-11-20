NAME =
MODE = run
#MODE = build
#MODE = spec
#MODE = init

CC = zircon
OPT =
VERSION =
OUTPUT = a.out

FLAGS =
WARNINGS =
HEADERS =
LIBS =

INPUT = main.zc I_client.zc I_engine.zc

all: default

default:
	cd src && ./$(CC) $(MODE) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT)

run:
	cd src && ./$(CC) run $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT)

#build:
#	cd src && ./$(CC) build $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT) -o $(OUTPUT)

clean:
	cd src && rm -rf $(OUTPUT) Object.h __zircon_main.c
