#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 20

void parse_filename(const char *filename, char *base, char *ext, int *num) {
    const char *dot = strrchr(filename, '.');
    if (dot == NULL) {
        strcpy(base, filename);
        ext[0] = '\0';
        *num = 0;
        return;
    }
    strncpy(base, filename, dot - filename);
    base[dot - filename] = '\0';
    strcpy(ext, dot + 1);

    char num_str[6];
    int len = strlen(filename);
    for (int i = len - 1; i >= 0; --i) {
        if (isdigit(filename[i])) {
            num_str[len - i - 1] = filename[i];
        } else {
            break;
        }
    }
    num_str[len - i - 1] = '\0';
    *num = atoi(num_str);
}

void generate_new_filenames(const char *input_format, const char *output_format, int n, char input_files[][MAX_FILENAME_LENGTH], char output_files[][MAX_FILENAME_LENGTH]) {
    char base_in[MAX_FILENAME_LENGTH], ext_in[MAX_FILENAME_LENGTH], base_out[MAX_FILENAME_LENGTH], ext_out[MAX_FILENAME_LENGTH];
    int num_in, num_out;

    parse_filename(input_format, base_in, ext_in, &num_in);
    parse_filename(output_format, base_out, ext_out, &num_out);

    for (int i = 0; i < n; ++i) {
        char new_base_in[MAX_FILENAME_LENGTH], new_ext_in[MAX_FILENAME_LENGTH], new_base_out[MAX_FILENAME_LENGTH], new_ext_out[MAX_FILENAME_LENGTH];
        int new_num_in = num_in + i, new_num_out = num_out + i;

        snprintf(new_base_in, sizeof(new_base_in), "%s%d", base_in, new_num_in);
        snprintf(new_ext_in, sizeof(new_ext_in), "%s", ext_in);
        snprintf(new_base_out, sizeof(new_base_out), "%s%d", base_out, new_num_out);
        snprintf(new_ext_out, sizeof(new_ext_out), "%s", ext_out);

        snprintf(input_files[i], MAX_FILENAME_LENGTH, "%s.%s", new_base_in, new_ext_in);
        snprintf(output_files[i], MAX_FILENAME_LENGTH, "%s.%s", new_base_out, new_ext_out);
    }
}

int main() {
    char input_format[MAX_FILENAME_LENGTH], output_format[MAX_FILENAME_LENGTH];
    int n;
    scanf("%s %s\n", input_format, output_format);
    scanf("%d\n", &n);

    char input_files[n][MAX_FILENAME_LENGTH], output_files[n][MAX_FILENAME_LENGTH];

    for (int i = 0; i < n; ++i) {
        scanf("%s %s\n", input_files[i], output_files[i]);
    }

    generate_new_filenames(input_format, output_format, n, input_files, output_files);

    for (int i = 0; i < n; ++i) {
        printf("%s %s\n", input_files[i], output_files[i]);
    }

    return 0;
}