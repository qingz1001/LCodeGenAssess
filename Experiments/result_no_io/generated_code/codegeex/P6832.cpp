#include <stdio.h>
#include <string.h>

int main() {
    char s[10000010];
    scanf("%s", s);
    int len = strlen(s);
    int maxFreq = 0;
    int freq[10000010] = {0};

    for (int i = 0; i < len; i++) {
        int count = 1;
        for (int j = i + 1; j < len; j++) {
            if (s[i] == s[j]) {
                count++;
            } else {
                break;
            }
        }
        freq[count]++;
        if (count > maxFreq) {
            maxFreq = count;
        }
    }

    printf("%d\n", freq[maxFreq]);
    return 0;
}