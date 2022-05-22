// Copyright 2022 los ultramarinos
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BEHAVIOR_TREE_NAVEGAR4_H
#define BEHAVIOR_TREE_NAVEGAR4_H

#include <string>

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int64.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "move_base_msgs/MoveBaseActionResult.h"

namespace behavior_trees
{
class Navegar2 : public BT::ActionNodeBase
{
  public:
    explicit Navegar2(const std::string& name , const BT::NodeConfiguration& config);
    void halt();
    BT::NodeStatus tick();

    void messageCallback(const std_msgs::Int64::ConstPtr& msg);
    static BT::PortsList providedPorts()
    {
      return {BT::InputPort<std::string>("object")};
    }

  private:
    ros::NodeHandle nh_;
    ros::Publisher activador;
    ros::Subscriber sub;
    int feedBack = 0;
    ros::Time i;
    int ac = 0;
};
}  // namespace behavior_trees
#endif  // BEHAVIOR_TREE_NAVEGAR4_H
