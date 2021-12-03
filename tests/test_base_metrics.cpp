//
// Created by achains on 30.10.2021.
//

#include <gtest/gtest.h>

#include "pc_utils.h"
#include "parse_utils.h"

#include "metrics.h"

std::vector<std::vector<double>> GetCalibrationMatrix(){
    return
            {
                    {4.276802385584e-04, -9.999672484946e-01, -8.084491683471e-03, -1.198459927713e-02},
                    {-7.210626507497e-03, 8.081198471645e-03, -9.999413164504e-01, -5.403984729748e-02},
                    {9.999738645903e-01, 4.859485810390e-04, -7.206933692422e-03, -2.921968648686e-01},
                    {0, 0, 0, 1}
            };
}

std::vector<Eigen::Matrix4d> GetCalibratedTrajectory(std::filesystem::path const & path){
    std::vector<std::vector<double>> trajectory = parse_utils::ParseTrajectory("data/00.txt");

    return pc_utils::CalibrateTrajectory(GetCalibrationMatrix(), trajectory);
}

std::vector<cilantro::PointCloud3d> GetPointClouds(std::filesystem::path const & path){
    std::vector<std::vector<double>> PCs_vector = parse_utils::GetPointClouds(path);
    std::vector<cilantro::PointCloud3d> PCs;

    for (auto & PC_vector : PCs_vector)
    {
        auto points = pc_utils::VectorToPointCloudPoints(PC_vector);
        auto PC = cilantro::PointCloud3d(points);
        PCs.push_back(PC);
    }

    return PCs;
}

TEST(BaseMetrics, MPV){
    std::vector<Eigen::Matrix4d> tj_gt = GetCalibratedTrajectory("data/00.txt");
    ASSERT_EQ(tj_gt.size(), 20);

    std::vector<cilantro::PointCloud3d> PCs = GetPointClouds("data/kitti_00");

    ASSERT_LE(std::fabs(map_metrics::mpv(PCs, tj_gt) - 0.08949105590777887), 1e8);
}

//TEST(BaseMetrics, MME){
//    std::vector<Eigen::Matrix4d> tj_gt = GetCalibratedTrajectory("data/00.txt");
//    ASSERT_EQ(tj_gt.size(), 20);
//
//    std::vector<open3d::geometry::PointCloud> PCs = GetPointClouds("data/kitti_00");
//
//    ASSERT_LE(std::fabs(map_metrics::mme(PCs, tj_gt) - 1.2553150544133582), 1e8);
//}
