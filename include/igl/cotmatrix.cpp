#include <test_common.h>
#include <igl/cotmatrix.h>

class cotmatrix : public ::testing::TestWithParam<std::string> {};

TEST_P(cotmatrix, constant_in_null_space)
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  Eigen::SparseMatrix<double> L;
  // Load example mesh: GetParam() will be name of mesh file
  test_common::load_mesh(GetParam(), V, F);
  igl::cotmatrix(V,F,L);
  ASSERT_EQ(V.rows(),L.rows());
  ASSERT_EQ(L.rows(),L.cols());
  Eigen::VectorXd C = Eigen::VectorXd::Ones(L.rows());
  Eigen::VectorXd Z = Eigen::VectorXd::Zero(L.rows());
  // ASSERT_EQ(a,b);
  // ASSERT_TRUE(a==b);
  // ASSERT_NEAR(a,b,1e-15)
  ASSERT_LT(((L*C)-(Z)).norm(),1e-12);
}

INSTANTIATE_TEST_CASE_P
(
 all_meshes,
 cotmatrix,
 ::testing::ValuesIn(test_common::all_meshes()),
 test_common::string_test_name
);
