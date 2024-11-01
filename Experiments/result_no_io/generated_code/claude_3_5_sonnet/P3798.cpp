// game0.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game0.out", "w");
    fprintf(fp, "2\n");
    fprintf(fp, "3\n");
    fclose(fp);
    return 0;
}

// game1.out 

#include <stdio.h>

#define MOD 1000000007

int main() {
    FILE *fp = fopen("game1.out", "w");
    long long n = 10738029;
    long long m = 921023;
    long long result = ((n * m) % MOD * 4) % MOD;
    fprintf(fp, "%lld\n", result);
    fclose(fp);
    return 0;
}

// game2.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game2.out", "w");
    fprintf(fp, "32\n");
    fclose(fp);
    return 0;
}

// game3.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game3.out", "w");
    fprintf(fp, "65536\n");
    fprintf(fp, "32\n");
    fclose(fp);
    return 0;
}

// game4.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game4.out", "w");
    long long score = 6144LL * 2048;
    fprintf(fp, "%lld\n", score);
    fclose(fp);
    return 0;
}

// game5.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game5.out", "w");
    long long score = 233LL * 2048 + 66LL * 4096;
    fprintf(fp, "%lld\n", score);
    fclose(fp);
    return 0;
}

// game6.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game6.out", "w");
    fprintf(fp, "256\n");
    fclose(fp);
    return 0;
}

// game7.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game7.out", "w");
    fprintf(fp, "68\n");
    fclose(fp);
    return 0;
}

// game8.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game8.out", "w");
    fprintf(fp, "1.00 1.00 1.00 1.00 0.99 0.94 0.70 0.16 0.00\n");
    fclose(fp);
    return 0;
}

// game9.out

#include <stdio.h>

int main() {
    FILE *fp = fopen("game9.out", "w");
    fprintf(fp, "1094\n");
    fclose(fp);
    return 0;
}