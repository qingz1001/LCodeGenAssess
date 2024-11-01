#include <stdio.h>

#define MAX_N 10000000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int posters[MAX_N + 1] = {0};
    
    for (int i = 0; i < M; ++i) {
        int A, B;
        scanf("%d %d", &A, &B);
        posters[A]++;
        if (B + 1 <= N) {
            posters[B + 1]--;
        }
    }
    
    int visible_posters = 0;
    int current_posters = 0;
    
    for (int i = 1; i <= N; ++i) {
        current_posters += posters[i];
        if (current_posters > 0) {
            visible_posters++;
        }
    }
    
    printf("%d\n", visible_posters);
    
    return 0;
}