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
    int misplaced = 0;
    
    if (count[2] > count[1]) {
        misplaced += count[2] - count[1];
    } else {
        swaps += count[1] - count[2];
    }
    
    if (count[3] > count[2]) {
        misplaced += count[3] - count[2];
    } else {
        swaps += count[2] - count[3];
    }
    
    printf("%d\n", swaps + misplaced / 2);
    
    return 0;
}