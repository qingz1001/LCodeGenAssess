#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

char input[MAXN];
int m;
struct Query {
    int x, y;
} queries[MAXM];

int main() {
    scanf("%s", input);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &queries[i].x, &queries[i].y);
    }

    int len = strlen(input);
    char buffer[MAXN];
    int pos = 0;

    for (int i = 0; i < len; ++i) {
        if (input[i] == 'B') {
            if (pos > 0) --pos;
        } else if (input[i] == 'P') {
            buffer[pos++] = '\0';
            printf("%s\n", buffer);
        } else {
            buffer[pos++] = input[i];
        }
    }

    return 0;
}