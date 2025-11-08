class Table():

    def __init__(self, data):

        from random import randint

        self.data = data
        self.name = "Function_"+str(randint(1, 10000))+".xlsx"

    
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
        Data_Frame.to_excel(self.name)
        print(f"Таблица создана!\nИмя файла: {self.name}")
    
    def Create_Plot(self):
        Width = None
        Height = None
        
        while Width == None and Height == None:
            try:
                Width, Height = map(float, input("Введите масштабы графика(Ширина Высота (чз пробел) )\n> ").split())
                break
            except ValueError:
                print(f"ОШИБКА {ValueError} (Некорректный ввод)\n Пожалуйста, введите два числа через пробел.")
        
        try:
            import pandas as pd
            import matplotlib.pyplot as plt
            
            OP_DATA = pd.read_excel(self.name)
            
            plt.figure(figsize=(Width, Height))
            plt.plot(OP_DATA['x'], OP_DATA['y'], marker='o', linestyle='-', linewidth=1, markersize=3)
            plt.title("График функции")
            plt.xlabel("x")
            plt.ylabel("y")
            plt.grid(True)
            
            plot_filename = self.name.replace('.xlsx', '_plot.png')
            plt.savefig(plot_filename)
            plt.close()
            
            print(f"График сохранен как: {plot_filename}")
            
        except Exception as e:
            print(f"Ошибка при создании графика: {e}")