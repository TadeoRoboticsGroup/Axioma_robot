#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>

using std::placeholders::_1;

class ScoobyMapPublisher : public rclcpp::Node
{
public:
    ScoobyMapPublisher()
        : Node("scooby_map_publisher")
    {
        tf_broadcaster_ =
            std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "odom", 1,
            std::bind(&ScoobyMapPublisher::odom_callback, this, _1));
    }

private:
    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) const
    {
        rclcpp::Time now = this->now();
        //RCLCPP_INFO(this->get_logger(), "Pose: '%f'", msg->x);
	
	std::string child_frame = msg->child_frame_id;
	
        geometry_msgs::msg::TransformStamped odom_tf;
        // Odom to Map frame
        odom_tf.transform.translation.x = 0.0;
        odom_tf.transform.translation.y = 0.0;
        odom_tf.transform.translation.z = 0.0;
        tf2::Quaternion q;
        q.setRPY(0, 0, 0);
        odom_tf.transform.rotation.x = q.x();
        odom_tf.transform.rotation.y = q.y();
        odom_tf.transform.rotation.z = q.z();
        odom_tf.transform.rotation.w = q.w();

        odom_tf.header.frame_id = "map";
        odom_tf.child_frame_id = "odom";
        odom_tf.header.stamp = now;
        tf_broadcaster_->sendTransform(odom_tf);
    }
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ScoobyMapPublisher>());
    rclcpp::shutdown();
    return 0;
}
