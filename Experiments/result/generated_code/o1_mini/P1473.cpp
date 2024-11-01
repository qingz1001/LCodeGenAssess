#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N;
char expr[30];

void backtrack(int pos, int sum, int last_num, int length) {
    if (pos > N) {
        if (sum == 0) {
            expr[length] = '\0';
            printf("%s\n", expr);
        }
        return;
    }

    // Operator '+'
    char temp[30];
    int new_sum = sum + pos;
    int new_last = pos;
    memcpy(temp, expr, length);
    temp[length++] = '+';
    int len = sprintf(temp + length, "%d", pos);
    backtrack(pos + 1, new_sum, new_last, length + len);

    // Operator '-'
    memcpy(temp, expr, length);
    temp[length++] = '-';
    new_sum = sum - pos;
    new_last = -pos;
    len = sprintf(temp + length, "%d", pos);
    backtrack(pos + 1, new_sum, new_last, length + len);

    // Operator ' ' (space)
    memcpy(temp, expr, length);
    temp[length++] = ' ';
    // Concatenate current number
    // Remove last_num from sum
    int combined_num = last_num * 10 + pos;
    new_sum = sum - last_num + combined_num;
    len = sprintf(temp + length, "%d", pos);
    backtrack(pos + 1, new_sum, combined_num, length + len);
}

int main(){
    scanf("%d", &N);
    sprintf(expr, "1");
    backtrack(2, 1, 1, 1);
    return 0;
}