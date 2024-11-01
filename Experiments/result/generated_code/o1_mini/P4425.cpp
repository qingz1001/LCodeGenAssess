#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
typedef long long ll;

ll T[MAXN];
int n, m, p;
ll LastAns;

// Function to check if a given t is feasible
int is_feasible(ll t) {
    // Early check: if any T[i] > t, impossible
    for(int i=0;i<n;i++) {
        if(T[i] > t) return 0;
    }
    // Initialize difference array
    int *diff = (int*)calloc(n+1, sizeof(int));
    for(int i=0;i<n;i++) {
        ll d = t - T[i];
        if(d <0){
            free(diff);
            return 0;
        }
        ll l = (i - d) % n;
        if(l <0) l += n;
        ll r = i;
        if(l <= r){
            diff[l]++;
            if(r+1 <=n) diff[r+1]--;
        }
        else{
            diff[0]++;
            if(r+1 <=n) diff[r+1]--;
            diff[l]++;
            if(n <=n) diff[n]--;
        }
    }
    // Compute prefix sum and check
    int cnt =0;
    for(int i=0;i<n;i++){
        cnt += diff[i];
        if(cnt == n){
            free(diff);
            return 1;
        }
    }
    free(diff);
    return 0;
}

// Function to find minimal t using binary search
ll find_min_t(){
    ll left = 0, right = 0;
    for(int i=0;i<n;i++) if(T[i]+n > right) right = T[i]+n;
    ll res = right;
    while(left <= right){
        ll mid = left + (right - left)/2;
        if(is_feasible(mid)){
            res = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    return res;
}

int main(){
    // Fast IO
    scanf("%d %d %d", &n, &m, &p);
    for(int i=0;i<n;i++) scanf("%lld", &T[i]);
    // Initial answer
    LastAns = find_min_t();
    printf("%lld\n", LastAns);
    // Process modifications
    for(int i=0;i<m;i++){
        ll x, y;
        scanf("%lld %lld", &x, &y);
        if(p){
            x ^= LastAns;
            y ^= LastAns;
            if(x <1 || x >n){
                // Invalid, but problem says input is valid
            }
            x--; // 0-based
        }
        else{
            x--; // 0-based
        }
        T[x] = y;
        LastAns = find_min_t();
        printf("%lld\n", LastAns);
    }
    return 0;
}