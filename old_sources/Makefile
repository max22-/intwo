CC=cc
YACC=bison
LEX=flex

intwo: main.c parser.tab.o lex.yy.o layout.o engine.o utility.o drawing.o
	$(CC) `gtk-config --cflags` `gtk-config --libs` \
	main.c parser.tab.o lex.yy.o layout.o engine.o utility.o drawing.o \
	-g -o intwo

utility.o: utility.c utility.h types.h
	$(CC) `gtk-config --cflags` -g -c utility.c

parser.tab.o: parser.tab.c
	$(CC) `gtk-config --cflags` -g -c parser.tab.c

lex.yy.o: lex.yy.c
	$(CC) `gtk-config --cflags` -g -c lex.yy.c

lex.yy.c: parser.l parser.tab.h
	$(LEX) parser.l

parser.tab.h: parser.y types.h
	$(YACC) -d parser.y

parser.tab.c: parser.y types.h utility.h
	$(YACC) -d parser.y

layout.o: layout.c layout.h types.h
	$(CC) `gtk-config --cflags` -g -c layout.c

engine.o: engine.c engine.h types.h utility.h
	$(CC) `gtk-config --cflags` -g -c engine.c

drawing.o: drawing.c drawing.h types.h
	$(CC) `gtk-config --cflags` -g -c drawing.c
