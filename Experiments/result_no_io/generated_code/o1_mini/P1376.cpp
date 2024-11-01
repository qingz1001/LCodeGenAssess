#include <stdio.h>
#include <limits.h>

typedef long long ll;

int main(){
    int N, S;
    scanf("%d %d", &N, &S);
    ll total = 0;
    ll min_val = LLONG_MAX;
    for(int i=1;i<=N;i++){
        int C_i, Y_i;
        scanf("%d %d", &C_i, &Y_i);
        ll current = (ll)C_i - (ll)S * i;
        if(current < min_val){
            min_val = current;
        }
        ll cost = (ll)S * i + min_val;
        total += (ll)Y_i * cost;
    }
    printf("%lld\n", total);
    return 0;
}