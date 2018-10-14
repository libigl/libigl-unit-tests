#include <gtest/gtest.h>
#include <test_common.h>
#include <igl/marching_tets.h>
#include <igl/readOBJ.h>
#include <igl/readMESH.h>
#include <igl/readDMAT.h>

class marching_tets : public ::testing::TestWithParam<std::string> {};

TEST(marching_tets, cube)
{
  Eigen::MatrixXd V, SV, TV;
  Eigen::MatrixXi F, SF, TF, TT;
  Eigen::VectorXd S;

  igl::readDMAT(test_common::data_path("marching_tets_scalars.dmat"), S);
  igl::readOBJ(test_common::data_path("marching_tets_output.obj"), V, F);
  igl::readMESH(test_common::data_path("marching_tets_input.mesh"), TV, TT, TF);

  igl::marching_tets(TV, TT, S, 0.45, SV, SF);
  test_common::assert_near(SV, V, 1e-16);
  test_common::assert_eq(SF, F);
}
