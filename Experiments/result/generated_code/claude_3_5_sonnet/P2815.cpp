#include <stdio.h>
#include <string.h>

void compress_ipv6(char *ipv6) {
    char compressed[40] = {0};
    char *groups[8];
    int group_count = 0;
    char *token = strtok(ipv6, ":");
    
    // 分割IPv6地址为8个组
    while (token != NULL) {
        groups[group_count++] = token;
        token = strtok(NULL, ":");
    }

    int max_zero_start = -1;
    int max_zero_count = 0;
    int current_zero_start = -1;
    int current_zero_count = 0;

    // 寻找最长的连续0组
    for (int i = 0; i < 8; i++) {
        if (strcmp(groups[i], "0000") == 0) {
            if (current_zero_start == -1) {
                current_zero_start = i;
            }
            current_zero_count++;
        } else {
            if (current_zero_count > max_zero_count) {
                max_zero_count = current_zero_count;
                max_zero_start = current_zero_start;
            }
            current_zero_start = -1;
            current_zero_count = 0;
        }
    }

    // 检查最后一组是否为连续的0
    if (current_zero_count > max_zero_count) {
        max_zero_count = current_zero_count;
        max_zero_start = current_zero_start;
    }

    // 压缩IPv6地址
    int compressed_index = 0;
    for (int i = 0; i < 8; i++) {
        if (i == max_zero_start && max_zero_count > 1) {
            strcat(compressed, "::");
            compressed_index += 2;
            i += max_zero_count - 1;
        } else {
            int j = 0;
            while (groups[i][j] == '0' && j < 3) j++;
            strcat(compressed, groups[i] + j);
            compressed_index += strlen(groups[i] + j);
            if (i < 7) {
                compressed[compressed_index++] = ':';
            }
        }
    }

    // 处理特殊情况：全0地址
    if (strcmp(compressed, "::") == 0) {
        strcpy(ipv6, "::");
    } else {
        strcpy(ipv6, compressed);
    }
}

int main() {
    char ipv6[40];
    scanf("%39s", ipv6);
    compress_ipv6(ipv6);
    printf("%s\n", ipv6);
    return 0;
}