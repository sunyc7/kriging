import matplotlib.pyplot as plt
import numpy
import os

radius=6371.0 # kilometer
lon=103.65    # degree
lat=32.091    # degree
dlon=5.0;     # degree
dlat=5.0;     # degree
dgad=10.0;    # km

lon0=lon-dlon; lat0=lat-dlat;
lon1=lon+dlon; lat1=lat-dlat;
lon2=lon-dlon; lat2=lat+dlat;

dirnm="./output/"
fnm=dirnm+"mesh2d_data.dat"

str1="./bin/kriging "+str(lon0)+" "+str(lat0)+" "+str(dgad)+" "+str(lon1)+" "+str(lat1)+" "+str(dgad)+" "+str(lon2)+" "+str(lat2)+">"+fnm

os.system(str1)

#--------------------------------------------------------------------------------
#plt.scatter(x1,y1)
#fp.close();
#--------------------------------------------------------------------------------
#plt.show()
#--------------------------------------------------------------------------------
# vim: ft=cpp:nu:nowrap
