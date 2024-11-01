#include <stdio.h>

unsigned int popcount(unsigned long long x) {
    unsigned int count = 0;
    while(x){
        count += x & 1;
        x >>=1;
    }
    return count;
}

int main(){
    unsigned long long N, K;
    scanf("%llu %llu", &N, &K);
    unsigned long long min_x = 0;
    unsigned int initial_pop = popcount(N);
    if(initial_pop <= K){
        min_x =0;
    }
    else{
        min_x = ~0ULL;
        for(int bit=0; bit<64; bit++){
            unsigned long long p = 1ULL << bit;
            if(p ==0) continue;
            unsigned long long rem = N % (p <<1);
            unsigned long long x = (p <<1) - rem;
            if(rem ==0){
                x =0;
            }
            unsigned long long candidate = N + x;
            unsigned int pc = popcount(candidate);
            if(pc <= K && x < min_x){
                min_x =x;
            }
        }
    }
    printf("%llu\n", min_x);
    return 0;
}