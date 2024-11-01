#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;
char operators[3] = {' ', '+', '-'};
char expr[2 * 9 + 1];
 
void backtrack(int i, long sum, long last, char *current, int pos) {
    if (i > N) {
        if (sum == 0) {
            current[pos] = '\0';
            printf("%s\n", current);
        }
        return;
    }
    for(int op = 0; op < 3; op++) {
        char next[2 * 9 + 1];
        strcpy(next, current);
        int new_pos = pos;
        next[new_pos++] = operators[op];
        int num_start = new_pos;
        int len = sprintf(next + new_pos, "%d", i);
        new_pos += len;
        if(operators[op] == ' ') {
            long new_last;
            if(last >= 0)
                new_last = last * 10 + i;
            else
                new_last = last * 10 - i;
            long new_sum = sum - last + new_last;
            backtrack(i+1, new_sum, new_last, next, new_pos);
        }
        else if(operators[op] == '+') {
            backtrack(i+1, sum + i, i, next, new_pos);
        }
        else { // '-'
            backtrack(i+1, sum - i, -i, next, new_pos);
        }
    }
}

int main(){
    scanf("%d", &N);
    strcpy(expr, "1");
    backtrack(2, 1, 1, expr, 1);
    return 0;
}