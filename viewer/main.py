import tkinter as tk
from tkinter import ttk
from tkinter import filedialog
import dataReader
import dataclasses


def runViewer():
    dataDict = {}
    dataReader.readDataTypeFile("dataTypes.csv", dataDict)
    dataReader.readDataFile("data.csv", dataDict)

    entries = dataDict["accel"].getEntryList()
    for entry in entries:
        print(entry.timeStamp, entry.values)
    root = tk.Tk()
    frame = ttk.Frame(root, padding = 10)
    frame.grid()

    ttk.Label(frame, text="Msstate Telemetry Viewer").grid(column=0, row=0)
    ttk.Button(frame, text="Quit", command=root.destroy).grid(column=0, row=1)

    filedialog.askdirectory()
    root.mainloop()

if __name__ == "__main__":
    runViewer()
