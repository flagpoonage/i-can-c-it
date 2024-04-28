SRCDIR := src
SHELL := /usr/bin/fish
SRCFILES := $(addprefix $(SRCDIR)/,mem.c sb.c file_lexer.c file_parser.c file_reader.c main.c)

out/icancit: $(SRCFILES)
	mkdir -p out
	cc $(SRCFILES) -g -o out/icancit

.PHONY: run mem time

run: out/icancit
	./out/icancit testfiles/js.lisp

mem: out/icancit
	valgrind --track-origins=yes out/icancit testfiles/js.lisp

time: out/icancit
	time ./out/icancit testfiles/js.lisp
