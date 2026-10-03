/* 第 6 章 #define 处理器练习（6-6）所需的散列表辅助函数，
 * 按 K&R §6.6 示例实现：hash / install / lookup / undef，共用同一张表。 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist* next;
    char* name;
    char* defn;
};

static struct nlist* hashtab[HASHSIZE];

struct nlist* lookup(char*);

unsigned hash(char* s) {
    unsigned retval;

    for (retval = 0; *s != '\0'; s++) {
	retval = 31 * retval + (unsigned char) *s;
    }
    return retval % HASHSIZE;
}

struct nlist* install(char* name, char* defn) {
    struct nlist* np;
    int hashval;

    if ((np = lookup(name)) == NULL) {
	np = (struct nlist*) malloc(sizeof(*np));
	if (np == NULL || (np -> name = strdup(name)) == NULL) {
	    return NULL;
	}
	hashval = hash(name);
	np -> next = hashtab[hashval];
	hashtab[hashval] = np;
    }else {
	free((void*) np -> defn);
    }
    if ((np -> defn = strdup(defn)) == NULL) {
	return NULL;
    }
    return np;
}

struct nlist* lookup(char* s) {
    struct nlist* np;

    for (np = hashtab[hash(s)]; np != NULL; np = np -> next) {
	if (strcmp(s, np -> name) == 0) {
	    return np;
	}
    }
    return NULL;
}

void undef(char* s) {
    int h;
    struct nlist* prev, *np;

    prev = NULL;
    h = hash(s);
    for (np = hashtab[h]; np != NULL; np = np -> next) {
	if (strcmp(s, np -> name) == 0) {
	    break;
	}
	prev = np;
    }
    if (np != NULL) {
	if (prev == NULL) {
	    hashtab[h] = np -> next;
	}else {
	    prev -> next = np -> next;
	}
	free((void*) np -> name);
	free((void*) np -> defn);
	free((void*) np);
    }
}
