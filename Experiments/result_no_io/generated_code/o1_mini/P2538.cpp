#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50
#define INF 100000000000LL

typedef long long ll;

ll distance_matrix[MAXN][MAXN];
int n, m, k;
int r[MAXN];
ll d[MAXN];
int castles_initial[MAXN];
ll coverage0[MAXN];
ll coverage1[MAXN];
ll existing_coverage0 = 0;
ll existing_coverage1 = 0;

int backtrack_func(unsigned long long uncovered0, unsigned long long uncovered1, int k_remaining) {
    if (uncovered0 == 0 && uncovered1 == 0)
        return 1;
    if (k_remaining == 0)
        return 0;
    int s;
    if (uncovered0 != 0)
        s = __builtin_ctzll(uncovered0);
    else
        s = 64 + __builtin_ctzll(uncovered1);
    for(int c = 0; c < n; c++) {
        if (distance_matrix[c][s] <= distance_matrix[c][s] && ((coverage0[c] >> s) & 1ULL)) {
            // Check if city c can cover city s
            if (distance_matrix[c][s] > distance_matrix[c][s]) continue;
            ll new_uncovered0 = uncovered0 & ~coverage0[c];
            ll new_uncovered1 = uncovered1 & ~coverage1[c];
            if (backtrack_func(new_uncovered0, new_uncovered1, k_remaining -1))
                return 1;
        }
    }
    // Alternatively, cover by any city that can cover s
    for(int c = 0; c < n; c++) {
        if (distance_matrix[c][s] <= distance_matrix[c][s]) {
            // If c can cover s
            if (distance_matrix[c][s] > distance_matrix[c][s]) continue;
            ll new_uncovered0 = uncovered0 & ~coverage0[c];
            ll new_uncovered1 = uncovered1 & ~coverage1[c];
            if (backtrack_func(new_uncovered0, new_uncovered1, k_remaining -1))
                return 1;
        }
    }
    return 0;
}

int check(ll D) {
    // Initialize coverage from existing castles
    existing_coverage0 = 0;
    existing_coverage1 = 0;
    for(int i =0; i < m; i++) {
        int c = castles_initial[i];
        existing_coverage0 |= coverage0[c];
        existing_coverage1 |= coverage1[c];
    }
    // Determine uncovered cities
    unsigned long long uncovered0 = (~existing_coverage0) & ((1ULL << n) -1);
    unsigned long long uncovered1 = (~existing_coverage1) & ((1ULL << n) -1);
    if (uncovered0 ==0 && uncovered1 ==0)
        return 1;
    // Backtrack to cover uncovered
    return backtrack_func(uncovered0, uncovered1, k);
}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for(int i=0;i<n;i++) scanf("%d", &r[i]);
    for(int i=0;i<n;i++) scanf("%lld", &d[i]);
    for(int i=0;i<m;i++) scanf("%d", &castles_initial[i]);
    // Initialize distance matrix
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            distance_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
    // Add roads
    for(int i=0;i<n;i++) {
        int to = r[i];
        ll len = d[i];
        if (len < distance_matrix[i][to]) {
            distance_matrix[i][to] = len;
            distance_matrix[to][i] = len;
        }
    }
    // Floyd-Warshall
    for(int k_fw=0; k_fw<n; k_fw++) {
        for(int i=0;i<n;i++) {
            for(int j=0; j<n; j++) {
                if (distance_matrix[i][k_fw] + distance_matrix[k_fw][j] < distance_matrix[i][j]) {
                    distance_matrix[i][j] = distance_matrix[i][k_fw] + distance_matrix[k_fw][j];
                }
            }
        }
    }
    // Binary search
    ll left = 0, right = 0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(distance_matrix[i][j] > right) right = distance_matrix[i][j];
        }
    }
    ll answer = right;
    while(left <= right){
        ll mid = left + (right - left)/2;
        // Precompute coverage for this D
        for(int c=0;c<n;c++){
            coverage0[c] =0;
            coverage1[c] =0;
            for(int s=0;s<n;s++) {
                if(distance_matrix[c][s] <= mid){
                    if(s <64) coverage0[c] |= (1ULL << s);
                    else coverage1[c] |= (1ULL << (s -64));
                }
            }
        }
        if(check(mid)){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%lld\n", answer);
    return 0;
}