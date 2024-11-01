#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

const int MAX = 100005;
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE = 911382629;

ll power1[MAX];
ll power2[MAX];
ll hash1[MAX];
ll hash2[MAX];

int cmp_ll(const void* a, const void* b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char s[MAX];
    scanf("%s", s);
    
    power1[0] = power2[0] = 1;
    for(int i=1;i<=n;i++){
        power1[i] = (power1[i-1] * BASE) % MOD1;
        power2[i] = (power2[i-1] * BASE) % MOD2;
    }
    
    hash1[0] = hash2[0] = 0;
    for(int i=1;i<=n;i++){
        hash1[i] = (hash1[i-1] * BASE + (s[i-1]-'a'+1)) % MOD1;
        hash2[i] = (hash2[i-1] * BASE + (s[i-1]-'a'+1)) % MOD2;
    }
    
    while(m--){
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int L = 1, R = (b - a +1) < (d - c +1) ? (b - a +1) : (d - c +1);
        int res = 0;
        while(L <= R){
            int mid = (L + R) /2;
            int cnt1 = b - a - mid +2;
            int cnt2 = d - c - mid +2;
            if(cnt1 <=0 || cnt2 <=0){
                R = mid -1;
                continue;
            }
            ll *hA = (ll*)malloc(sizeof(ll)*cnt1);
            ll *hB = (ll*)malloc(sizeof(ll)*cnt2);
            for(int i=0;i<cnt1;i++){
                int start = a + i;
                ll cur1 = (hash1[start + mid -1] - (hash1[start-1] * power1[mid])%MOD1 + MOD1) % MOD1;
                ll cur2 = (hash2[start + mid -1] - (hash2[start-1] * power2[mid])%MOD2 + MOD2) % MOD2;
                hA[i] = cur1 * MOD2 + cur2;
            }
            for(int i=0;i<cnt2;i++){
                int start = c + i;
                ll cur1 = (hash1[start + mid -1] - (hash1[start-1] * power1[mid])%MOD1 + MOD1) % MOD1;
                ll cur2 = (hash2[start + mid -1] - (hash2[start-1] * power2[mid])%MOD2 + MOD2) % MOD2;
                hB[i] = cur1 * MOD2 + cur2;
            }
            qsort(hA, cnt1, sizeof(ll), cmp_ll);
            qsort(hB, cnt2, sizeof(ll), cmp_ll);
            int i1=0, i2=0;
            int found = 0;
            while(i1 < cnt1 && i2 < cnt2){
                if(hA[i1] == hB[i2]){
                    found =1;
                    break;
                }
                if(hA[i1] < hB[i2]) i1++;
                else i2++;
            }
            free(hA);
            free(hB);
            if(found){
                res = mid;
                L = mid +1;
            }
            else{
                R = mid -1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}