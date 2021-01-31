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

INPUT = Z_main.zc \
		V_client.zc \
		\
		C_engine.zc \
		C_aggregator.zc \
		C_exporter.zc \
		C_loader.zc \
		\
		M_date.zc \
		M_time.zc \
		M_bank_account.zc \
		M_read_handler.zc \
		M_write_handler.zc

all: default

default:
	cd src && ./$(CC) $(MODE) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT)

run:
	cd src && ./$(CC) run $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT)

build:
	cd src && ./$(CC) build $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT)

d:
	cd src && ./$(CC) -cfile $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) $(INPUT)

clean:
	cd src && rm -rf $(OUTPUT) Object.h __zircon_main.c *.h
