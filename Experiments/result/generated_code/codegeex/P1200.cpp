#include <stdio.h>

int main() {
    char comet[7], group[7];
    scanf("%s%s", comet, group);

    int cometProduct = 1, groupProduct = 1;

    for (int i = 0; comet[i] != '\0'; i++) {
        cometProduct *= comet[i] - 'A' + 1;
    }

    for (int i = 0; group[i] != '\0'; i++) {
        groupProduct *= group[i] - 'A' + 1;
    }

    if (cometProduct % 47 == groupProduct % 47) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }

    return 0;
}