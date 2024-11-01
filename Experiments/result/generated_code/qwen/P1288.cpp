#include <stdio.h>
#include <stdbool.h>

bool canWin(int N, int edges[], int start) {
    if (edges[start] == 0 && edges[(start + 1) % N] == 0) return false;
    
    for (int i = 0; i < N; i++) {
        if (edges[i] != 0) {
            edges[i]--;
            if (!canWin(N, edges, (i + 1) % N)) {
                edges[i]++;
                return true;
            }
            edges[i]++;
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