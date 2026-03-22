//
// Created by yasalzzt on 2025/12/17.
//
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>

Logger::EndLog Logger::endl;
static thread_local std::string t_curMsg;
static thread_local level t_curLev = DEBUG;

Logger& Logger::getInstance() {
    static Logger log;
    return log;
}

Logger::Logger() {
    logFile_.open("logFile.log",std::ios::app);
    if (!logFile_.is_open()) {
        throw std::runtime_error("Logger could not open logFile.txt");
    }
}

void Logger::clear()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (logFile_.is_open()) {
        logFile_.close();
    }

    logFile_.open("logFile.log", std::ios::out | std::ios::trunc);
}

Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

Logger &Logger::operator <<(level lev){
    t_curLev = lev;
    return *this;
}

Logger &Logger::operator<<(const std::string& msg){
    t_curMsg += msg;
    return *this;
}

Logger& Logger::operator<<(const EndLog&) {
    log(t_curMsg, t_curLev);
    t_curMsg.clear();
    t_curLev = DEBUG;
    return *this;
}

void Logger::log(const std::string &msg, level lev)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::string level_str;
    switch (lev) {
    case DEBUG:
        level_str = "[DEBUG] ";
        break;
    case INFO:
        level_str = "[INFO] ";
        break;
    case WARNING:
        level_str = "[WARNING] ";
        break;
    case ERROR:
        level_str = "[ERROR] ";
        break;
    }
    if (logFile_.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S] ", std::localtime(&time));

        logFile_ << level_str << buffer << msg << std::endl;
    }
}

bool Logger::deleteLogFile() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logFile_.is_open()) {
        logFile_.close();
    }

    bool result = std::filesystem::remove("logFile.log");

    logFile_.open("logFile.log", std::ios::app);
    return result;
}

