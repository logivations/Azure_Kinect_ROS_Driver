// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// System headers
//
#include <sstream>

// Library headers
//
#include "rclcpp/rclcpp.hpp"
#include <k4a/k4a.h>

// Project headers
//
#include "azure_kinect_ros_driver/k4a_ros_device.h"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  // Setup the K4A device (K4AROSDevice is now a rclcpp::Node)
  rclcpp::NodeOptions options;
  auto device = std::make_shared<K4AROSDevice>(options);

  k4a_result_t result = device->startCameras();

  if (result != K4A_RESULT_SUCCEEDED)
  {
    RCLCPP_ERROR_STREAM(device->get_logger(), "Failed to start cameras");
    return -1;
  }

  result = device->startImu();
  if (result != K4A_RESULT_SUCCEEDED)
  {
    RCLCPP_ERROR_STREAM(device->get_logger(), "Failed to start IMU");
    return -2;
  }

  RCLCPP_INFO(device->get_logger(), "K4A Started");

  if (result == K4A_RESULT_SUCCEEDED)
  {
    rclcpp::spin(device);

    RCLCPP_INFO(device->get_logger(), "ROS Exit Started");
  }

  device.reset();

  rclcpp::shutdown();

  return 0;
}