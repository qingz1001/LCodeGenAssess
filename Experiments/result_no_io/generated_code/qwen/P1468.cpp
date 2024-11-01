#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

void toggle(int *lights, int n) {
    for (int i = 0; i < n; i++) {
        lights[i] = 1 - lights[i];
    }
}

void toggleOdd(int *lights, int n) {
    for (int i = 0; i < n; i += 2) {
        lights[i] = 1 - lights[i];
    }
}

void toggleEven(int *lights, int n) {
    for (int i = 1; i < n; i += 2) {
        lights[i] = 1 - lights[i];
    }
}

void toggleMultipleOfThree(int *lights, int n) {
    for (int i = 0; i < n; i++) {
        if ((i + 1) % 3 == 0) {
            lights[i] = 1 - lights[i];
        }
    }
}

void backtrack(int *lights, int n, int c, int count, int *result, int *resultSize) {
    if (count > c) return;
    if (count == c) {
        int allOff = 1;
        for (int i = 0; i < n; i++) {
            if (lights[i]) {
                allOff = 0;
                break;
            }
        }
        if (allOff) {
            result[*resultSize] = 0;
            (*resultSize)++;
        } else {
            int valid = 1;
            for (int i = 0; i < n; i++) {
                if (lights[i] && result[*resultSize] & (1 << i)) {
                    valid = 0;
                    break;
                }
                if (!lights[i] && !(result[*resultSize] & (1 << i))) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                result[*resultSize] = 1;
                (*resultSize)++;
            }
        }
        return;
    }

    int temp[MAX_N];
    for (int i = 0; i < n; i++) {
        temp[i] = lights[i];
    }

    toggle(lights, n);
    backtrack(lights, n, c, count + 1, result, resultSize);

    for (int i = 0; i < n; i++) {
        lights[i] = temp[i];
    }

    toggleOdd(lights, n);
    backtrack(lights, n, c, count + 1, result, resultSize);

    for (int i = 0; i < n; i++) {
        lights[i] = temp[i];
    }

    toggleEven(lights, n);
    backtrack(lights, n, c, count + 1, result, resultSize);

    for (int i = 0; i < n; i++) {
        lights[i] = temp[i];
    }

    toggleMultipleOfThree(lights, n);
    backtrack(lights, n, c, count + 1, result, resultSize);
}

int main() {
    int n, c;
    scanf("%d %d", &n, &c);

    int *lastOn = (int *)malloc(n * sizeof(int));
    int *lastOff = (int *)malloc(n * sizeof(int));

    int index = 0;
    while (1) {
        int num;
        scanf("%d", &num);
        if (num == -1) break;
        lastOn[index++] = num - 1;
    }

    index = 0;
    while (1) {
        int num;
        scanf("%d", &num);
        if (num == -1) break;
        lastOff[index++] = num - 1;
    }

    int *result = (int *)malloc((1 << n) * sizeof(int));
    int resultSize = 0;

    int initialLights[MAX_N];
    for (int i = 0; i < n; i++) {
        initialLights[i] = 1;
    }

    backtrack(initialLights, n, c, 0, result, &resultSize);

    if (resultSize == 0) {
        printf("IMPOSSIBLE\n");
    } else {
        for (int i = 0; i < resultSize; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d", result[i] & (1 << j) ? 1 : 0);
            }
            printf("\n");
        }
    }

    free(lastOn);
    free(lastOff);
    free(result);

    return 0;
}