/***************************************************************************************************
 *  Project  : allocate memory by new/delete 
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
#include"tool_memory.h"
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
float ***new3Dfloat(int nk,int nj,int ni)
{
  if(nk<=0 or nj<=0 or ni<=0)
  { 
    std::cout<<"Error in new3Dfloat in tool_memory.cpp"<<std::endl;
    return NULL;
  }

  float ***p=new float**[nk];
  for(int k=0;k<nk;k++) p[k]=new float*[nj];
  for(int k=0;k<nk;k++) for(int j=0;j<nj;j++) p[k][j]=new float[ni];

  for(int k=0;k<nk;k++) for(int j=0;j<nj;j++) for(int i=0;i<ni;i++) p[k][j][i]=0.0;

  return p;
}
//--------------------------------------------------------------------------------------------------
void delete3Dfloat(float*** p,int nk, int nj)
{
  for(int k=0;k<nk;k++) for(int j=0;j<nj;j++) delete[] p[k][j];
  for(int k=0;k<nk;k++) delete[] p[k];
  delete[] p;
  p=NULL;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
float **new2Dfloat(int nk,int nj)
{
  if(nk<=0 or nj<=0)
  { 
    std::cout<<"Error new2Dfloat in tool_memory.cpp"<<std::endl;
    return NULL;
  }

  float **p=new float*[nk];
  for(int k=0;k<nk;k++) p[k]=new float[nj];

  for(int k=0;k<nk;k++) for(int j=0;j<nj;j++) p[k][j]=0.0;

  return p;
}
//--------------------------------------------------------------------------------------------------
void delete2Dfloat(float** p,int nk)
{
  for(int k=0;k<nk;k++) delete[] p[k];
  delete[] p;
  p=NULL;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
float *new1Dfloat(int nk)
{
  if(nk<=0)
  { 
    std::cout<<"Error new1Dfloat in tool_memory.cpp"<<std::endl;
    return NULL;
  }

  float *p=new float[nk];

  for(int k=0;k<nk;k++) p[k]=0.0;

  return p;
}
//--------------------------------------------------------------------------------------------------
void delete1Dfloat(float* p)
{
  delete[] p;
  p=NULL;
}
//--------------------------------------------------------------------------------------------------

//**************************************************************************************************
// vim: ft=cpp:nu:nowrap
