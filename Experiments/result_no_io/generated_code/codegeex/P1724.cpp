#include <stdio.h>
#include <string.h>

int main() {
    char S[5001];
    int T;
    scanf("%s %d", S, &T);
    int len = strlen(S);
    
    int x = 0, y = 0;
    for (int i = 0; i < T; i++) {
        switch (S[i % len]) {
            case 'E':
                x++;
                break;
            case 'S':
                y--;
                break;
            case 'W':
                x--;
                break;
            case 'N':
                y++;
                break;
        }
    }
    
    printf("%d %d\n", x, y);
    return 0;
}