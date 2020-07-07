import matplotlib.pyplot as plt
import numpy

dirnm="./output/"
fnm=dirnm+"mesh2d_data.dat"

fp=open(fnm,'r+')
line=(fp.readline()).split()
nlon=int(line[0])
nlat=int(line[1])

print(nlon)
print(nlat)

lon2d=numpy.zeros((nlon,nlat))
lat2d=numpy.zeros((nlon,nlat))
val2d=numpy.zeros((nlon,nlat))
raw2d=numpy.zeros((nlon,nlat))

line=fp.readline()
print(line)

for j in range(0,nlat):
  line=(fp.readline()).split()
  for i in range(0,nlon):
    lon2d[i][j]=float(line[i])

line=fp.readline()
print(line)

for j in range(0,nlat):
  line=(fp.readline()).split()
  for i in range(0,nlon):
    lat2d[i][j]=float(line[i])

line=fp.readline()
print(line)

for j in range(0,nlat):
  line=(fp.readline()).split()
  for i in range(0,nlon):
    raw2d[i][j]=float(line[i])

#line=fp.readline()
#print(line)
#for j in range(0,nlat):
# line=(fp.readline()).split()
# for i in range(0,nlon):
#   val2d[i][j]=float(line[i])
#fp.close();

plt.pcolormesh(lon2d,lat2d,raw2d)
#plt.pcolormesh(lon2d,lat2d,val2d)

#--------------------------------------------------------------------------------
#plt.scatter(x1,y1)
#--------------------------------------------------------------------------------
plt.show()
#--------------------------------------------------------------------------------
# vim: ft=cpp:nu:nowrap
