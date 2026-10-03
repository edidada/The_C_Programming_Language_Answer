/* 5-13 tail 程序所需的 getline（与 5-6 练习中的指针版实现一致）。 */

#include <stdio.h>

int getline(char* s, int lim) {
    int c;
    char* t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
	*s++ = c;
    }
    if (c == '\n') {
	*s++ = c;
    }
    *s = '\0';
    return s - t;
}
