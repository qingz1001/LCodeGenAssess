#include <stdio.h>
#include <string.h>

int main() {
    char s[100005];
    fgets(s, 100005, stdin);

    int len = strlen(s);
    int windows = 0, linux = 0, mac = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '\\' && s[i + 1] == 'r') {
            if (s[i + 2] == 'n') {
                windows++;
                i += 2;
            } else {
                mac++;
                i += 1;
            }
        } else if (s[i] == '\\' && s[i + 1] == 'n') {
            linux++;
            i += 1;
        }
    }

    if (windows > 0) {
        printf("windows\n");
    } else if (linux > 0) {
        printf("linux\n");
    } else if (mac > 0) {
        printf("mac\n");
    }

    return 0;
}