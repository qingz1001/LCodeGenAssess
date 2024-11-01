#include <stdio.h>
#include <string.h>

double convert(int value, const char *from, const char *to) {
    double base = 1.0;
    if (strcmp(from, "GB") == 0) base *= 1024 * 1024 * 1024;
    else if (strcmp(from, "MB") == 0) base *= 1024 * 1024;
    else if (strcmp(from, "KB") == 0) base *= 1024;
    else if (strcmp(from, "B") == 0) base *= 1;

    double result = value * base;

    if (strcmp(to, "GB") == 0) result /= (1024 * 1024 * 1024);
    else if (strcmp(to, "MB") == 0) result /= (1024 * 1024);
    else if (strcmp(to, "KB") == 0) result /= 1024;
    else if (strcmp(to, "B") == 0) result /= 1;

    return result;
}

int main() {
    char input[20];
    scanf("%s", input);

    int value;
    char from[3], to[3];
    sscanf(input, "%d%2s=?%2s", &value, from, to);

    double result = convert(value, from, to);
    printf("%.6f\n", result);

    return 0;
}