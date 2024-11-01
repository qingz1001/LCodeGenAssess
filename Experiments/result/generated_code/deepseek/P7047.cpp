#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_N 1500

void generate_combinations(char *prefix, int n, char **result, int *count) {
    if (n == 0) {
        result[*count] = strdup(prefix);
        (*count)++;
        return;
    }
    char new_prefix[MAX_N + 1];
    strcpy(new_prefix, prefix);
    new_prefix[strlen(prefix)] = '0';
    new_prefix[strlen(prefix) + 1] = '\0';
    generate_combinations(new_prefix, n - 1, result, count);

    new_prefix[strlen(prefix)] = '1';
    new_prefix[strlen(prefix) + 1] = '\0';
    generate_combinations(new_prefix, n - 1, result, count);
}

double calculate_variance(char *data, int n) {
    int len = strlen(data);
    int sub_count = len - n + 1;
    int values[sub_count];
    double mean, variance = 0.0;

    for (int i = 0; i < sub_count; i++) {
        values[i] = 0;
        for (int j = 0; j < n; j++) {
            values[i] = (values[i] << 1) + (data[i + j] - '0');
        }
    }

    mean = 0.0;
    for (int i = 0; i < sub_count; i++) {
        mean += values[i];
    }
    mean /= sub_count;

    for (int i = 0; i < sub_count; i++) {
        variance += (values[i] - mean) * (values[i] - mean);
    }
    variance /= sub_count;

    return variance;
}

int main() {
    char input[MAX_N + 1];
    scanf("%s", input);
    int n = strlen(input);

    char *combinations[1 << n];
    int count = 0;
    generate_combinations("", n, combinations, &count);

    double min_variance = INFINITY;
    char *min_combinations[1 << n];
    int min_count = 0;

    for (int i = 0; i < count; i++) {
        char full_data[2 * n + 1];
        strcpy(full_data, input);
        strcat(full_data, combinations[i]);
        double variance = calculate_variance(full_data, n);
        if (variance < min_variance) {
            min_variance = variance;
            min_count = 0;
            min_combinations[min_count++] = strdup(combinations[i]);
        } else if (variance == min_variance) {
            min_combinations[min_count++] = strdup(combinations[i]);
        }
        free(combinations[i]);
    }

    for (int i = 0; i < min_count; i++) {
        printf("%s\n", min_combinations[i]);
        free(min_combinations[i]);
    }

    return 0;
}