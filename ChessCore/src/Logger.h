#pragma once
#include "pch.h"

#define Log Logger::get()
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define RED    "\033[31m"
#define RESET  "\033[0m"

class Logger {
private:
    std::string prefix = "[GLOBAL]";

    Logger() {}

public:
    inline static bool showErrors = true;
    inline static bool showWarns = true;
    inline static bool showInfos = false;
    inline static bool showPrefix = false;

    class TempLogger {
    private:
        const Logger& base;
        std::string tempPrefix;

    public:
        TempLogger(const Logger& logger, const std::string& tp = "")
            : base(logger), tempPrefix(tp.empty() ? " " : " [" + tp + "] ") {
        }

        template<typename... Args>
        void info(const Args&... msg) const {
            if (base.showInfos) {
                std::cout << (showPrefix ? base.prefix : "") << tempPrefix << GREEN << "[INFO] " << RESET;
                ( (std::cout << msg), ... );
                std::cout << std::endl;
            }
        }
        template<typename... Args>
        void warn(const Args&... msg) const {
            if (base.showWarns) {
                std::cout << (showPrefix ? base.prefix : "") << tempPrefix << YELLOW << "[WARN] " << RESET;
                ( (std::cout << msg), ... );
                std::cout << std::endl;
            }
        }
        template<typename... Args>
        void error(const Args&... msg) const {
            if (base.showErrors) {
                std::cout << (showPrefix ? base.prefix : "") << tempPrefix << RED << "[ERROR] " << RESET;
                ( (std::cout << msg), ... );
                std::cout << std::endl;
            }
        }
    };
   
    static Logger& get() {
        static Logger instance;
        return instance;
    }

    void changePrefix(const std::string& p) {
        prefix = "[" + p + "]";
    }
    template<typename... Args>
    void info(const Args... msg) const {
        TempLogger(*this).info(msg...);
    }
    template<typename... Args>
    void warn(const Args... msg) const {
        TempLogger(*this).warn(msg...);
    }
    template<typename... Args>
    void error(const Args... msg) const {
        TempLogger(*this).error(msg...);
    }

    TempLogger tprefix(const std::string& tp) const {
        return TempLogger(*this, tp);
    }
};