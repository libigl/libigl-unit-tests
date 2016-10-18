#!/bin/bash
#
# Creates a template for testing a new igl function given its name.

if [ $# -eq 0 ]
then
  echo "Usage:

# cd include/igl/
./new.sh cotmatrix"
  exit 1
fi

name="$1"
cpp="$name.cpp"
if [ -f $cpp ]
then
  echo "Error: $cpp already exists"
  exit 1
else
  echo "
#include <test_common.h>
#include <igl/$name.h>

class $name : public ::testing::TestWithParam<std::string> {};

TEST_P($name, change_to_meaningful_name)
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  Eigen::SparseMatrix<double> L;
  // Load example mesh: GetParam() will be name of mesh file
  test_common::load_mesh(GetParam(), V, F);
  // ASSERT_EQ(a,b);
  // ASSERT_TRUE(a==b);
  // ASSERT_NEAR(a,b,1e-15)
  // ASSERT_LT(a,1e-12);
}

INSTANTIATE_TEST_CASE_P
(
 all_meshes,
 $name,
 ::testing::ValuesIn(test_common::all_meshes()),
 test_common::string_test_name
);" > $cpp
fi
