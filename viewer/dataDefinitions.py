class DataEntry:
    def __init__(self, timeStamp, values):
        self.timeStamp = float(timeStamp)
        self.values = [float(value) for value in values]

    def getSize(self):
        return len(self.values)
class TelemetryDataType:
    def __init__(self, name, valueNames):
        self.name = name
        self.size = len(valueNames)
        self.entries = {}
        self.valueNames = {k:v for v, k in enumerate(valueNames)}


    def addEntry(self, entryToAdd):
        if entryToAdd.getSize() != len(self.valueNames):
            print("Unable to add entry to data type", self.name)
            return

        self.entries[entryToAdd.timeStamp] = entryToAdd

    def getEntryList(self):
        return [value for (key, value) in sorted(self.entries.items())]

    def getEntryAtTime(self, timeStamp):
        if (timeStamp in self.entries):
            return self.entries[timeStamp]
        else:
            return DataEntry(timeStamp, [0 for x in range(self.size)])


