#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int platforms[10] = {0};
    for (int i = 0; i < k; i++) {
        scanf("%d", &platforms[i]);
    }
    
    int time = 0;
    int current_step = 0;
    int platform_index = 0;
    
    while (current_step < n) {
        time++;
        current_step += m;
        
        if (platform_index < k && current_step >= platforms[platform_index]) {
            m++;
            platform_index++;
        }
    }
    
    printf("%d\n", time);
    
    return 0;
}