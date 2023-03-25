CC=cc
YACC=bison
LEX=flex
CFLAGS = $(shell pkg-config gtk+-2.0 --cflags)
LDFLAGS = $(shell pkg-config gtk+-2.0 --libs)

intwo: main.c parser.tab.o lex.yy.o layout.o engine.o utility.o drawing.o
	$(CC) $(CFLAGS) \
	main.c parser.tab.o lex.yy.o layout.o engine.o utility.o drawing.o \
	-g -o intwo $(LDFLAGS)

utility.o: utility.c utility.h types.h
	$(CC) $(CFLAGS) -g -c utility.c

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -g -c parser.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -g -c lex.yy.c

lex.yy.c: parser.l parser.tab.h
	$(LEX) parser.l

parser.tab.h: parser.y types.h
	$(YACC) -d parser.y

parser.tab.c: parser.y types.h utility.h
	$(YACC) -d parser.y

layout.o: layout.c layout.h types.h
	$(CC) $(CFLAGS) -g -c layout.c

engine.o: engine.c engine.h types.h utility.h
	$(CC) $(CFLAGS) -g -c engine.c

drawing.o: drawing.c drawing.h types.h
	$(CC) $(CFLAGS) -g -c drawing.c

.PHONY: clean

clean:
	rm -f intwo *.o lex.yy.c parser.tab.*
