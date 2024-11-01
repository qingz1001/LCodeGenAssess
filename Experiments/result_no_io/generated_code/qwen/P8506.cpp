#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // consume newline character

    int count = 0;

    for (int i = 0; i < n; i++) {
        char line[101];
        fgets(line, sizeof(line), stdin);

        if (strlen(line) > 0 && line[0] == '#') {
            int j = 1;
            while (j < strlen(line) && line[j] == ' ') {
                j++;
            }
            if (j < strlen(line) && line[j] != '#') {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}