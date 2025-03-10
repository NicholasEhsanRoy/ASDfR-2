#include "../include/Seq01.hpp"

namespace Seq {
    Seq01::Seq01(const rclcpp::NodeOptions &options) : Node("Seq01", options) {
        parse_parameters();
        initialize();
    }

    void Seq01::parse_parameters() {
        history_ = this->declare_parameter("history", "keep_last");
        depth_ = this->declare_parameter("depth", 10);
    }

    void Seq01::publish_numbers() {
        auto now = std::chrono::system_clock::now();
        auto timestamp_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

        auto message = std_msgs::msg::Int64MultiArray();
        message.data = {std::rand(), timestamp_ns};
        
        RCLCPP_INFO(this->get_logger(), "Publishing: [%ld, %ld]", message.data[0], message.data[1]);
        publisher_->publish(message);
    }

    void Seq01::initialize() {
        // Set up QoS
        auto qos = rclcpp::QoS(depth_);
        (history_ == "keep_all") ? qos.keep_all() : qos.keep_last(depth_);
        
        // Create publisher
        publisher_ = this->create_publisher<std_msgs::msg::Int64MultiArray>("random_numbers", qos);
        
        
        // Create a 1 kHz timer (1 ms interval)
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1),
            std::bind(&Seq01::publish_numbers, this));
        }
} // end of namespace

RCLCPP_COMPONENTS_REGISTER_NODE(Seq::Seq01)
