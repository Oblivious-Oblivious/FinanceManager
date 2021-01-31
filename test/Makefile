ZZ = zircon
ZZFLAGS = -cfile

CC = clang
OPT = -march=native -O2
#VERSION = -std=c89
OUTPUT = a.out

#FLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
WARNINGS = -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-format-extra-args -Wno-return-type -Wno-void-pointer-to-int-cast -Wno-format
REMOVE_WARN =
HEADERS =
LIBS =

CCINPUT = run_all_specs.c

ZZDEPENDS = C_engine.zc \
			C_loader.zc \
			C_aggregator.zc \
			C_exporter.zc \
			M_read_handler.zc \
			M_write_handler.zc \
			M_date.zc \
			M_time.zc \
			M_bank_account.zc

all: compiler

compiler:
	cp ../src/*.zc ../src/env.zdb ./
	./$(ZZ) $(ZZFLAGS) $(ZZDEPENDS)
	$(CC) $(OPT) $(VERSION) $(HEADERS) $(FLAGS) $(WARNINGS) $(REMOVE_WARN) $(LIBS) -o $(OUTPUT) $(CCINPUT)
	rm ./*.zc
	@echo
	./$(OUTPUT)

clean:
	mv cSpec.h cSpec.hh
	rm -rf $(OUTPUT) Object.h ./*.zc ./*.h ./*.zdb ./*.txt
	mv cSpec.hh cSpec.h
