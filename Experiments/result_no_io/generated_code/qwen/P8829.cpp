#include <stdio.h>
#include <string.h>

int main() {
    int value;
    char unit1[4], unit2[4];
    scanf("%d %s =? %s", &value, unit1, unit2);

    double factor;
    if (strcmp(unit1, "GB") == 0) factor = 1.0 / (1 << 30);
    else if (strcmp(unit1, "MB") == 0) factor = 1.0 / (1 << 20);
    else if (strcmp(unit1, "KB") == 0) factor = 1.0 / (1 << 10);
    else if (strcmp(unit1, "B") == 0) factor = 1.0;

    if (strcmp(unit2, "GB") == 0) factor /= 1.0 / (1 << 30);
    else if (strcmp(unit2, "MB") == 0) factor /= 1.0 / (1 << 20);
    else if (strcmp(unit2, "KB") == 0) factor /= 1.0 / (1 << 10);
    else if (strcmp(unit2, "B") == 0) factor /= 1.0;

    printf("%.6f\n", value * factor);

    return 0;
}