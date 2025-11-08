class Function():

    def __init__(self, function, x): #Записываем переменный результат
        self.result = [] #Результат будет состоять из двумерного списка планом [x, y] с шагом x += 0.1
        self.function = function
        self.x = x
        self.y = 0


    def TryFunc(self):
        
        from math import sin, cos, exp, pow, sqrt, tan, pi
        
        if self.function == 1:
            def funcFirst(x):
                if x < 0:
                    raise ValueError("Аргумент не должен быть меньше 0!")
                if cos(sqrt(x)) == 0:
                    raise ValueError("Аргумент не должен быть равным Pi/2 + n*Pi!")
                self.y = ((sin((x**2)+(x**-1)+(x**1/3)))/tan(exp(cos(sqrt(x)))))*pow(10, -6)
            try:
                return(funcFirst(self.x))
            except ValueError as Error:
                print(Error)

        elif self.function == 2:
            if self.x < 0:
                self.y = 0.5*self.x
            elif 0 <= self.x <= 3.61:
                self.y = 1
            else:
                self.y = exp(-(self.x+0.8))
        else:
            from numpy import arange
            temp = 0.0
            for i in arange (self.x+1.0):
                if i == 0:
                    temp += cos(self.x*i)
                else: temp += cos(self.x*i)/i
            self.y = temp


    def CalculateFunc(self):
        
        self.result = [self.x, self.y]
        return self.result