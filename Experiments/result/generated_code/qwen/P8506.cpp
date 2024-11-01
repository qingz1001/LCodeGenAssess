#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        char line[101];
        scanf("%s", line);
        
        if (line[0] == '#' && line[1] != ' ' && line[1] != '\0') {
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}