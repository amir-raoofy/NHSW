#include <vector>
#include <array>

/*
 *	integer data structure
 */

typedef float FLOAT;
typedef std::vector <int> LineFlagField;
typedef std::vector < std::vector <int> > RectangleFlagField;
typedef std::vector < std::vector < std::vector <int> > >CubeFlagField;

/*
 *	field data structure
 */
typedef std::vector < float > DiscreteLine;
typedef std::vector < std::vector <float> > DiscreteRectangle;
typedef std::vector < std::vector < std::vector <float> > > DiscreteCube;

/*
 *	stencil structors
 */
//typedef std::array <float,3> Stencil1D;
//typedef std::array <float,5> Stencil2D;
//typedef std::array <float,7> Stencil3D;
//typedef std::array <float,2> BoundaryStencil1D;
//typedef std::array <float,4> BoundaryStencil2D;
//typedef std::array <float,6> BoundaryStencil3D;

/*
 *	sparce matrix structors
 */
/*
typedef std::vector <Stencil1D> SparseMatrix1D;
typedef std::vector < std::vector <Stencil2D> > SparseMatrix2D;
typedef std::vector < std::vector < std::vector <Stencil3D> > > SparseMatrix3D;
*/
/*
 *	1d matrix along the whole 2d domain
 */
/*
typedef std::vector < SparseMatrix1D> PolyMatrix1dx1d;
typedef std::vector < std::vector < SparseMatrix1D> > PolyMatrix2dx1d;
*/

