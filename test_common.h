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
  inline std::vector<std::string> closed_manifold_meshes()
  {
    return 
      {
        "cube.obj",
        "decimated-knight.obj",
        };
  };
  inline std::vector<std::string> manifold_meshes()
  {
    std::vector<std::string> meshes = closed_manifold_meshes();
    meshes.insert(meshes.end(),
      {
        "boolean_minus_test_cube.obj",
        "boolean_minus_test_green.obj",
        "bunny.off",
        "elephant.off"});
    return meshes;
  };
  inline std::vector<std::string> all_meshes()
  {
    std::vector<std::string> meshes = manifold_meshes();
    meshes.insert(meshes.end(),
      {
        "truck.obj"});
    return meshes;
  };
  inline std::string data_path(std::string s)
  {
    return std::string(TEST_DIR) + "/data/" + s;
  };

  // TODO: this seems like a pointless indirection. Should just find and
  // replace test_common::load_mesh(X,...) with
  // igl::read_triangle_mesh(test_common::data_path(X),...)
  template<typename DerivedV, typename DerivedF>
  void load_mesh(
    const std::string& filename, 
    Eigen::PlainObjectBase<DerivedV>& V,
    Eigen::PlainObjectBase<DerivedF>& F)
  {
    igl::read_triangle_mesh(data_path(filename), V, F);
  }

  // TODO: this seems like a pointless indirection. Should just find and
  // replace test_common::load_matrix(X,...) with
  // igl::readDMAT(test_common::data_path(X),...)
  template<typename Derived>
  void load_matrix(
    const std::string& filename,
    Eigen::PlainObjectBase<Derived>& M) 
  {
    igl::readDMAT(data_path(filename), M);
  }
}
