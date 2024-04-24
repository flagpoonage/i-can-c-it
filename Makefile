stringb: mem.c sb.c file_reader.c stringb.c
	mkdir -p out
	cc mem.c sb.c file_reader.c stringb.c -o out/stringb

run: stringb
	./out/stringb js.lisp
