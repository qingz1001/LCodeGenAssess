#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_digit(int digit){
    if(digit < 10) return '0' + digit;
    else return 'A' + (digit - 10);
}

void convert_to_negative_base(long n, int R, char *result){
    if(n == 0){
        strcpy(result, "0");
        return;
    }
    char temp[100];
    int index = 0;
    long num = n;
    while(num != 0){
        long remainder = num % R;
        num /= R;
        if(remainder < 0){
            remainder -= R;
            num +=1;
        }
        temp[index++] = get_digit(remainder);
    }
    for(int i = 0; i < index; i++) {
        result[i] = temp[index - i -1];
    }
    result[index] = '\0';
}

int main(){
    long n;
    int R;
    while(scanf("%ld %d", &n, &R) != EOF){
        char res[100];
        convert_to_negative_base(n, R, res);
        printf("%s\n", res);
    }
    return 0;
}