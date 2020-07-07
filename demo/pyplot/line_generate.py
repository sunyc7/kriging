import matplotlib.pyplot as plt
import numpy
import os

radius=6371.0
lon=103.65
lat=32.091
dist=4.0/180.0*numpy.pi*radius
dx=0.4

dirnm="./output/"

fp=open(dirnm+"line_info.dat","w")

#--------------------------------------------------------------------------------
for n in range(0,18,1):
#--------------------------------------------------------------------------------
  azim=n*10.0;
  #--- llad2ll 01
  str1="./bin/llad2ll "+str(lon)+" "+str(lat)+" "+str(azim)+" "+str(dist)
  result=os.popen(str1);line=result.read().split();
  x1=float(line[4]);
  y1=float(line[5]);
  #--- llad2ll 02
  str1="./bin/llad2ll "+str(lon)+" "+str(lat)+" "+str(azim+180)+" "+str(dist)
  result=os.popen(str1);line=result.read().split();
  x2=float(line[4]);
  y2=float(line[5]);

  fnm="line"+"%02d"%(n+1)+"lonlatdist_400m.dat"

  str1=str(x1)+" "+str(y1)+" "+str(x2)+" "+str(y2)
  fp.writelines(str1+" "+fnm+"\n");

  os.system("./bin/prj2pts "+str1+" "+str(dx)+">"+dirnm+fnm)

  plt.scatter(x1,y1)
  plt.scatter(x2,y2)
#--------------------------------------------------------------------------------
fp.close();
#--------------------------------------------------------------------------------
plt.show()
#--------------------------------------------------------------------------------
