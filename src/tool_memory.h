/********************************************************************************
 *  Project  : allocate memory by new/delete 
 *  Function : 
 *-------------------------------------------------------------------------------
 *  Author   : Yao-Chong SUN
 *  Company  : SUSTECH, CHINA.
 *-------------------------------------------------------------------------------
 *  Copyright 2020-2021. You should have received a copy of the GNU
 *  General Public License v3.0 along with ndg2d.
 *  If not, see <http://www.gnu.org/licenses/>.
********************************************************************************/
#ifndef __TOOL_MEMORY_H__
#define __TOOL_MEMORY_H__
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
float*** new3Dfloat(int,int,int);
float**  new2Dfloat(int,int);
float*   new1Dfloat(int);
//-------------------------------------------------------------------------------
void delete3Dfloat(float***,int,int);
void delete2Dfloat(float**,int);
void delete1Dfloat(float*);
//-------------------------------------------------------------------------------
#endif
//*******************************************************************************
// vim: ft=cpp:nu:nowrap
