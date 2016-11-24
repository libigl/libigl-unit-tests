#include <test_common.h>
#include <igl/qslim.h>
#include <igl/cylinder.h>
#include <igl/hausdorff.h>

TEST(qslim,cylinder)
{
  using namespace igl;
  const int axis_devisions = 5;
  const int height_devisions = 2+10;
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  cylinder(axis_devisions,height_devisions,V,F);
  Eigen::MatrixXd U;
  Eigen::MatrixXi G;
  Eigen::VectorXi I,J;
  qslim(V,F,2*axis_devisions,U,G,I,J);
  ASSERT_EQ(axis_devisions*2,U.rows());
  double d;
  igl::hausdorff(V,F,U,G,d);
  ASSERT_NEAR(d,0,2e-10);
}
