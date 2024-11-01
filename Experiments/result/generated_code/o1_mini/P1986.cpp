#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Interval;

int compare(const void *p1, const void *p2) {
    Interval *i1 = (Interval*)p1;
    Interval *i2 = (Interval*)p2;
    if (i1->b != i2->b)
        return i1->b - i2->b;
    return i1->a - i2->a;
}

#define MAXN 30001
int BIT[MAXN];
int next_available_pos[MAXN];
int n, m;

int lowbit(int x) {
    return x & (-x);
}

void update(int idx) {
    while (idx <= n) {
        BIT[idx] += 1;
        idx += lowbit(idx);
    }
}

int query(int idx) {
    int res = 0;
    while (idx > 0) {
        res += BIT[idx];
        idx -= lowbit(idx);
    }
    return res;
}

int find_set(int x) {
    if (next_available_pos[x] != x)
        next_available_pos[x] = find_set(next_available_pos[x]);
    return next_available_pos[x];
}

int main(){
    scanf("%d %d", &n, &m);
    Interval intervals[m];
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &intervals[i].a, &intervals[i].b, &intervals[i].c);
    }
    qsort(intervals, m, sizeof(Interval), compare);
    for(int i=1;i<=n;i++) next_available_pos[i] = i;
    int microphone_count = 0;
    for(int i=0;i<m;i++){
        int a = intervals[i].a;
        int b = intervals[i].b;
        int c = intervals[i].c;
        int current = query(b) - query(a-1);
        if(current >= c) continue;
        int need = c - current;
        while(need >0){
            int pos = find_set(b);
            if(pos < a) break;
            update(pos);
            microphone_count++;
            next_available_pos[pos] = pos -1;
            need--;
        }
    }
    printf("%d\n", microphone_count);
    return 0;
}