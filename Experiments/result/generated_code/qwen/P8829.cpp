#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    double value;
    char from_unit[10], to_unit[10];

    scanf("%lf%s=%s", &value, from_unit, to_unit);

    if (strcmp(from_unit, "B") == 0) {
        if (strcmp(to_unit, "KB") == 0) {
            value /= 1024;
        } else if (strcmp(to_unit, "MB") == 0) {
            value /= 1024 * 1024;
        } else if (strcmp(to_unit, "GB") == 0) {
            value /= 1024 * 1024 * 1024;
        }
    } else if (strcmp(from_unit, "KB") == 0) {
        if (strcmp(to_unit, "B") == 0) {
            value *= 1024;
        } else if (strcmp(to_unit, "MB") == 0) {
            value /= 1024;
        } else if (strcmp(to_unit, "GB") == 0) {
            value /= 1024 * 1024;
        }
    } else if (strcmp(from_unit, "MB") == 0) {
        if (strcmp(to_unit, "B") == 0) {
            value *= 1024 * 1024;
        } else if (strcmp(to_unit, "KB") == 0) {
            value *= 1024;
        } else if (strcmp(to_unit, "GB") == 0) {
            value /= 1024;
        }
    } else if (strcmp(from_unit, "GB") == 0) {
        if (strcmp(to_unit, "B") == 0) {
            value *= 1024 * 1024 * 1024;
        } else if (strcmp(to_unit, "KB") == 0) {
            value *= 1024 * 1024;
        } else if (strcmp(to_unit, "MB") == 0) {
            value *= 1024;
        }
    }

    printf("%.6f\n", value);
    return 0;
}