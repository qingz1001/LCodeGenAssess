#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40005
#define MAXQ 100005
#define MAXLEN 10005

int n, q;
char S[MAXN][MAXLEN];
int X[MAXQ], Y[MAXQ];
int lcp[MAXN][MAXN];

void compute_lcp() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int len = 0;
            while (i + len < n && j + len < n && S[i][len] == S[j][len]) {
                len++;
            }
            lcp[i][j] = len;
        }
    }
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%s", S[i]);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &X[i], &Y[i]);
        X[i]--;
        Y[i]--;
    }

    compute_lcp();

    // Find P_G with maximum value W(P_G)
    int perm[MAXN];
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    long long max_value = 0;
    do {
        long long current_value = 0;
        for (int i = 1; i < n; i++) {
            current_value += (long long)lcp[perm[i - 1]][perm[i]] * lcp[perm[i - 1]][perm[i]];
        }
        if (current_value > max_value) {
            max_value = current_value;
        }
    } while (next_permutation(perm, perm + n));

    printf("%lld\n", max_value);

    // Find P_B with maximum total task reward
    int tasks[MAXQ];
    memset(tasks, 0, sizeof(tasks));
    for (int i = 0; i < q; i++) {
        int x = X[i], y = Y[i];
        if (x != y) {
            tasks[i] = 1;
        }
    }

    int best_perm[MAXN];
    memcpy(best_perm, perm, sizeof(best_perm));
    int best_reward = 0;

    for (int mask = 0; mask < (1 << q); mask++) {
        int current_reward = 0;
        for (int i = 0; i < q; i++) {
            if (mask & (1 << i)) {
                current_reward += (tasks[i] << i);
            }
        }
        int current_perm[MAXN];
        memcpy(current_perm, perm, sizeof(current_perm));
        do {
            int valid = 1;
            for (int i = 0; i < q; i++) {
                int x = X[i], y = Y[i];
                if ((mask & (1 << i)) && !(x < y && current_perm[x] + 1 == current_perm[y])) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                long long current_value = 0;
                for (int i = 1; i < n; i++) {
                    current_value += (long long)lcp[current_perm[i - 1]][current_perm[i]] * lcp[current_perm[i - 1]][current_perm[i]];
                }
                if (current_value + current_reward > max_value + best_reward) {
                    max_value += current_reward;
                    best_reward = current_reward;
                    memcpy(best_perm, current_perm, sizeof(best_perm));
                }
            }
        } while (next_permutation(current_perm, current_perm + n));
    }

    printf("%d ", q);
    for (int i = 0; i < q; i++) {
        if (best_reward & (1 << i)) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", best_perm[i] + 1);
    }
    printf("\n");

    return 0;
}