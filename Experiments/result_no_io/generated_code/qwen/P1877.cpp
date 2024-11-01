#include <stdio.h>

int main() {
    int n, beginLevel, maxLevel;
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);

    int minChange = beginLevel;
    for (int i = 0; i < n; i++) {
        int change;
        scanf("%d", &change);
        if (change > minChange) {
            minChange = change;
        }
    }

    int maxVolume = beginLevel - minChange;
    if (maxVolume < 0 || maxVolume > maxLevel) {
        printf("-1\n");
    } else {
        printf("%d\n", maxVolume);
    }

    return 0;
}