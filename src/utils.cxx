#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <array>
#include <utility>
#include "utils.hpp"

namespace cpu{

fs::path find_cpu_under_hwmon(int cpu_brand_id){
    /**
     * brand_id: 0: AMD 1: Intel 
    */
    std::string strbuf;
    const std::string cpu_device_name = (cpu_brand_id == 1)? "coretemp": "k10temp"; 
    const fs::path hwmon("/sys/class/hwmon/");

    for (const auto &p: fs::directory_iterator(hwmon)){
        if (p.is_directory()){
            std::ifstream name(p.path()/"name");
            std::getline(name, strbuf);
            name.close();
            if (strbuf == cpu_device_name){
                return p.path();
            }
        }
    }

    return fs::path{};
}

std::array<std::string, 4> parsing_proc_cpuinfo(){
    
    std::ifstream sys_cpuinfo_log("/proc/cpuinfo");
    std::array<std::string, 4> info;
    std::map<std::string, int> key_to_index={
        {"vendor_id", 0}, 
        {"model name", 1}, 
        {"processor", 2} 
    };
    
    std::string strbuf, item;

    while (std::getline(sys_cpuinfo_log, strbuf)){
        
        std::stringstream ss(strbuf);
        /*
            cpuinfo file structure:
            key: value
            ...
        */

        //read key
        std::getline(ss, item, ':');
        item.erase(item.find_last_not_of("  \t\n\r\f\v") + 1);
        
        auto it = key_to_index.find(item);
        if (it == key_to_index.end()){
            //not a wanted key
            continue;
        }

        //read value and strip it
        std::getline(ss, item);
        size_t start =  item.find_first_not_of("  \t\n\r\f\v");
        item = ( start == std::string::npos) ? "" : item.substr(start);
        info[it->second] = item;
        
    }

    int brand_id = -1;
    if (info[0] == "AuthenticAMD"){
        brand_id = 0;
        info[0] = "AMD";
    }
    else if (info[0] == "GenuineIntel"){
        brand_id = 1;
        info[0] = "Intel";
    }
    else{
        throw std::runtime_error(std::string("Unknow CPU brand: ") + info[0]);
    }
    
    info[2] = std::to_string(std::stoi(info[2]) + 1);
    info[3] = find_cpu_under_hwmon(brand_id).string();
    
    return info;
}

CPUInfo::CPUInfo(){
    
    std::array<std::string, 4> parsing_result;
    parsing_result = parsing_proc_cpuinfo();
    vender_ = parsing_result[0];
    name_ = parsing_result[1];
    corenum_ = std::stoi(parsing_result[2]);
    hwmon_dir_ = fs::path(parsing_result[3]);

}

const CPUInfo& CPUInfo::instance() {
    static CPUInfo obj;           // thread-safe since C++11
    return obj;
}

CPU_Temperature_Monitor::CPU_Temperature_Monitor(){  
    cpu_temperature_file = cpuinfo.hwmon_dir()/"temp1_input";
    temperature_istream = std::make_unique<std::ifstream>(
        cpu_temperature_file
    ); 
}

void CPU_Temperature_Monitor::refresh_temperature_from_file() {
    
    temperature_istream->clear();      // clear eof flags
    temperature_istream->seekg(0);     // rewind
    temperature_strbuf.assign(
        std::istreambuf_iterator<char>(*temperature_istream),
        std::istreambuf_iterator<char>()
    );
    temperature_strbuf.insert(2, ".");
    temperature_strbuf.pop_back();
}

}