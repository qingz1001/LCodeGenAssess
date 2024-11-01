#include <stdio.h>

int play_game(int m, int n) {
    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }
    
    int turns = 0;
    while (n > 0) {
        m %= n;
        turns++;
        if (m == 0) {
            return turns % 2;
        }
        int temp = m;
        m = n;
        n = temp;
    }
    return turns % 2;
}

int main() {
    int C;
    scanf("%d", &C);
    
    while (C--) {
        int M, N;
        scanf("%d %d", &M, &N);
        
        if (play_game(M, N) == 0) {
            printf("Stan wins\n");
        } else {
            printf("Ollie wins\n");
        }
    }
    
    return 0;
}