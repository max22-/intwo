in (Interaction Nets), README.txt, March 23. 2000
Sylvain LIPPI, lippi@iml.univ-mrs.fr

Here are some informations about installing and using "in":
a graphical interpreter for the interaction nets.

WARNING: THIS IS NOT A USER MANUAL.

To install "in", you need:

- GTK 1.1.14 (or later)
- flex and bison (lex and yacc should be well too)
- gcc (cc should be well too)


COMPILE:

1) extract the .tar				>> tar xvf in.tar
2) get in the "in" repertory	>> cd in
3) compile the sources			>> make


RUN:

The executable is called "in" (comme Interaction Nets)
                        >> in examples/arith_unaire.in
                        OR
                        >> in

(two sample programs are given in the "examples" subdirectory)

USE:

The user interface is very simple and provide two windows:
 - "net" shows the current net during the execution
 - "next rule" shows the NEXT rule that will be applied

The "reduce" button reduce only one cut although "Reduce all"
reduce all cuts until an irreducible net is reached.

the syntax for describing an interaction system is
nearly the same as in the article "Interaction nets"
(POPL90) by Yves Lafont; differences are:

- brackets are replaced by parentheses
- rules are SEPARATED by commas
- we can specify a color for each symbol


KNOWN BUGS:

- no message if there is a syntax error.
- irreducible cuts are forbidden when using the "reduce all" button.

Thank you to contact me for any problem, question, suggestion or remark.


lippi@iml.univ-mrs.fr


