#include <stdio.h>
#include <stdlib.h> /* atof */
#include <ctype.h>

#define MAX_OP 100 /* max operand size or sign */
#define NUMBER '0' /* signal that a number has been found */
#define MAXVAL 100 /* max stack depth val */
#define BUFSIZE 100

int getop(char *s);
void push(double);
double pop(void);
void ungetch(int);
int getch(void);

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0; /* the next free position in buf (index) */

/* enter character (maybe, returned to the stream) */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* returns character to the input stream */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else {
		buf[bufp] = c;
		bufp++;
	}
}

static int sp = 0; /* next free position on stack */
static double val[MAXVAL]; /* operand stack */

/* push: pushes number f into the operand stack*/
void push(double f)
{
	if (sp < MAXVAL) {
		val[sp] = f;
		sp++;
	} else
		fprintf(stderr, "error: stack full, can't push %g\n", f);
}

/* pop: pops and returns a top number from the stack */
double pop(void)
{
	if (sp > 0) {
		sp--;
		return val[sp];
	} else {
		fprintf(stderr, "error: stack empty\n");
		return 0.0;
	}
}

/* getop: pops the next operand or operation sign */
int getop(char *s)
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		; /* skip spaces and tabulations */
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			; /* accumulation of integer part */

	if(c == '.')
		while (isdigit(s[++i] = c = getch()))
			; /* accumulation of float part */

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int main()
{
	int type;
	double op2;
	char s[MAX_OP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				fprintf(stderr, "error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
