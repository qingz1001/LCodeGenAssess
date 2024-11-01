#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long value;
    int is_unknown;
} Operand;

int main(){
    char c;
    Operand A, B, C;
    // Parse A
    // Skip leading spaces
    while((c = getchar()) != EOF && isspace(c));
    if(c == '?'){
        A.is_unknown = 1;
        A.value = 0;
    }
    else{
        A.is_unknown = 0;
        long long num = 0;
        do{
            num = num *10 + (c - '0');
            c = getchar();
        }while(isdigit(c));
        A.value = num;
    }
    // Skip spaces
    while(c != EOF && isspace(c)) c = getchar();
    // Operator
    char op = c;
    c = getchar();
    // Skip spaces
    while(c != EOF && isspace(c)) c = getchar();
    // Parse B
    if(c == '?'){
        B.is_unknown = 1;
        B.value = 0;
    }
    else{
        B.is_unknown = 0;
        long long num = 0;
        do{
            num = num *10 + (c - '0');
            c = getchar();
        }while(isdigit(c));
        B.value = num;
    }
    // Skip spaces
    while(c != EOF && isspace(c)) c = getchar();
    // Expect '='
    while(c != '=' && c != EOF){
        c = getchar();
    }
    c = getchar();
    // Skip spaces
    while(c != EOF && isspace(c)) c = getchar();
    // Parse C
    if(c == '?'){
        C.is_unknown = 1;
        C.value = 0;
    }
    else{
        C.is_unknown = 0;
        long long num = 0;
        do{
            num = num *10 + (c - '0');
            c = getchar();
        }while(isdigit(c));
        C.value = num;
    }
    long long result;
    if(A.is_unknown){
        if(op == '+'){
            result = C.value - B.value;
        }
        else{
            result = C.value + B.value;
        }
    }
    else if(B.is_unknown){
        if(op == '+'){
            result = C.value - A.value;
        }
        else{
            result = A.value - C.value;
        }
    }
    else{ // C is unknown
        if(op == '+'){
            result = A.value + B.value;
        }
        else{
            result = A.value - B.value;
        }
    }
    printf("%lld\n", result);
    return 0;
}