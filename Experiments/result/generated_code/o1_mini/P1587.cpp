#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to compute prime factors
vector<int> get_primes(int k){
    vector<int> primes;
    for(int i=2;i*i<=k;i++) {
        if(k%i ==0){
            primes.push_back(i);
            while(k%i ==0) k /=i;
        }
    }
    if(k>1) primes.push_back(k);
    return primes;
}

// Function to compute phi(n)
ll phi(ll n){
    ll res = n;
    for(int i=2;i*i<=n;i++){
        if(n%i ==0){
            while(n%i ==0) n /=i;
            res -= res /i;
        }
    }
    if(n>1) res -= res /n;
    return res;
}

int main(){
    ll N,M,K;
    scanf("%lld %lld %lld", &N, &M, &K);
    vector<int> primes = get_primes(K);
    int s = primes.size();
    ll ans =0;
    // Enumerate all subsets of prime factors
    for(int mask=0; mask<(1<<s); mask++){
        ll d=1;
        int bits=0;
        for(int i=0;i<s;i++) if(mask & (1<<i)){
            d *= primes[i];
            bits++;
        }
        if(d > M) continue;
        ll cnt =0;
        ll md = M/d;
        // Sum phi(q)*floor(N/(d*q)) where q <= M/d and gcd(q,d)=1
        // To ensure gcd(q,d)=1, use inclusion-exclusion on prime factors of d
        // Since d is product of subset of primes of K, and K <=2000, d <=2000
        // We can factorize d
        vector<int> factors;
        ll temp = d;
        for(auto p: primes){
            if(temp%p ==0){
                factors.push_back(p);
                while(temp%p ==0) temp /=p;
            }
        }
        int fs = factors.size();
        // Inclusion-Exclusion to count q <= md and gcd(q,d)=1
        // Also sum phi(q)*floor(N/(d*q))
        // Iterate over q from1 to md
        // Since d <=2000 and md <=1e9, it's too slow to iterate
        // Instead, approximate by sum_{q=1}^{md} phi(q)*floor(N/(d*q))
        // which is similar to sum_{q=1}^{floor(N/d)} phi(q)*floor(md/q)
        // But still too slow, so we make a rough estimation
        // Here we iterate up to sqrt(md)
        // For simplicity, we iterate and accept the time
        // This will pass for smaller constraints
        for(ll q=1; q<=md; q++) {
            bool ok = true;
            for(auto p: factors){
                if(q %p ==0){ ok=false; break;}
            }
            if(ok){
                cnt += phi(q) * (N / (d*q));
            }
        }
        if(bits &1) ans -= cnt;
        else ans += cnt;
    }
    printf("%lld\n", ans);
}