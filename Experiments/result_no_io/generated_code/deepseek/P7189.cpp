#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    int times[3][2];
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &times[i][0], &times[i][1]);
    }
    
    int max_end = 0;
    for (int i = 0; i < 3; i++) {
        if (times[i][1] > max_end) {
            max_end = times[i][1];
        }
    }
    
    int cost = 0;
    for (int t = 1; t < max_end; t++) {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            if (times[i][0] <= t && t < times[i][1]) {
                count++;
            }
        }
        if (count == 1) {
            cost += a;
        } else if (count == 2) {
            cost += 2 * b;
        } else if (count == 3) {
            cost += 3 * c;
        }
    }
    
    printf("%d\n", cost);
    return 0;
}