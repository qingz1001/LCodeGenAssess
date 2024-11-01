#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int painters[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &painters[i]);
    }

    int a = 0, b = 0;
    int maxPainter = 0, minPainter = m + 1;
    int currentPainter = painters[0];
    int count = 1;

    for (int i = 1; i <= n; i++) {
        if (painters[i] == currentPainter) {
            count++;
        } else {
            if (count > 1 && painters[i-1] != painters[i]) {
                if (painters[i-1] < minPainter) {
                    minPainter = painters[i-1];
                }
                if (painters[i] > maxPainter) {
                    maxPainter = painters[i];
                }
            }
            currentPainter = painters[i];
            count = 1;
        }
    }

    printf("%d %d\n", minPainter, maxPainter);
    return 0;
}