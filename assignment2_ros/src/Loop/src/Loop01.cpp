#include "../include/Loop01.hpp"


namespace Loop {
    Loop01::Loop01(const rclcpp::NodeOptions &options) : Node("Loop01", options) {
        parse_parameters();
        initialize();
    }

    void Loop01::parse_parameters() {
        history_ = this->declare_parameter("history", "keep_last");
        depth_ = this->declare_parameter("depth", 10);
    }

    void Loop01::initialize() {
        auto qos = rclcpp::QoS(depth_);
        (history_ == "keep_all") ? qos.keep_all() : qos.keep_last(depth_);

        publisher_ = this->create_publisher<std_msgs::msg::Int64MultiArray>("seq_consume", qos);

        auto loop_callback = [this](std_msgs::msg::Int64MultiArray::SharedPtr msg) -> void {
            auto now = std::chrono::system_clock::now();
            auto timestamp_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
            auto message = std_msgs::msg::Int64MultiArray();
            message.data = {msg->data[0], msg->data[1], timestamp_ns};
    
            publisher_->publish(message);
            // RCLCPP_INFO(this->get_logger(), "Received: [%ld, %ld, %ld]", msg->data[0], msg->data[1], timestamp_ns);
        };

        subscriber_ = create_subscription<std_msgs::msg::Int64MultiArray>("seq_generate", qos, loop_callback);
    }

} // end of namespace

RCLCPP_COMPONENTS_REGISTER_NODE(Loop::Loop01)