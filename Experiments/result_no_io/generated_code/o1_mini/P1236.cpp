#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solution_found = 0;
char solution_steps[3][30];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int search(int nums[], int n, char steps[][30], int step_count) {
    if (solution_found) return 0;
    if (step_count == 3) {
        if (n == 1 && nums[0] == 24) {
            for(int i=0;i<3;i++) {
                strcpy(solution_steps[i], steps[i]);
            }
            solution_found = 1;
        }
        return 0;
    }
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            int a = nums[i];
            int b = nums[j];
            int remaining[n-2];
            int index = 0;
            for(int k=0; k<n; k++) {
                if(k != i && k != j) {
                    remaining[index++] = nums[k];
                }
            }
            // Addition
            {
                int res = a + b;
                char step[30];
                sprintf(step, "%d+%d=%d", max(a,b), min(a,b), res);
                char new_steps[3][30];
                for(int s=0;s<step_count;s++) strcpy(new_steps[s], steps[s]);
                strcpy(new_steps[step_count], step);
                int new_nums[n-1];
                for(int k=0; k<n-2; k++) new_nums[k] = remaining[k];
                new_nums[n-2] = res;
                search(new_nums, n-1, new_steps, step_count+1);
                if(solution_found) return 0;
            }
            // Subtraction a - b
            if(a > b) {
                int res = a - b;
                char step[30];
                sprintf(step, "%d-%d=%d", a, b, res);
                char new_steps[3][30];
                for(int s=0;s<step_count;s++) strcpy(new_steps[s], steps[s]);
                strcpy(new_steps[step_count], step);
                int new_nums[n-1];
                for(int k=0; k<n-2; k++) new_nums[k] = remaining[k];
                new_nums[n-2] = res;
                search(new_nums, n-1, new_steps, step_count+1);
                if(solution_found) return 0;
            }
            // Subtraction b - a
            if(b > a) {
                int res = b - a;
                char step[30];
                sprintf(step, "%d-%d=%d", b, a, res);
                char new_steps[3][30];
                for(int s=0;s<step_count;s++) strcpy(new_steps[s], steps[s]);
                strcpy(new_steps[step_count], step);
                int new_nums[n-1];
                for(int k=0; k<n-2; k++) new_nums[k] = remaining[k];
                new_nums[n-2] = res;
                search(new_nums, n-1, new_steps, step_count+1);
                if(solution_found) return 0;
            }
            // Multiplication
            {
                int res = a * b;
                char step[30];
                sprintf(step, "%d*%d=%d", max(a,b), min(a,b), res);
                char new_steps[3][30];
                for(int s=0;s<step_count;s++) strcpy(new_steps[s], steps[s]);
                strcpy(new_steps[step_count], step);
                int new_nums[n-1];
                for(int k=0; k<n-2; k++) new_nums[k] = remaining[k];
                new_nums[n-2] = res;
                search(new_nums, n-1, new_steps, step_count+1);
                if(solution_found) return 0;
            }
            // Division a / b
            if(b != 0 && a % b == 0) {
                int res = a / b;
                char step[30];
                sprintf(step, "%d/%d=%d", a, b, res);
                char new_steps[3][30];
                for(int s=0;s<step_count;s++) strcpy(new_steps[s], steps[s]);
                strcpy(new_steps[step_count], step);
                int new_nums[n-1];
                for(int k=0; k<n-2; k++) new_nums[k] = remaining[k];
                new_nums[n-2] = res;
                search(new_nums, n-1, new_steps, step_count+1);
                if(solution_found) return 0;
            }
            // Division b / a
            if(a != 0 && b % a == 0) {
                int res = b / a;
                char step[30];
                sprintf(step, "%d/%d=%d", b, a, res);
                char new_steps[3][30];
                for(int s=0;s<step_count;s++) strcpy(new_steps[s], steps[s]);
                strcpy(new_steps[step_count], step);
                int new_nums[n-1];
                for(int k=0; k<n-2; k++) new_nums[k] = remaining[k];
                new_nums[n-2] = res;
                search(new_nums, n-1, new_steps, step_count+1);
                if(solution_found) return 0;
            }
        }
    }
    return 0;
}

int main(){
    int input[4];
    for(int i=0;i<4;i++) scanf("%d", &input[i]);
    char steps[3][30];
    search(input, 4, steps, 0);
    if(solution_found){
        for(int i=0;i<3;i++) printf("%s\n", solution_steps[i]);
    }
    else{
        printf("No answer!\n");
    }
    return 0;
}