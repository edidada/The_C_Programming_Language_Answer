/* K&R 附录 B 的排序实现，签名与第 5 章各练习声明的
 * void qsort(char* v[], int left, int right, int (*comp)(void*, void*)) 一致。
 * 若不链接此文件，练习程序会误链接 C 库签名的 qsort，导致排序实际未执行。 */

#include <string.h>

void swap(char* v[], int i, int j) {
    char* temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(char* v[], int left, int right, int (*comp)(void*, void*)) {
    int i, last;

    if (left >= right) {
	return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
	if ((*comp)(v[i], v[left]) < 0) {
	    swap(v, ++last, i);
	}
    }
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
}
