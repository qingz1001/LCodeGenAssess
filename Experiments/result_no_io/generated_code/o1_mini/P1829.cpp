#include <stdio.h>
#include <stdlib.h>

#define MOD 20101009
#define MAX_NM 10000000

unsigned int phi_arr[MAX_NM + 1];

int main(){
    unsigned int n, m;
    if(scanf("%u %u", &n, &m)!=2){
        return 1;
    }
    unsigned int min_nm = n < m ? n : m;
    for(unsigned int i=0; i<=min_nm; i++) {
        phi_arr[i] = i;
    }
    for(unsigned int p=2; p<=min_nm; p++){
        if(phi_arr[p] == p){
            for(unsigned int k=p; k<=min_nm; k += p){
                phi_arr[k] -= phi_arr[k] / p;
            }
        }
    }
    unsigned long long sum = 0;
    for(unsigned int d=1; d<=min_nm; d++){
        unsigned int t1 = n / d;
        unsigned int t2 = m / d;
        unsigned long long term = ((unsigned long long)phi_arr[d] * t1) % MOD;
        term = (term * t2) % MOD;
        sum = (sum + term) % MOD;
    }
    printf("%llu\n", sum);
    return 0;
}