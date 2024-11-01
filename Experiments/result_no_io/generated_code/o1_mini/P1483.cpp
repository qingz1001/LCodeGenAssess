#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000001

long long a_arr[MAX_N];
long long add_vals[MAX_N];

long long sum_add(long long j){
    long long sum = 0;
    long long sqrt_j = (long long)sqrt((double)j);
    for(long long i = 1; i <= sqrt_j; i++){
        if(j % i == 0){
            sum += add_vals[i];
            if(j / i != i){
                sum += add_vals[j/i];
            }
        }
    }
    return sum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, m;
    scanf("%lld %lld", &n, &m);
    for(long long i = 1; i <= n; i++){
        scanf("%lld", &a_arr[i]);
    }
    for(long long i = 0; i < m; i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            long long x, y;
            scanf("%lld %lld", &x, &y);
            add_vals[x] += y;
        }
        else if(type == 2){
            long long j;
            scanf("%lld", &j);
            long long res = a_arr[j] + sum_add(j);
            printf("%lld\n", res);
        }
    }
    return 0;
}