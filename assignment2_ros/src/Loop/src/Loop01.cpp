#include "../include/Loop01.hpp"


namespace Loop {
    Loop01::Loop01(const rclcpp::NodeOptions &options) {
        parse_parameters();
        initialize();
    }

    void Loop01::parse_parameters() {
        history_ = this->declare_parameter("history", "keep_last");
        depth_ = this->declare_parameter("depth", 10);
    }

    void Loop01::initialize() {
        auto qos = rclcpp::QoS(depth_);
        (history_ == "keep_all") ? filter_qos.keep_all() : filter_qos.keep_last(depth_);
    }
} // end of namespace

RCLCPP_COMPONENTS_REGISTER_NODE(Loop::Loop01)