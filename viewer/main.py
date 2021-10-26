import tkinter as tk
from tkinter import Canvas, StringVar, ttk
from tkinter import filedialog
import numpy
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasAgg, FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
import matplotlib.animation as animation
import dataReader
from matplotlib import style
style.use('ggplot')

LARGE_FONT = ("Verdana", 12)

def plotAllValuesOfEntryType(subplot, dataDict):
    entries = dataDict.getEntryList()
    
    for name in dataDict.valueNames:
        plotX, plotY = getSingularEntrySeriesForMatPlotLib(entries, dataDict.valueNames[name])
        subplot.plot(plotX, plotY)


def getSingularEntrySeriesForMatPlotLib(entries, index):
    times = []
    values = []
    for entry in entries:
        times.append(entry.timeStamp)
        values.append(entry.values[index])

    return times, values


class TelemetryViewerApp(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        container = ttk.Frame(self)
        
        container.pack(side = "top", fill="both", expand=True)

        container.grid()

        self.dataDict = {}
        dataReader.readDataTypeFile("dataTypes.csv", self.dataDict)
        dataReader.readDataFile("data.csv", self.dataDict)

        self.frames = {}
        frame = MainPage(container, self)
        self.frames[MainPage] = frame

        frame.grid(row=0, column = 0, sticky="nsew")
        
        self.show_frame(MainPage)

    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

class MainPage(ttk.Frame):
    def __init__(self, parent, controller):
        ttk.Frame.__init__(self, parent)
        label = ttk.Label(self, text="Space Cowboys Telemetry Sensor", font=LARGE_FONT)
        label.grid(row = 0, column = 0)
        self.controller = controller
        self.variable = tk.StringVar(controller)
        self.variable.set(list(controller.dataDict.keys())[0])
        
        f = Figure(figsize=(5,5), dpi =100)
        a = f.add_subplot(111)
        plotAllValuesOfEntryType(a, controller.dataDict["accel"])

        options = ttk.OptionMenu(
            self, 
            self.variable, 
            list(controller.dataDict.keys())[0],
            *list(controller.dataDict.keys()),
            command= lambda var: self.updateGraph(a,var))

        options.grid(row = 0, column = 1)
        
        
        
        self.plotFrame = ttk.Frame(self)
        self.plotFrame.grid(row = 1, column = 0)
        self.canvas = FigureCanvasTkAgg(f, self.plotFrame)

        self.canvas.draw()

        self.canvas.get_tk_widget().pack(side = tk.TOP, fill=tk.BOTH, expand=True)
        toolbar = NavigationToolbar2Tk(self.canvas, self.plotFrame)
        toolbar.update()
        self.canvas._tkcanvas.pack(side=tk.TOP, fill = tk.BOTH, expand=True)

 
    def updateGraph(self, subplot, select):
        subplot.clear()
        plotAllValuesOfEntryType(subplot, self.controller.dataDict[select])
        self.canvas.draw()
    
    
    
    

if __name__ == "__main__":
    app = TelemetryViewerApp()
    app.mainloop()
