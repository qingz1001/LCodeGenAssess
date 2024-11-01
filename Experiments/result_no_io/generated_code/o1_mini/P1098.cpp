#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int p1, p2, p3;
    scanf("%d %d %d", &p1, &p2, &p3);
    char s[105];
    scanf("%s", s);
    int n = strlen(s);
    char output[1005];
    int out_idx = 0;
    for(int i=0;i<n;i++){
        if(s[i] == '-' && i>0 && i<n-1){
            char left = s[i-1];
            char right = s[i+1];
            int is_lower = islower(left) && islower(right);
            int is_digit = isdigit(left) && isdigit(right);
            if( (is_lower || is_digit) && right > left){
                if(right == left +1){
                    // Just remove '-', append right
                    output[out_idx++] = right;
                }
                else{
                    // Expand
                    char fill_chars[100];
                    int fill_cnt =0;
                    for(char c = left +1; c < right; c++) fill_chars[fill_cnt++] = c;
                    // Apply p3
                    if(p3 ==2){
                        for(int j=0; j < fill_cnt/2; j++){
                            char tmp = fill_chars[j];
                            fill_chars[j] = fill_chars[fill_cnt -1 -j];
                            fill_chars[fill_cnt -1 -j] = tmp;
                        }
                    }
                    // Generate expansion
                    for(int j=0; j < fill_cnt; j++){
                        char to_append;
                        if(p1 ==3){
                            to_append = '*';
                        }
                        else{
                            if(is_lower){
                                if(p1 ==1){
                                    to_append = fill_chars[j];
                                }
                                else { // p1 ==2
                                    to_append = toupper(fill_chars[j]);
                                }
                            }
                            else { // digits
                                to_append = fill_chars[j];
                            }
                        }
                        if(p1 ==3){
                            for(int k=0; k < p2; k++) output[out_idx++] = '*';
                        }
                        else{
                            for(int k=0; k < p2; k++) output[out_idx++] = to_append;
                        }
                    }
                }
                continue;
            }
        }
        output[out_idx++] = s[i];
    }
    output[out_idx] = '\0';
    printf("%s", output);
    return 0;
}