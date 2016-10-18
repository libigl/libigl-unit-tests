#pragma once


#include <igl/read_triangle_mesh.h>
#include <igl/readDMAT.h>

#include <Eigen/Core>
#include <gtest/gtest.h>

#include <cctype>
#include <string>
#include <functional>
#include <algorithm>

namespace test_common 
{
  // Input:
  //   s  arbitrary string
  // Returns s with all non-alphanumeric characters replaced with underscores '_'
  inline std::string safe_test_name(std::string s)
  {
    std::for_each(s.begin(),s.end(),[](char &c){if(!std::isalnum(c)) c='_';});
    return s;
  };
  inline std::string string_test_name(const ::testing::TestParamInfo<std::string>& info)
  {
    return test_common::safe_test_name(info.param);
  };
  inline std::vector<std::string> all_meshes()
  {
    return std::vector<std::string>(
      {
        "boolean_minus_test_cube.obj",
        "boolean_minus_test_green.obj",
        "bunny.off",
        "cube.obj",
        "elephant.off",
        "truck.obj"});
  };
  inline std::vector<std::string> manifold_meshes()
  {
    return std::vector<std::string>(
      {
        "boolean_minus_test_cube.obj",
        "boolean_minus_test_green.obj",
        "bunny.off",
        "cube.obj",
        "elephant.off"});
  };
  inline std::vector<std::string> closed_manifold_meshes()
  {
    return std::vector<std::string>(
      {
        "cube.obj"});
  };

  template<typename DerivedV, typename DerivedF>
  void load_mesh(
          const std::string& filename, 
          Eigen::PlainObjectBase<DerivedV>& V,
          Eigen::PlainObjectBase<DerivedF>& F) {
      auto find_file = [&](const std::string& val) {
          return std::string(TEST_DIR) + "/data/" + val;
      };
      igl::read_triangle_mesh(find_file(filename), V, F);
  }

  template<typename Derived>
  void load_matrix(const std::string& filename,
          Eigen::PlainObjectBase<Derived>& M) {
      igl::readDMAT(std::string(TEST_DIR) + "/data/" + filename, M);
  }
}
