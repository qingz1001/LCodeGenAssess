#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define MAX_LEN 30000

int n;
char viruses[MAX_N][MAX_LEN];
int virus_len[MAX_N];

int is_safe(char *code, int len) {
    for (int i = 0; i < n; i++) {
        if (strstr(code, viruses[i]) != NULL) {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", viruses[i]);
        virus_len[i] = strlen(viruses[i]);
    }

    char code[MAX_LEN + 1];
    strcpy(code, "0");
    int pos = 1;

    while (pos < MAX_LEN) {
        if (is_safe(code, pos)) {
            printf("TAK\n");
            return 0;
        }
        if (pos + virus_len[0] <= MAX_LEN) {
            strcat(code, viruses[0]);
            pos += virus_len[0];
        } else {
            break;
        }
    }

    printf("NIE\n");
    return 0;
}