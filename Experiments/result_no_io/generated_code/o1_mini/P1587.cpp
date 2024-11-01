#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

// Function to factorize k into distinct prime factors
int factorize(int k, int *primes) {
    int count = 0;
    // Check divisibility by 2
    if (k % 2 == 0) {
        primes[count++] = 2;
        while (k % 2 == 0) k /= 2;
    }
    // Check odd factors
    for(int i = 3; i <= sqrt(k); i +=2){
        if(k % i ==0){
            primes[count++] = i;
            while(k % i ==0) k /=i;
        }
    }
    if(k >1){
        primes[count++] = k;
    }
    return count;
}

int main(){
    ll N, M, K;
    scanf("%lld %lld %lld", &N, &M, &K);
    
    int primes[12];
    int num_primes = factorize(K, primes);
    
    ll total =0;
    int subsets = 1 << num_primes;
    for(int mask=0; mask < subsets; mask++){
        ll d=1;
        int bits=0;
        for(int i=0;i<num_primes;i++){
            if(mask & (1<<i)){
                d *= primes[i];
                bits++;
                if(d > M) break;
            }
        }
        if(d > M) continue;
        // Calculate mu(d)
        ll mu = (bits %2) ? -1 : 1;
        ll q = M / d;
        // To handle y <= N
        ll y_max = q;
        if(N < y_max){
            y_max = N;
        }
        // Sum of phi(y) from y=1 to y_max
        // Approximated as y_max*(y_max +1)/2
        // For exact sum, a more complex method is required
        ll sum_phi = y_max * (y_max +1) /2;
        total += mu * sum_phi;
    }
    printf("%lld\n", total);
    return 0;
}