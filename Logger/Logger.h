#ifndef LOGGER_H
#define LOGGER_H
/*
 *  包含头文件:
 *  #include "Logger.h"
 *  1. 使用宏方式（推荐）:
 *  LOG_DEBUG("调试信息");
 *  LOG_INFO("用户登录成功");
 *  LOG_WARN("密码格式不正确");
 *  LOG_ERROR("数据库连接失败");
 *
 *  2. 使用流式操作符:
 *  Logger::getInstance() << DEBUG << "xxxxxx" << Logger::endl;
 *  Logger::getInstance() << INFO << "xxxxxx" << Logger::endl;
 *
 *  3. 使用直接log方法:
 *  Logger::getInstance().log("直接记录错误信息", ERROR);
 *  Logger::getInstance().log("默认使用DEBUG级别");
 *
 *  4. 日志文件管理:
 *  Logger::getInstance().clear();           // 清空日志文件内容
 *  Logger::getInstance().deleteLogFile();   // 删除日志文件
 *
 *  日志级别:
 *  DEBUG   - 调试信息，开发阶段使用
 *  INFO    - 一般信息，正常流程记录
 *  WARNING - 警告信息，不影响运行但需要注意
 *  ERROR   - 错误信息，需要处理的异常情况
 *
 *  日志文件:
 *  默认生成在当前目录下的 logFile.log 文件中
 *  格式: [级别] [时间戳] 日志内容
 *  示例: [INFO] [2024-01-20 15:30:45] 用户登录成功
 */
#define LOG Logger::getInstance()
#define LOG_DEBUG(msg) Logger::getInstance() << DEBUG  << msg << Logger::endl
#define LOG_INFO(msg)  Logger::getInstance() << INFO << msg << Logger::endl
#define LOG_WARN(msg)  Logger::getInstance() << WARNING << msg << Logger::endl
#define LOG_ERROR(msg) Logger::getInstance() << ERROR << msg << Logger::endl

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <filesystem>

enum level {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static Logger& getInstance();
    ~Logger();
    class EndLog {};

    Logger(const Logger& ) = delete;
    Logger& operator=(const Logger& ) = delete;

    Logger& operator<<(level lev);
    Logger& operator<<(const std::string& msg);
    Logger& operator<<(const EndLog&);

    void log(const std::string& msg,level lev = DEBUG);
    friend Logger operator<<(level levconst ,std::string& msg);

    void clear();
    bool deleteLogFile();

    static EndLog endl;

private:
    Logger();
    std::ofstream logFile_;
    std::mutex mutex_;
};



#endif //LOGGER_H
