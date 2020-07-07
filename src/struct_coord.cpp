/***************************************************************************************************
 *  Project  : geological coordinate
 *  Function :
 *--------------------------------------------------------------------------------------------------
 *  Author   : Yao-Chong SUN
 *  Company  : SUSTECH, CHINA.
 *--------------------------------------------------------------------------------------------------
 *  Copyright 2020-2021. You should have received a copy of the GNU
 *  General Public License v3.0 along with ndg2d.
 *  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************************************/
#include<iostream>
#include<cmath>
#include<map>
#include<string>
#include<iterator>
#include"struct_coord.h"
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
double km2m(double v){return v*1000.0;}
double m2km(double v){return v/1000.0;}
double deg2rad(double v){constexpr static const double pi=4.0*atan(1.0); return v/180.0*pi;}
double rad2deg(double v){constexpr static const double pi=4.0*atan(1.0); return v*180.0/pi;}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
void coord:: errorMessage(std::string errMsg,int n)
{
  std::cout<<"The Error occured at "<<errMsg<<std::endl;
  if(n==0)
  {
    std::cout<<"Usage of coord struct."<<std::endl;
    std::cout<<"  coord a;"<<std::endl;
    std::cout<<"  a.clear():"<<std::endl;
    std::cout<<"    initial all the variables in struct a."<<std::endl;
    std::cout<<"  set method contains 5 protypes"<<std::endl;
    std::cout<<"    a.set(arg1,arg2)"<<std::endl;
    std::cout<<"      arg1: longitude in degree "<<std::endl;
    std::cout<<"      arg2: latitude  in degree "<<std::endl;
    std::cout<<"    a.set(arg1,arg2,arg3)"<<std::endl;
    std::cout<<"      arg1: longitude "<<std::endl;
    std::cout<<"      arg2: latitude  "<<std::endl;
    std::cout<<"      arg3: degree or radian for argv1 and argv2 "<<std::endl;
    std::cout<<"    a.set(arg1,arg2,arg3)"<<std::endl;
    std::cout<<"      arg1: longitude in degree "<<std::endl;
    std::cout<<"      arg2: latitude  in degree "<<std::endl;
    std::cout<<"      arg3: elevation in km "<<std::endl;
    std::cout<<"    a.set(arg1,arg2,arg3,arg4)"<<std::endl;
    std::cout<<"      arg1: longitude "<<std::endl;
    std::cout<<"      arg2: latitude  "<<std::endl;
    std::cout<<"      arg3: elevation "<<std::endl;
    std::cout<<"      arg4: degree, radian, km or m for argv1, argv2, argv3 "<<std::endl;
    std::cout<<"    a.set(arg1,arg2,arg3,arg4,argv5)"<<std::endl;
    std::cout<<"      arg1: longitude "<<std::endl;
    std::cout<<"      arg2: latitude  "<<std::endl;
    std::cout<<"      arg3: elevation "<<std::endl;
    std::cout<<"      arg4: degree or radian for argv1 and argv2 "<<std::endl;
    std::cout<<"      arg5: km or m for argv3 "<<std::endl;
  }
  else if(n==1)
  {
    std::cout<<"  The variable names are "<<std::endl;
    std::cout<<"    \"longitude\" and \"lon\" "<<std::endl;
    std::cout<<"    \"latitude\"  and \"lat\" "<<std::endl;
    std::cout<<"    \"elevation\" and \"ele\" "<<std::endl;
    std::cout<<"    \"degree\"    and \"deg\" "<<std::endl;
    std::cout<<"    \"radian\"    and \"rad\" "<<std::endl;
    std::cout<<"    \"kilometer\" and \"km\"  "<<std::endl;
    std::cout<<"    \"meter\"     and \"m\"   "<<std::endl;
  }
  else if(n==2)
  {
    std::cout<<"The variable and its unit, or the operation and its element does not match."<<std::endl;
    std::cout<<"  The units of \"longitude\" are \"degree\"    and \"radian\""<<std::endl;
    std::cout<<"  The units of \"latitude\"  are \"degree\"    and \"radian\""<<std::endl;
    std::cout<<"  The units of \"elevation\" are \"kilometer\" and \"meter\" "<<std::endl;
    std::cout<<"  The operations of \"unit\" are \"kilometer\", \"meter\", \"degree\" and \"radian\""<<std::endl;
  }
  else if(n==3)
  {
    std::cout<<"  The range for \"longitude\" is [-180,+180] in degree and [-pi,+pi] in radian"<<std::endl;
  }
  else if(n==4)
  {
    std::cout<<"  The range for \"latitude\" is [-90,+90] in degree and [-pi/2,+pi/2] in radian"<<std::endl;
  }
  else if(n==5)
  {
    std::cout<<"  The range for \"elevation\" is [-6371,+8848] in kilometer"<<std::endl;
    std::cout<<"  The range for \"elevation\" is [-6371000,+8848888] in meter"<<std::endl;
  }
  exit(0);
}
//--------------------------------------------------------------------------------------------------
void coord:: checkname(std::string *argv1,std::string *argv2)
{
  checkname(argv1); 
  checkname(argv2);
  std::string errMsg="checkname(string*,string*)";

  std::multimap<std::string,std::string>::iterator it;
  for(it=v2uMap.begin();it!=v2uMap.end();++it) if(it->first==*argv1 and it->second==*argv2) return;

  errorMessage(errMsg,1);
}
//--------------------------------------------------------------------------------------------------
void coord:: checkname(std::string *argv)
{
  std::string errMsg="checkname(string*)";

  if(varsMap.count(*argv) and unitMap.count(*argv)) errorMessage(errMsg,1);
 
  std::map<std::string,std::string>:: iterator it;
  for(it=varsMap.begin();it!=varsMap.end();++it) if(it->first==*argv) *argv=it->second;
  for(it=unitMap.begin();it!=unitMap.end();++it) if(it->first==*argv) *argv=it->second;

  return;
}
//--------------------------------------------------------------------------------------------------
void coord:: check2val(std::string varname)
{
  checkname(&varname);
  std::string errMsg="check2val(string*)";

  if(varname=="longitude")
  {
    if(fabs(deg.lon)>180.0 ) errorMessage(errMsg,3);
    if(fabs(rad.lon)>pi    ) errorMessage(errMsg,3);
  }

  if(varname=="latitude" )
  {
    if(fabs(deg.lat)>90.0  ) errorMessage(errMsg,4);
    if(fabs(rad.lat)>pi/2.0) errorMessage(errMsg,4);
  }

  if(varname=="elevation")
  {
    if(km.e>8848.0   or km.e<-6371.0  ) errorMessage(errMsg,5);
    if(m.e>8848000.0 or m.e<-6371000.0) errorMessage(errMsg,5);
  }
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
void coord:: clear()
{
  deg.lon=0.0;
  deg.lat=0.0;

  rad.lon=0.0;
  rad.lat=0.0;

  km.e=0.0;
  km.x=0.0;
  km.y=0.0;
  km.z=0.0;
  km.r=R_km;

  m.e=0.0;
  m.x=0.0;
  m.y=0.0;
  m.z=0.0;
  m.r=km2m(R_km);

  lon=0.0;
  lat=0.0;
  r=0.0;
  e=0.0;
  x=0.0;
  y=0.0;
  z=0.0;
  R=0.0;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
void coord:: sphere2cart()
{
  km.x=km.r*cos(rad.lat)*cos(rad.lon);
  km.y=km.r*cos(rad.lat)*sin(rad.lon);
  km.z=km.r*sin(rad.lat);

  m.x=m.r*cos(rad.lat)*cos(rad.lon);
  m.y=m.r*cos(rad.lat)*sin(rad.lon);
  m.z=m.r*sin(rad.lat);
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
void coord:: set(double lon,double lat){set(lon,lat,"deg");}
//--------------------------------------------------------------------------------------------------
void coord:: set(double lon,double lat,double e){set(lon,lat,e,"deg","km");}
//--------------------------------------------------------------------------------------------------
void coord:: set(double lon,double lat,std::string unitname)
{
  clear();
  setbase("longitude",unitname,lon);
  setbase("latitude" ,unitname,lat);
  setbase("elevation","m",0.0);
  sphere2cart();
  set("unit","kilometer","all");
  set("unit","radian","all");
}
//--------------------------------------------------------------------------------------------------
void coord:: set(double lon,double lat,double e,std::string unitname1,std::string unitname2)
{
  clear();
  setbase("longitude",unitname1,lon);
  setbase("latitude" ,unitname1,lat);
  setbase("elevation",unitname2,e  );
  sphere2cart();
  set("unit","kilometer","all");
  set("unit","radian","all");
}
//--------------------------------------------------------------------------------------------------
void coord:: set(double lon,double lat,double e,std::string unitname)
{
  clear();
  checkname(&unitname);
  if(unitname=="kilometer" or unitname=="meter")
  {
    setbase("longitude","degree",lon);
    setbase("latitude" ,"degree",lat);
    setbase("elevation",unitname,e);
  }
  if(unitname=="degree" or unitname=="radian")
  {
    setbase("longitude",unitname,lon);
    setbase("latitude" ,unitname,lat);
    setbase("elevation","km",e);
  }
  sphere2cart();
  set("unit","kilometer","all");
  set("unit","radian","all");
}
//--------------------------------------------------------------------------------------------------
void coord:: setbase(std::string varname,std::string varunit,double varval)
{
  checkname(&varname,&varunit);
  if(varname=="longitude" and varunit=="degree"   ){deg.lon=varval;rad.lon=deg2rad(deg.lon);}
  if(varname=="longitude" and varunit=="radian"   ){rad.lon=varval;deg.lon=rad2deg(rad.lon);}
  if(varname=="latitude"  and varunit=="degree"   ){deg.lat=varval;rad.lat=deg2rad(deg.lat);}
  if(varname=="latitude"  and varunit=="radian"   ){rad.lat=varval;deg.lat=rad2deg(rad.lat);}
  if(varname=="elevation" and varunit=="kilometer"){km.e=varval;m.e=km2m(km.e);}
  if(varname=="elevation" and varunit=="meter"    ){m.e=varval;km.e=m2km(m.e);}
  check2val(varname);
  set("unit","kilometer","all");
  set("unit","radian"   ,"all");
}
//--------------------------------------------------------------------------------------------------
void coord:: set(std::string onm,std::string vnm1,std::string vnm2)
{
  checkname(&vnm1);
  checkname(&vnm2);

  std:: string errMsg="set(sting,string,string)";
  if(onm!="unit") errorMessage(errMsg,6);
  if((vnm1=="meter" or vnm1=="kilometer") and vnm2=="all")
  {
    setunit(vnm1,"x");
    setunit(vnm1,"y");
    setunit(vnm1,"z");
    setunit(vnm1,"radius");
    setunit(vnm1,"elevation");
    setunit(vnm1,"Radius");
  } else
  if((vnm1=="radian" or vnm1=="degree") and vnm2=="all")
  {
    setunit(vnm1,"longitude");
    setunit(vnm1,"latitude");
  } else
  if((vnm1=="meter" or vnm1=="kilometer") and (vnm2=="radian" or vnm2=="degree"))
  {
    // --- meter/kilometer
    setunit(vnm1,"x");
    setunit(vnm1,"y");
    setunit(vnm1,"z");
    setunit(vnm1,"radius");
    setunit(vnm1,"elevation");
    setunit(vnm1,"Radius");
    // --- radian/degree
    setunit(vnm2,"longitude");
    setunit(vnm2,"latitude");
  } else
  if((vnm2=="meter" or vnm2=="kilometer") and (vnm1=="radian" or vnm1=="degree"))
  {
    // --- meter/kilometer
    setunit(vnm1,"x");
    setunit(vnm1,"y");
    setunit(vnm1,"z");
    setunit(vnm1,"radius");
    setunit(vnm1,"elevation");
    setunit(vnm1,"Radius");
    // --- radian/degree
    setunit(vnm2,"longitude");
    setunit(vnm2,"latitude");
  } else
  {
    setunit(vnm1,vnm2);
  }
}
//--------------------------------------------------------------------------------------------------
void coord:: setunit(std::string unitname,std::string varname)
{
  checkname(&varname,&unitname);
  if(varname=="x"         and unitname=="kilometer") x=km.x;
  if(varname=="y"         and unitname=="kilometer") y=km.y;
  if(varname=="z"         and unitname=="kilometer") z=km.z;
  if(varname=="radius"    and unitname=="kilometer") r=km.r;
  if(varname=="elevation" and unitname=="kilometer") e=km.e;
  if(varname=="Radius"    and unitname=="kilometer") R=R_km;

  if(varname=="x"         and unitname=="meter") x=m.x;
  if(varname=="y"         and unitname=="meter") y=m.y;
  if(varname=="z"         and unitname=="meter") z=m.z;
  if(varname=="radius"    and unitname=="meter") r=m.r;
  if(varname=="elevation" and unitname=="meter") e=m.e;
  if(varname=="Radius"    and unitname=="meter") R=km2m(R_km);

  if(varname=="longitude" and unitname=="degree") lon=deg.lon;
  if(varname=="latitude"  and unitname=="degree") lat=deg.lat;

  if(varname=="longitude" and unitname=="radian") lon=rad.lon;
  if(varname=="latitude"  and unitname=="radian") lat=rad.lat;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// coord functions
//--------------------------------------------------------------------------------------------------
double gtriarea(coord p,coord q,coord r)
{
  double a1=garcdist(p,q)/p.R;
  double a2=garcdist(q,r)/q.R;
  double a3=garcdist(r,p)/r.R;
  double s=(a1+a2+a3)/2.0;
  double e=sqrt(s/2.0)*sqrt((s-a1)/2.0)*sqrt((s-a2)/2.0)*sqrt(s-a3)/2.0;
  return 4.0*atan(e)*pow(p.R,2); // 
}
//--------------------------------------------------------------------------------------------------
double garcdist(coord p,coord q)
{
  p.set("unit","km","all"); p.set("unit","radian","all");
  q.set("unit","km","all"); q.set("unit","radian","all");
  double e2norm=sqrt(pow((p.x-q.x)/p.R,2)+pow((p.y-q.y)/p.R,2)+pow((p.z-q.z)/p.R,2));
  return 2.0*asin(e2norm/2.0)*p.R;
}
//--------------------------------------------------------------------------------------------------
double azimuth(coord p,coord q)
{
  p.set("unit","km","all"); p.set("unit","radian","all");
  q.set("unit","km","all"); q.set("unit","radian","all");
  double d1=garcdist(p,q);

  // special relative locations
  if(fabs(d1)            <p.delta) return  0.0; // two points have same location
  if(fabs(p.lat-p.pi/2.0)<p.delta) return p.pi; // reference point on the North Polar 
  if(fabs(q.lat-p.pi/2.0)<p.delta) return  0.0; // observation point on the North Polar 
  if(fabs(p.lon-q.lon)<p.delta and p.lat<q.lat) return  0.0;
  if(fabs(p.lon-q.lon)<p.delta and p.lat>q.lat) return p.pi;
  if(fabs(fabs(p.lon-q.lon)-p.pi)<p.delta)    return  0.0;

  coord o; o.set(p.lon,p.pi/2.0,0.0,"rad","km");
  double d2=garcdist(p,o);
  double d3=garcdist(q,o);

  double azi=acos((cos(d3/p.R)-cos(d1/p.R)*cos(d2/p.R))/sin(d1/p.R)/sin(d2/p.R));

  if(p.lon>q.lon and p.lon-q.lon<p.pi) azi=2.0*p.pi-azi;
  if(p.lon<q.lon and q.lon-p.lon>p.pi) azi=2.0*p.pi-azi;

  return azi;
}
//--------------------------------------------------------------------------------------------------
coord llad2ll(coord p, double azim, double dist)
{
  p.set("unit","km","all"); p.set("unit","radian","all");

  // check azimuth
  if(azim<0.0 or azim>2.0*p.pi    )
  { 
    std::cout<<"Error: azimuth is not in [0,2*pi]"<<std::endl;
    exit(0);
  }
  // check great arc distance 
  if(dist<0.0 or dist>2.0*p.pi*p.R)
  {
    std::cout<<"Error: great arc distance should in [0,2*pi*R]"<<std::endl;
    exit(0);
  }

  coord o; o.set(p.lon,p.pi/2.0,0.0,"rad","km");
  double d1=garcdist(p,o);

  if(fabs(d1)<p.delta)
  {
    std::cout<<"Error: reference point is on north polar"<<std::endl;
    exit(0);
  }

  coord r;
  double lon;
  double lat;

  if(fabs(dist)<p.delta) return p;

  if(fabs(azim-p.pi)<p.delta) 
  {
    if(dist+d1<p.pi*p.R)
    {
      lon=p.lon;
      lat=p.lat-dist/p.R;
    } else 
    if(fabs(dist+d1-p.pi*p.R)<p.delta)
    {
      lon=p.lon;
      lat=-p.pi/2.0;
    } else 
    if(dist+d1>p.pi*p.R and dist+d1<2.0*p.pi*p.R)
    {
      if(p.lon>0.0) lon=p.lon-p.pi;
      if(p.lon<0.0) lon=p.lon+p.pi;
      if(fabs(p.lon)<p.delta) lon=p.pi;
      lat=p.pi/2.0-(2.0*p.pi-(dist+d1)/p.R);
    } else
    if(fabs(dist+d1-2.0*p.pi*p.R)<p.delta)
    {
      lon=p.lon;
      lat=p.pi/2.0;
    } else 
    if(dist+d1>2.0*p.pi*p.R)
    {
      lon=p.lon;
      lat=p.pi/2.0-((dist+d1)/p.R-2.0*p.pi);
    }
    r.set(lon,lat,0.0,"rad","km");
    return r;
  }

  if(fabs(azim-0.0)<p.delta) 
  {
    if(dist<d1)
    {
      lon=p.lon;
      lat=p.lat+dist/p.R;
    } else
    if(fabs(dist-d1)<p.delta)
    {
      lon=p.lon;
      lat=p.pi/2.0;
    } else 
    if(dist>d1 and dist-d1<p.pi*p.R)
    {
      if(p.lon>0.0) lon=p.lon-p.pi;
      if(p.lon<0.0) lon=p.lon+p.pi;
      if(fabs(p.lon)<p.delta) lon=p.pi;
      lat=p.pi/2.0-(dist-d1)/p.R; 
    } else 
    if(fabs(dist-d1-p.pi*p.R)<p.delta)
    {
      lon=p.lon;
      lat=-p.pi/2.0; 
    }
    else if(dist-d1>p.pi*p.R)
    {
      lon=p.lon;
      lat=(dist-d1)/p.R-p.pi*3.0/2.0;
    }
    r.set(lon,lat,0.0,"rad","km");
    return r;
  }

  double d2=dist;
  double d3=p.R*acos(cos(d1/p.R)*cos(d2/p.R)+sin(d1/p.R)*sin(d2/p.R)*cos(azim));
  lat=p.pi/2.0-d3/p.R;  

  double dlon=acos((cos(d2/p.R)-cos(d1/p.R)*cos(d3/p.R))/sin(d1/p.R)/sin(d3/p.R));

  if(azim<p.pi) lon=p.lon+dlon;
  if(azim>p.pi) lon=p.lon-dlon;

  if(lon> p.pi) lon=lon-2.0*p.pi;
  if(lon<-p.pi) lon=lon+2.0*p.pi;

  r.set(lon,lat,0.0,"rad","km");

  return r;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
coord* prj2pts(coord p,coord q,double dx,int* npts)
{
  // function name
  std::string func_name="prj2pts(coord,coord,double,int*)";

  // check dx for great arc distance
  if(dx<0.0 or dx>2.0*p.pi*p.R)
  {
    std::cout<<"Error: dx is in [0,2*pi*R] for "<<func_name<<std::endl;
    exit(0);
  }

  if(fabs(dx)<p.delta)
  {
    std::cout<<"Error: dx can not be zero for "<<func_name<<std::endl;
    exit(0);
  }

  p.set("unit","km","all"); p.set("unit","radian","all");
  q.set("unit","km","all"); q.set("unit","radian","all");

  double d=garcdist(p,q);
  double a=azimuth(p,q);

  if(fabs(d)<p.delta)
  {
    std::cout<<"Error: p and q can not have same location in prj2pts"<<std::endl;
    exit(0);
  }

  if(d<dx)
  {
    std::cout<<"Error: d should be larger than dx in prj2pts."<<std::endl;
    exit(0);
  }

  int n=floor(d/dx)+2;

  coord* r=new coord[n];
  r[0]=p;
  r[n-1]=q;
  for(int i=1;i<=n-2;i++) r[i]=llad2ll(p,a,dx*i);

  *npts=n;
  return r;
}
//--------------------------------------------------------------------------------------------------
coord* prj2pts(coord p,coord q,int npts,double* dx)
{
  // function name
  std::string func_name="prj2pts(coord,coord,int,double*)";

  // check dx for great arc distance
  if(npts<=0)
  {
    std::cout<<"Error: npts should >0 for "<<func_name<<std::endl;
    exit(0);
  }

  p.set("unit","km","all"); p.set("unit","radian","all");
  q.set("unit","km","all"); q.set("unit","radian","all");

  double d=garcdist(p,q);
  double a=azimuth(p,q);

  if(fabs(d)<p.delta)
  {
    std::cout<<"Error: p and q can not have same location in prj2pts"<<std::endl;
    exit(0);
  }

  *dx=d/float(npts-1);

  coord* r=new coord[npts];
  for(int i=0;i<npts;i++) r[i]=llad2ll(p,a,(*dx)*i);

  return r;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
coord** new2Dcoord(int nk,int nj)
{
  if(nk<=0 or nj<=0)
  {
    std::cout<<"Error: new2Dcoord in tool_memory.cpp"<<std::endl;
    return NULL;
  }
  coord** p=new coord*[nk];
  for(int k=0;k<nk;k++) p[k]= new coord[nj];

  return p;
}
//--------------------------------------------------------------------------------------------------
void delete2Dcoord(coord** p,int nk)
{
  for(int k=0;k<nk;k++) delete[] p[k];
  delete[] p;
  p=NULL;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
coord* new1Dcoord(int nk)
{
  if(nk<=0)
  {
    std::cout<<"Error: new1Dcoord in tool_memory.cpp"<<std::endl;
    return NULL;
  }
  coord *p=new coord[nk];

  return p;
}
//--------------------------------------------------------------------------------------------------
void delete1Dcoord(coord* p)
{
  delete[] p;
  p=NULL;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
double peakval(coord** g,int ni,int nj,std::string onm)
{
  double v;

  if(onm=="maxlon")
  {
    v=g[0][0].deg.lon;
    for(int j=0;j<nj;j++) for(int i=0;i<ni;i++) if(v<g[j][i].deg.lon) v=g[j][i].deg.lon;
  } else
  if(onm=="minlon")
  {
    v=g[0][0].deg.lon;
    for(int j=0;j<nj;j++) for(int i=0;i<ni;i++) if(v>g[j][i].deg.lon) v=g[j][i].deg.lon;
  } else
  if(onm=="maxlat")
  {
    v=g[0][0].deg.lat;
    for(int j=0;j<nj;j++) for(int i=0;i<ni;i++) if(v<g[j][i].deg.lat) v=g[j][i].deg.lat;
  } else
  if(onm=="minlat")
  {
    v=g[0][0].deg.lat;
    for(int j=0;j<nj;j++) for(int i=0;i<ni;i++) if(v>g[j][i].deg.lat) v=g[j][i].deg.lat;
  } else
  {
    std::cout<<"  Error: peakval"<<std::endl;
    exit(0);
  }
  return v;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// vim: ft=cpp:nu:nowrap
