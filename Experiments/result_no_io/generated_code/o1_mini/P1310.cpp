#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007

typedef struct {
    int count0;
    int count1;
} CountPair;

int main(){
    int L;
    scanf("%d", &L);
    char *operators = (char*)malloc((L+1)*sizeof(char));
    scanf("%s", operators);
    
    // Build the expression
    int expr_size = 2*L +1;
    char *expr = (char*)malloc((2*L +2)*sizeof(char));
    int expr_idx =0;
    expr[expr_idx++] = '_';
    for(int i=0;i<L;i++){
        expr[expr_idx++] = operators[i];
        if(operators[i] != ')'){
            expr[expr_idx++] = '_';
        }
    }
    int expr_len = expr_idx;
    
    free(operators);
    
    // Shunting Yard to convert to RPN
    char *rpn = (char*)malloc((expr_len+1)*sizeof(char));
    int rpn_len =0;
    
    char *op_stack = (char*)malloc((expr_len+1)*sizeof(char));
    int op_top = -1;
    
    // Define precedence
    int precedence(char c){
        if(c == '*') return 2;
        if(c == '+') return 1;
        return 0;
    }
    
    for(int i=0;i<expr_len;i++){
        char token = expr[i];
        if(token == '_'){
            rpn[rpn_len++] = token;
        }
        else if(token == '('){
            op_stack[++op_top] = token;
        }
        else if(token == ')'){
            while(op_top >=0 && op_stack[op_top] != '('){
                rpn[rpn_len++] = op_stack[op_top--];
            }
            if(op_top >=0 && op_stack[op_top] == '('){
                op_top--;
            }
        }
        else { // operator '+' or '*'
            while(op_top >=0 && op_stack[op_top] != '(' && precedence(op_stack[op_top]) >= precedence(token)){
                rpn[rpn_len++] = op_stack[op_top--];
            }
            op_stack[++op_top] = token;
        }
    }
    while(op_top >=0){
        rpn[rpn_len++] = op_stack[op_top--];
    }
    free(op_stack);
    free(expr);
    
    // Evaluate RPN
    CountPair *stack_cp = (CountPair*)malloc((rpn_len+1)*sizeof(CountPair));
    int stack_size_cp =0;
    
    for(int i=0;i<rpn_len;i++){
        char token = rpn[i];
        if(token == '_'){
            stack_cp[stack_size_cp].count0 =1;
            stack_cp[stack_size_cp].count1 =1;
            stack_size_cp++;
        }
        else { // operator '+' or '*'
            if(stack_size_cp <2){
                // Invalid expression, but as per problem constraints, assume valid
            }
            CountPair b = stack_cp[--stack_size_cp];
            CountPair a = stack_cp[--stack_size_cp];
            CountPair res;
            if(token == '+'){
                res.count0 = (a.count0 * b.count0) % MOD;
                long long total = ((long long)(a.count0 + a.count1) * (b.count0 + b.count1)) % MOD;
                res.count1 = (total - ((long long)a.count0 * b.count0) % MOD) % MOD;
                if(res.count1 <0) res.count1 += MOD;
            }
            else if(token == '*'){
                res.count1 = ((long long)a.count1 * b.count1) % MOD;
                long long total = ((long long)(a.count0 + a.count1) * (b.count0 + b.count1)) % MOD;
                res.count0 = (total - ((long long)a.count1 * b.count1) % MOD) % MOD;
                if(res.count0 <0) res.count0 += MOD;
            }
            stack_cp[stack_size_cp++] = res;
        }
    }
    free(rpn);
    
    if(stack_size_cp !=1){
        // Invalid expression, but assume valid
    }
    printf("%d\n", stack_cp[0].count0);
    free(stack_cp);
    return 0;
}