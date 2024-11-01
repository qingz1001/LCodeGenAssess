#include <stdio.h>
#include <string.h>

#define MAXN 200010

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, y;
        char s[MAXN];
        scanf("%d %d %d %s", &n, &x, &y, s);
        
        int max_win = 0;
        int current_win = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') {
                current_win++;
                if (current_win > max_win) {
                    max_win = current_win;
                }
            } else {
                current_win = 0;
            }
        }
        
        int result = max_win + 1;
        printf("%d\n", result);
    }
    return 0;
}