#include <stdio.h>
#include <string.h>

int main() {
    int a, b;
    char s[100001];
    
    scanf("%d %d", &a, &b);
    scanf("%s", s);
    
    int n = strlen(s);
    int t_count = 0, s_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (s[i] == 'T') {
            t_count++;
        } else {
            s_count++;
        }
    }
    
    if (t_count < b || s_count < a) {
        printf("-1\n");
        return 0;
    }
    
    int min_changes = 0;
    
    for (int i = 0; i < n; i++) {
        if ((i + 1 <= a && s[i] == 'T') || (i + 1 > a && s[i] == 'S')) {
            min_changes++;
        }
    }
    
    printf("%d\n", min_changes);
    
    return 0;
}