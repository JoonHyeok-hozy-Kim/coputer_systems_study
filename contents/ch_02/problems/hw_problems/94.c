#include <stdio.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0xff && frac != 0){
        return f;
    } else if (exp > 0) {
        // printf("%.8x\n", f);
        // printf("%.8x\n", ((f << 1) >> 1) | ~(f | 0x7fffffff));
        exp--;
        return sign << 31 | exp << 23 | frac;
    } else if (exp == 1) {
        // printf("%.8x\n", f);
        // printf("%.8x\n", ((f << 1) >> 1) | ~(f | 0x7fffffff));
        exp = 0;
        frac >>= 1;
        frac |= 0x00400000;
        return sign << 31 | exp << 23 | frac;
    } else {
        frac >>= 1;
        return sign << 31 | exp << 23 | frac;
    }
}

float u2f(unsigned u){
    return *((float *) &u);
}

int main(){
    unsigned u;
    float a, b;

    u = 0x40000000;
    a = u2f(u);
    b = u2f(float_half(u));
    printf("[%d] %.50f vs %.50f (%.8x)\n", a==b*2, a, b, u);

    u = 0x00400000;
    a = u2f(u);
    b = u2f(float_half(u));
    printf("[%d] %.50f vs %.50f (%.8x)\n", a==b*2, a, b, u);

    // for (u=0xff800001; u>=0; u--){
    //     a = u2f(u);
    //     b = u2f(float_twice(u));
    //     printf("[%d] %f vs %f (%.8x)\n", a+b==0, a, b, u);
    // }
}