#include <stdio.h>
#include <stdbool.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int m;
        scanf("%d", &m);
        int a[31];
        for (int i = 0; i < m; i++) {
            scanf("%d", &a[i]);
        }
        int count = 0;
        for (int i = 0; i < m; i++) {
            bool found = false;
            for (int j = 0; j < m; j++) {
                if (j != i) {
                    for (int k = 0; k < m; k++) {
                        if (k != i && k != j && a[k] == a[i] - a[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
            }
            if (found) count++;
        }
        printf("%d\n", count);
    }
    return 0;
}