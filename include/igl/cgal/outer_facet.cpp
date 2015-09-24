#include <test_common.h>

#include <igl/cgal/outer_facet.h>

TEST(OuterFacet, Simple) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    test_common::load_mesh("cube.obj", V, F);

    const size_t num_faces = F.rows();

    Eigen::VectorXi I(num_faces);
    I.setLinSpaced(num_faces, 0, num_faces-1);

    size_t fid = num_faces + 1;
    bool flipped;
    igl::cgal::outer_facet(V, F, I, fid, flipped);

    ASSERT_LT(fid, num_faces);
    ASSERT_FALSE(flipped);
}

TEST(OuterFacet, DuplicatedOppositeFaces) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F1;
    test_common::load_mesh("cube.obj", V, F1);

    Eigen::MatrixXi F2 = F1;
    F2.col(0).swap(F2.col(1));

    Eigen::MatrixXi F(F1.rows()*2, F1.cols());
    F << F1, F2;

    Eigen::VectorXi I(F.rows());
    I.setLinSpaced(F.rows(), 0, F.rows()-1);

    size_t fid = F.rows() + 1;
    bool flipped;
    igl::cgal::outer_facet(V, F, I, fid, flipped);

    ASSERT_LT(fid, F.rows());
    ASSERT_FALSE(flipped);
}

TEST(OuterFacet, FullyDegnerated) {
    Eigen::MatrixXd V(7, 3);
    V <<  0.0, 0.0, 0.0, // 0
          1.0, 0.0, 0.0, // 1
          0.0, 1.0, 0.0, // 2
          0.0, 0.0, 1.0, // 3
         -1.0, 0.0, 0.0, // 4
          0.0,-1.0, 0.0, // 5
          0.0, 0.0,-1.0; // 6

    Eigen::MatrixXi F(24, 3);
    F << 0, 1, 2,
         0, 2, 1,
         0, 1, 5,
         0, 5, 1,
         0, 1, 3,
         0, 3, 1,
         0, 1, 6,
         0, 6, 1,
         0, 4, 2,
         0, 2, 4,
         0, 4, 5,
         0, 5, 4,
         0, 4, 3,
         0, 3, 4,
         0, 4, 6,
         0, 6, 4,
         0, 2, 3,
         0, 3, 2,
         0, 5, 3,
         0, 3, 5,
         0, 2, 6,
         0, 6, 2,
         0, 5, 6,
         0, 6, 5;

    Eigen::VectorXi I(F.rows());
    I.setLinSpaced(F.rows(), 0, F.rows()-1);

    size_t fid = F.rows() + 1;
    bool flipped;
    igl::cgal::outer_facet(V, F, I, fid, flipped);

    ASSERT_LT(fid, F.rows());
    ASSERT_FALSE(flipped);
}

TEST(OuterFacet, InvertedNormal) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    test_common::load_mesh("cube.obj", V, F);
    F.col(0).swap(F.col(1));

    Eigen::VectorXi I(F.rows());
    I.setLinSpaced(F.rows(), 0, F.rows()-1);

    size_t fid = F.rows() + 1;
    bool flipped;
    igl::cgal::outer_facet(V, F, I, fid, flipped);

    ASSERT_LT(fid, F.rows());
    ASSERT_TRUE(flipped);
}

