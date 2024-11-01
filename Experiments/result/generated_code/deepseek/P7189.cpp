#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    int start[3], end[3];
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }
    
    int total_cost = 0;
    for (int time = 1; time <= 100; time++) {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            if (time > start[i] && time <= end[i]) {
                count++;
            }
        }
        
        if (count == 1) {
            total_cost += a * count;
        } else if (count == 2) {
            total_cost += b * count;
        } else if (count == 3) {
            total_cost += c * count;
        }
    }
    
    printf("%d\n", total_cost);
    return 0;
}