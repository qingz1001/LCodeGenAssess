#include <stdio.h>
#include <string.h>

int main() {
    char comet[7], group[7];
    int i, cometProduct = 1, groupProduct = 1;

    // Read the comet name
    scanf("%s", comet);
    // Read the group name
    scanf("%s", group);

    // Calculate the product of letters in the comet name
    for (i = 0; comet[i] != '\0'; i++) {
        cometProduct *= (comet[i] - 'A' + 1);
    }

    // Calculate the product of letters in the group name
    for (i = 0; group[i] != '\0'; i++) {
        groupProduct *= (group[i] - 'A' + 1);
    }

    // Check if the products modulo 47 are equal
    if (cometProduct % 47 == groupProduct % 47) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }

    return 0;
}