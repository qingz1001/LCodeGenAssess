#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year, month, day, hour, minute;
} Time;

int is_leap(int year) {
    if(year % 400 == 0) return 1;
    if(year % 100 == 0) return 0;
    if(year % 4 == 0) return 1;
    return 0;
}

int days_in_month(int year, int month) {
    int dim[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(month ==2 && is_leap(year)) return 29;
    return dim[month-1];
}

long long parse_time(Time t){
    long long days=0;
    for(int y=0;y<t.year;y++){
        days += is_leap(y) ? 366 : 365;
    }
    for(int m=1;m<t.month;m++){
        days += days_in_month(t.year, m);
    }
    days += t.day -1;
    long long minutes = days * 1440LL + t.hour * 60 + t.minute;
    return minutes;
}

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int N;
    scanf("%d", &N);
    int *times = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &times[i]);
    char s1[20], s2[20];
    scanf("%s %s", s1, s2);
    Time t1, t2;
    sscanf(s1, "%4d-%2d-%2d-%2d:%2d", &t1.year, &t1.month, &t1.day, &t1.hour, &t1.minute);
    sscanf(s2, "%4d-%2d-%2d-%2d:%2d", &t2.year, &t2.month, &t2.day, &t2.hour, &t2.minute);
    long long tm1 = parse_time(t1);
    long long tm2 = parse_time(t2);
    long long total = tm2 - tm1;
    if(total <0) total =0;
    qsort(times, N, sizeof(int), cmp);
    int count=0;
    long long sum=0;
    for(int i=0;i<N;i++){
        if(sum + times[i] > total) break;
        sum += times[i];
        count++;
    }
    printf("%d\n", count);
    free(times);
    return 0;
}