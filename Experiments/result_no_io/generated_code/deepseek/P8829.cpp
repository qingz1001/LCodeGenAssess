#include <stdio.h>
#include <string.h>

int main() {
    char input[20];
    scanf("%s", input);

    int value;
    char fromUnit[3], toUnit[3];
    sscanf(input, "%d%2s=%*c%2s", &value, fromUnit, toUnit);

    double conversionFactor[4][4] = {
        {1, 1024, 1024*1024, 1024*1024*1024}, // GB
        {1.0/1024, 1, 1024, 1024*1024},       // MB
        {1.0/(1024*1024), 1.0/1024, 1, 1024}, // KB
        {1.0/(1024*1024*1024), 1.0/(1024*1024), 1.0/1024, 1} // B
    };

    int fromIndex, toIndex;
    char units[4][3] = {"GB", "MB", "KB", "B"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(fromUnit, units[i]) == 0) {
            fromIndex = i;
        }
        if (strcmp(toUnit, units[i]) == 0) {
            toIndex = i;
        }
    }

    double result = value * conversionFactor[fromIndex][toIndex];
    printf("%.6f\n", result);

    return 0;
}