#ifndef SEQ01_HPP
#define SEQ01_HPP

#include <boost/asio.hpp>
#include <random> 
#include <chrono>
#include <vector>
#include <fstream>
#include <iomanip> 

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "std_msgs/msg/int64_multi_array.hpp"      

namespace Seq {

    struct OutputData {
        int64_t gen_ts, random, loop_reception_ts, rt_ts;
    };

    class Seq01 : public rclcpp::Node {
    public:
        explicit Seq01(const rclcpp::NodeOptions &options);

    private:
        void parse_parameters();
        void initialize();

        void publish_numbers();

        bool written;

        std::string history_;
        size_t depth_;
        rclcpp::TimerBase::SharedPtr timer_;

        std::vector<OutputData> data_vector;

        rclcpp::Subscription<std_msgs::msg::Int64MultiArray>::SharedPtr subscriber_;
        rclcpp::Publisher<std_msgs::msg::Int64MultiArray>::SharedPtr publisher_;
    };

}  // namespace seq

#endif