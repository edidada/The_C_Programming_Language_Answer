/* 第 5 章排序练习共用的数值比较函数（K&R §5.11 示例实现）。 */

#include <stdlib.h>

int numcmp(char* s1, char* s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
	return -1;
    }else if (v1 > v2) {
	return 1;
    }
    return 0;
}
