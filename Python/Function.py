class Function():

    def __init__(self, function, x): #Записываем переменный результат
        self.result = [] #Результат будет состоять из двумерного списка планом [x, y] с шагом x += 0.1

        self.x = x
        self.y = 0

        from math import sin, cos, exp, pow, sqrt, tan, pi


        if function == 1:
            self.function = 1

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
        
        from math import sin, cos, exp, sqrt, tan

        if self.function != '0':

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

        else:
            temp = 0.0
            for i in range (int(self.x)):
                if i == 0:
                    temp += cos(self.x*i)
                else: temp += cos(self.x*i)/i
            self.y = temp

        self.result = [self.x, self.y]
        return self.result