#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <memory>
#include <functional>

using std::placeholders::_1;
void sub_callback(rclcpp::Node::SharedPtr node, const std_msgs::msg::Int32::SharedPtr msg)
{
    RCLCPP_INFO(node->get_logger(), "node Received message: %d", msg->data);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_sub1_2");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    std::function<void(const std_msgs::msg::Int32::SharedPtr msg)> fn;
    fn = std::bind(sub_callback, node, _1);
    auto sub = node->create_subscription<std_msgs::msg::Int32>("/topic_psub1_2",qos_profile,fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}