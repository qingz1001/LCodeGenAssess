#include <stdio.h>
#include <string.h>

int main() {
    char commands[5004];
    int T;
    scanf("%s %d", commands, &T);
    
    int x = 0, y = 0;
    int len = strlen(commands);
    
    for (int t = 0; t < T; ++t) {
        switch (commands[t % len]) {
            case 'E': x++; break;
            case 'S': y--; break;
            case 'W': x--; break;
            case 'N': y++; break;
        }
    }
    
    printf("%d %d\n", x, y);
    return 0;
}