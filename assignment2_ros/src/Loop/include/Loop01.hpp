#ifndef LOOP01_HPP
#define LOOP01_HPP

#include <boost/asio.hpp>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/int32.hpp"       

namespace Loop {
    class Loop01 : public rclcpp::Node {
    public:
        explicit Loop01(const rclcpp::NodeOptions &options);

    private:
        void parse_parameters();
        void initialize();

        std::string history_;
        size_t depth_;

        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_filter_;
        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_filter_;
    };

}  // namespace loop

#endif