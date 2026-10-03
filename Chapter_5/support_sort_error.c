/* 5-17 排序程序所需的报错函数（K&R §5.11 示例实现）。 */

#include <stdio.h>
#include <stdlib.h>

void error(char* s) {
    fprintf(stderr, "%s\n", s);
    exit(2);
}
