import matplotlib.pyplot as plt
import sys 

fnm=sys.argv[1]
fp=open(fnm,'r+')
line=(fp.readline()).split()
npts=float(line[0])
while True:
  line=(fp.readline()).split()
  if not line: break
  x=float(line[0])
  y=float(line[1])
  plt.scatter(x,y)
plt.show()
