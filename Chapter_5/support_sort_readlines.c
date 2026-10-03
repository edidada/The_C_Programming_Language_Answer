/* 第 5 章排序练习（5-14 ~ 5-17）共用的辅助函数，按 K&R 书 §5.11 的示例实现。
 * 提供: readlines, error；供缺少这些书中示例代码的练习文件链接。 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

static int readline_(char* line, int max) {
    int c, i;

    for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
	line[i] = c;
    }
    if (c == '\n') {
	line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

int readlines(char* lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = readline_(line, MAXLEN)) > 0) {
	if (nlines >= maxlines || (p = (char*) malloc(len)) == NULL) {
	    return -1;
	}
	line[len - 1] = '\0'; /* 去掉换行符 */
	strcpy(p, line);
	lineptr[nlines++] = p;
    }
    return nlines;
}
