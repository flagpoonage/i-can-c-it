SRCDIR := src
SRCFILES := $(addprefix $(SRCDIR)/,mem.c sb.c file_reader.c main.c)

icancit: $(SRCFILES)
	mkdir -p out
	cc $(SRCFILES) -o out/icancit

run: icancit
	./out/icancit js.lisp

mem: icancit
	valgrind --track-origins=yes out/icancit