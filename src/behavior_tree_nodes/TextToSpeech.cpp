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

/*#include <string>*/
#include "behavior_tree/TextToSpeech.h"
#include "sound_play/SoundRequest.h"
#include "std_msgs/String.h"
#include "diagnostic_msgs/DiagnosticArray.h"
/*#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ros/ros.h"*/

namespace behavior_tree
{


TextToSpeech::TextToSpeech(const std::string& name,  const BT::NodeConfiguration & config)
: BT::ActionNodeBase(name, config)
{
  sub = nh.subscribe("/diagnostics", 10, &TextToSpeech::messageCallback, this);
	ad = nh.advertise<sound_play::SoundRequest>("/robotsound",10);
  charla = "Hello there , I see that you need help. Please point repeatedly (shaking your hand) the bag you want me to take" ;
	
}


void TextToSpeech::messageCallback(const diagnostic_msgs::DiagnosticArray::ConstPtr& msg)
{ 
  //std::cout << msg->status[0].message << "\n" ;
  feedback = msg->status[0].message ;
}

void TextToSpeech::halt()
{
  
  // ROS_INFO("TextToSpeech halt");
}

BT::NodeStatus TextToSpeech::tick()
{
  if(ac < 20){
      ac++;
      //std::cout << "PUBLICANDO" << "\n" ;
      if(ac < 3 ){
			sound_play::SoundRequest habla ;
			habla.sound = -3 ;
			habla.command = 1 ;
			habla.volume = 1 ;
			habla.arg = charla ;
			ad.publish(habla) ;
      }
      return BT::NodeStatus::RUNNING;
	}

 
  if (feedback != "0 sounds playing") {
    return BT::NodeStatus::RUNNING;
  }
  else {
     if(!exito){
      sound_play::SoundRequest habla ;
			habla.sound = -1 ;
			habla.command = 0 ;
			habla.volume = 1 ;
			habla.arg = charla ;
			ad.publish(habla) ;
      exito=true;
     }
    return BT::NodeStatus::SUCCESS;
  }
}

}  // namespace behavior_tree


BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<behavior_tree::TextToSpeech>("TextToSpeech");
}