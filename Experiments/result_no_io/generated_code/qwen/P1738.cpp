#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 100
#define MAX_N 1000

int main() {
    int N;
    scanf("%d", &N);
    
    char paths[MAX_N][MAX_PATH_LENGTH];
    for (int i = 0; i < N; ++i) {
        scanf("%s", paths[i]);
    }
    
    for (int i = 0; i < N; ++i) {
        int count = 0;
        for (int j = 1; j < strlen(paths[i]); ++j) {
            if (paths[i][j] == '/') {
                count++;
            }
        }
        printf("%d\n", count);
    }
    
    return 0;
}