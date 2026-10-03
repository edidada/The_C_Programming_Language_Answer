#include <stdio.h>

/**
 * 练习 3-2: 编写一个函数 escape(s,t), 将字符串 t 复制到字符串 s 中，并在复制过程中将换行符、制表符等不可显示字符分别转换 \n、\t 等相应的可显示的转移字符序列。要求使用 switch 语句。再编写一个具有相反功能的函数，在复制过程中将转义字符序列转换为实际字符。
 * */

void escape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i) {
	switch(t[i]) {
	    case '\n':
		s[j++] = '\\';
		s[j++] = 'n';
		break;
	    case '\t':
		s[j++] = '\\';
		s[j++] = 't';
		break;
	    default:
		s[j++] = t[i];
		break;
	}
    }
    s[j] = '\0';
}

void unescape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i) {
	if (t[i] != '\\') { 
	    s[j++] = t[i];
	}else {
	    switch(t[++i]) {
		case 'n':
		    s[j++] = '\n';
		    break;
		case 't':
		    s[j++] = '\t';
		    break;
		default:
		    s[j++] = '\\';
		    s[j++] = t[i];
		    break;
	    }
	}
    }
    s[j] = '\0';
}
