int32 random
int64 timestamp

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
        auto message = std_msgs::msg::Int64MultiArray();
        message.data = {42, 84};
        
        RCLCPP_INFO(this->get_logger(), "Publishing: [%ld, %ld]", message.data[0], message.data[1]);
        publisher_->publish(message);
    }

    void Seq01::initialize() {
        // Set up QoS
        auto qos = rclcpp::QoS(depth_);
        (history_ == "keep_all") ? qos.keep_all() : qos.keep_last(depth_);
        
        // Create publisher
        publisher_ = this->create_publisher<std_msgs::msg::Int64MultiArray>("random_numbers", qos);
        
        // Random number generator setup
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(0, 100);
        
        // Create a 1 kHz timer (1 ms interval)
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&Seq01::publish_numbers, this));
        }
} // end of namespace

RCLCPP_COMPONENTS_REGISTER_NODE(Seq::Seq01)
