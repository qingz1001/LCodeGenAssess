#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int count = 0;
    int current_char = '0';
    for (int i = 0; i < N * N; i++) {
        int num;
        scanf("%d", &num);
        
        while (num > 0) {
            printf("%c", current_char);
            num--;
            count++;
            
            if (count == N * N) break;
            
            if (current_char == '0') {
                current_char = '1';
            } else {
                current_char = '0';
            }
        }
    }
    
    return 0;
}