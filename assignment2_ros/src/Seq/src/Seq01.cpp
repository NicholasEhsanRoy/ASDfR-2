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
        // RCLCPP_INFO(this->get_logger(), "Publishing: [%ld, %ld]", message.data[0], message.data[1]);
        publisher_->publish(message);
    }

    void Seq01::initialize() {
        // Set up QoS
        auto qos = rclcpp::QoS(depth_);
        (history_ == "keep_all") ? qos.keep_all() : qos.keep_last(depth_);

        data_vector.reserve(10000);
        written = false;
        
        // Create publisher
        publisher_ = this->create_publisher<std_msgs::msg::Int64MultiArray>("seq_generate", qos);
        
        
        // Create a 1 kHz timer (1 ms interval)
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1),
            std::bind(&Seq01::publish_numbers, this));

        auto seq_consume_callback = [this](std_msgs::msg::Int64MultiArray::SharedPtr msg) -> void {
            auto now = std::chrono::system_clock::now();
            auto timestamp_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

            if (this->data_vector.size() >= 10000 && !written) {
                std::cout << "10,000 entries found!\n";
                this->written = true;
                std::ofstream file("assignment2-3-seq-data.csv");
                if (file.is_open()) {
                    // Write header to the CSV (optional)
                    file << "gen_ts,random,loop_reception_ts,rt_ts\n";
                    
                    // Loop through the static timestamps vector and write each timestamp to the file
                    for (size_t i = 0; i < 10000; ++i) {
                        // Convert timestamp to seconds with 10 decimal places
                        float a, b, c, d;

                        a = this->data_vector[i].gen_ts / 1000000000.0;
                        b = this->data_vector[i].random / 1000000000.0;
                        c = this->data_vector[i].loop_reception_ts / 1000000000.0;
                        d = this->data_vector[i].rt_ts / 1000000000.0;

                        // Write the timestamp as seconds with 10 decimal points
                        file << std::fixed << std::setprecision(10) << a << ','
                             << std::fixed << std::setprecision(10) << b << ',' 
                             << std::fixed << std::setprecision(10) << c << ',' 
                             << std::fixed << std::setprecision(10) << d << "\n";
                    }

                    // Close the file
                    file.close();
                    std::cout << "Done writing\n";
                } else {
                    std::cerr << "Error opening file for writing." << std::endl;
                }
            } else {
                this->data_vector.push_back(Seq::OutputData{msg->data[0], msg->data[1], msg->data[2], timestamp_ns});
            }
            // RCLCPP_INFO(this->get_logger(), "Received: [%ld, %ld, %ld, %ld]", msg->data[0], msg->data[1], msg->data[2], timestamp_ns);
        };

        subscriber_ = create_subscription<std_msgs::msg::Int64MultiArray>("seq_consume", qos, seq_consume_callback);

    }
} // end of namespace

RCLCPP_COMPONENTS_REGISTER_NODE(Seq::Seq01)
