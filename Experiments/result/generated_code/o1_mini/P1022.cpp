#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    char s[1001];
    scanf("%1000s", s);
    char var = 0;
    int len = strlen(s);
    for(int i=0;i<len;i++) {
        if(islower(s[i])){
            var = s[i];
            break;
        }
    }
    int eq = -1;
    for(int i=0;i<len;i++) {
        if(s[i]=='='){
            eq = i;
            break;
        }
    }
    if(eq == -1) return 0;
    char left[1001], right[1001];
    strncpy(left, s, eq);
    left[eq] = '\0';
    strcpy(right, s + eq +1);
    // Function to parse expression
    double parse_coeff=0, parse_const=0;
    auto parse = [&](char *expr, double *coeff, double *const_sum) {
        int i=0;
        int sign=1;
        int len_expr = strlen(expr);
        while(i < len_expr){
            if(expr[i] == '+'){
                sign = 1;
                i++;
            }
            else if(expr[i] == '-'){
                sign = -1;
                i++;
            }
            // Now parse the term
            int start = i;
            int has_num = 0;
            int num = 0;
            while(i < len_expr && isdigit(expr[i])){
                has_num =1;
                num = num*10 + (expr[i]-'0');
                i++;
            }
            if(i < len_expr && expr[i] == var){
                if(has_num){
                    *coeff += sign * num;
                }
                else{
                    *coeff += sign *1;
                }
                i++;
            }
            else{
                if(has_num){
                    *const_sum += sign * num;
                }
            }
        }
    };
    parse(left, &parse_coeff, &parse_const);
    double left_coeff = parse_coeff;
    double left_const = parse_const;
    parse_coeff =0;
    parse_const =0;
    parse(right, &parse_coeff, &parse_const);
    double right_coeff = parse_coeff;
    double right_const = parse_const;
    double numerator = right_const - left_const;
    double denominator = left_coeff - right_coeff;
    double x = numerator / denominator;
    printf("%c=%.3lf", var, x);
    return 0;
}