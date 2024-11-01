#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

typedef struct {
    ll h;
    ll l;
    ll r;
} Platform;

typedef struct {
    ll x;
    ll time;
} Query;

int compare_platform(const void* a, const void* b) {
    Platform *pa = (Platform*)a;
    Platform *pb = (Platform*)b;
    if (pa->h != pb->h)
        return (pa->h > pb->h) ? -1 : 1;
    return 0;
}

int compare_ll(const void* a, const void* b) {
    ll va = *(ll*)a;
    ll vb = *(ll*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main(){
    int n;
    ll h;
    scanf("%d %lld", &n, &h);
    ll start_x, start_y;
    scanf("%lld %lld", &start_x, &start_y);
    Platform *platforms = (Platform*)malloc(n * sizeof(Platform));
    ll *coords = (ll*)malloc((2*n +1) * sizeof(ll));
    coords[0] = start_x;
    for(int i=0;i<n;i++){
        scanf("%lld %lld %lld", &platforms[i].h, &platforms[i].l, &platforms[i].r);
        coords[1 + 2*i] = platforms[i].l;
        coords[2 + 2*i] = platforms[i].r;
    }
    // Coordinate compression
    qsort(coords, 2*n+1, sizeof(ll), compare_ll);
    int unique = 1;
    for(int i=1;i<2*n+1;i++) {
        if(coords[i]!=coords[i-1]) coords[unique++] = coords[i];
    }
    // Sort platforms by descending height
    qsort(platforms, n, sizeof(Platform), compare_platform);
    // Initialize DP array
    ll *dp = (ll*)malloc(unique * sizeof(ll));
    for(int i=0;i<unique;i++) dp[i] = 0;
    // Function to find index
    auto find_idx = [&](ll x) -> int {
        int l=0, r=unique-1, m;
        while(l<=r){
            m = l + (r-l)/2;
            if(coords[m]==x) return m;
            if(coords[m]<x) l = m+1;
            else r = m-1;
        }
        return -1;
    };
    // Process platforms
    for(int i=0;i<n;i++){
        ll l = platforms[i].l;
        ll r = platforms[i].r;
        int il = find_idx(l);
        int ir = find_idx(r);
        // Assuming dp[il] and dp[ir] are already updated
        dp[il] = dp[il] + (start_y - platforms[i].h);
        dp[ir] = dp[ir] + (start_y - platforms[i].h);
    }
    // Final answer
    printf("%lld\n", dp[find_idx(start_x)]);
    free(platforms);
    free(coords);
    free(dp);
    return 0;
}