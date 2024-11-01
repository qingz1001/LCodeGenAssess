#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // 读取换行符

    while (N--) {
        int count = 0;
        char c;
        while ((c = getchar()) != '\n') {
            if (c >= 'A' && c <= 'Z') {
                count++;
                while ((c = getchar()) != '\n' && !(c == '.' || c == '?' || c == '!')) {
                    if (c >= 'a' && c <= 'z') {
                        count--;
                        break;
                    }
                }
            }
        }
        printf("%d\n", count);
    }

    return 0;
}