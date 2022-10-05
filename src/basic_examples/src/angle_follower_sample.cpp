#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "angles/angles.h"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class AngleFollower : public rclcpp::Node{
  public:
    AngleFollower()
    : Node("angleFollower_cmd_vel")
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
      timer_ = this->create_wall_timer(
        10ms, std::bind(&AngleFollower::timer_callback, this));
    }
    geometry_msgs::msg::Twist AngularPID(double camera_angle, double houghLine_angle){
        k_p_ = 0.4;
        k_i_ =  1;
        k_d_ =  0.7;
        period_ = 0.1;

        geometry_msgs::msg::Twist velocity;

        double ang_diff = angles::shortest_angular_distance(camera_angle, houghLine_angle);

		float angle = houghLine_angle;
		float th = camera_angle;
		float zw = 0;
		float error = 0;      float error1 = 0;     float error2 = 0;     float error3 = 0;
		float th1 = 0;        
		float zw_old = 0;

        error = ang_diff;

        zw = k_p_*error + k_i_*period_*(angle-(th+th1)/2.0) +
		(k_d_/(6*period_))*((error-error3)+3*(error1-error2)) + zw_old;
		
		th1 = th;
		error3 = error2;
		error2 = error1;
		error1 = error;
		zw_old = zw;

    	velocity.linear.set__x(0.2);
		velocity.angular.set__z(zw);

		return velocity;
    }

    void HoughLineTest(){
        
    }

  private:
    void timer_callback()
    {
      geometry_msgs::msg::Twist msg = AngularPID(camera_angle_, houghLine_angle_);
      RCLCPP_INFO(this->get_logger(), "Publishing angular Vel: '%f'", msg.angular.z);
      publisher_->publish(msg);
      
    }   
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    const double camera_angle_ = 0.0;     // radian
    double houghLine_angle_ = 0.0;        // radian

    //-- PID --
    double k_p_, k_i_, k_d_; 
    double period_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AngleFollower>());
  rclcpp::shutdown();
  return 0;
}