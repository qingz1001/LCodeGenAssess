#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char s[256];
    fgets(s, sizeof(s), stdin);
    int a=0, b=0, c=0;
    int len = strlen(s);
    for(int i=0;i<len;i++){
        if(s[i]=='a' || s[i]=='b' || s[i]=='c'){
            char var = s[i];
            // Expect ':', '=', so skip until '='
            while(i<len && s[i]!='=') i++;
            if(i<len && s[i]=='=') i++;
            if(i<len && s[i]=='>') i++;
            if(i<len && s[i]=='>') i++;
            if(i<len && s[i]=='>') i++;
            if(i<len && s[i]==';'){
                // Empty assignment, skip
                continue;
            }
            if(i<len && s[i]==':'){
                // Skip
                continue;
            }
            if(i<len && s[i]==':'){
                // Handle ':='
                i++;
                if(i<len && s[i]=='=') i++;
            }
            // Now s[i] should be the value
            if(i<len){
                char val = s[i];
                int num;
                if(isdigit(val)){
                    num = val - '0';
                }
                else{
                    switch(val){
                        case 'a': num = a; break;
                        case 'b': num = b; break;
                        case 'c': num = c; break;
                        default: num = 0;
                    }
                }
                switch(var){
                    case 'a': a = num; break;
                    case 'b': b = num; break;
                    case 'c': c = num; break;
                }
            }
        }
    }
    printf("%d %d %d\n",a,b,c);
    return 0;
}