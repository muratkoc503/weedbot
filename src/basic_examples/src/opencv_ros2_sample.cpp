#include <stdlib.h>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "image_transport/image_transport.h"
#include <cv_bridge/cv_bridge.h>
#include "sensor_msgs/image_encodings.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageConverter : public rclcpp::Node {
private:
    const std::string OPENCV_WINDOW = "Image window";
    image_transport::Subscriber sub_;
    image_transport::Publisher pub_;

    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg) {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
            cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        cv::waitKey(3);

        pub_.publish(cv_ptr->toImageMsg());
    }

public:
    ImageConverter() : Node("image_converter") {

        cv::namedWindow(OPENCV_WINDOW);

        rmw_qos_profile_t custom_qos = rmw_qos_profile_sensor_data;
        pub_ = image_transport::create_publisher(this, "out_image_base_topic", custom_qos);
        sub_ = image_transport::create_subscription(this, "/camera/image_raw",
                std::bind(&ImageConverter::imageCallback, this, std::placeholders::_1), "raw", custom_qos);

    }

    ~ImageConverter()
    {
        cv::destroyWindow(OPENCV_WINDOW);
    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageConverter>());
    rclcpp::shutdown();
    return 0;
}