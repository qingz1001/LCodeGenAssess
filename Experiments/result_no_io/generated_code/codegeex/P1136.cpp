#include <stdio.h>
#include <string.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    char s[501];
    scanf("%s", s);

    int j_count = 0, z_count = 0;
    for (int i = 0; i < N; i++) {
        if (s[i] == 'j') j_count++;
        else z_count++;
    }

    int max_jz = 0;
    for (int i = 0; i <= K && i <= j_count; i++) {
        int j_needed = i;
        int z_needed = (K - i) / 2;
        if (z_needed > z_count) continue;
        int current_jz = 0;
        int j_used = 0, z_used = 0;
        for (int j = 0; j < N; j++) {
            if (s[j] == 'j' && j_used < j_needed) {
                j_used++;
                current_jz++;
            } else if (s[j] == 'z' && z_used < z_needed) {
                z_used++;
                current_jz++;
            }
        }
        max_jz = (current_jz > max_jz) ? current_jz : max_jz;
    }

    printf("%d\n", max_jz);
    return 0;
}