#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int platforms[k];
    for (int i = 0; i < k; i++) {
        scanf("%d", &platforms[i]);
    }
    
    int time = 0;
    int current_step = 0;
    int platform_index = 0;
    
    while (current_step < n) {
        if (platform_index < k && current_step == platforms[platform_index]) {
            m++;
            platform_index++;
        }
        
        if (current_step + m <= n) {
            current_step += m;
            time++;
        } else {
            current_step = n;
            time++;
        }
    }
    
    printf("%d\n", time);
    return 0;
}