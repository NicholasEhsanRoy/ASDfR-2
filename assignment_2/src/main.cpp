#include <iostream>
#include <thread>
#include <fstream> 
#include <iomanip> 

#include "q2.hpp"
// #include "q1.hpp"

int main() {
    // Q2 /////////////////////////
    Q2::Q2 q2;
    std::cout << "Waiting for thread to finish..." << std::endl;
    q2.wait();
    std::cout << "Thread has finished! Now safe to access class members." << std::endl;
        std::cout << "Final Answer: " << Q2::Q2::final_answer << std::endl;
    std::ofstream file("../../timestampsq2.csv");
    if (file.is_open()) {
        // Write header to the CSV (optional)
        file << "Timestamp (seconds)\n";

        // Loop through the static timestamps vector and write each timestamp to the file
        for (size_t i = 0; i < Q2::Q2::timestamps.size(); ++i) {
            // Convert timestamp to seconds with 10 decimal places
            double timestamp_in_seconds = Q2::Q2::timestamps[i].tv_sec + 
                                          static_cast<double>(Q2::Q2::timestamps[i].tv_nsec) / 1000000000.0;

            // Write the timestamp as seconds with 10 decimal points
            file << std::fixed << std::setprecision(10) << timestamp_in_seconds << "\n";
        }

        // Close the file
        file.close();
        std::cout << "Timestamps written to 'timestampsq2.csv'." << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
    }
    // Q1 /////////////////////////
    // Q1::Q1 q1;
    // std::cout << "Waiting for thread to finish..." << std::endl;
    // q1.wait();
    // std::cout << "Thread has finished! Now safe to access class members." << std::endl;
    //     std::cout << "Final Answer: " << Q1::Q1::final_answer << std::endl;
    // std::ofstream file("../../timestampsq1.csv");
    // if (file.is_open()) {
    //     // Write header to the CSV (optional)
    //     file << "Timestamp (seconds)\n";

    //     // Loop through the static timestamps vector and write each timestamp to the file
    //     for (size_t i = 0; i < Q1::Q1::timestamps.size(); ++i) {
    //         // Convert timestamp to seconds with 10 decimal places
    //         double timestamp_in_seconds = Q1::Q1::timestamps[i].tv_sec + 
    //                                       static_cast<double>(Q1::Q1::timestamps[i].tv_nsec) / 1000000000.0;

    //         // Write the timestamp as seconds with 10 decimal points
    //         file << std::fixed << std::setprecision(10) << timestamp_in_seconds << "\n";
    //     }

    //     // Close the file
    //     file.close();
    //     std::cout << "Timestamps written to 'timestamps.csv'." << std::endl;
    // } else {
    //     std::cerr << "Error opening file for writing." << std::endl;
    // }

    return 0;
}


//Q2:
// on vm
// 91 seconds under stress
// 63 seconds without stress
// on relbot
// Total time: 75 seconds and 227819745 nanoseconds (no stress)


