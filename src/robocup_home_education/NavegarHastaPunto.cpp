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

#include <string>

#include "std_msgs/Bool.h"
#include "std_msgs/Int64.h"
#include "geometry_msgs/PoseStamped.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "actionlib/client/simple_action_client.h"

namespace navigation
{
class Navigator
{
  public:
    explicit Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", false), goal_sended_(false)
    {
      wp_sub_ = nh_.subscribe("/navigate_to", 1, &Navigator::navigateCallback, this);
    }

    void navigateCallback(geometry_msgs::PoseStamped goal_pose_)
    {
      ROS_INFO("[navigate_to_wp] Commanding to (%f %f)", goal_pose_.pose.position.x, goal_pose_.pose.position.y);
      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose = goal_pose_;
      goal.target_pose.header.frame_id = "map";
      goal.target_pose.header.stamp = ros::Time::now();
      action_client_.sendGoal(goal);
      goal_sended_ = true;
    }

    int step()
    {
      if (goal_sended_)
      {
        bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
        actionlib::SimpleClientGoalState state = action_client_.getState();
        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = action_client_.getState();
          if (state == actionlib::SimpleClientGoalState::SUCCEEDED)
          {
            ROS_INFO("[navigate_to_wp] Goal Reached!");
            return 1;
          }
          else
          {
            ROS_INFO("[navigate_to_wp] Something bad happened!");
            return -1;
          }
          goal_sended_ = false;
          return 0;
        }
      }
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    bool goal_sended_;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
};
}  // namespace navigation

int main(int argc, char** argv)
{
  ros::init(argc, argv, "NavegarHastaPunto");
  ros::NodeHandle nh("~");
  navigation::Navigator navigator(nh);
  ros::Publisher resulatdo = nh.advertise<std_msgs::Int64>("/resultado_navegacion", 10);

  while (ros::ok())
  {
    int estado = navigator.step();
    std_msgs::Int64 msg;
    msg.data = estado;
    resulatdo.publish(msg);
    ros::spinOnce();
  }
  return 0;
}
