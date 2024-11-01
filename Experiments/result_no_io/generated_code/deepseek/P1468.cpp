#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_C 10000

int n, c;
int on[MAX_N], off[MAX_N];
int on_count, off_count;

void apply_button(int *lights, int button) {
    switch (button) {
        case 1:
            for (int i = 0; i < n; i++) lights[i] = 1 - lights[i];
            break;
        case 2:
            for (int i = 0; i < n; i += 2) lights[i] = 1 - lights[i];
            break;
        case 3:
            for (int i = 1; i < n; i += 2) lights[i] = 1 - lights[i];
            break;
        case 4:
            for (int i = 0; i < n; i += 3) lights[i] = 1 - lights[i];
            break;
    }
}

int is_valid(int *lights) {
    for (int i = 0; i < on_count; i++) {
        if (lights[on[i]] != 1) return 0;
    }
    for (int i = 0; i < off_count; i++) {
        if (lights[off[i]] != 0) return 0;
    }
    return 1;
}

void print_lights(int *lights) {
    for (int i = 0; i < n; i++) {
        printf("%d", lights[i]);
    }
    printf("\n");
}

int compare_lights(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

void solve() {
    int lights[MAX_N];
    char *results[16];
    int result_count = 0;

    for (int i = 0; i < 16; i++) {
        memset(lights, 1, sizeof(lights));
        int press_count = 0;
        for (int j = 0; j < 4; j++) {
            if (i & (1 << j)) {
                apply_button(lights, j + 1);
                press_count++;
            }
        }
        if (press_count <= c && (c - press_count) % 2 == 0) {
            if (is_valid(lights)) {
                char *result = (char *)malloc(n + 1);
                for (int k = 0; k < n; k++) {
                    result[k] = lights[k] + '0';
                }
                result[n] = '\0';
                results[result_count++] = result;
            }
        }
    }

    if (result_count == 0) {
        printf("IMPOSSIBLE\n");
    } else {
        qsort(results, result_count, sizeof(char *), compare_lights);
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", results[i]);
            free(results[i]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &c);
    on_count = 0;
    off_count = 0;

    int temp;
    while (1) {
        scanf("%d", &temp);
        if (temp == -1) break;
        on[on_count++] = temp - 1;
    }
    while (1) {
        scanf("%d", &temp);
        if (temp == -1) break;
        off[off_count++] = temp - 1;
    }

    solve();

    return 0;
}