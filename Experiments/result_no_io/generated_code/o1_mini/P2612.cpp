#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(){
    int N;
    long long M;
    int K;
    scanf("%d %lld %d", &N, &M, &K);
    
    // Calculate min and max possible L
    long long minL = N-1;
    // Max L is when permutation alternates between low and high
    // The maximal possible sum is roughly N*N/2
    // To calculate exact max L, use the following:
    // Arrange numbers as 1, N, 2, N-1, 3, N-2, ...
    long long maxL = 0;
    int low = 1, high = N;
    int prev = -1;
    bool flag = true;
    while(low <= high){
        if(flag){
            if(prev != -1){
                maxL += abs(high - prev);
            }
            prev = high;
            high--;
        }
        else{
            if(prev != -1){
                maxL += abs(low - prev);
            }
            prev = low;
            low++;
        }
        flag = !flag;
    }
    
    if(M <= minL){
        // Probability is 1
        printf("1");
        if(K >0){
            printf(".");
            for(int i=0;i<K;i++) printf("0");
        }
        printf("\n");
        return 0;
    }
    if(M > maxL){
        // Probability is 0
        printf("0");
        if(K >0){
            printf(".");
            for(int i=0;i<K;i++) printf("0");
        }
        printf("\n");
        return 0;
    }
    
    // Calculate mean and variance
    double mu = (double)(N-1)*(N+1)/3.0;
    double variance = ((double)(N-1)*(2.0*N*N + N -1))/9.0;
    double sigma = sqrt(variance);
    
    // Calculate z-score
    double z = (M - mu)/sigma;
    
    // Calculate probability using complementary error function
    // P(L >= M) = 0.5 * erfc(z / sqrt(2))
    double P = 0.5 * erfc(z / sqrt(2.0));
    
    // Handle boundary cases where P is very close to 0 or 1
    if(P > 1.0){
        P = 1.0;
    }
    if(P < 0.0){
        P = 0.0;
    }
    
    // Print with K decimal digits, rounding
    // To handle up to K=30, use string manipulation
    char format[20];
    sprintf(format, "%%.%dlf\n", K > 30 ? 30 : K);
    char buffer[100];
    sprintf(buffer, format, P);
    
    // Now handle rounding to exactly K digits
    // Split buffer into integer and fractional parts
    char integer_part[50], fractional_part[50];
    int dot = -1;
    int len = strlen(buffer);
    for(int i=0;i<len;i++) if(buffer[i] == '.'){dot = i; break;}
    if(dot == -1){
        // No decimal point, append one
        printf("%s", buffer);
        if(K >0){
            printf(".");
            for(int i=0;i<K;i++) printf("0");
        }
        printf("\n");
        return 0;
    }
    // Copy integer part
    for(int i=0;i<dot;i++) integer_part[i] = buffer[i];
    integer_part[dot] = '\0';
    // Copy fractional part
    int frac_len = len - dot -1;
    if(frac_len < K){
        for(int i=0;i<frac_len;i++) fractional_part[i] = buffer[dot+1+i];
        for(int i=frac_len;i<K;i++) fractional_part[i] = '0';
        fractional_part[K] = '\0';
    }
    else{
        for(int i=0;i<K;i++) fractional_part[i] = buffer[dot+1+i];
        // Check for rounding
        if(dot+1+K < len){
            if(buffer[dot+1+K] >= '5'){
                // Round up
                int pos = K-1;
                while(pos >=0 && fractional_part[pos] == '9'){
                    fractional_part[pos] = '0';
                    pos--;
                }
                if(pos >=0){
                    fractional_part[pos] +=1;
                }
                else{
                    // Need to carry to integer part
                    int int_len = strlen(integer_part);
                    pos = int_len -1;
                    while(pos >=0 && integer_part[pos] == '9'){
                        integer_part[pos] = '0';
                        pos--;
                    }
                    if(pos >=0){
                        integer_part[pos] +=1;
                    }
                    else{
                        // All digits were 9
                        printf("1");
                        if(K >0){
                            printf(".");
                            for(int i=0;i<K;i++) printf("0");
                        }
                        printf("\n");
                        return 0;
                    }
                }
            }
        }
        fractional_part[K] = '\0';
    }
    
    // Print the result
    printf("%s", integer_part);
    if(K >0){
        printf(".");
        for(int i=0;i<K;i++) printf("%c", fractional_part[i]);
    }
    printf("\n");
    
    return 0;
}