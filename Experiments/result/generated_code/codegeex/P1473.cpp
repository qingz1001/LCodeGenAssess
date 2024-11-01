#include <stdio.h>
#include <string.h>

void dfs(int n, int pos, int sum, char *seq) {
    if (pos == n) {
        if (sum == 0) {
            printf("%s\n", seq);
        }
        return;
    }
    char new_seq[100];
    strcpy(new_seq, seq);
    new_seq[pos * 2] = '+';
    dfs(n, pos + 1, sum + pos + 1, new_seq);
    strcpy(new_seq, seq);
    new_seq[pos * 2] = '-';
    dfs(n, pos + 1, sum - (pos + 1), new_seq);
    strcpy(new_seq, seq);
    new_seq[pos * 2] = ' ';
    dfs(n, pos + 1, sum, new_seq);
}

int main() {
    int n;
    scanf("%d", &n);
    char seq[100];
    memset(seq, 0, sizeof(seq));
    seq[0] = '1';
    dfs(n, 1, 1, seq);
    return 0;
}