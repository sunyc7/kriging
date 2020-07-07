/***************************************************************************************************
 *  Project  : Crust1.0
 *  Function :
 *--------------------------------------------------------------------------------------------------
 *  Author   : Yao-Chong SUN
 *  Company  : SUSTECH, CHINA.
 *--------------------------------------------------------------------------------------------------
 *  Copyright 2020-2021. You should have received a copy of the GNU
 *  General Public License v3.0 along with ndg2d.
 *  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************************************/
#include<cmath>
#include<iostream>
#include"tool_memory.h"
#include"struct_coord.h"
//--------------------------------------------------------------------------------------------------
coord2D* getGrid(coord o,coord h,coord v,float dh,float dv)
{
  o.set("unit","km","radian");
  h.set("unit","km","radian");
  v.set("unit","km","radian");

  // points in longitude or latitude direction
  int nlon=0;
  int nlat=0;
  coord* h1d=prj2pts(o,h,dh,&nlon);
  coord* v1d=prj2pts(o,v,dv,&nlat);

  // coord2D array
  coord2D* p2d=new coord2D;
  p2d->nlon=nlon;
  p2d->nlat=nlat;
  p2d->v=new2Dcoord(nlon,nlat);

  for(int i=0,j=0;i<nlon;i++) p2d->v[i][j].set(h1d[i].lon,h1d[i].lat,0.0,"rad","km");
  for(int i=0,j=0;j<nlat;j++) p2d->v[i][j].set(v1d[j].lon,v1d[j].lat,0.0,"rad","km");
  for(int i=0;i<nlon;i++) for(int j=1;j<nlat;j++) p2d->v[i][j]=llad2ll(p2d->v[i][j-1],0.0,dv);

  delete1Dcoord(h1d);
  delete1Dcoord(v1d);
  return p2d;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
void genElev(coord2D* grid,float h)
{
  float x0=grid->v[grid->nlon/2][grid->nlat/2].km.x;
  float y0=grid->v[grid->nlon/2][grid->nlat/2].km.y;
  float sigmax=200.0;
  float sigmay=100.0;

  for(int i=0;i<grid->nlon;i++) for(int j=0;j<grid->nlat;j++)
  {
    float x=grid->v[i][j].km.x;
    float y=grid->v[i][j].km.y;
    float e=h*exp(-(x-x0)*(x-x0)/2.0/sigmax/sigmax-(y-y0)*(y-y0)/2.0/sigmay/sigmay);
    grid->v[i][j].set(grid->v[i][j].deg.lon,grid->v[i][j].deg.lat,e,"deg","km");
  }
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// vim: ft=cpp:nu:nowrap
