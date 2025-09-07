#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <utility>
namespace cpu{

namespace fs = std::filesystem;
fs::path find_cpu_under_hwmon(int cpu_brand_id);
std::array<std::string, 4> parsing_proc_cpuinfo();
class CPU_Temperature_Monitor;


class CPUInfo {

    CPUInfo();               

    std::string vender_, name_;
    int corenum_ = 0;    
    fs::path hwmon_dir_; 

    public:
        static const CPUInfo& instance();
        
        static const fs::path cache;
        
        const std::string& vendor() const { return vender_; }
        const std::string& name()   const { return name_; }
        int corenum() const { return corenum_; }
        
        const fs::path& hwmon_dir() const {return hwmon_dir_;} 
        fs::path& hwmon_dir() {return hwmon_dir_;} 
};


class CPU_Temperature_Monitor{
    
    public:
        const CPUInfo& cpuinfo = CPUInfo::instance(); 

    protected:
        std::string temperature_strbuf;
        fs::path cpu_temperature_file;
        std::unique_ptr<std::ifstream> temperature_istream;

    public:
        CPU_Temperature_Monitor();
        inline const fs::path &temperature_file(){ return cpu_temperature_file;}
        inline const std::string &temp() const { return temperature_strbuf; } 
        void refresh_temperature_from_file();  
};

};