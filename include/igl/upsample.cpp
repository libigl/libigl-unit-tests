
#include <test_common.h>
#include <igl/upsample.h>

class upsample : public ::testing::TestWithParam<std::string> {};

TEST_P(upsample, change_to_meaningful_name)
{
  Eigen::MatrixXd V,NV;
  Eigen::MatrixXi F,NF;
  // Load example mesh: GetParam() will be name of mesh file
  test_common::load_mesh(GetParam(), V, F);
  igl::upsample(V,F,NV,NF);
  ASSERT_GE(NV.rows(),V.rows());
  ASSERT_EQ(NF.rows(),4*F.rows());
  // V should be first part of V
  test_common::assert_eq(V,NV.topLeftCorner(V.rows(),V.cols()));
  // Expect a particular order 
  for(int f = 0;f<F.rows();f++)
  {
    ASSERT_EQ( F(f,0), NF((f*4)+0,0) );
    ASSERT_EQ( F(f,1), NF((f*4)+1,0) );
    ASSERT_EQ( F(f,2), NF((f*4)+3,1) );
  }
}

INSTANTIATE_TEST_CASE_P
(
  all_meshes,
  upsample,
  ::testing::ValuesIn(test_common::all_meshes()),
  test_common::string_test_name
);
