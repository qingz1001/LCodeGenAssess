#include <stdio.h>

int main() {
    int L, N;
    scanf("%d %d", &L, &N);
    
    int min_time = 0;
    int max_time = 0;
    
    for (int i = 0; i < N; i++) {
        int position;
        scanf("%d", &position);
        
        int time_to_left = position;
        int time_to_right = L - position + 1;
        
        if (time_to_left > time_to_right) {
            min_time = time_to_left;
            max_time = time_to_right;
        } else {
            min_time = time_to_right;
            max_time = time_to_left;
        }
    }
    
    printf("%d %d\n", min_time, max_time);
    
    return 0;
}