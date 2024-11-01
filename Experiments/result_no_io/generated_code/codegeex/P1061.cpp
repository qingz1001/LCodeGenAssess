#include <stdio.h>
#include <string.h>

int main() {
    int s, t, w;
    scanf("%d%d%d", &s, &t, &w);
    char str[w + 1];
    scanf("%s", str);

    for (int i = 0; i < 5; i++) {
        int j = w - 1;
        while (j >= 0 && str[j] == (char)(t + 'a' - 1)) {
            j--;
        }
        if (j == -1) {
            break;
        }
        str[j]++;
        for (int k = j + 1; k < w; k++) {
            str[k] = (char)(str[j] + (k - j));
        }
        printf("%s\n", str);
    }

    return 0;
}