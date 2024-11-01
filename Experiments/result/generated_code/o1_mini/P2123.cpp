#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll a;
    ll b;
} Minister;

int cmp(const void *x, const void *y){
    Minister *m1 = (Minister*)x;
    Minister *m2 = (Minister*)y;
    if(m2->b > m1->b) return 1;
    else if(m2->b < m1->b) return -1;
    else return 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        Minister *m = (Minister*)malloc(n * sizeof(Minister));
        for(int i=0;i<n;i++) scanf("%lld %lld", &m[i].a, &m[i].b);
        qsort(m, n, sizeof(Minister), cmp);
        ll S = 0;
        ll c_prev = 0;
        ll max_c = 0;
        for(int i=0;i<n;i++){
            S += m[i].a;
            if(i ==0){
                c_prev = m[i].a + m[i].b;
            }
            else{
                if(S > c_prev){
                    c_prev = S + m[i].b;
                }
                else{
                    c_prev = c_prev + m[i].b;
                }
            }
            if(c_prev > max_c) max_c = c_prev;
        }
        printf("%lld\n", max_c);
        free(m);
    }
}