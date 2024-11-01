#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char expr[2005];
    scanf("%2004s", expr);
    int len = strlen(expr);
    int index = 0;
    long long total = 0;
    
    while(index < len){
        // Parse operators or assume '+' if no operator
        char sign = '+';
        int multiplicator = 1;
        int count =1;
        if(expr[index] == '+' || expr[index] == '-'){
            sign = expr[index];
            if(index+1 < len && expr[index+1] == '('){
                // Operator followed by (number)
                index +=2; // skip sign and '('
                // Parse multiplicator
                multiplicator =0;
                while(index < len && isdigit(expr[index])){
                    multiplicator = multiplicator *10 + (expr[index]-'0');
                    index++;
                }
                // expect ')'
                if(index < len && expr[index] == ')'){
                    index++;
                }
                // Now parse term
                long long term =0;
                while(index < len && isdigit(expr[index])){
                    term = term *10 + (expr[index]-'0');
                    index++;
                }
                if(sign == '+'){
                    total += multiplicator * term;
                }
                else{
                    total -= multiplicator * term;
                }
            }
            else{
                // Multiple operators
                char current_sign = expr[index];
                int op_count =0;
                while(index < len && expr[index] == current_sign){
                    op_count++;
                    index++;
                }
                // Now parse term
                long long term =0;
                while(index < len && isdigit(expr[index])){
                    term = term *10 + (expr[index]-'0');
                    index++;
                }
                if(current_sign == '+'){
                    total += (long long)op_count * term;
                }
                else{
                    total -= (long long)op_count * term;
                }
            }
        }
        else{
            // No operator, assume '+'
            // Parse term
            long long term =0;
            while(index < len && isdigit(expr[index])){
                term = term *10 + (expr[index]-'0');
                index++;
            }
            total += term;
        }
    }
    
    printf("%lld", total);
    return 0;
}