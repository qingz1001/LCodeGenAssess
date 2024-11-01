#include <stdio.h>
#include <string.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    char S[N+1];
    scanf("%s", S);

    int j_count = 0, z_count = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] == 'j') j_count++;
        else z_count++;
    }

    int jz_count = 0;
    for (int i = 0; i < N - 1; i++) {
        if (S[i] == 'j' && S[i + 1] == 'z') jz_count++;
    }

    // 如果可以交换次数大于等于 j 和 z 的数量之和，则所有 jz 都可以形成
    if (K >= j_count + z_count) {
        printf("%d\n", N - 1);
        return 0;
    }

    // 优先交换 j 和 z 的交界处，因为这样会增加 jz 的数量
    for (int i = 0; i < N - 1 && K > 0; i++) {
        if (S[i] == 'j' && S[i + 1] == 'z') {
            jz_count++;
            K--;
        }
    }

    // 如果剩余交换次数为偶数，则可以继续形成 jz
    if (K % 2 == 0) {
        printf("%d\n", jz_count + K / 2);
    } else {
        printf("%d\n", jz_count + (K - 1) / 2);
    }

    return 0;
}