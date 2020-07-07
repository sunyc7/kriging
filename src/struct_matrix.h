/********************************************************************************
 *  Project  :
 *  Function : 
 *-------------------------------------------------------------------------------
 *  Author   : Yao-Chong SUN
 *  Company  : SUSTECH, CHINA.
 *-------------------------------------------------------------------------------
 *  Copyright 2020-2021. You should have received a copy of the GNU
 *  General Public License v3.0 along with ndg2d.
 *  If not, see <http://www.gnu.org/licenses/>.
********************************************************************************/
#ifndef __STRUCT_MATRIX_H__
#define __STRUCT_MATRIX_H__
//-------------------------------------------------------------------------------
struct RMATRIX
{
  private:
    void errorMessage(std::string);
    void clear();
    // variable
    int n1=-1;
    int n2=-1;
  public:
    // variable
    float** mat=NULL;
    // method
    void disp();
    int  ndim(std::string);
    // method
    void set(int,int);
    void T();
    void zero();
    void identity();
    void interchanges(int,int);
    void scaling(float,int);
    void replacement(float,int,int);
    RMATRIX(){clear();}
    RMATRIX(int n1,int n2){clear();set(n1,n2);}
   ~RMATRIX(){clear();}
};
//-------------------------------------------------------------------------------
void     matMultiply(RMATRIX&,RMATRIX&,RMATRIX&);
//-------------------------------------------------------------------------------
RMATRIX* matAdd(RMATRIX&,RMATRIX&);
RMATRIX* matSubstrate(RMATRIX&,RMATRIX&);
RMATRIX* matMultiply(RMATRIX&,RMATRIX&);
RMATRIX* matTranspose(RMATRIX&);
RMATRIX* matInv(RMATRIX&);
float    matDet(RMATRIX&);
//-------------------------------------------------------------------------------
#endif
//*******************************************************************************
// vim: ft=cpp:nu:nowrap
