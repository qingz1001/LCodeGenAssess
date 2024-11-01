#include <stdio.h>

int main() {
    int v, n, c;
    scanf("%d %d %d", &v, &n, &c);
    
    int total_volume = 0;
    int total_effort = 0;
    
    for (int i = 0; i < n; i++) {
        int volume, effort;
        scanf("%d %d", &volume, &effort);
        total_volume += volume;
        total_effort += effort;
    }
    
    if (total_volume >= v) {
        int remaining_effort = c - total_effort * v / total_volume;
        printf("%d\n", remaining_effort);
    } else {
        printf("Impossible\n");
    }
    
    return 0;
}