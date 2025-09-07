# Qt CPU Temperature Monitor

Inspired by the Linux `sensors` utility, this is a lightweight desktop application to monitor CPU temperature, built with **C++** and **Qt**, tested on **KUbuntu**.

## Features
- Real-time CPU temperature monitoring
- Simple Qt-based UI
- Reads system temperature from `/sys/class/hwmon/`

- <img src="pics/app.gif" width=30%>



## Build
### Requirements
- g++ (C++23 or later)
- Linux system with /sys/class/hwmon/ available
- CMake
- QT6

### Building Command
- Executable GUI program  
    - Build:
        - ```
            make build
            make app
            ``` 
    - execution:
        - ```
            ./cputemp_monitor
            ```
    - clean:
        - ```
            make clean_build
            ``` 
- System application and install
    - Build and install:
        - ```
            make build_exe
            make app exe
            ```
    - Uninstall 
        - ```
            make clean_app
            ```

## Testing core the component
To test the function about finding and reading CPU information and temperature
```
make 
./test
```
