/**
 * 练习 5-9：用指针方式替代数组下标方式改写函数 day_of_year 和 month_day。
 * */

static char daytab[2][14] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    char* p;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    p = daytab[leap];
    while (--month) {
	day += *++p;
    }
    return day;
}

void month_day(int year, int yearday, int* pmonth, int* pday) {
    int leap;
    char* p;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    p = daytab[leap];
    while (yearday > *++p) {
	yearday -= *p;
    }
    *pmonth = p - *(daytab + leap);
    *pday = yearday;
}
