import matplotlib.pyplot as plt

dirnm="./output/"
for n in range(0,18,6):
  fnm=dirnm+"line"+"%02d"%(n+1)+"lonlatdist_400m.dat"
  print(fnm)
  fp=open(fnm,'r+')
  while True:
    line=(fp.readline()).split()
    if not line: break
    x=float(line[0])
    y=float(line[1])
    plt.scatter(x,y)
plt.show()
