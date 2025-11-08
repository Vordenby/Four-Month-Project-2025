#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

double Golden(FuncPtr f, double a, double b) {
    double phi = (1 + sqrt(5)) / 2;
    double resphi = 2 - phi;
    
    double x1 = a + resphi * (b - a);
    double x2 = b - resphi * (b - a);
    
    double f1 = f(x1);
    double f2 = f(x2);
    
    while (fabs(b - a) > 1e-6) {
        if (f1 > f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + resphi * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = b - resphi * (b - a);
            f2 = f(x2);
        }
    }
    
    return (a + b) / 2;
}

void Describe_Func(FuncPtr f, double a, double b, double step) {
    double max = f(a);
    double min = f(a);
    int mon = 1;
    int ch_sign = 0;
    
    for (double x = a; x <= b; x += step) {
        double y = f(x);
        if (y > max) max = y;
        if (y < min) min = y;
        
        if (x != a && (y - f(x - step)) * (y - f(x + step)) > 0) {
            mon = 0;
        }
        
        if (y < 0) ch_sign--;
        else if (y > 0) ch_sign++;
    }
    
    printf("Максимум: %.6e\n", max);
    printf("Минимум: %.6e\n", min);
    
    if (mon) {
        printf("Функция монотонна.\n");
    } else {
        printf("не монотонна.\n");
    }
    
    if (ch_sign > 0) {
        printf("Функция знакопеременная.\n");
    } else {
        printf("Функция одного знака.\n");
    }
    
    double test_x = b;
    if (test_x != 0) {
        double y1 = f(test_x);
        double y2 = f(-test_x);
        if (fabs(y1 - y2) < 1e-3) {
            printf("Функция четная.\n");
        } else {
            printf("Функция нечетная.\n");
        }
    }
}

void Range(FuncPtr f, double a, double b, double step) {
    double max = f(a);
    double min = f(a);
    
    for (double x = a; x <= b; x += step) {
        double y = f(x);
        if (y > max) max = y;
        if (y < min) min = y;
    }
    
    printf("Диапазон: от %.6e до %.6e\n", min, max);
}

void Make_Points(FuncPtr f, double a, double b, double step) {
    FILE *fp = fopen("points.dat", "w");
    if (!fp) {
        printf("Ошибка открытия!\n");
        return;
    }
    
    for (double x = a; x <= b; x += step) {
        fprintf(fp, "%.6f\t%.6e\n", x, f(x));
    }
    fclose(fp);
    printf("Точки успешно записаны в файл points.dat\n");
}

void Make_Matrix(FuncPtr f, double a, double b, double step) {
    FILE *fp = fopen("matrix.dat", "w");
    if (!fp) {
        printf("Ошибка открытия!\n");
        return;
    }
    
    for (double x = a; x <= b; x += step) {
        fprintf(fp, "%.6f\t%.6e\n", x, f(x));
    }
    fclose(fp);
    printf("Матрица успешно записана в файл matrix.dat\n");
}

typedef struct {
    double x;
    double y;
} Point;

void Print_Table(FuncPtr f, double a, double b, double step) {
    printf("\n      x\t\tf(x)\n");
    printf("------------------------\n");
    for (double x = a; x <= b; x += step) {
        printf("%10.3f\t%14.6e\n", x, f(x));
    }
}

void Write_To_txt(FuncPtr f, double a, double b, double step) {
    FILE *fp = fopen("dat.txt", "w");
    
    if (!fp) {
        printf("Ошибка открытия!\n");
        return;
    }
    
    for (double x = a; x <= b; x += step) {
        fprintf(fp, "%.6f\t%.6e\n", x, f(x));
    }
    fclose(fp);
    printf("Успешно записано!\n");
}

void Compute_File(FuncPtr f) {
    FILE *fp = fopen("dat.txt", "r");
    
    if (!fp) {
        printf("Файл не найден.\n");
        return;
    }
    
    double x, y;
    
    while (fscanf(fp, "%lf\t%lf", &x, &y) == 2) {
        printf("f(%.3f) = %.6e\n", x, y);
    }
    fclose(fp);
}


FuncPtr Select_Func() {
    int ch;
    
    printf("\nВыберите функцию:\n");
    printf("1 - f1(x)\n2 - f2(x)\n3 - f3(x)\n> ");
    scanf("%d", &ch);
    
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
        printf("\n1 - Вычислить значение\n2 - Табулировать\n3 - Выполнить операцию\n4 - Выход\n> ");
        scanf("%d", &choise);
        
        if (choise == 4) {
            break;
        }
        
        FuncPtr f = Select_Func();
        
        if (!f) {
            printf("Неверный выбор fn(x)!\n");
            continue;
        }
        
        double a, b, step, x;
        printf("Введите начало, конец интервала и шаг (через пробел): ");
        scanf("%lf %lf %lf", &a, &b, &step);
        
        switch (choise) {
            case 1:
                printf("Введите x: ");
                scanf("%lf", &x);
                printf("f(x) = %.6e\n", f(x));
                break;
            
            case 2:
                Print_Table(f, a, b, step);
                break;
            
            case 3:
                int op;
                printf("Выберите операцию:\n1 - Запись в файл dat.txt\n2 - Расчет из файла dat.txt\n3 - Построение графика (Python)\n4 - Поиск максимума\n5 - Анализ функции\n6 - Массив точек\n7 - Двумерный массив аргументов и значений\n8 - Размах функции\n> ");
                scanf("%d", &op);
                
                switch (op) {
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
                        printf("Неверный номер операции!\n");
                        break;
                }
                break;
            
            default:
                printf("Неверный пункт меню!\n");
                break;
        }
    }
    
    printf("Программа завершена.\n");
    return 0;
}
