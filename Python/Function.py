class Function():

    def __init__(self, function, x): #Записываем переменный результат
        self.result = [] #Результат будет состоять из двумерного списка планом [x, y] с шагом x += 0.1

        self.x = x
        self.y = 0

        from math import sin, cos, exp, pow, sqrt, tan


        if function == 1:
            self.function = ((sin((x**2)+(x**-1)+(x**1/3)))/tan(exp(cos(sqrt(x)))))*pow(10, -6)

        elif function == 2:
            if x < 0:
                return 0.5*x
            elif 0 <= x <= 3.61:
                return 1
            else:
                return exp(-(x+0.8))
        else:
            self.function = '0'

    def CalculateFunc(self):

        if self.function != '0':
            from math import sin, cos, exp, sqrt, tan

            self.y = ((sin((self.x**2) + (self.x**-1) + (self.x**1/3))) / tan(exp(cos(sqrt(self.x))))) * (10**-6)
        
        else:
            temp = 0.0
            for i in range(int(self.x)):
                
                temp += cos(self.x*i)/i

        self.result = [self.x, self.y]
        return self.result