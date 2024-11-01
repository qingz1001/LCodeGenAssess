#include <stdio.h>
#include <limits.h>

typedef long long ll;

int main(){
    int N;
    ll S;
    scanf("%d %lld", &N, &S);
    ll C, Y;
    ll min_cost = LLONG_MAX;
    ll total_cost = 0;
    for(int i=1;i<=N;i++){
        scanf("%lld %lld", &C, &Y);
        ll current = C - S * i;
        if(current < min_cost){
            min_cost = current;
        }
        total_cost += Y * (min_cost + S * i);
    }
    printf("%lld\n", total_cost);
    return 0;
}