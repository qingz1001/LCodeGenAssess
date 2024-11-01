#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 101

int main() {
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        char path[MAX_PATH_LENGTH];
        scanf("%s", path);
        
        int count = 0;
        for (int j = 0; j < strlen(path); j++) {
            if (path[j] == '/') {
                count++;
            }
        }
        
        printf("%d\n", count - 1);
    }
    
    return 0;
}