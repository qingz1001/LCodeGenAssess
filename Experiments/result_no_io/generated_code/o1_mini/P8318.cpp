#include <stdio.h>
typedef unsigned long long ull;

struct Operation {
    int k;
    int x;
    int y;
} ops[200];

ull isqrt(ull x) {
    if(x ==0 || x ==1) return x;
    ull low =1, high =x, res=0;
    while(low <= high){
        ull mid = low + (high - low) /2;
        if(mid <= x / mid){
            res = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ull a[n+1];
    for(int i=1;i<=n;i++) scanf("%llu", &a[i]);
    for(int i=0;i<m;i++) scanf("%d %d %d", &ops[i].k, &ops[i].x, &ops[i].y);
    for(int i=m-1;i>=0;i--){
        int k = ops[i].k;
        int x = ops[i].x;
        int y = ops[i].y;
        if(k ==1){
            if(x == y){
                a[x] /=2;
            }
            else{
                a[x] -= a[y];
            }
        }
        else if(k ==2){
            if(x == y){
                a[x] = isqrt(a[x]);
            }
            else{
                a[x] /= a[y];
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%llu%c", a[i], i==n? '\n':' ');
    }
    return 0;
}