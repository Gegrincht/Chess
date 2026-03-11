#pragma once
#include <iostream>
#include <string>

#define Log Logger::get()

#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define RED    "\033[31m"
#define RESET  "\033[0m"

class Logger {
private:
    std::string prefix = "GLOBAL";

    Logger(); // Konstruktor privat, Singleton Pattern

public:
    static bool active;

    // ---------------- TempLogger ----------------
    class TempLogger {
    private:
        const Logger& base;
        std::string tempPrefix;

    public:
        TempLogger(const Logger& logger, const std::string& tp = "");

        void info(const std::string& msg) const;
        void warn(const std::string& msg) const;
        void error(const std::string& msg) const;
    };

    // ---------------- Singleton Zugriff ----------------
    static Logger& get();

    // ---------------- Logger Methoden ----------------
    void changePrefix(const std::string& p);
    void info(const std::string& msg) const;
    void warn(const std::string& msg) const;
    void error(const std::string& msg) const;

    TempLogger tprefix(const std::string& tp) const;
};
