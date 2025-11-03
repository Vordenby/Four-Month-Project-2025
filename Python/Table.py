class Table():

    def __init__(self, data):

        from random import randint

        self.data = data
        self.name = "Function_"+str(randint(1, 10000))

    
    def CreateTable(self):

        def GetPath():
            
            import os, sys

            if getattr(sys, 'frozen', False):
                os.chdir(os.path.dirname(sys.executable))
            else:
                os.chdir(os.path.dirname(os.path.abspath(__file__)))
        
        path = GetPath()

        Xes = []
        Yes = []

        for i in self.data:
            Xes.append(i[0])
            Yes.append(i[1])

        import pandas as pd
        from random import randint

        Data_Frame = pd.DataFrame(
            {
                "x": [x for x in Xes],
                "y": [y for y in Yes]
            }
        )
        Data_Frame.to_excel(self.name + ".xslx")
    
    def Create_Plot(self):

        Width, Height = map(float, input("Введите масштабы графика(Ширина Высота (чз пробел) )\n> ").split())

        import pandas as pd

        OP_DATA = pd.read_excel(self.name+".xslx")

        OP_DATA.plot(
            x='x',
            y='y',
            figsize=(Width, Height),
            title="График функции"
        )