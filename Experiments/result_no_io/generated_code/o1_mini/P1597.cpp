#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char s[256];
    fgets(s, sizeof(s), stdin);
    int a=0, b=0, c=0;
    int len = strlen(s);
    int i=0;
    while(i < len){
        // Skip any non a,b,c
        if(s[i]=='a' || s[i]=='b' || s[i]=='c'){
            char var = s[i];
            i++;
            // Check for :=
            if(s[i] == ':' && s[i+1] == '='){
                i +=2;
                // Get RHS
                char rhs = s[i];
                int value=0;
                if(isdigit(rhs)){
                    value = rhs - '0';
                }
                else{
                    if(rhs == 'a') value = a;
                    else if(rhs == 'b') value = b;
                    else if(rhs == 'c') value = c;
                }
                // Assign
                if(var == 'a') a = value;
                else if(var == 'b') b = value;
                else if(var == 'c') c = value;
                i++;
            }
        }
        else{
            i++;
        }
    }
    printf("%d %d %d\n", a, b, c);
    return 0;
}