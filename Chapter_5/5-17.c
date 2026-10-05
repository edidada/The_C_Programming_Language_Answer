/**
 * 练习 5-17：增加字段处理功能，以使得排序程序可以根据行内的不同字段进行排序，每个字段按照一个单独的选项集合进行排序。（在对英文原书索引进行排序时，索引条目使用了 -df 选项，而对页码排序时使用了 -n 选项。
 * */

#include <stdio.h>
#include <ctype.h>

#define NUMERIC 1
#define DECR    2
#define FOLD    4
#define DIR     8
#define LINES   100

int charcmp(char*, char*);
void error(char*);
int numcmp(char*, char*);
void readargs(int argc, char* argv[]);
int readlines(char* lineptr[], int maxlines);
void qsort(char* v[], int left, int right, int (*comp)(void*, void*));
void writelines(char* lineptr[], int nlines, int order);
void substr(char* s, char* str);

char option = 0;
int pos1 = 0;
int pos2 = 0;

int main(int argc, char* argv[]) {
    char* lineptr[LINES];
    int nlines;
    int rc = 0;

    readargs(argc, argv);
    if ((nlines = readlines(lineptr, LINES)) > 0) {
	if (option & NUMERIC) {
	    qsort((void**)lineptr, 0, nlines - 1, (int (*)(void*, void*))numcmp);
	}else {
	    qsort((void**)lineptr, 0, nlines - 1, (int (*)(void*, void*))charcmp);
	}
	writelines(lineptr, nlines, option & DECR);
    }else {
	printf("input too big to sort \n");
	rc = -1;
    }
    return rc;
}

void readargs(int argc, char* argv[]) {
    int c = 0;
    int atoi(char*);

    while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')) {
	if (c == '-' && !isdigit(*(argv[0] + 1))) {
	    while (c == *++argv[0]) {
		switch (c) {
		    case 'd':
			option |= DIR;
			break;
		    case 'f':
			option |= FOLD;
			break;
		    case 'n':
			option |= NUMERIC;
			break;
		    case 'r':
			option |= DECR;
			break;
		    default:
			printf("sort: illegal option %c\n", c);
			error("Usage: sort -dfnr [+pos1] [-pos2]");
			break;
		}
	    }
	}else if (c == '-') {
	    pos2 = atoi(argv[0] + 1);
	}else if ((pos1 = atoi(argv[0] + 1)) < 0) {
	    error("Usage: sort -dfnr [+pos1] [-pos2]");
	}
    }
    if (argc || pos1 > pos2) {
	error("Usage: sort -dfnr [+pos1] [-pos2]");
    }
}

#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAXSTR 100

int numcmp(char* s1, char* s2) {
    double v1, v2;
    char str[MAXSTR];

    substr(s1, str);
    v1 = atof(str);
    substr(s2, str);
    v2 = atof(str);
    if (v1 < v2) {
	return -1;
    }else if (v1 > v2) {
	return 1;
    }else {
	return 0;
    }
}

#define FOLD 4
#define DIR  8

int charcmp(char* s, char* t) {
    char a, b;
    int i, j, endpos;
    extern char option;
    extern int pos1, pos2;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DIR) ? 1 : 0;

    i = j = pos1;
    if (pos2 > 0) {
	endpos = pos2;
    }else if ((endpos = strlen(s)) > strlen(t)) {
	endpos = strlen(t);
    }
    do {
	if (dir) {
	    while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0') {
		i++;
	    }
	    while (j < endpos && !isalnum(t[j]) && t[j] != ' ' && t[j] != '\0') {
		j++;
	    }
	}
	if (i < endpos && j < endpos) {
	    a = fold ? tolower(s[i]) : s[i];
	    i++;
	    b = fold ? tolower(t[j]) : t[j];
	    j++;
	    if (a == b && a == '\0') {
		return 0;
	    }
	}
    }while (a == b && i < endpos && j < endpos);
    return a - b;
}

#include <string.h>

void error(char*);

void substr(char* s, char* str) {
    int i, j, len;
    extern int pos1, pos2;

    len = strlen(s);
    if (pos2 > 0 && len > pos2) {
	len = pos2;
    }else if (pos2 > 0 && len < pos2) {
	error("substr: string too short");
    }
    for (j = 0, i = pos1; i < len; i++, j++) {
	str[j] = s[i];
    }
    str[j] = '\0';
}
