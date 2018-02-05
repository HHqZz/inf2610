bin_PROGRAMS = hello

hello_SOURCES = hello.c

EXTRA_DIST = minisys.asm

all-local: minisys

minisys.o: minisys.asm
	$(NASM) $(NAFLAGS) -g -o $@ $<

minisys: minisys.o
	ld -o $@ $<

