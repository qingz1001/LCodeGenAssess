#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 10001
#define MAX_N 5

char A[MAX_LEN];
char B[MAX_N][MAX_LEN];
int N;
int len_A;
int len_B[MAX_N];

int min_cover[MAX_LEN];
bool max_cover[MAX_LEN];

void solve() {
    scanf("%s", A);
    scanf("%d", &N);
    
    len_A = strlen(A);
    for (int i = 0; i < N; i++) {
        scanf("%s", B[i]);
        len_B[i] = strlen(B[i]);
    }

    memset(min_cover, 0x3f, sizeof(min_cover));
    memset(max_cover, false, sizeof(max_cover));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= len_A - len_B[i]; j++) {
            if (strncmp(A + j, B[i], len_B[i]) == 0) {
                int end = j + len_B[i] - 1;
                if (end < min_cover[j]) {
                    min_cover[j] = end;
                }
                for (int k = j; k <= end; k++) {
                    max_cover[k] = true;
                }
            }
        }
    }

    int min_ans = 0;
    int last = -1;
    for (int i = 0; i < len_A; i++) {
        if (min_cover[i] != 0x3f3f3f3f) {
            min_ans += min_cover[i] - (last > i ? last : i) + 1;
            last = min_cover[i];
        }
    }

    int max_ans = 0;
    for (int i = 0; i < len_A; i++) {
        if (max_cover[i]) {
            max_ans++;
        }
    }

    printf("%d %d\n", min_ans, max_ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}