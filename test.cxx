#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>
#include "utils.hpp"

namespace fs = std::filesystem;
inline const fs::path local_cpuinfo_file = fs::path("cpuinfo");

int main(){
    cpu::CPU_Temperature_Monitor monitor = cpu::CPU_Temperature_Monitor();
    std::cout << monitor.cpuinfo.vendor() << " | " 
    << monitor.cpuinfo.name() << " | " << monitor.cpuinfo.corenum() << "\n"
    << monitor.temperature_file() << '\n';
    for (;;){
        monitor.refresh_temperature_from_file();
        std::cout << "\033[2J\033[H";
        std::cout << monitor.temp() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}