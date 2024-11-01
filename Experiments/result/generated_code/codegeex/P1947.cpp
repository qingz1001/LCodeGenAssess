#include <stdio.h>

extern "C" int Seniorious(int x);

extern "C" int Chtholly(int n, int c) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        int response = Seniorious(mid);
        if (response == 0) {
            return mid;
        } else if (response == 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}