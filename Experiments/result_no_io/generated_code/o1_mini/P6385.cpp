#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef long long ll;

const int MAX = 30005;
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE1 = 911;
const ll BASE2 = 3571;

ll hash1[MAX];
ll hash2_[MAX];
ll power1_[MAX];
ll power2_[MAX];

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    char S[MAX];
    scanf("%s", S+1);
    
    power1_[0] = 1;
    power2_[0] = 1;
    hash1[0] = 0;
    hash2_[0] = 0;
    for(int i=1;i<=n;i++){
        hash1[i] = (hash1[i-1] * BASE1 + (S[i]-'a'+1)) % MOD1;
        hash2_[i] = (hash2_[i-1] * BASE2 + (S[i]-'a'+1)) % MOD2;
        power1_[i] = (power1_[i-1] * BASE1) % MOD1;
        power2_[i] = (power2_[i-1] * BASE2) % MOD2;
    }
    
    // Function to get hash from l to r
    // Returns 1 if hashes match, 0 otherwise
    auto compare = [&](int l1, int r1, int l2, int r2) -> int {
        if(r1 < l1 || r2 < l2) return 0;
        ll cur1 = (hash1[r1] - (hash1[l1-1] * power1_[r1 - l1 +1]) % MOD1 + MOD1) % MOD1;
        ll cur2 = (hash2_[r1] - (hash2_[l1-1] * power2_[r1 - l1 +1]) % MOD2 + MOD2) % MOD2;
        ll cur3 = (hash1[r2] - (hash1[l2-1] * power1_[r2 - l2 +1]) % MOD1 + MOD1) % MOD1;
        ll cur4 = (hash2_[r2] - (hash2_[l2-1] * power2_[r2 - l2 +1]) % MOD2 + MOD2) % MOD2;
        return (cur1 == cur3) && (cur2 == cur4);
    };
    
    while(q--){
        int i, p, k;
        scanf("%d %d %d", &i, &p, &k);
        // Compute LCP between S[i..] and S[p..]
        int max_len = n - i +1;
        if(p > n) { // No match possible
            max_len =0;
        }
        if(p + max_len -1 > n){
            max_len = n - p +1;
        }
        if(max_len <0) max_len =0;
        int left =0, right = max_len;
        while(left < right){
            int mid = left + (right - left +1)/2;
            if(compare(i, i + mid -1, p, p + mid -1)){
                left = mid;
            }
            else{
                right = mid -1;
            }
        }
        int lcp = left;
        int j_max = i + lcp -1;
        if(j_max > n) j_max = n;
        int teleport_cost = n - j_max;
        int op_cost = (k >=i) ? (k - i) : (i -k);
        ll total_cost = (ll)teleport_cost + (ll)op_cost;
        printf("%lld\n", total_cost);
    }
    return 0;
}