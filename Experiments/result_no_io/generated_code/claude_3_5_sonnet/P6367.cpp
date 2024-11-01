#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_NAME_LEN 21

typedef struct {
    char name[MAX_NAME_LEN];
    int count;
} Child;

int main() {
    int n, total_warnings = 0;
    Child children[MAX_N];
    int child_count = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char current_name[MAX_NAME_LEN];
        scanf("%s", current_name);

        int child_index = -1;
        for (int j = 0; j < child_count; j++) {
            if (strcmp(children[j].name, current_name) == 0) {
                child_index = j;
                break;
            }
        }

        if (child_index == -1) {
            strcpy(children[child_count].name, current_name);
            children[child_count].count = 1;
            child_count++;
        } else {
            int others_total = 0;
            for (int j = 0; j < child_count; j++) {
                if (j != child_index) {
                    others_total += children[j].count;
                }
            }

            if (children[child_index].count > others_total) {
                total_warnings++;
            }

            children[child_index].count++;
        }
    }

    printf("%d\n", total_warnings);

    return 0;
}