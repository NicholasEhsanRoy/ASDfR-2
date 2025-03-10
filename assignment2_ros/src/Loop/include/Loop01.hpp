#ifndef LOOP01_HPP
#define LOOP01_HPP

#include <boost/asio.hpp>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/int64_multi_array.hpp"          

namespace Loop {
    class Loop01 : public rclcpp::Node {
    public:
        explicit Loop01(const rclcpp::NodeOptions &options);

    private:
        void parse_parameters();
        void initialize();
        // void loop_callback(const std_msgs::msg::Int64MultiArray::SharedPtr msg);

        std::string history_;
        size_t depth_;

        rclcpp::Subscription<std_msgs::msg::Int64MultiArray>::SharedPtr subscriber_;
        rclcpp::Publisher<std_msgs::msg::Int64MultiArray>::SharedPtr publisher_;
    };

}  // namespace loop

#endif