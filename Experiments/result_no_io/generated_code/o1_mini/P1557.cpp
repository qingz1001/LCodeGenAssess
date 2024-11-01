#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char s[2005];
    fgets(s, sizeof(s), stdin);
    int len = strlen(s);
    long long result =0;
    int i=0;
    while(i < len){
        // Skip any whitespace
        while(i < len && isspace(s[i])) i++;
        if(i >= len) break;

        // Read operators
        int op_start = i;
        int op_count =0;
        int multiplier =0;
        while(i < len && (s[i] == '+' || s[i] == '-')){
            if(s[i] == '+') multiplier +=1;
            else multiplier -=1;
            op_count++;
            i++;
        }

        if(op_count >0){
            if(op_count ==1 && i < len && s[i] == '('){
                // single operator with (digit)
                int sign = (s[op_start] == '+') ? 1 : -1;
                i++; // skip '('
                if(i >= len || !isdigit(s[i])){ 
                    // Invalid format
                    return 0;
                }
                int digit = s[i]-'0';
                i++;
                if(i >= len || s[i] != ')'){
                    // Invalid format
                    return 0;
                }
                i++; // skip ')'
                // Read number
                long long num=0;
                while(i < len && isdigit(s[i])){
                    num = num*10 + (s[i]-'0');
                    i++;
                }
                result += sign * digit * num;
            }
            else{
                // multiple operators, compute multiplier
                // Read number
                long long num=0;
                while(i < len && isdigit(s[i])){
                    num = num*10 + (s[i]-'0');
                    i++;
                }
                result += multiplier * num;
            }
        }
        else{
            // No operators, read number
            long long num=0;
            while(i < len && isdigit(s[i])){
                num = num*10 + (s[i]-'0');
                i++;
            }
            result += num;
        }
    }
    printf("%lld", result);
}