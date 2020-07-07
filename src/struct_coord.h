/***************************************************************************************************
 *  A program package for calculating
 *    great arc dist,
 *    azimuth,
 *    projection
 *  on the spherical Earth coordinate.
 *--------------------------------------------------------------------------------------------------
 *  Author   : Yao-Chong SUN
 *  Company  : SUSTECH, CHINA.
 *--------------------------------------------------------------------------------------------------
 *  Copyright 2020-2021. You should have received a copy of the GNU
 *  General Public License v3.0 along with ndg2d.
 *  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************************************/
#ifndef __STRUCT_COORD_H__
#define __STRUCT_COORD_H__
//--------------------------------------------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<map>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
struct coord
{
  private:
    // variable name
    std::map<std::string,std::string> varsMap=
    {
      {"all"      ,"all"      },
      {"All"      ,"all"      },
      {"ALL"      ,"all"      },
      {"longitude","longitude"},
      {"Longitude","longitude"},
      {"LONGITUDE","longitude"},
      {"lon"      ,"longitude"},
      {"Lon"      ,"longitude"},
      {"LON"      ,"longitude"},
      {"latitude" ,"latitude" },
      {"Latitude" ,"latitude" },
      {"LATITUDE" ,"latitude" },
      {"lat"      ,"latitude" },
      {"Lat"      ,"latitude" },
      {"LAT"      ,"latitude" },
      {"radius"   ,"radius"   },
      {"r"        ,"radius"   },
      {"elevation","elevation"},
      {"Elevation","elevation"},
      {"ELEVATION","elevation"},
      {"ele"      ,"elevation"},
      {"Ele"      ,"elevation"},
      {"ELE"      ,"elevation"},
      {"x"        ,"x"        },
      {"X"        ,"x"        },
      {"y"        ,"y"        },
      {"Y"        ,"y"        },
      {"z"        ,"z"        },
      {"Z"        ,"z"        },
      {"Radius"   ,"Radius"   },
      {"R"        ,"Radisu"   }
    };
    // unit name
    std::map<std::string,std::string> unitMap=
    {
      {"meter"    ,"meter"    },
      {"Meter"    ,"meter"    },
      {"METER"    ,"meter"    },
      {"m"        ,"meter"    },
      {"M"        ,"meter"    },
      {"kilometer","kilometer"},
      {"Kilometer","kilometer"},
      {"KILOMETER","kilometer"},
      {"km"       ,"kilometer"},
      {"Km"       ,"kilometer"},
      {"KM"       ,"kilometer"},
      {"degree"   ,"degree"   },
      {"Degree"   ,"degree"   },
      {"DEGREE"   ,"degree"   },
      {"deg"      ,"degree"   },
      {"Deg"      ,"degree"   },
      {"DEG"      ,"degree"   },
      {"radian"   ,"radian"   },
      {"Radian"   ,"radian"   },
      {"RADIAN"   ,"radian"   },
      {"rad"      ,"radian"   },
      {"Rad"      ,"radian"   },
      {"RAD"      ,"radian"   }
    };                        
    // variable to unit map
    std::multimap<std::string,std::string> v2uMap=
    {
      {"longitude","degree"   },
      {"longitude","radian"   },
      {"latitude" ,"degree"   },
      {"latitude" ,"radian"   },
      {"radius"   ,"meter"    },
      {"radius"   ,"kilometer"},
      {"elevation","meter"    },
      {"elevation","kilometer"},
      {"x"        ,"meter"    },
      {"x"        ,"kilometer"},
      {"y"        ,"meter"    },
      {"y"        ,"kilometer"},
      {"z"        ,"meter"    },
      {"z"        ,"kilometer"},
      {"Radius"   ,"meter"    },
      {"Radius"   ,"kilometer"}
    };
    // functions
    void errorMessage(std::string,int);
    void checkname(std::string*);
    void checkname(std::string*,std::string*);
    void setbase(std::string,std::string,double);
    void setunit(std::string,std::string);

  public:
    // const pi and Earth's Radius
    constexpr static const double pi=4.0*atan(1.0);
    constexpr static const double R_km=6371.000;
    constexpr static const double delta=1.0e-6;
    // variables
    struct DEGREE{double lon;double lat;}deg;
    struct RADIAN{double lon;double lat;}rad;
    struct KILOMETER{double x;double y;double z;double r;double e;}km;
    struct METER{double x;double y;double z;double r;double e;}m;
    double lon;
    double lat;
    double x;
    double y;
    double z;
    double r;
    double e;
    double R;
    // interior functions
    void clear();
    void sphere2cart();
    void check2val(std::string);
    // set value and units 
    void set(std::string,std::string,std::string);
    void set(double,double);
    void set(double,double,std::string);
    void set(double,double,double);
    void set(double,double,double,std::string);
    void set(double,double,double,std::string,std::string);
    coord(){clear();}
   ~coord(){clear();}
};
//-------------------------------------------------------------------------------
coord*  new1Dcoord(int);
coord** new2Dcoord(int,int);
void delete1Dcoord(coord*);
void delete2Dcoord(coord**,int);
//-------------------------------------------------------------------------------
double gtriarea(coord,coord,coord);
double garcdist(coord,coord);
double azimuth(coord,coord);
coord  llad2ll(coord,double,double);
//-------------------------------------------------------------------------------
coord* prj2pts(coord,coord,double,int*);
coord* prj2pts(coord,coord,int,double*);
//-------------------------------------------------------------------------------
double peakval(coord**,int,int,std::string);
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
struct coord1D
{
  int npts;
  coord* v;
};
//-------------------------------------------------------------------------------
struct coord2D
{
  int nlon;
  int nlat;
  coord** v;
};
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
#endif
//*******************************************************************************
// vim: ft=cpp:nu:nowrap
