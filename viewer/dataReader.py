import csv
import dataDefinitions
def readDataTypeFile(filename, dataEntryDict):
    with open(filename) as csvfile:
        reader = csv.reader(csvfile, delimiter = ' ')
        for row in reader:
            dataEntryDict[row[0]] = dataDefinitions.TelemetryDataType(row[0], row[1], row[2:])



def readDataFile(filename, dataEntryDict):

    with open(filename) as csvfile:
        reader = csv.reader(csvfile, delimiter = ' ')
        for row in reader:
            dataEntryDict[row[0]].addEntry(dataDefinitions.DataEntry(row[1], row[2:]))



