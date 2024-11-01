#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int p1, p2, p3;
    scanf("%d %d %d", &p1, &p2, &p3);
    char S[105];
    scanf("%s", S);
    char output[1000];
    int out_idx = 0;
    int len = strlen(S);
    for(int i=0;i<len;i++){
        if(S[i]=='-' && i>0 && i<len-1){
            char left = S[i-1];
            char right = S[i+1];
            if( ((isdigit(left) && isdigit(right)) || (islower(left) && islower(right))) && right > left){
                if(right - left ==1){
                    // Just remove '-'
                    continue;
                }
                int start = left +1;
                int end = right;
                int count = end - start;
                char fill[100];
                int fill_len =0;
                if(p1 ==3){
                    for(int c=start; c<end; c++){
                        for(int j=0; j<p2; j++) fill[fill_len++] = '*';
                    }
                }
                else{
                    for(int c=start; c<end; c++){
                        char ch;
                        if(islower(left)){
                            if(p1 ==1) ch = c;
                            else if(p1 ==2) ch = toupper(c);
                        }
                        else{
                            ch = c;
                        }
                        for(int j=0; j<p2; j++) fill[fill_len++] = ch;
                    }
                }
                // Apply reverse if needed
                if(p3 ==2){
                    for(int j=0; j < fill_len/2; j++){
                        char tmp = fill[j];
                        fill[j] = fill[fill_len-1 -j];
                        fill[fill_len-1 -j] = tmp;
                    }
                }
                // Append fill to output
                for(int j=0; j<fill_len; j++) output[out_idx++] = fill[j];
                i++; // Skip right character
                continue;
            }
        }
        output[out_idx++] = S[i];
    }
    output[out_idx] = '\0';
    printf("%s", output);
}