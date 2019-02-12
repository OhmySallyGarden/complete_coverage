#ifndef COVERAGE_BINN_H_
#define COVERAGE_BINN_H_

#include <coverage_binn/partition_binn.h>
#include <nav_msgs/OccupancyGrid.h>
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>

class CoverageBinn {
 public:
  CoverageBinn();

 private:
  void onMapReceived(const nav_msgs::OccupancyGrid& grid);
  void mainLoop(ros::NodeHandle& nh);
  bool updateRobotPose(const tf2_ros::Buffer& tfBuffer);
  void BINN();
  void evolveNeuralNetwork(double deltaTime);
  double calculateI(PartitionBinn::CellStatus status, bool covered);
  double calculateWeightSum(int l, int k, double x);
  double calculateWeight(int l0, int k0, int l1, int k1);
  void getNeighbors(int l, int k, std::vector<PartitionBinn::Point>& neighbors);

  struct Pose {
    double x;
    double y;
    double yaw;
  };

  bool m_mapInitialized;
  PartitionBinn m_partition;
  Pose m_pose;

  // Neural network params
  double m_A = 50.0;
  double m_B = 0.1;
  double m_D = -0.1;
  double m_E = 100.0;
  double m_mu = 1.0;
};

#endif
