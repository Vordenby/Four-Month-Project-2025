#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

#define _USE_MATH_DEFINES
#define EPS 1e-6

typedef double (*FuncPtr)(double);

double f1(double x) {
    if (x == 0) return 0;
    
    double numerator = sin(x*x + pow(x, -1) + cbrt(x)) * EPS;
    double denominator = tan(exp(cos(sqrt(fabs(x)))));
    
    if (denominator == 0) return 0;
    
    return numerator / denominator;
}

double f2(double x) {
    if (x > 3.61) {
        return exp(-(x+0.8)); 
    } else if (x >= 0) {
        return 1;
    } else {
        return 0.5*x;
    }
}

double f3(double x) {
    double sum = 0;
    
    for (int i = 1; i <= 10; i++) {
        if (i == 0) continue;
        sum += cos(i*x)/i;
    }
    
    return sum;
}

int main(void) {

    while (1)
    {

        short int choose, chf;
        
        printf("\nВыберите функцию:\n");
        printf("1 - f1(x)\n2 - f2(x)\n3 - f3(x)\n> ");
        scanf("%d", &chf);

        if (chf == 1) {
            FuncPtr f = f1;
            } else if (chf == 2) {
                FuncPtr f = f2;
                } else if (chf == 3) {
                    FuncPtr f = f3;
                    } else {
                        FuncPtr f = NULL;
                        }

        printf("\n МЕНЮ \n");
        printf("1 - Найти значение F(x) при заданном значении x\n2 - Вычислить значения F(x) на интервале\n\n");
    }
    


}