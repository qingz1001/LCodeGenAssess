#include <stdio.h>
#include <stdbool.h>

#define MAX_N 12

int n;
int x[MAX_N+1], y[MAX_N+1];
int partner[MAX_N+1];
int next_on_right[MAX_N+1];

int count = 0;

bool cycle_exists() {
    for (int start = 1; start <= n; start++) {
        int pos = start;
        for (int count = 0; count < n; count++) {
            pos = next_on_right[partner[pos]];
        }
        if (pos != 0) return true;
    }
    return false;
}

void solve() {
    int i, j;

    // find next on right for each wormhole
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (x[j] > x[i] && y[i] == y[j]) {
                if (next_on_right[i] == 0 ||
                    x[j] - x[i] < x[next_on_right[i]] - x[i]) {
                    next_on_right[i] = j;
                }
            }
        }
    }

    // find first unpaired wormhole
    i = 1;
    while (i <= n && partner[i] != 0) i++;

    // everyone paired?
    if (i > n) {
        if (cycle_exists()) count++;
        return;
    }

    // try pairing i with each unpaired j
    for (j = i+1; j <= n; j++) {
        if (partner[j] == 0) {
            partner[i] = j;
            partner[j] = i;
            solve();
            partner[i] = partner[j] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    solve();
    printf("%d\n", count);
    return 0;
}