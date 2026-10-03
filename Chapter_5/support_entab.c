/* 5-11 练习中的 entab/tabpos 实现，供 5-12 链接复用。 */

#include <stdio.h>

#define MAXLINE 100
#define YES     1
#define NO      0

int tabpos(int pos, char* tab);
void entab(char* tab);

int tabpos(int pos, char* tab) {
    if (pos > MAXLINE) {
	return YES;
    }else {
	return tab[pos];
    }
}

void entab(char* tab) {
    int c, pos;
    int nb = 0;
    int nt = 0;

    for (pos = 1; (c = getchar()) != EOF; pos++) {
	if (c == ' ') {
	    if (tabpos(pos, tab) == NO) {
		++nb;
	    }else {
		nb = 0;
		++nt;
	    }
	}else {
	    for (; nt > 0; nt--) {
		putchar('\t');
	    }
	    if (c == '\t') {
		nb = 0;
	    }else {
		for (; nb > 0; nb--) {
		    putchar(' ');
		}
	    }
	    putchar(c);
	    if (c == '\n') {
		pos = 0;
	    }else if (c == '\t') {
		while (tabpos(pos, tab) != YES) {
		    ++pos;
		}
	    }
	}
    }
}
