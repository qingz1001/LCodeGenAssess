#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to calculate the number of steps between prefix and prefix + 1
ll get_steps(ll N, ll prefix, ll next_prefix){
    ll steps = 0;
    while(prefix <= N){
        steps += (N < (next_prefix - 1)) ? (N - prefix + 1) : (next_prefix - prefix);
        prefix *= 10;
        next_prefix *= 10;
    }
    return steps;
}

// Function to get the rank of K in lex order from 1 to N
ll get_rank(ll N, ll K){
    ll rank = 1;
    ll prefix = 1;
    while(prefix != K){
        ll steps = get_steps(N, prefix, prefix + 1);
        if(prefix <= K && K < prefix + steps){
            prefix *= 10;
            rank += 1;
        }
        else{
            rank += steps;
            prefix +=1;
        }
    }
    return rank;
}

int main(){
    ll K, M;
    if(scanf("%lld %lld", &K, &M)!=2){
        return 0;
    }
    ll low = K, high = K + M * 10;
    ll result = 0;
    while(low <= high){
        ll mid = low + (high - low)/2;
        ll rank = get_rank(mid, K);
        if(rank == M){
            result = mid;
            high = mid -1;
        }
        else if(rank < M){
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    // Verify if the result is valid
    if(result !=0 && get_rank(result, K) == M){
        printf("%lld\n", result);
    }
    else{
        printf("0\n");
    }
    return 0;
}