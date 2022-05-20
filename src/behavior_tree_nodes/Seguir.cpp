// Copyright 2019 Intelligent Robotics Lab
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

#include "behavior_tree/Seguir.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "std_msgs/String.h"
#include "ros/ros.h"

namespace behavior_trees
{

Seguir::Seguir(const std::string& name , const BT::NodeConfiguration & config): BT::ActionNodeBase(name, config),nh_(),feedBack(" ")
{   
  activador = nh_.advertise<std_msgs::Bool>("/control_seguimiento",10);
  sub = nh_.subscribe<std_msgs::String>("/status_seguimiento", 10, &Seguir::messageCallback, this); 
}


void
Seguir::messageCallback(const std_msgs::String::ConstPtr& msg)
{
  feedBack = msg->data ;
  //std::cout << msg->data  ;
}


void
Seguir::halt()
{
  ROS_INFO("Seguir halt");
}

BT::NodeStatus
Seguir::tick()
{
 
  if(a < 10){
  //ROS_INFO("Centrar RUNNING Esperansdo");
  std_msgs::Bool act ;
  act.data = true ;
  activador.publish(act);
  a++ ;
  return BT::NodeStatus::RUNNING;
  }
  
  if (feedBack == "RUNNING") {
       
         return BT::NodeStatus::RUNNING;
  } 

  if (feedBack == "SUCCESS") {
    if(!exito){
      std_msgs::Bool act ;
     act.data = false ;
     activador.publish(act);
    }
    return BT::NodeStatus::SUCCESS;
  }
    
  

  return BT::NodeStatus::RUNNING;
}

}  // namespace behavior_trees


BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<behavior_trees::Seguir>("Seguir");
}
