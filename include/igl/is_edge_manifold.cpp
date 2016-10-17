#include <test_common.h>
#include <igl/is_edge_manifold.h>

TEST(is_edge_manifold, simple)
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  test_common::load_mesh("elephant.off", V, F);
  ASSERT_TRUE( igl::is_edge_manifold(F) );
  test_common::load_mesh("bunny.off", V, F);
  ASSERT_TRUE( igl::is_edge_manifold(F) );
  test_common::load_mesh("cube.obj", V, F);
  ASSERT_TRUE( igl::is_edge_manifold(F) );
}
