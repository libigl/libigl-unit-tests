#include <test_common.h>
#include <igl/doublearea.h>

TEST(doublearea, simple)
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  test_common::load_mesh("elephant.off", V, F);

  Eigen::VectorXd A1,A2;
  igl::doublearea(V,F,A1);
  Eigen::MatrixXd A(F.rows(),3);
  Eigen::MatrixXd B(F.rows(),3);
  Eigen::MatrixXd C(F.rows(),3);
  for(int f = 0;f<F.rows();f++)
  {
    A.row(f) = V.row(F(f,0));
    B.row(f) = V.row(F(f,1));
    C.row(f) = V.row(F(f,2));
  }
  igl::doublearea(A,B,C,A2);
  ASSERT_EQ(A1.size(),A2.size());
  for(int a = 0;a<A1.size();a++)
  {
    ASSERT_NEAR(A1(a),A2(a),1e-15);
  }
}
