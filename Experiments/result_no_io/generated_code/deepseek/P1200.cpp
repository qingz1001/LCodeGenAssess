#include <stdio.h>

int calculate_value(char *name) {
    int value = 1;
    for (int i = 0; name[i] != '\0'; i++) {
        value *= (name[i] - 'A' + 1);
    }
    return value % 47;
}

int main() {
    char comet_name[7];
    char group_name[7];

    scanf("%6s", comet_name);
    scanf("%6s", group_name);

    int comet_value = calculate_value(comet_name);
    int group_value = calculate_value(group_name);

    if (comet_value == group_value) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }

    return 0;
}