#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    scanf("%s", input);

    long long num;
    char unit1[5], unit2[5];

    sscanf(input, "%lld%s=?%s", &num, unit1, unit2);

    double result = 0.0;

    if (strcmp(unit1, "GB") == 0) {
        if (strcmp(unit2, "MB") == 0) {
            result = num * 1024.0;
        } else if (strcmp(unit2, "KB") == 0) {
            result = num * 1048576.0;
        } else if (strcmp(unit2, "B") == 0) {
            result = num * 1073741824.0;
        }
    } else if (strcmp(unit1, "MB") == 0) {
        if (strcmp(unit2, "GB") == 0) {
            result = num / 1024.0;
        } else if (strcmp(unit2, "KB") == 0) {
            result = num * 1024.0;
        } else if (strcmp(unit2, "B") == 0) {
            result = num * 1048576.0;
        }
    } else if (strcmp(unit1, "KB") == 0) {
        if (strcmp(unit2, "GB") == 0) {
            result = num / 1048576.0;
        } else if (strcmp(unit2, "MB") == 0) {
            result = num / 1024.0;
        } else if (strcmp(unit2, "B") == 0) {
            result = num * 1024.0;
        }
    } else if (strcmp(unit1, "B") == 0) {
        if (strcmp(unit2, "GB") == 0) {
            result = num / 1073741824.0;
        } else if (strcmp(unit2, "MB") == 0) {
            result = num / 1048576.0;
        } else if (strcmp(unit2, "KB") == 0) {
            result = num / 1024.0;
        }
    }

    printf("%.6f\n", result);

    return 0;
}