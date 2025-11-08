#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

typedef double (*FuncPtr)(double);

#define EPS 1e-6 // 10^-6

double f1(double x) {

    return (sin(x*x + pow(x, -1) + cbrt(x)) * EPS)/tan((exp(cos(sqrt(fabs(x))))));

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

    for (int i = 1; i <= 10; i++ ) {
        sum+= cos(i*x)/i;
    }

    return sum;

}

void Print_Table(FuncPtr f, double a, double b, double step) {

    printf("\n      x\t\tf(x)\n");
    printf("------------------------\n");
    for (double x = a; x <= b; x += step) {
        printf("%10.3f\t%14.6e\n");
    }
}

void Write_To_txt(FuncPtr f, double a, double b, double step) {

    FILE *fp = fopen("dat.txt", "w");

    if (!fp) {
        printf("Ошибка открытия!");
        return;
    }

    for (double x = a; x <= b; x += step) {
        fprintf(fp, "%.6f\t%.6e\n");
    }
    fclose(fp);
    printf("Успешно записано!");

}

void Compute_File(FuncPtr f) {

    FILE *fp = fopen("dat.txt", "r");

    if (!fp) {
        printf("Файл не найден.");
    }

    double x, y;

    while (fscanf(fp, "%lf\t%lf", &x, &y) == 1) {
        printf("f(%.3f) = %.6e\n", x, y);
    }
    fclose(fp);

}

double Golden(FuncPtr f, double a, double b) {
    const double phi = (1 + sqrt(5)) / 2;

    double c, d;

    while (fabs(b - a) > EPS)
    {
        c = b - (b - a) / phi;
        d = a + (b - a) / phi;

        if (f(c) < f(d)) {
            a = c;
            } else {
                b = d;
            }
    }
    
    return (a + b) / 2;

}

void Describe_Func(FuncPtr f, double a, double b, double step) {

    double prev = f(a);
    int increasing = 0, decreasing = 0, ch_sign = 0;
    double prev_sign = (prev > 0) - (prev < 0);

    for (double x = a + step; x <= b; x+=step) {

        double y = f(x);

        if (y > prev) { 
            increasing++; 
            } else {
                decreasing++;
        }
        
        double sign = (y > 0) - (y < 0);

        if (sign != 0 && sign != prev_sign && prev_sign != 0) {
            ch_sign++;
        }

        prev = y;

        prev_sign = sign;

    }

    printf("Функция");

    if (increasing && !decreasing) {
        printf("возрастающая.\n");
        } else if (decreasing && !increasing) {
            printf("убывающая.\n");
            } else {
                printf("не монотонна.\n");
            }

            if (ch_sign > 0) {
                printf("Функция знакопеременная.\n");
                } else {
                printf("Функция одного знака.\n");
            }

            if (fabs(f(-b) - f(b)) < 1e-3) {
                printf("Функция симметрична.\n");
                } else {
                    printf("Функция несимметрична.\n");
            }

}

//Mass

typedef struct {
    double x;
    double y;
} Point;


void Make_Points(FuncPtr f, double a, double b, double step) {

    int n = (int)((b-a) / step) + 1;

    Point *arr = malloc(n*sizeof(Point));

    int i = 0;

    for (double x = a; x <= b; x += step) {

        arr[i].x = x;
        arr[i].y = f(x);

        i++;
        
    }

    printf("\nТочки:\n");
    for (int j = 0; j < n; j++) {

        printf("(%.3f, %.6e)\n", arr[j].x, arr[j].y);

    }

    free(arr);

}

void Make_Matrix(FuncPtr f, double a, double b, double step) {

    int n = (int)((b-a) / step) + 1;
    double **matrix = malloc(n*sizeof(double *));

    double x = a;

    for (int i = 0; i < n; i++) {
        matrix[i][0] = x;
        matrix[i][1] = f(x);
    }

    printf("\nМассив аргументов и значений:\n");

    for (int i = 0; i < n; i++) {
        printf("x = %.3f\tf(x) = %.6e\n", matrix[i][0], matrix[i][1]);
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }

    free(matrix);

}

void Range(FuncPtr f, double a, double b, double step) {

    double Min_X = a, Max_X = b;
    double Min_Y = f(a), Max_Y = f(b);

    for (double x = a; x <= b; x += step) {
        double y = f(x);

        if (y < Min_Y) {
            Min_Y = y;
            } else {
                Max_Y = y;
            }   
    }
    
    printf("Размах по Ox: %.3f\n", fabs(Max_X-Min_X));
    printf("Размах по Oy: %.6e\n", fabs(Max_Y-Min_Y));

}

FuncPtr Select_Func() {

    int ch;

    printf("\nВыберите функцию:\n");

    printf("1 - f1(x)\n2 - f2(x)\n3 - f3(x)\n> "); scanf("%d", &ch);

    switch (ch) {

        case 1: return f1;

        case 2: return f2;

        case 3: return f3;

        default: return NULL;

    }
}

//-----------------------------------------------------------------------------

int main(void) {

    setlocale(LC_ALL, ".UTF-8");

    int choise;

    while (1) {

        printf("\n====МЕНЮ====\n");

        printf("\n1- Вычислить значение\n2 - Табулировать\n3 - Выполнить операцию\n4 - Выход\n> "); scanf("%d", &choise);

        if (choise == 4) {break;}

        FuncPtr f = Select_Func();

        if (!f) {printf("Неверный выбор fn(x)!");}

        double a, b, step, x;

        printf("Введите начало, конец интервала и шаг (чз пробел): ");scanf("%lf %lf %lf", &a, &b, &step);

        switch (choise)
        {
        
            case 1:
                printf("Введите x:");scanf("%lf", &x);
                printf("f(x) = %.6e\n", f(x));
                break;
            
            case 2:
                Print_Table(f, a, b, step);
                break;
            
            case 3:
                int op;

                printf("Выберите операцию:\n1 - Запись в файл dat.txt\n2 - Расчет из файла dat.txt\n3 - Построение графика(Python)\n4 - Поиск максимума\n5 - Анализ функции\n6 - Массив точек\n7 - Двумерный массив аргументов и значений\n8 - Размах функции\n> ");
                scanf("%d", &op);

                switch (op)
                {
                case 1:
                    Write_To_txt(f, a, b, step);
                    break;

                case 2:
                    Compute_File(f);
                    break;

                case 3:
                    system("PyPlot.exe");
                    break;

                case 4:
                    printf("Максимум при x = %.6f\n", Golden(f, a, b));
                    break;
                
                case 5:
                    Describe_Func(f, a, b, step);
                    break;

                case 6:
                    Make_Points(f, a, b, step);
                    break;
                
                case 7:
                    Make_Matrix(f, a, b, step);
                    break;

                case 8:
                    Range(f, a, b, step);
                    break;
                
                default:
                    printf("Неверный номер операции!");
                    break;
                }
            default:
                printf("Неверный пункт меню!");
        }
    }

    printf("Программа завершена.\n");
    return 0;

}