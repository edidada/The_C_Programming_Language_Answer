/* 第 5 章排序练习共用输出函数：order 非 0 时按逆序打印（对应 DECR 选项）。 */

#include <stdio.h>

void writelines(char* lineptr[], int nlines, int order) {
    int i;

    if (order) {
	for (i = nlines - 1; i >= 0; --i) {
	    printf("%s\n", lineptr[i]);
	}
    }else {
	for (i = 0; i < nlines; i++) {
	    printf("%s\n", lineptr[i]);
	}
    }
}
