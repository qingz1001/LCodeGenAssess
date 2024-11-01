#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1001
#define MAX_LENGTH 11

int main() {
    int n, m;
    scanf("%d", &n);
    char words[MAX_WORDS][MAX_LENGTH];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    scanf("%d", &m);
    char article[MAX_WORDS][MAX_LENGTH];
    for (int i = 0; i < m; i++) {
        scanf("%s", article[i]);
    }

    int count = 0, maxCount = 0, minLen = m;
    int start = 0, end = 0;
    int visited[MAX_WORDS] = {0};

    while (end < m) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && strcmp(words[i], article[end]) == 0) {
                visited[i] = 1;
                count++;
                found = 1;
                break;
            }
        }
        if (found) {
            end++;
            if (count > maxCount) {
                maxCount = count;
                minLen = end - start;
            } else if (count == maxCount) {
                minLen = (end - start) < minLen ? (end - start) : minLen;
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (visited[i] && strcmp(words[i], article[start]) == 0) {
                    visited[i] = 0;
                    count--;
                    break;
                }
            }
            start++;
        }
    }

    printf("%d\n%d\n", maxCount, minLen);
    return 0;
}