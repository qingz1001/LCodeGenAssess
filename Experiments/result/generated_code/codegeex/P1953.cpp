#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char first[20], ext[20];
    int change, n;
    scanf("%s", first);

    // Determine if we are changing the main name and extension or just the numbers
    if (strcmp(first, "1") == 0 || strcmp(first, "0") == 0) {
        change = atoi(first);
        scanf("%d", &n);
    } else {
        scanf("%s", ext);
        change = -1;
        n = 0;
        while (scanf("%s", first) != EOF) {
            n++;
        }
        rewind(stdin); // Reset the input buffer
    }

    // Read the input again to process the file names
    for (int i = 0; i < n; i++) {
        if (change != -1) {
            printf("data%d.%s data%d.%s\n", i + change, first, i + change, ext);
        } else {
            int len = strlen(first);
            int num = 0;
            for (int j = len - 1; j >= 0; j--) {
                if (first[j] >= '0' && first[j] <= '9') {
                    num = num * 10 + (first[j] - '0');
                } else {
                    break;
                }
            }
            if (num == 0) {
                num = len;
            }
            first[num - 1] = '\0';
            printf("%s%d.%s %s%d.%s\n", first, i, first + num, first, i, first + num);
        }
    }

    return 0;
}