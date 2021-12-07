//
// Created by achains on 18.11.2021.
//

#ifndef MAP_METRICS_METRICS_UTILS_H
#define MAP_METRICS_METRICS_UTILS_H

#include <cilantro/core/kd_tree.hpp>
#include <cilantro/utilities/point_cloud.hpp>

#include <optional>

namespace metrics_utils {

    using PointCloud = cilantro::PointCloud3d;
    using KDTree = cilantro::KDTree3d<>;

    Eigen::MatrixX3d FindCov(Eigen::MatrixX3d const & M);

    // Points are represented like
    //    x1   ...   xn
    //  ( y1 ) ... ( yn )
    //    z1   ...   zn
    Eigen::MatrixX3d TransformPointIdxToMatrix(cilantro::VectorSet3d const & points, std::vector<int> const & idx);

    PointCloud AggregateMap(std::vector<PointCloud> const & pcs, std::vector<Eigen::Matrix4d> const & ts);

    std::vector<int> GetRadiusSearchIndices(KDTree const & tree,
                                                       Eigen::Vector3d const & query, double radius);

    namespace metrics_algorithm{
        std::optional<double> ComputeEigenvalues(cilantro::VectorSet3d const & points,
                                                  std::vector<int> const & indices);

        std::optional<double> ComputeEntropy(cilantro::VectorSet3d const & points,
                                              std::vector<int> const & indices);
    } // namespace metrics_algorithm
} // namespace metrics_utils

#endif //MAP_METRICS_METRICS_UTILS_H
