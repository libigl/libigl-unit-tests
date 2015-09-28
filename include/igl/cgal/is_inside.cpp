#include <test_common.h>

#include <igl/cgal/is_inside.h>

namespace IsInsideHelper {

template<typename DerivedP, typename DerivedV, typename DerivedF>
void create_tiny_tet(
        const Eigen::PlainObjectBase<DerivedP>& p,
        Eigen::PlainObjectBase<DerivedV>& V,
        Eigen::PlainObjectBase<DerivedF>& F) {
    const typename DerivedP::Scalar EPS = 1e-6;
    V.resize(4, 3);
    V << p(0,0), p(1,0), p(2,0),
         p(0,0) + EPS, p(1,0), p(2,0),
         p(0,0), p(1,0) + EPS, p(2,0),
         p(0,0), p(1,0), p(2,0) + EPS;
    F.resize(4, 3);
    F << 0, 2, 1,
         0, 3, 2,
         0, 1, 3,
         1, 2, 3;
}

TEST(IsInside, simple) {
    Eigen::MatrixXd V1;
    Eigen::MatrixXi F1;
    test_common::load_mesh("cube.obj", V1, F1);

    Eigen::VectorXd centroid = V1.colwise().sum() / V1.rows();
    Eigen::VectorXd max_corner = V1.colwise().maxCoeff();
    max_corner += Eigen::VectorXd::Ones(3);

    Eigen::MatrixXd V2;
    Eigen::MatrixXi F2;
    create_tiny_tet(centroid, V2, F2);

    ASSERT_FALSE(igl::cgal::is_inside(V1, F1, V2, F2));
    ASSERT_TRUE(igl::cgal::is_inside(V2, F2, V1, F1));

    Eigen::MatrixXd V3;
    Eigen::MatrixXi F3;
    create_tiny_tet(max_corner, V3, F3);

    ASSERT_FALSE(igl::cgal::is_inside(V1, F1, V3, F3));
    ASSERT_FALSE(igl::cgal::is_inside(V3, F3, V1, F1));
}

}
