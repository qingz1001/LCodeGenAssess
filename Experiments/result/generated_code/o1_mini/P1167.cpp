#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int is_leap(int year){
    if(year % 400 == 0) return 1;
    if(year % 100 == 0) return 0;
    if(year % 4 == 0) return 1;
    return 0;
}

int month_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

ll get_minutes(int yyyy, int mm, int dd, int hh, int Mi){
    ll total_days = 0;
    for(int y=0; y < yyyy; y++){
        total_days += is_leap(y) ? 366 : 365;
    }
    for(int m=1; m < mm; m++){
        if(m == 2 && is_leap(yyyy)) total_days += 29;
        else total_days += month_days[m-1];
    }
    total_days += dd -1;
    ll total_minutes = total_days * 24 * 60 + hh * 60 + Mi;
    return total_minutes;
}

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int N;
    scanf("%d", &N);
    int* times = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &times[i]);
    char s1[20], s2[20];
    scanf("%s %s", s1, s2);
    int y1, m1, d1, h1, mi1;
    sscanf(s1, "%d-%d-%d-%d:%d", &y1, &m1, &d1, &h1, &mi1);
    int y2, m2, d2, h2, mi2;
    sscanf(s2, "%d-%d-%d-%d:%d", &y2, &m2, &d2, &h2, &mi2);
    ll t1 = get_minutes(y1, m1, d1, h1, mi1);
    ll t2 = get_minutes(y2, m2, d2, h2, mi2);
    ll diff = t2 - t1;
    if(diff < 0) diff = 0;
    qsort(times, N, sizeof(int), cmp);
    int count = 0;
    ll sum = 0;
    for(int i=0;i<N;i++){
        if(sum + times[i] > diff) break;
        sum += times[i];
        count++;
    }
    printf("%d", count);
    free(times);
    return 0;
}