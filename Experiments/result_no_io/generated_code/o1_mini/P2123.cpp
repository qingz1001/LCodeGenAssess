#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll a;
    ll b;
} Minister;

int cmp(const void *p1, const void *p2){
    Minister m1 = *(Minister*)p1;
    Minister m2 = *(Minister*)p2;
    if(m1.b != m2.b){
        return (m2.b > m1.b) - (m2.b < m1.b);
    }
    if(m1.a != m2.a){
        return (m1.a > m2.a) - (m1.a < m2.a);
    }
    return 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        Minister *ministers = (Minister*)malloc(n * sizeof(Minister));
        for(int i=0;i<n;i++){
            scanf("%lld %lld", &ministers[i].a, &ministers[i].b);
        }
        qsort(ministers, n, sizeof(Minister), cmp);
        ll sum_a = 0;
        ll c_prev = 0;
        ll max_c = 0;
        for(int i=0;i<n;i++){
            sum_a += ministers[i].a;
            if(i == 0){
                c_prev = ministers[i].a + ministers[i].b;
            }
            else{
                if(sum_a > c_prev){
                    c_prev = sum_a + ministers[i].b;
                }
                else{
                    c_prev = c_prev + ministers[i].b;
                }
            }
            if(c_prev > max_c){
                max_c = c_prev;
            }
        }
        printf("%lld\n", max_c);
        free(ministers);
    }
    return 0;
}