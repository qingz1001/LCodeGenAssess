#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void* a, const void* b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        ll n, c, q;
        scanf("%lld %lld %lld", &n, &c, &q);
        ll* ci = (ll*)malloc(c * sizeof(ll));
        ll* ti = (ll*)malloc(c * sizeof(ll));
        ll S =0;
        ll max_ci =0;
        for(int i=0;i<c;i++){
            scanf("%lld %lld", &ci[i], &ti[i]);
            S += ci[i] * ti[i];
            if(ci[i] > max_ci) max_ci = ci[i];
        }
        ll* attacks = (ll*)malloc(q * sizeof(ll));
        for(int i=0;i<q;i++) scanf("%lld", &attacks[i]);
        if(S > n){
            printf("0\n");
            free(ci);
            free(ti);
            free(attacks);
            continue;
        }
        if(max_ci > n){
            printf("0\n");
            free(ci);
            free(ti);
            free(attacks);
            continue;
        }
        // Initialize forbidden cells array
        ll* forb = (ll*)malloc((q+2) * sizeof(ll));
        int fcnt =0;
        forb[fcnt++] = 0;
        forb[fcnt++] = n+1;
        // Initialize max_free and count_max
        ll max_free = n;
        int count_max =1;
        int ans = -1;
        for(int i=0;i<q;i++){
            ll ai = attacks[i];
            // Insert ai into forb in sorted order
            int left =0, right = fcnt;
            while(left < right){
                int mid = left + (right - left)/2;
                if(forb[mid] < ai) left = mid +1;
                else right = mid;
            }
            // Check if ai is already forbidden
            if(left < fcnt && forb[left] == ai){
                // Already forbidden, no change
            }
            else{
                // Insert ai at position left
                for(int j=fcnt; j>left; j--){
                    forb[j] = forb[j-1];
                }
                forb[left] = ai;
                fcnt++;
                // Find L and R
                ll L = forb[left-1];
                ll R = forb[left+1];
                ll current_segment = R - L -1;
                if(current_segment == max_free){
                    count_max--;
                    ll len1 = ai - L -1;
                    ll len2 = R - ai -1;
                    if(len1 == max_free) count_max++;
                    if(len2 == max_free) count_max++;
                    if(count_max ==0){
                        if(len1 > len2) max_free = len1;
                        else max_free = len2;
                        if(len1 > max_free) max_free = len1;
                        if(len2 > max_free) max_free = len2;
                    }
                }
                else{
                    // No change to max_free
                }
            }
            // Check conditions
            ll forbidden = i+1;
            if(S > (n - forbidden) || max_free < max_ci){
                ans = i+1;
                break;
            }
        }
        if(ans == -1){
            // After all attacks, check
            if(S > (n - q) || max_free < max_ci){
                ans = q;
            }
        }
        // Initial possibility check
        if(S > n || max_ci > n){
            ans =0;
        }
        printf("%d\n", (ans == -1) ? -1 : ans);
        free(ci);
        free(ti);
        free(attacks);
        free(forb);
    }
}