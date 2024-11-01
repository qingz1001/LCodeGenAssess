#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int *lights = (int*)calloc(N+1, sizeof(int));
    
    for (int i = 0; i < M; i++) {
        int command, S, E;
        scanf("%d %d %d", &command, &S, &E);
        
        if (command == 0) {
            // Toggle the lights in the range [S, E]
            for (int j = S; j <= E; j++) {
                lights[j] = !lights[j];
            }
        } else if (command == 1) {
            // Count the number of lights on in the range [S, E]
            int count = 0;
            for (int j = S; j <= E; j++) {
                if (lights[j]) {
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }
    
    free(lights);
    return 0;
}