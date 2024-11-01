#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int count[4] = {0};
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        count[x]++;
    }
    
    int swaps = 0;
    if (count[2] > 0) {
        swaps += count[2];
        count[1] -= count[2];
    }
    if (count[1] > 0) {
        swaps += count[1];
        count[3] -= count[1];
    }
    if (count[3] > 0) {
        swaps += count[3];
    }
    
    printf("%d\n", swaps);
    return 0;
}