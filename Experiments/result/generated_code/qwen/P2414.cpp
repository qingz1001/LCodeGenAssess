#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

char s[MAXN];
int queries[MAXM][2];
char print_buffer[MAXN * MAXN];
int print_index;
int print_count;

void process_input(const char *input) {
    int len = strlen(input);
    for (int i = 0; i < len; ++i) {
        if (input[i] == 'B') {
            if (print_index > 0) {
                --print_index;
            }
        } else if (input[i] == 'P') {
            print_buffer[print_index++] = '\0';
            printf("%s\n", print_buffer);
            strcpy(print_buffer, print_buffer + print_index);
            print_index = 0;
        } else {
            print_buffer[print_index++] = input[i];
        }
    }
}

void process_query(int x, int y) {
    const char *str_x = print_buffer + print_index;
    const char *str_y = print_buffer + print_index;
    int count = 0;
    while (*str_x != '\0' && *str_y != '\0') {
        if (*str_x == *str_y) {
            ++count;
            ++str_x;
            ++str_y;
        } else {
            break;
        }
    }
    printf("%d\n", count);
}

int main() {
    scanf("%s", s);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    process_input(s);

    for (int i = 0; i < m; ++i) {
        process_query(queries[i][0], queries[i][1]);
    }

    return 0;
}