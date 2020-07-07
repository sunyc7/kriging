/***************************************************************************************************
 *  Project  :
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
#include"tool_memory.h"
#include"struct_matrix.h"
//--------------------------------------------------------------------------------------------------
constexpr static const double DELTA=1.0e-10;
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
void RMATRIX:: errorMessage(std::string str)
{
  std::cout<<"ERROR in RMATRIX"<<std::endl;
  if(str=="set01") std::cout<<"  the input n1 or n2 <=0 in set"<<std::endl;
  if(str=="ndim") std::cout<<"  the input for ndim is R,r(Row) or C,c(Column)"<<std::endl;
  if(str=="interchanges") std::cout<<"  the input r1 or r2 for interchanges is wrong."<<std::endl;
  if(str=="scaling") std::cout<<"  the input r for scaling is wrong."<<std::endl;
  if(str=="replacement") std::cout<<"  the input r1 or r2 for replacement is wrong."<<std::endl;

  exit(0); 
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: clear()
{
  if(mat!=NULL) delete2Dfloat(mat,n1);
  mat=NULL;
  n1=-1;
  n2=-1;
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: disp()
{
  for(int j=0;j<n1;j++)
  {
    for(int i=0;i<n2;i++) std::cout<<mat[j][i]<<" ";
    std::cout<<std::endl;
  }
}
//--------------------------------------------------------------------------------------------------
int RMATRIX:: ndim(std::string str)
{
  if(str=="R" or str=="r" ) return n1;
  if(str=="C" or str=="c" ) return n2;
  errorMessage("ndim");
  return -1;
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: set(int m1,int m2)
{
  if(m1<=0 or m2<=0) errorMessage("set01");
  if(mat!=NULL) delete2Dfloat(mat,n1);
  n1=m1;
  n2=m2;
  mat=new2Dfloat(n1,n2);
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: T()
{
  if(mat==NULL) return;
  float**p=new2Dfloat(n2,n1);
  for(int j=0;j<n1;j++) for(int i=0;i<n2;i++) p[i][j]=mat[j][i];
  delete2Dfloat(mat,n1);
  mat=p;
  n1=n1+n2;
  n2=n1-n2;
  n1=n1-n2;
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: zero()
{
  if(mat==NULL) return;
  for(int j=0;j<n1;j++) for(int i=0;i<n2;i++) mat[j][i]=0.0;
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: identity()
{
  if(mat==NULL) return;
  for(int j=0;j<n1;j++) for(int i=0;i<n2;i++) if(i==j) mat[j][i]=1.0; else mat[j][i]=0.0;
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: interchanges(int r1,int r2)
{
  if(r1<0 or r1>=n2) errorMessage("interchanges");
  if(r2<0 or r2>=n2) errorMessage("interchanges");
  for(int i=0;i<n2;i++)
  {
    float val;
    val=mat[r1][i];
    mat[r1][i]=mat[r2][i];
    mat[r2][i]=val;
  }
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: scaling(float ratio,int r)
{
  if(r<0 or r>=n2) errorMessage("scaling");
  for(int i=0;i<n2;i++) mat[r][i]=mat[r][i]*ratio;
}
//--------------------------------------------------------------------------------------------------
void RMATRIX:: replacement(float ratio,int r1,int r2)
{
  if(r1<0 or r1>=n2) errorMessage("replacement");
  if(r2<0 or r2>=n2) errorMessage("replacement");
  for(int i=0;i<n2;i++) mat[r2][i]+=mat[r1][i]*ratio;
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Functions
//--------------------------------------------------------------------------------------------------
void errorMessage(std::string str)
{
  std::cout<<"ERROR in "<<str<<" function"<<std::endl;

  if(str=="matAdd") std::cout<<"  A and B do not match."<<std::endl;

  if(str=="matSubstrate") std::cout<<"  A and B do not match."<<std::endl;

  if(str=="matPU0") std::cout<<"  A,P,U are not square matrix."<<std::endl;

  if(str=="matPU1") std::cout<<"  A,P,U do not match."<<std::endl;

  if(str=="matPU2") std::cout<<"  A is singular."<<std::endl;

  if(str=="matDet" ) std::cout<<"  A is not square matrix."<<std::endl;

  if(str=="matInv0") std::cout<<"  A is not square matrix."<<std::endl;

  if(str=="matInv1") std::cout<<"  A is singular."<<std::endl;

  if(str=="matInv2") std::cout<<"  A is singular."<<std::endl;

  exit(0); 
}
//--------------------------------------------------------------------------------------------------
RMATRIX* matAdd(RMATRIX& A,RMATRIX& B)
{
  std::string snm="matAdd";

  if(A.ndim("r")!=B.ndim("r")) errorMessage(snm);
  if(A.ndim("c")!=B.ndim("c")) errorMessage(snm);

  RMATRIX* p=new RMATRIX(A.ndim("r"),A.ndim("c"));

  for(int j=0;j<A.ndim("r");j++) for(int i=0;i<A.ndim("c");i++)
  {
    p->mat[j][i]=A.mat[j][i]+B.mat[j][i];
  }

  return p;
}
//--------------------------------------------------------------------------------------------------
RMATRIX* matSubstrate(RMATRIX& A,RMATRIX& B)
{
  std::string snm="matSubstrate";

  if(A.ndim("r")!=B.ndim("r")) errorMessage(snm);
  if(A.ndim("c")!=B.ndim("c")) errorMessage(snm);

  RMATRIX* p=new RMATRIX(A.ndim("r"),A.ndim("c"));

  for(int j=0;j<A.ndim("r");j++) for(int i=0;i<A.ndim("c");i++)
  {
    p->mat[j][i]=A.mat[j][i]-B.mat[j][i];
  }

  return p;
}
//--------------------------------------------------------------------------------------------------
RMATRIX* matMultiply(RMATRIX& A,RMATRIX& B)
{
  std::string snm="matMultiply";

  if(A.ndim("c")!=B.ndim("r")) errorMessage(snm);

  RMATRIX* p=new RMATRIX(A.ndim("r"),B.ndim("c"));

  p->zero();

  for(int j=0;j<p->ndim("r");j++) for(int i=0;i<p->ndim("c");i++)
  {
    for(int m=0;m<A.ndim("c");m++) p->mat[j][i]+=A.mat[j][m]*B.mat[m][i];
  }

  return p;
}
//--------------------------------------------------------------------------------------------------
void matMultiply(RMATRIX& A,RMATRIX& B,RMATRIX& X)
{
  std::string snm="matMultiply";

  if(A.ndim("c")!=B.ndim("r")) errorMessage(snm);
  if(A.ndim("r")!=X.ndim("r")) errorMessage(snm);
  if(B.ndim("c")!=X.ndim("c")) errorMessage(snm);

  X.zero();

  for(int i=0;i<X.ndim("r");i++) for(int j=0;j<X.ndim("c");j++)
  {
    for(int n=0;n<A.ndim("c");n++) X.mat[i][j]+=A.mat[i][n]*B.mat[n][j];
  }
}
//--------------------------------------------------------------------------------------------------
RMATRIX* matTranspose(RMATRIX& A)
{
  RMATRIX* p=new RMATRIX(A.ndim("c"),A.ndim("r"));
  for(int j=0;j<p->ndim("r");j++) for(int i=0;i<p->ndim("c");i++) p->mat[j][i]=A.mat[i][j];
  return p;
}
//--------------------------------------------------------------------------------------------------
int matP2I(RMATRIX& P) // permutation matrix to Idenitity matrix
{
  int n=0;
  RMATRIX U(P.ndim("r"),P.ndim("c"));  
  for(int j=0;j<U.ndim("r");j++) for(int i=0;i<U.ndim("c");i++) U.mat[j][i]=P.mat[j][i];
  for(int i=0;i<U.ndim("c")-1;i++)
  {
    int j=i;
    for(int k=j+1;k<U.ndim("r");k++) if(fabs(U.mat[k][i])>fabs(U.mat[j][i])) j=k;
    if(j!=i)
    { 
      U.interchanges(i,j);
      n++;
    }
  }
  return n;
}
//--------------------------------------------------------------------------------------------------
void matPAU(RMATRIX& P,RMATRIX& A,RMATRIX& U) // private
{
  std::string s="matPU";
  if(A.ndim("r")!=A.ndim("c")) errorMessage(s+"0");
  if(P.ndim("r")!=P.ndim("c")) errorMessage(s+"0");
  if(U.ndim("r")!=U.ndim("c")) errorMessage(s+"0");
  if(A.ndim("r")!=P.ndim("r")) errorMessage(s+"1");
  if(P.ndim("r")!=U.ndim("r")) errorMessage(s+"1");

  // initial P and U
  P.identity();
  for(int j=0;j<U.ndim("r");j++) for(int i=0;i<U.ndim("c");i++) U.mat[j][i]=A.mat[j][i];

  // PU by Gaussian Eliminate
  for(int i=0;i<U.ndim("c")-1;i++)
  {
    int j=i;
    for(int k=j+1;k<U.ndim("r");k++) if(fabs(U.mat[k][i])>fabs(U.mat[j][i])) j=k;
    if(j!=i)
    {
      P.interchanges(i,j);
      U.interchanges(i,j);
      j=i;
    }

    if(fabs(U.mat[j][i])<DELTA) continue;

    for(int k=j+1;k<U.ndim("r");k++)
    {
      float r=U.mat[k][i]/U.mat[j][i];
      U.replacement(-r,j,k);
    }
  }
}
//--------------------------------------------------------------------------------------------------
void matALU(RMATRIX& A,RMATRIX& L,RMATRIX& U) // Private
{
  std::string s="matALU";
  if(A.ndim("r")!=A.ndim("c")) errorMessage(s+"0");
  if(L.ndim("r")!=L.ndim("c")) errorMessage(s+"0");
  if(U.ndim("r")!=U.ndim("c")) errorMessage(s+"0");
  if(A.ndim("r")!=L.ndim("r")) errorMessage(s+"1");
  if(L.ndim("r")!=U.ndim("r")) errorMessage(s+"1");

  L.identity();
  for(int j=0;j<U.ndim("r");j++) for(int i=0;i<U.ndim("c");i++) U.mat[j][i]=A.mat[j][i];

  for(int i=0;i<U.ndim("c");i++)
  {
    int j=i;
    for(int k=j+1;k<U.ndim("r");k++)
    {
      float r=U.mat[k][i]/U.mat[j][i];
      U.replacement(-r,j,k);
      L.mat[k][i]=r;
    }
  }
}
//--------------------------------------------------------------------------------------------------
void matPALU(RMATRIX& P,RMATRIX& A,RMATRIX& L,RMATRIX& U) // private
{
  std::string s="matPLU";
  if(A.ndim("r")!=A.ndim("c")) errorMessage(s+"0");

  matPAU(P,A,U);
  RMATRIX* PA=matMultiply(P,A);
  matALU(*PA,L,U);
/*
  std::cout<<std::endl;
  std::cout<<"PALU: P" <<std::endl;
  P.disp();

  std::cout<<std::endl;
  std::cout<<"PALU: A" <<std::endl;
  A.disp();

  std::cout<<std::endl;
  std::cout<<"PALU: L" <<std::endl;
  L.disp();

  std::cout<<std::endl;
  std::cout<<"PALU: U" <<std::endl;
  U.disp();
*/
  delete PA;
}
//--------------------------------------------------------------------------------------------------
float matDet(RMATRIX& A)
{
  std::string snm="matDet";
  if(A.ndim("r")!=A.ndim("c")) errorMessage(snm);

  // 1st-order square matrix
  if(A.ndim("r")==1) return A.mat[0][0];

  // >= 2nd-order square matrix by PLU Decomposite of Matrix
  RMATRIX P(A.ndim("r"),A.ndim("c"));
  RMATRIX U(A.ndim("r"),A.ndim("c"));
  matPAU(P,A,U);
  float det=1.0;
  for(int n=0;n<matP2I(P);n++) det*=-1.0;
  for(int n=0;n<U.ndim("r");n++) det=det*U.mat[n][n];

  return det;
}
//--------------------------------------------------------------------------------------------------
void matInvUTri(RMATRIX& U)
{
  RMATRIX* I=new RMATRIX(U.ndim("r"),U.ndim("c"));
  I->identity();

  for(int j=U.ndim("c")-1;j>=0;j--)
  {
    int i=j;
    float r=1.0/U.mat[i][j];
    U.scaling(r,i);
    I->scaling(r,i);
    for(i=j-1;i>=0;i--)
    {
      r=U.mat[i][j]/U.mat[j][j];
      U.replacement(-r,j,i);
      I->replacement(-r,j,i);
    }
  }
  for(int i=0;i<U.ndim("r");i++) for(int j=0;j<U.ndim("c");j++) U.mat[i][j]=I->mat[i][j];
  delete I;
}
//--------------------------------------------------------------------------------------------------
void matInvLTri(RMATRIX& L)
{
  RMATRIX* I=new RMATRIX(L.ndim("r"),L.ndim("c"));
  I->identity();

  for(int j=0;j<L.ndim("c");j++)
  {
    int i=j;
    float r=1.0/L.mat[i][j];
    L.scaling(r,i);
    I->scaling(r,i);
    for(i=j+1;i<L.ndim("r");i++)
    {
      r=L.mat[i][j]/L.mat[j][j];
      L.replacement(-r,j,i);
      I->replacement(-r,j,i);
    }
  }
  for(int i=0;i<L.ndim("r");i++) for(int j=0;j<L.ndim("c");j++) L.mat[i][j]=I->mat[i][j];
  delete I;
}
//--------------------------------------------------------------------------------------------------
RMATRIX* matInv(RMATRIX& A)
{
  std::string snm="matInv";
  if(A.ndim("r")!=A.ndim("c")) errorMessage(snm+"0");

  // rank 1
  if(A.ndim("r")==1)
  {
    if(fabs(A.mat[0][0])>DELTA)
    {
      RMATRIX* iA=new RMATRIX(A.ndim("r"),A.ndim("c"));
      iA->mat[0][0]=1.0/A.mat[0][0];
      return iA;
    }
    if(fabs(A.mat[0][0])<DELTA)
    {
      errorMessage(snm+"1");
    }
  }

  RMATRIX P(A.ndim("r"),A.ndim("c"));
  RMATRIX L(A.ndim("r"),A.ndim("c"));
  RMATRIX U(A.ndim("r"),A.ndim("c"));
  matPALU(P,A,L,U);

  for(int n=0;n<U.ndim("r");n++) if(fabs(U.mat[n][n])<DELTA) errorMessage(snm+"2");

  matInvUTri(U);
  matInvLTri(L);

  RMATRIX* T=matMultiply(U,L);
  RMATRIX* iA=matMultiply(*T,P);

  delete T;

  return iA;
}
//--------------------------------------------------------------------------------------------------

//**************************************************************************************************
// vim: ft=cpp:nu:nowrap
