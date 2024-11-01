#include <stdio.h>
#include <string.h>

int n;
char s[20];
char in[20];
char out[20];
int bcnt = 0, ccnt = 0;
int flag = 1;

void dfs(int i) {
    if (i == n) {
        if (bcnt != 0 || ccnt != 0) {
            flag = 0;
            return;
        }
        for (int j = 0; j < n; j++) {
            if (out[j] != s[j]) {
                flag = 0;
                return;
            }
        }
        return;
    }
    if (in[i] == 'A') {
        if (bcnt < n - 1) {
            in[i] = 'B';
            bcnt++;
            printf("%c A B\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            in[i] = 'A';
            bcnt--;
        }
        if (ccnt < n - 1) {
            in[i] = 'C';
            ccnt++;
            printf("%c A C\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            in[i] = 'A';
            ccnt--;
        }
        if (bcnt == 0 && ccnt == 0) {
            out[i] = 'D';
            printf("%c A D\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            out[i] = 0;
        }
    } else if (in[i] == 'B') {
        if (bcnt > 0) {
            bcnt--;
            printf("%c B A\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            bcnt++;
        }
        if (ccnt < n - 1) {
            in[i] = 'C';
            ccnt++;
            printf("%c B C\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            in[i] = 'B';
            ccnt--;
        }
        if (bcnt == 0 && ccnt == 0) {
            out[i] = 'D';
            printf("%c B D\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            out[i] = 0;
        }
    } else if (in[i] == 'C') {
        if (ccnt > 0) {
            ccnt--;
            printf("%c C A\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            ccnt++;
        }
        if (bcnt < n - 1) {
            in[i] = 'B';
            bcnt++;
            printf("%c C B\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            in[i] = 'C';
            bcnt--;
        }
        if (bcnt == 0 && ccnt == 0) {
            out[i] = 'D';
            printf("%c C D\n", s[i]);
            dfs(i + 1);
            if (flag == 0) return;
            out[i] = 0;
        }
    }
    flag = 0;
}

int main() {
    scanf("%d %s", &n, s);
    for (int i = 0; i < n; i++) in[i] = 'A';
    dfs(0);
    if (flag == 0) printf("NO\n");
    return 0;
}