/* 第 8 章练习的报错辅助函数（K&R 书 Chapter 8 示例风格的可变参数 error）。 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "stdin: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(2);
}
