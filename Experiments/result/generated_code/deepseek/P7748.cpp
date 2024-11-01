#include <stdio.h>

int main() {
    int K, N;
    scanf("%d %d", &K, &N);
    
    int current_time = 0;
    int current_holder = K;
    
    for (int i = 0; i < N; i++) {
        int T;
        char response;
        scanf("%d %c", &T, &response);
        
        current_time += T;
        if (current_time >= 210) {
            printf("%d\n", current_holder);
            return 0;
        }
        
        if (response == 'T') {
            current_holder = (current_holder % 8) + 1;
        }
    }
    
    printf("%d\n", current_holder);
    return 0;
}