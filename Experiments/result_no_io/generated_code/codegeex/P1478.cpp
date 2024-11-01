#include <stdio.h>

int main() {
    int n, s;
    scanf("%d %d", &n, &s);
    
    int a, b;
    scanf("%d %d", &a, &b);
    
    int apples[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &apples[i][0], &apples[i][1]);
    }
    
    int max_apples = 0;
    
    // Sort apples by height in descending order
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (apples[i][0] < apples[j][0]) {
                int temp0 = apples[i][0];
                int temp1 = apples[i][1];
                apples[i][0] = apples[j][0];
                apples[i][1] = apples[j][1];
                apples[j][0] = temp0;
                apples[j][1] = temp1;
            }
        }
    }
    
    // Try to pick the apples
    for (int i = 0; i < n; i++) {
        if (apples[i][0] <= b || apples[i][0] <= a + b) {
            if (s >= apples[i][1]) {
                s -= apples[i][1];
                max_apples++;
            }
        }
    }
    
    printf("%d\n", max_apples);
    return 0;
}