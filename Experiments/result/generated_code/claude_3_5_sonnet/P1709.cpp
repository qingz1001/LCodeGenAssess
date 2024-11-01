#include <stdio.h>
#include <string.h>

#define MAXN 5000005

char s[MAXN];
int n;

int compare(int a, int b) {
    for (int i = 0; i < n; i++) {
        if (s[(a+i)%n] != s[(b+i)%n])
            return s[(a+i)%n] - s[(b+i)%n];
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);

    int min_pos = 0;
    for (int i = 1; i < n; i++) {
        if (compare(i, min_pos) < 0) {
            min_pos = i;
        }
    }

    printf("%d\n", min_pos);

    return 0;
}