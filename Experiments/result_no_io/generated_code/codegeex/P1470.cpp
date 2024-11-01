#include <stdio.h>
#include <string.h>

#define MAX_P 201
#define MAX_LEN 10

int main() {
    char P[MAX_P][MAX_LEN + 1];
    int numP = 0;
    char line[77];
    int len;

    // 读取元素集合
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (line[0] == '.' && line[1] == '\n') {
            break;
        }
        sscanf(line, "%s", P[numP]);
        numP++;
    }

    // 读取序列 S
    char S[200001];
    fgets(S, sizeof(S), stdin);
    len = strlen(S);
    S[len - 1] = '\0';  // 去掉末尾的换行符

    int maxPrefixLength = 0;
    int currentPrefixLength = 0;

    while (1) {
        int found = 0;
        for (int i = 0; i < numP; i++) {
            if (strncmp(S + currentPrefixLength, P[i], strlen(P[i])) == 0) {
                currentPrefixLength += strlen(P[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            break;
        }
        maxPrefixLength = currentPrefixLength;
    }

    printf("%d\n", maxPrefixLength);
    return 0;
}