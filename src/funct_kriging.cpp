/***************************************************************************************************
 *  Project  : Kriging interpolation
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
#include"struct_matrix.h"
//--------------------------------------------------------------------------------------------------
float semivariogram(float h, float a)
{
  if(h<=a) return 1.0-1.5*h/a+0.5*h*h*h/a/a/a;
  return 0.0;
}
//--------------------------------------------------------------------------------------------------
float e2dist(coord& p,coord& q,float R)
{
  float x1=cos(p.rad.lat)*cos(p.rad.lon);
  float y1=cos(p.rad.lat)*sin(p.rad.lon);
  float z1=sin(p.rad.lat);

  float x2=cos(q.rad.lat)*cos(q.rad.lon);
  float y2=cos(q.rad.lat)*sin(q.rad.lon);
  float z2=sin(q.rad.lat);

  float e2norm=sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2)); 

  return 2.0*asin(e2norm/2.0)*R;
}
//--------------------------------------------------------------------------------------------------
void kriging_ordinary(coord2D* r,coord2D* s,float a) // r->raw data, s-> smooth data
{
  for(int i=0;i<r->nlon;i++) for(int j=0;j<r->nlat;j++) r->v[i][j].set("unit","km","radian");
  for(int i=0;i<s->nlon;i++) for(int j=0;j<s->nlat;j++) s->v[i][j].set("unit","km","radian");

  float R=0.0;
  for(int i=0;i<r->nlon;i++) for(int j=0;j<r->nlat;j++)
  {
    R=R+r->v[i][j].r+r->v[i][j].e;
  }
  R=R/(r->nlon*r->nlat);

  //std::cout<<"R="<<R<<std::endl;

  int npts=r->nlon*r->nlat+1;

  RMATRIX A(npts,npts);
  RMATRIX b(npts,1);
  RMATRIX x(npts,1);

  A.zero();
  b.zero();
  x.zero();

  // obtain A matrix
  for(int n1=0,i=0;i<r->nlon;i++) for(int j=0;j<r->nlat;j++)
  {
    for(int n2=0,l=0;l<r->nlon;l++) for(int m=0;m<r->nlat;m++)
    {
      A.mat[n1][n2++]=semivariogram(e2dist(r->v[i][j],r->v[l][m],R),a);
    }
    n1++;
  }
  for(int i=0;i<npts-1;i++) A.mat[i][npts-1]=1.0;
  for(int j=0;j<npts-1;j++) A.mat[npts-1][j]=1.0;
  A.mat[npts-1][npts-1]=0.0;
  RMATRIX* iA=matInv(A);

  for(int i=0;i<s->nlon;i++) for(int j=0;j<s->nlat;j++)
  {
    for(int l=0,n=0;l<r->nlon;l++) for(int m=0;m<r->nlat;m++) 
    {
      b.mat[n++][0]=semivariogram(e2dist(s->v[i][j],r->v[l][m],R),a);
    }
    b.mat[npts-1][0]=1.0;
    matMultiply(*iA,b,x);
    float sum=0.0;
    for(int l=0,n=0;l<r->nlon;l++) for(int m=0;m<r->nlat;m++) 
    {
      sum+=x.mat[n++][0]*r->v[l][m].km.e;
    }
    s->v[i][j].set(s->v[i][j].deg.lon,s->v[i][j].deg.lat,sum,"degree","km");
  }
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// vim: ft=cpp:nu:nowrap
