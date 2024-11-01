#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

// Function to compute (base^exp) % mod
ll powmod_func(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            res = (__int128(res) * base) % mod;
        }
        base = (__int128(base) * base) % mod;
        exp >>=1;
    }
    return res;
}

int main(){
    ll a, b, k;
    while(scanf("%lld %lld %lld", &a, &b, &k) ==3){
        ll mod =1;
        for(int i=0;i<k;i++) mod *=10;
        ll ans=0;
        if(a > b){
            ans = powmod_func(2, a + b -1, mod);
        }
        else{
            // Compute C(b, 0 to a-1) mod mod
            ll *cum_sum = (ll*)calloc(a +1, sizeof(ll));
            if(a >0){
                ll Cb =1 % mod;
                cum_sum[0] =1 % mod;
                for(ll B=1; B <a && B <=b; B++){
                    // C(b, B) = C(b, B-1) * (b - B +1) / B
                    __int128 numerator = (__int128(Cb) * (b - B +1));
                    Cb = numerator / B;
                    Cb %= mod;
                    cum_sum[B] = (cum_sum[B-1] + Cb) % mod;
                }
                // If B <a but B >b, C(b,B}=0
                for(ll B=a -1; B <a -1 && B <=b; B++);
                for(ll B= (a -1)>=0 ? a -1 : 0; B <a && B <=b; B++){
                    // C(b, B)=0 if B >b
                    if(B >b){
                        cum_sum[B] = cum_sum[B-1];
                    }
                }
                // If a >b +1e4 but a <=b+10000, C(b,B}=0 for B >b
                for(ll B = b +1; B <a; B++){
                    cum_sum[B] = cum_sum[B-1];
                }
            }
            // Compute sum over A=0 to a: C(a,A) * sum_{B=0}^{A-1} C(b,B}
            ll sum =0;
            ll Ca =1 % mod;
            for(ll A=0; A <=a; A++){
                ll sumB;
                if(A ==0){
                    sumB =0;
                }
                else{
                    if(A -1 <=a && A -1 >=0){
                        sumB = cum_sum[A -1];
                    }
                    else{
                        sumB = cum_sum[a];
                    }
                }
                sum = (sum + (__int128(Ca) * sumB) % mod) % mod;
                // Update Ca for next A
                if(A <a){
                    // Ca = Ca * (a - A) / (A +1)
                    __int128 numerator = (__int128(Ca) * (a - A));
                    Ca = numerator / (A +1);
                    Ca %= mod;
                }
            }
            ans = sum;
            free(cum_sum);
        }
        // Prepare the answer with leading zeros
        char buffer[20];
        sprintf(buffer, "%lld", ans);
        int len = strlen(buffer);
        if(len <k){
            for(int i=0;i<k - len;i++) printf("0");
        }
        printf("%s\n", buffer);
    }
    return 0;
}