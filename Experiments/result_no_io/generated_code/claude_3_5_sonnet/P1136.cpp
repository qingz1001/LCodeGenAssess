#include <stdio.h>
#include <string.h>

#define MAX_N 505

char s[MAX_N];
int n, k;

int count_jz() {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'j' && s[i + 1] == 'z') {
            count++;
        }
    }
    return count;
}

void swap(int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

int main() {
    scanf("%d %d", &n, &k);
    scanf("%s", s);

    int j_count = 0, z_count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'j') j_count++;
        else z_count++;
    }

    int min_count = (j_count < z_count) ? j_count : z_count;
    int max_jz = (min_count <= k) ? min_count : k;

    int j_pos = 0, z_pos = n - 1;
    for (int i = 0; i < max_jz; i++) {
        while (j_pos < n && s[j_pos] == 'j') j_pos++;
        while (z_pos >= 0 && s[z_pos] == 'z') z_pos--;

        if (j_pos < z_pos) {
            swap(j_pos, z_pos);
        }
        j_pos++;
        z_pos--;
    }

    printf("%d\n", count_jz());

    return 0;
}