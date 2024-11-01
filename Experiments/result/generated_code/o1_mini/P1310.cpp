#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAX 100005

int main(){
    int L;
    scanf("%d", &L);
    if(L == 0){
        // Single variable
        printf("1");
        return 0;
    }
    char s[MAX];
    scanf("%s", s);
    // Operator stack: 0 for '(', 1 for '+', 2 for '*'
    int op_stack[MAX];
    int op_top = -1;
    // Operand stacks
    int count0_stack[MAX];
    int count1_stack[MAX];
    int count_top = -1;
    // Function to get precedence
    int precedence(char op){
        if(op == '*') return 2;
        if(op == '+') return 1;
        return 0;
    }
    // Function to apply operator
    // Returns 1 if applied successfully
    int apply(){
        if(count_top <1){
            // Not enough operands
            return 0;
        }
        char op = op_stack[op_top--];
        int b0 = count0_stack[count_top--];
        int b1 = count1_stack[count_top--];
        int a0 = count0_stack[count_top--];
        int a1 = count1_stack[count_top--];
        int res0, res1;
        if(op == '+'){
            res0 = (a0 * b0) % MOD;
            res1 = (a0 * b1 + a1 * b0 + a1 * b1) % MOD;
        }
        else if(op == '*'){
            res0 = (a0 * b0 + a0 * b1 + a1 * b0) % MOD;
            res1 = (a1 * b1) % MOD;
        }
        count0_stack[++count_top] = res0;
        count1_stack[++count_top] = res1;
        return 1;
    }
    int pos =0;
    int expecting_operand =1;
    while(pos < L){
        if(expecting_operand){
            if(s[pos] == '('){
                op_stack[++op_top] = '(';
                pos++;
            }
            else{
                // Insert implicit variable
                count0_stack[++count_top] =1;
                count1_stack[++count_top] =1;
                expecting_operand =0;
            }
        }
        else{
            if(s[pos] == '+' || s[pos] == '*'){
                char current_op = s[pos];
                while(op_top >=0 && op_stack[op_top] != '(' && precedence(op_stack[op_top]) >= precedence(current_op)){
                    if(!apply()) return 0;
                }
                op_stack[++op_top] = current_op;
                pos++;
                expecting_operand =1;
            }
            else if(s[pos] == ')'){
                while(op_top >=0 && op_stack[op_top] != '('){
                    if(!apply()) return 0;
                }
                if(op_top >=0 && op_stack[op_top] == '('){
                    op_top--;
                }
                pos++;
                expecting_operand =0;
            }
            else{
                // Insert implicit variable
                count0_stack[++count_top] =1;
                count1_stack[++count_top] =1;
                expecting_operand =0;
            }
        }
    }
    while(op_top >=0){
        if(op_stack[op_top] == '('){
            // Mismatched parentheses
            return 0;
        }
        if(!apply()) return 0;
    }
    if(count_top !=0){
        // More than one operand remains
        // Not expected
        return 0;
    }
    printf("%d", count0_stack[count_top]%MOD);
    return 0;
}