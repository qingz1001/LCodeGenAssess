#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 10
#define MAX_M (1 << MAX_N)

long long dp[MAX_M][2];
int pay_method[MAX_M], change_cost[MAX_M];
int flow[MAX_M][MAX_M];
int N, M;

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

long long calculate_cost(int state, int pos) {
    long long cost = 0;
    int na = count_bits(state & ((1 << pos) - 1));
    int nb = pos - na;
    
    for (int i = 0; i < pos; i++) {
        for (int j = i + 1; j < pos; j++) {
            if ((state & (1 << i)) && (state & (1 << j))) {
                cost += (long long)flow[i][j - i - 1] * na * nb;
            } else if (!(state & (1 << i)) && !(state & (1 << j))) {
                cost += (long long)flow[i][j - i - 1] * na * nb;
            } else {
                cost += (long long)flow[i][j - i - 1] * (na + nb - 1);
            }
        }
    }
    return cost;
}

long long solve() {
    for (int i = 0; i < M; i++) {
        dp[i][0] = dp[i][1] = LLONG_MAX;
    }
    
    dp[1][pay_method[0]] = 0;
    dp[1][1 - pay_method[0]] = change_cost[0];
    
    for (int i = 2; i <= M; i++) {
        for (int j = 0; j < 2; j++) {
            int prev_state = i - (i & -i);
            long long cost = calculate_cost(i, __builtin_ctz(i) + 1);
            
            dp[i][j] = min(dp[i][j], dp[prev_state][j] + cost);
            dp[i][j] = min(dp[i][j], dp[prev_state][1-j] + cost + change_cost[__builtin_ctz(i)]);
        }
    }
    
    return min(dp[M][0], dp[M][1]);
}

int main() {
    scanf("%d", &N);
    M = 1 << N;
    
    for (int i = 0; i < M; i++) {
        scanf("%d", &pay_method[i]);
    }
    
    for (int i = 0; i < M; i++) {
        scanf("%d", &change_cost[i]);
    }
    
    for (int i = 0; i < M - 1; i++) {
        for (int j = 0; j < M - i - 1; j++) {
            scanf("%d", &flow[i][j]);
        }
    }
    
    printf("%lld\n", solve());
    
    return 0;
}