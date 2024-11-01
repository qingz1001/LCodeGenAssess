#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int platforms[10];
    for (int i = 0; i < k; i++) {
        scanf("%d", &platforms[i]);
    }
    
    int time = 0;
    int current_step = 0;
    
    while (current_step < n) {
        time++;
        current_step += m;
        
        for (int i = 0; i < k; i++) {
            if (current_step == platforms[i]) {
                m++;
                break;
            }
        }
    }
    
    printf("%d\n", time);
    return 0;
}