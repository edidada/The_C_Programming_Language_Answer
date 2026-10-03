/**
 * 练习 5-18：修改 dcl 程序，使它能够处理输入中的错误。
 * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

void dcl(void);
void dirdcl(void);
void errmsg(char*);
int gettoken(void);

extern int tokentype;
extern char token[];
extern char name[];
extern char out[];
extern int prevtoken;

void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*'; ) {
	ns++;
    }
    dirdcl();
    while (ns-- > 0) {
	strcat(out, " pointer to");
    }
}

void dirdcl(void) {
    int type;
    
    if (tokentype == '(') {
	dcl();
	if (tokentype != ')') {
	    errmsg("error: missing )\n");
	}
    }else if (tokentype == NAME) {
	strcpy(name, token);
    }else {
	errmsg("error: expected name or (dcl)\n");
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
	if (type == PARENS) {
	    strcat(out, " function returning");
	}else {
	    strcat(out, " array");
	    strcat(out, token);
	    strcat(out, " of");
	}
    }
}

void errmsg(char* msg) {
    printf("%s", msg);
    prevtoken = YES;
}

#include <ctype.h>
#include <string.h>

int prevtoken = NO;

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char* p = token;

    if (prevtoken == YES) {
	prevtoken = NO;
	return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t');
    if (c == '(') {
	if ((c = getch()) == ')') {
	    strcpy(token, "()");
	    return tokentype = PARENS;
	}else {
	    ungetch(c);
	    return tokentype = '(';
	}
    }else if (c == '[') {
	for (*p++ = c; (*p++ = getch()) != ']';);
	*p = '\0';
	return tokentype = BRACKETS;
    }else if (isalpha(c)) {
	for (*p++ = c; isalpha(c = getch()); *p++ = c);
	*p = '\0';
	ungetch(c);
	return tokentype = NAME;
    }else {
	return tokentype = c;
    }
}
