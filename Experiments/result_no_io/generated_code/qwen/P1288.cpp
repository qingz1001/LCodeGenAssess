#include <stdio.h>
#include <stdbool.h>

bool canWin(int N, int* edges, int start) {
    if (N == 1 && edges[0] != 0) return true;
    for (int i = 0; i < N; i++) {
        if (edges[i] > 0) {
            edges[i]--;
            bool win = false;
            for (int j = 0; j < N; j++) {
                if (edges[j] > 0) {
                    edges[j]--;
                    win |= !canWin(N, edges, (start + i + 1) % N);
                    edges[j]++;
                }
            }
            edges[i]++;
            if (!win) return true;
        }
    }
    return false;
}

int main() {
    int N;
    scanf("%d", &N);
    int edges[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &edges[i]);
    }
    bool result = canWin(N, edges, 0);
    if (result) printf("YES\n");
    else printf("NO\n");
    return 0;
}