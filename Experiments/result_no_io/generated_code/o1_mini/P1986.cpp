#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Interval;

int compare(const void *x, const void *y){
    Interval *a = (Interval *)x;
    Interval *b_ = (Interval *)y;
    if(a->b != b_->b) return a->b - b_->b;
    return a->a - b_->a;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Interval intervals[m];
    for(int i=0;i<m;i++) scanf("%d %d %d", &intervals[i].a, &intervals[i].b, &intervals[i].c);
    qsort(intervals, m, sizeof(Interval), compare);
    // Fenwick Tree
    int BITree[n+2];
    for(int i=0;i<=n;i++) BITree[i]=0;
    auto update = [&](int idx) {
        while(idx <= n){
            BITree[idx]++;
            idx += idx & (-idx);
        }
    };
    auto query = [&](int idx) -> int {
        int res=0;
        while(idx >0){
            res += BITree[idx];
            idx -= idx & (-idx);
        }
        return res;
    };
    int placed =0;
    int placed_flags[n+1];
    for(int i=1;i<=n;i++) placed_flags[i]=0;
    for(int i=0;i<m;i++){
        int a = intervals[i].a;
        int b = intervals[i].b;
        int c = intervals[i].c;
        int current = query(b) - query(a-1);
        if(current >= c) continue;
        int need = c - current;
        for(int pos = b; pos >=a && need >0; pos--){
            if(!placed_flags[pos]){
                placed_flags[pos]=1;
                update(pos);
                placed++;
                need--;
            }
        }
    }
    printf("%d\n", placed);
    return 0;
}