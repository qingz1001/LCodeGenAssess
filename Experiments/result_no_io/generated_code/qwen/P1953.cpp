#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 20

void extract_number(const char *filename, int *number) {
    for (int i = strlen(filename) - 1; i >= 0; --i) {
        if (filename[i] >= '0' && filename[i] <= '9') {
            *number = filename[i] - '0';
            break;
        }
    }
}

void format_filename(const char *template, int number, char *result) {
    snprintf(result, MAX_FILENAME_LENGTH, template, number);
}

int main() {
    char input_template[MAX_FILENAME_LENGTH], output_template[MAX_FILENAME_LENGTH];
    int need_reformat = 1;

    scanf("%s", input_template);
    if (input_template[0] == '1' || input_template[0] == '0') {
        need_reformat = atoi(input_template);
    } else {
        scanf("%s", output_template);
    }

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char in_filename[MAX_FILENAME_LENGTH], out_filename[MAX_FILENAME_LENGTH];
        scanf("%s %s", in_filename, out_filename);

        if (need_reformat) {
            int in_number, out_number;
            extract_number(in_filename, &in_number);
            extract_number(out_filename, &out_number);

            char new_in_filename[MAX_FILENAME_LENGTH], new_out_filename[MAX_FILENAME_LENGTH];
            format_filename(input_template, in_number + 1, new_in_filename);
            format_filename(output_template, out_number + 1, new_out_filename);

            printf("%s %s\n", new_in_filename, new_out_filename);
        } else {
            printf("%s %s\n", in_filename, out_filename);
        }
    }

    return 0;
}