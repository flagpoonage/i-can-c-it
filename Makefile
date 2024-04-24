SRCDIR := src
SRCFILES := $(addprefix $(SRCDIR)/,mem.c sb.c file_reader.c main.c)

out/icancit: $(SRCFILES)
	mkdir -p out
	cc $(SRCFILES) -o out/icancit

.PHONY: run mem

run: out/icancit
	./out/icancit testfiles/js.lisp

mem: out/icancit
	valgrind --track-origins=yes out/icancit testfiles/js.lisp
