#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000000

int main() {
    char input[MAX_LEN];
    scanf("%s", input);

    int len = strlen(input);
    int x = 0;
    int i = 0;

    while (i < len) {
        if (input[i] == 'F' && input[i+1] == 'D') {
            int j = i + 3;
            while (input[j] >= '0' && input[j] <= '9') {
                j++;
            }
            x += atoi(input + i + 3);
            i = j;
        } else if (input[i] == 'B' && input[i+1] == 'K') {
            int j = i + 3;
            while (input[j] >= '0' && input[j] <= '9') {
                j++;
            }
            x -= atoi(input + i + 3);
            i = j;
        } else if (input[i] == 'R' && input[i+1] == 'E' && input[i+2] == 'P' && input[i+3] == 'E' && input[i+4] == 'A' && input[i+5] == 'T') {
            int j = i + 6;
            int repeat_count = 0;
            while (input[j] >= '0' && input[j] <= '9') {
                repeat_count = repeat_count * 10 + (input[j] - '0');
                j++;
            }
            int k = j + 1;
            int temp_x = 0;
            while (input[k] != ']') {
                if (input[k] == 'F' && input[k+1] == 'D') {
                    int l = k + 3;
                    while (input[l] >= '0' && input[l] <= '9') {
                        l++;
                    }
                    temp_x += atoi(input + k + 3);
                    k = l;
                } else if (input[k] == 'B' && input[k+1] == 'K') {
                    int l = k + 3;
                    while (input[l] >= '0' && input[l] <= '9') {
                        l++;
                    }
                    temp_x -= atoi(input + k + 3);
                    k = l;
                }
            }
            x += temp_x * repeat_count;
            i = k + 1;
        } else {
            i++;
        }
    }

    printf("%d\n", abs(x));
    return 0;
}