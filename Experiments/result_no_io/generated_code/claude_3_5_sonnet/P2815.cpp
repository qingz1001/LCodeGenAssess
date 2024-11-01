#include <stdio.h>
#include <string.h>

void compress_ipv6(char *ipv6) {
    char result[40] = {0};
    char *groups[8];
    int group_count = 0;
    char *token = strtok(ipv6, ":");
    
    while (token != NULL) {
        groups[group_count++] = token;
        token = strtok(NULL, ":");
    }

    int max_zero_start = -1, max_zero_length = 0;
    int current_zero_start = -1, current_zero_length = 0;

    for (int i = 0; i < 8; i++) {
        if (strcmp(groups[i], "0000") == 0) {
            if (current_zero_start == -1) {
                current_zero_start = i;
            }
            current_zero_length++;
        } else {
            if (current_zero_length > max_zero_length) {
                max_zero_length = current_zero_length;
                max_zero_start = current_zero_start;
            }
            current_zero_start = -1;
            current_zero_length = 0;
        }
    }

    if (current_zero_length > max_zero_length) {
        max_zero_length = current_zero_length;
        max_zero_start = current_zero_start;
    }

    for (int i = 0; i < 8; i++) {
        if (i == max_zero_start && max_zero_length > 1) {
            strcat(result, i == 0 ? "::" : ":");
            i += max_zero_length - 1;
        } else {
            char *ptr = groups[i];
            while (*ptr == '0' && *(ptr + 1) != '\0') ptr++;
            strcat(result, ptr);
            if (i < 7) strcat(result, ":");
        }
    }

    if (result[0] == ':' && result[1] == ':') {
        memmove(result, result + 1, strlen(result));
    }
    
    printf("%s\n", result);
}

int main() {
    char ipv6[40];
    scanf("%39s", ipv6);
    compress_ipv6(ipv6);
    return 0;
}