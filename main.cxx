#include <iostream>
#include <fstream>
#include <filesystem>

#include <array>
#include <utility>
#include <map>

#include <QTimer>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>
#include <QIcon>
#include <QFile>     // for QFile::exists
#include <QtGlobal>

#include "include/utils.hpp"


namespace fs = std::filesystem;
inline const fs::path local_cpuinfo_file = fs::path(".cache")/"cpuinfo.txt";


QLabel* create_cpu_temp_label(){
    QLabel *label  = new QLabel("—");
    label->setAlignment(Qt::AlignCenter);
    //label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont font = label->font();
    font.setPointSize(24);
    label->setFont(font);
    label->setStyleSheet("border: 2px solid blue;");
    return label;
}

QLabel* create_time_label(){
    QLabel *label  = new QLabel("—");
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QFont font = label->font();
    font.setPointSize(14);   
    label->setFont(font);
    label->setText(
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
    );
    return label;
}

int main(int argc, char *argv[]) {
    
    cpu::CPU_Temperature_Monitor monitor = cpu::CPU_Temperature_Monitor();

    // app
    QApplication app(argc, argv);
    app.setApplicationName("cputemp_monitor");      
    app.setDesktopFileName("cputemp");
    app.setWindowIcon(QIcon(":/pics/icon.png"));

    // Window  UI
    QWidget win;
    win.setWindowTitle("CPU Temp");
    win.setWindowIcon(QIcon(":/pics/icon.png"));
    QVBoxLayout *layout = new QVBoxLayout(&win);

    QLabel *temp_label = create_cpu_temp_label();
    auto set_cpu_temp_label = [&monitor, temp_label](){
        monitor.refresh_temperature_from_file();
        temp_label->setText(
            QString::fromStdString(monitor.temp() + " °C")
        );
    };
    
    QLabel *date_label = create_time_label();
    auto set_date_label = [date_label](){
        date_label->setText(
            QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
        );
    };

    set_cpu_temp_label();
    set_date_label();

    layout->addWidget(date_label);
    layout->addWidget(temp_label);
    
    QTimer *cpu_read_timer = new QTimer(&win);
    QObject::connect(cpu_read_timer, &QTimer::timeout, set_cpu_temp_label);
    cpu_read_timer->start(500); // 500 ms

    QTimer *date_timer = new QTimer(&win);
    QObject::connect(date_timer, &QTimer::timeout, set_date_label);
    date_timer->start(1000); //1 sec

    win.show();
    return app.exec();
}
