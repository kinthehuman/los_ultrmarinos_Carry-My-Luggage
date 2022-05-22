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

#include <cmath>
#include <memory>

#include "tf/tf.h"
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose2D.h"


bool act = false;
int data_number = 0;
int orientacion = 0;
int fr = 10;
const int max_data = 5;
const int min_dif = max_data/10;
std_msgs::String msg;
geometry_msgs::Pose2D mSensorsData;

void activacionTree(const std_msgs::Bool::ConstPtr& pp)
{
  act = pp->data;
}

void movementReceived(const geometry_msgs::Pose2DConstPtr& lado)
{
  if (act)
  {
    mSensorsData = *lado;
    data_number++;
    orientacion = orientacion + mSensorsData.x;
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "identificadorLado");
  ros::NodeHandle nh;
  ros::Rate loop_rate(fr);

  // ros::Publisher talkPub = nh.advertise<std_msgs::String>("/nodo_hablar", fr);
  ros::Publisher treePub = nh.advertise<std_msgs::String>("/status_maleta", fr);

  ros::Subscriber movementSub = nh.subscribe<geometry_msgs::Pose2D>("/movement_data", fr, movementReceived);
  ros::Subscriber Activador = nh.subscribe("/control_maleta", fr, activacionTree);

  while (ros::ok())
  {
    if (act)
    {
      if (data_number > max_data)
      {
        if (orientacion > min_dif)
        {
          /*
          std::stringstream result;
          result << "DERECHA";
          msg.data = result.str();
          talkPub.publish(msg);
          */
          std::cout << " EXITOOOOOOO DERECHA ";

          std::stringstream status;
          status << "SUCCESS_DERECHA";
          msg.data = status.str();
          treePub.publish(msg);
        }
        else if (orientacion < -min_dif)
        {
          /*
          std::stringstream result;
          result << "IZQUIERDA";
          msg.data = result.str();
          talkPub.publish(msg);
          */

          std::cout << " EXITOOOOOOO IZQUIERDA ";

          std::stringstream status;
          status << "SUCCESS_IZQUIERDA";
          msg.data = status.str();
          treePub.publish(msg);
        }
        else if (-min_dif <= orientacion <= min_dif)
        {
          /*
          std::stringstream result;
          result << "FAIL";
          msg.data = result.str();
          talkPub.publish(msg);
          */

          std::stringstream status;
          status << "NO_MOVIMIENTO";
          msg.data = status.str();
          treePub.publish(msg);
        }
        data_number = 0;
        orientacion = 0;
      }
      else
      {
        std::stringstream status;
        status << "RUNNING";
        msg.data = status.str();
        treePub.publish(msg);
      }
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
