#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int innovation[n], contribution[m];
    for (int i = 0; i < n; i++) {
        scanf("%d", &innovation[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &contribution[i]);
    }

    bool found[n];
    for (int i = 0; i < n; i++) {
        found[i] = false;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (innovation[j] == contribution[i]) {
                found[j] = true;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (found[i]) {
            printf("%d ", innovation[i]);
        }
    }
    printf("\n");

    return 0;
}