/* 第 4 章逆波兰计算器练习共用的 getop / push / pop / getch / ungetch，
 * 与 4-4 练习中的实现一致，供 4-6、5-10、6-x 等含 main 的练习文件链接。 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int c, i;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    i = 0;
    if (!isdigit(c) && c != '.' && c != '-') {
	return c;
    }
    if (c == '-') {
	if (isdigit(c = getch()) || c == '.') {
	    s[++i] = c;
	}else {
	    if (c != EOF) {
		ungetch(c);
	    }
	    return '-';
	}
    }
    if (isdigit(c)) {
	while (isdigit(s[++i] = c = getch()));
    }
    if (c == '.') {
	while (isdigit(s[++i] = c = getch()));
    }
    s[i] = '\0';
    if (c != EOF) {
	ungetch(c);
    }
    return NUMBER;
}

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) {
	val[sp++] = f;
    }else {
	printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    if (sp > 0) {
	return val[--sp];
    }else {
	printf("error: stack empty\n");
	return 0.0;
    }
}

char buf[BUFSIZE];
int  bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
	printf("ungetch: too many characters\n");
    }else {
	buf[bufp++] = c;
    }
}
