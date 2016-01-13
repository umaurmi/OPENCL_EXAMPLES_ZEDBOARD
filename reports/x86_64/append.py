#!/usr/bin/python
'''import os
import glob
import csv
import xlwt # from http://www.python-excel.org/

for csvfile in glob.glob(os.path.join('.', '*.csv')):
    wb = xlwt.Workbook()
    ws = wb.add_sheet('data')
    with open(csvfile, 'rb') as f:
        reader = csv.reader(f)
        for r, row in enumerate(reader):
            for c, val in enumerate(row):
                ws.write(r, c, val)
    wb.save(csvfile + '.xls')      #code to create individual csv files donot touch'''



import os
import platform
import glob
import csv
import xlwt

print("starting new workbook") 
wb = xlwt.Workbook()
for csvfile in glob.glob(os.path.join('.', '*.csv')):
           
    fpath = csvfile.split("/", 1)
    fname = fpath[1].split(".", 1) ## fname[0] should be our worksheet name
    print("adding sheet " + fname[0]) 
    ws = wb.add_sheet(fname[0])
    with open(csvfile, 'rb') as f:
        reader = csv.reader(f)
        for r, row in enumerate(reader):
            for c, col in enumerate(row):
                ws.write(r, c, col)
	
            print("saving workbook")
    if platform.processor() == 'armv7l':
    	wb.save('armv7l.xls')
    elif platform.processor() == 'armv7a':
    	wb.save('armv7a.xls')
    elif platform.processor() == 'x86_64':
    	wb.save('x86_64.xls')

		
            


