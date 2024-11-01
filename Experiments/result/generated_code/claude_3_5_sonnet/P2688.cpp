#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 4000005
#define MAX_C 100005

int prefix_sum[MAX_N];
int ship_lengths[MAX_C], ship_counts[MAX_C];

int solve() {
    int n, c, q;
    scanf("%d %d %d", &n, &c, &q);
    
    long long total_length = 0;
    for (int i = 0; i < c; i++) {
        scanf("%d %d", &ship_lengths[i], &ship_counts[i]);
        total_length += (long long)ship_lengths[i] * ship_counts[i];
    }
    
    if (total_length > n) return 0;
    
    memset(prefix_sum, 0, sizeof(prefix_sum));
    for (int i = 0; i < q; i++) {
        int pos;
        scanf("%d", &pos);
        prefix_sum[pos]++;
        prefix_sum[n+1]--;
    }
    
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] += prefix_sum[i-1];
    }
    
    int max_ships = 0;
    for (int i = 1; i <= n; i++) {
        if (prefix_sum[i] == 0) max_ships++;
    }
    
    int ships_placed = 0;
    for (int i = 0; i < c; i++) {
        ships_placed += ship_counts[i];
    }
    
    if (max_ships < ships_placed) return 1;
    
    int current_ships = 0;
    for (int i = 1; i <= n; i++) {
        if (prefix_sum[i] == 0) {
            current_ships++;
        } else {
            if (current_ships >= ships_placed) return i;
            current_ships = 0;
        }
    }
    
    if (current_ships >= ships_placed) return q + 1;
    
    return -1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        printf("%d\n", solve());
    }
    return 0;
}