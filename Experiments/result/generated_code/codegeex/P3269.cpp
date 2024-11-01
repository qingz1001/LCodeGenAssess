#include <stdio.h>
#include <string.h>

int T;
char A[10001];
char B[5][10001];
int N;

int find(char *a, char *b, int start) {
    int lena = strlen(a);
    int lenb = strlen(b);
    for (int i = start; i <= lena - lenb; i++) {
        int j;
        for (j = 0; j < lenb; j++) {
            if (a[i + j] != b[j]) break;
        }
        if (j == lenb) return i;
    }
    return -1;
}

void solve() {
    int lenA = strlen(A);
    int Minans = lenA, Maxans = 0;
    for (int i = 0; i < (1 << N); i++) {
        int pos[5] = {0};
        int flag = 1;
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                int p = find(A, B[j], pos[j]);
                if (p == -1) {
                    flag = 0;
                    break;
                }
                pos[j] = p + strlen(B[j]);
            }
        }
        if (flag) {
            int covered = 0;
            for (int j = 0; j < lenA; j++) {
                int coveredBy = 0;
                for (int k = 0; k < N; k++) {
                    if (i & (1 << k)) {
                        if (j >= pos[k] && j < pos[k] + strlen(B[k])) {
                            coveredBy = 1;
                            break;
                        }
                    }
                }
                if (coveredBy) covered++;
            }
            Minans = covered < Minans ? covered : Minans;
            Maxans = covered > Maxans ? covered : Maxans;
        }
    }
    printf("%d %d\n", Minans, Maxans);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%s", A);
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%s", B[i]);
        }
        solve();
    }
    return 0;
}