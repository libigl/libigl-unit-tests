#include <test_common.h>
#include <igl/decimate.h>
#include <igl/sort.h>
#include <igl/sortrows.h>

class decimate : public ::testing::TestWithParam<std::string> {};

TEST_P(decimate, closed)
{
  Eigen::MatrixXd V,U;
  Eigen::MatrixXi F,G;
  Eigen::VectorXi J;
  // Load example mesh: GetParam() will be name of mesh file
  test_common::load_mesh(GetParam(), V, F);
  igl::decimate(V,F,0,U,G,J);
  ASSERT_EQ(U.rows(),4);
  ASSERT_EQ(G.rows(),4);
  {
    Eigen::MatrixXi I;
    igl::sort(Eigen::MatrixXi(G),2,true,G,I);
  }
  {
    Eigen::VectorXi I;
    igl::sortrows(Eigen::MatrixXi(G),true,G,I);
  }
  // Tet with sorted faces
  Eigen::MatrixXi T(4,3);
  T<<
    0,1,2,
    0,1,3,
    0,2,3,
    1,2,3;
  test_common::assert_eq(G,T);
}

INSTANTIATE_TEST_CASE_P
(
  closed_genus_0_meshes,
  decimate,
  ::testing::ValuesIn(test_common::closed_genus_0_meshes()),
  test_common::string_test_name
);
