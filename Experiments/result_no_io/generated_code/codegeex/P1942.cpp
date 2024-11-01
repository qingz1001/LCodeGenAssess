#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char word[1001];
    while (scanf("%s", word) != EOF) {
        int len = strlen(word);
        int sum = 0;
        for (int i = 0; i < len; i++) {
            if (word[i] == '1') {
                sum += i + 1;
            }
        }
        if (sum % (n + 1) == 0) {
            printf("%s\n", word);
        } else if (len < n) {
            for (int i = 0; i <= len; i++) {
                char temp[1001];
                strncpy(temp, word, i);
                temp[i] = '0';
                strncat(temp, word + i, len - i);
                if (strlen(temp) == n) {
                    int temp_sum = 0;
                    for (int j = 0; j < n; j++) {
                        if (temp[j] == '1') {
                            temp_sum += j + 1;
                        }
                    }
                    if (temp_sum % (n + 1) == 0) {
                        printf("%s\n", temp);
                        break;
                    }
                }
            }
            for (int i = 0; i <= len; i++) {
                char temp[1001];
                strncpy(temp, word, i);
                temp[i] = '1';
                strncat(temp, word + i, len - i);
                if (strlen(temp) == n) {
                    int temp_sum = 0;
                    for (int j = 0; j < n; j++) {
                        if (temp[j] == '1') {
                            temp_sum += j + 1;
                        }
                    }
                    if (temp_sum % (n + 1) == 0) {
                        printf("%s\n", temp);
                        break;
                    }
                }
            }
        } else if (len > n) {
            for (int i = 0; i < len; i++) {
                char temp[1001];
                strncpy(temp, word, i);
                strncat(temp, word + i + 1, len - i - 1);
                if (strlen(temp) == n) {
                    int temp_sum = 0;
                    for (int j = 0; j < n; j++) {
                        if (temp[j] == '1') {
                            temp_sum += j + 1;
                        }
                    }
                    if (temp_sum % (n + 1) == 0) {
                        printf("%s\n", temp);
                        break;
                    }
                }
            }
        } else {
            printf("-1\n");
        }
    }
    return 0;
}