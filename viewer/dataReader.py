import csv
import dataclasses
def readDataTypeFile(filename, dataEntryDict):
    with open(filename) as csvfile:
        reader = csv.reader(csvfile, delimiter = ' ')
        for row in reader:
            dataEntryDict[row[0]] = dataclasses.TelemetryDataType(row[0], row[1:])



def readDataFile(filename, dataEntryDict):

    with open(filename) as csvfile:
        reader = csv.reader(csvfile, delimiter = ' ')
        for row in reader:
            dataEntryDict[row[0]].addEntry(dataclasses.DataEntry(row[1], row[2:]))



