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
        if (s[i] == 'T') t_count++;
        else if (s[i] == 'S') s_count++;
    }
    
    if (t_count < b || s_count < a) {
        printf("-1\n");
    } else {
        printf("%d\n", (t_count - b > s_count - a) ? (t_count - b) : (s_count - a));
    }
    
    return 0;
}