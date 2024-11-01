#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    
    int max_eat[k];
    for (int i = 0; i < k; i++) {
        scanf("%d", &max_eat[i]);
    }
    
    int fat[n], category[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &fat[i], &category[i]);
    }
    
    int total_fat = 0;
    int eaten[k] = {0};
    
    for (int i = 0; i < n; i++) {
        if (eaten[category[i] - 1] < max_eat[category[i] - 1] && total_fat + fat[i] <= m) {
            total_fat += fat[i];
            eaten[category[i] - 1]++;
        }
    }
    
    printf("%d\n", total_fat);
    
    return 0;
}