#!/usr/bin/python

import sys, codecs, os
if sys.stdout.encoding is None:
        sys.stdout = codecs.open("/dev/stdout", "w", 'utf-8')

fr = open('pdb_files/1hhoa.ent','r')
fw = open('parsed/1hhoa_parsed.txt','w')

count = 0
ca = 0
line = fr.readline()
while line!='':
  count = count + 1
  x = line.strip('\n')
  y = x.split()
  if len(y)!=12:
    print 'parsing inconsistency @line:', count
  if(y[2]=='CA'):
    fw.write(y[6]+' '+y[7]+' '+y[8]+'\n')
    ca = ca + 1
  line = fr.readline()
  
fw.close()
fr.close()

print 'count = ', count
print 'Number of C-alpha atoms: ', ca

