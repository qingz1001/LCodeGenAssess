#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef long long ll;
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE1 = 911382629;
const ll BASE2 = 3571428571;

// Precompute powers
ll pow1[30005];
ll pow2[30005];

int main(){
    int T;
    pow1[0] = 1;
    pow2[0] = 1;
    for(int i=1;i<=30000;i++){
        pow1[i] = (pow1[i-1] * BASE1) % MOD1;
        pow2[i] = (pow2[i-1] * BASE2) % MOD2;
    }
    scanf("%d", &T);
    while(T--){
        char S[30005];
        scanf("%s", S);
        int n = strlen(S);
        // Check if all characters are same
        int same = 1;
        for(int i=1;i<n;i++) if(S[i]!=S[0]) {same=0; break;}
        if(same){
            ll count=0;
            for(int l=4;l<=n;l+=2){
                int Q = l /2;
                if(Q <2) continue;
                ll splits = Q -1;
                count += (ll)(n - l +1) * splits;
            }
            printf("%lld\n", count);
            continue;
        }
        // Compute prefix hashes
        ll hash1[30005], hash2[30005];
        hash1[0] = 0;
        hash2[0] = 0;
        for(int i=0;i<n;i++){
            hash1[i+1] = (hash1[i] * BASE1 + (S[i]-'a'+1)) % MOD1;
            hash2[i+1] = (hash2[i] * BASE2 + (S[i]-'a'+1)) % MOD2;
        }
        ll total =0;
        for(int l=4;l<=n;l+=2){
            int Q = l /2;
            for(int a=1;a<Q;a++){
                int b = Q -a;
                if(2*a + 2*b != l){
                    continue;
                }
                // Iterate over all possible starting positions
                for(int i=0;i + l <=n;i++){
                    // Compare A and A
                    ll hashA1 = (hash1[i+a] - hash1[i] * pow1[a]) % MOD1;
                    if(hashA1 <0) hashA1 += MOD1;
                    ll hashA2 = (hash1[i+2*a] - hash1[i+a] * pow1[a]) % MOD1;
                    if(hashA2 <0) hashA2 += MOD1;
                    if(hashA1 != hashA2) continue;
                    ll hashB1 = (hash2[i +2*a +b] - hash2[i +2*a] * pow2[b]) % MOD2;
                    if(hashB1 <0) hashB1 += MOD2;
                    ll hashB2 = (hash2[i +2*a +2*b] - hash2[i +2*a +b] * pow2[b]) % MOD2;
                    if(hashB2 <0) hashB2 += MOD2;
                    if(hashB1 != hashB2) continue;
                    total++;
                }
            }
        }
        printf("%lld\n", total);
    }
}