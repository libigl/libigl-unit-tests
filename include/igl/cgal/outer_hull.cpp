#include <test_common.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <igl/cgal/outer_hull.h>

TEST(OuterHull, CubeWithFold) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    test_common::load_mesh("cube_with_fold.ply", V, F);

    Eigen::MatrixXi G,J,flip;
    igl::cgal::outer_hull(V, F, G, J, flip);
}
