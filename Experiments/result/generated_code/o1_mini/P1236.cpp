#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int operand1;
    char operator;
    int operand2;
    int result;
} Operation;

Operation solution_ops[3];
bool found_solution = false;

void search(int numbers[], int n, Operation ops[], int step) {
    if (found_solution) return;
    if (n == 1) {
        if (numbers[0] == 24) {
            for(int i=0;i<step;i++) {
                solution_ops[i] = ops[i];
            }
            found_solution = true;
        }
        return;
    }
    for(int i=0;i<n && !found_solution;i++) {
        for(int j=0;j<n && !found_solution;j++) {
            if(j == i) continue;
            int a = numbers[i];
            int b = numbers[j];
            char operators[] = {'+', '-', '*', '/'};
            for(int o=0;o<4 && !found_solution;o++) {
                char op = operators[o];
                int res;
                bool valid = false;
                switch(op){
                    case '+':
                        res = a + b;
                        valid = true;
                        break;
                    case '-':
                        if(a > b){
                            res = a - b;
                            valid = true;
                        }
                        break;
                    case '*':
                        res = a * b;
                        valid = true;
                        break;
                    case '/':
                        if(b != 0 && a % b == 0){
                            res = a / b;
                            valid = true;
                        }
                        break;
                }
                if(valid){
                    int new_numbers[4];
                    int idx = 0;
                    for(int k=0;k<n;k++) {
                        if(k != i && k != j){
                            new_numbers[idx++] = numbers[k];
                        }
                    }
                    new_numbers[idx++] = res;
                    Operation current_op;
                    current_op.operator = op;
                    if(a >= b){
                        current_op.operand1 = a;
                        current_op.operand2 = b;
                    }
                    else{
                        current_op.operand1 = b;
                        current_op.operand2 = a;
                    }
                    current_op.result = res;
                    ops[step] = current_op;
                    search(new_numbers, idx, ops, step +1);
                }
            }
        }
    }
}

int main(){
    int input[4];
    for(int i=0;i<4;i++) {
        scanf("%d", &input[i]);
    }
    Operation ops[3];
    search(input, 4, ops, 0);
    if(found_solution){
        for(int i=0;i<3;i++) {
            printf("%d%c%d=%d\n", solution_ops[i].operand1, solution_ops[i].operator, solution_ops[i].operand2, solution_ops[i].result);
        }
    }
    else{
        printf("No answer!\n");
    }
    return 0;
}