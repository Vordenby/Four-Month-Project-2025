class Function():

    def __init__(self, function, x): #Записываем переменный результат
        self.result = [] #Результат будет состоять из двумерного списка планом [x, y] с шагом x += 0.1
        self.function = function
        self.x = x
        self.y = 0

    def CalculateFunc(self):
        
        from math import sin, cos, exp, pow, sqrt, tan, pi

        if self.function == 1:
            try:
                if self.x < 0:
                    raise ValueError("Аргумент не должен быть меньше 0!")
                if cos(sqrt(self.x)) == 0:
                    raise ValueError("Аргумент не должен быть равным Pi/2 + n*Pi!")
                self.y = ((sin((self.x**2)+(self.x**-1)+(pow(self.x, 1/3))))/tan(exp(cos(sqrt(self.x)))))*pow(10, -6)
            except ValueError as Error:
                print(Error)
                self.y = None
        elif self.function == 2:
            if self.x < 0:
                self.y = self.x * 0.5
            elif 0 <= self.x <= 3.61:
                self.y = 1
            elif self.x > 3.61:
                self.y = exp(-(self.x+0.8))
        else:
            from numpy import arange
            temp = 0.0
            for i in range (1, int(self.x)+1):
                if i == 0:
                    temp += cos(self.x*i)
                else: temp += cos(self.x*i)/i
            self.y = temp
               
        self.result = [self.x, self.y]
        return self.result