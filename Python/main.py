from Function import Function #Импортируем класс
from Table import Table

temporary_choosing = 0

while temporary_choosing <= 0 or temporary_choosing > 3:
    print("\n\n F1(x) = sin(x^2 + x^-1 + x^1/3)/tg(e^cos(sqrt(x))) * 10^-6")
    print("\n               e^-(x+0.8), x>3.61\nF2(x) = 1,      0<=x<=3.61\n                0.5x, x<0")
    print("\n F3(x) = cos(x) + cos(2x)/2 + cos(3x)/3 + ...")
    temporary_choosing = int(input("Выберите нужную функцию\n> "))

a, b = map(float, input("Введите интервал (от A до B)\n> ").split())
delay = float(input("Запишите шаг для x\n> "))

res = []

from numpy import arange

for i in arange(a, b+delay, delay):
    Func = Function(temporary_choosing, i)
    res.append(Func.CalculateFunc())

table = Table(res)
table.CreateTable()
table.Create_Plot()