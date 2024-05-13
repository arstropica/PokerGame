/**
 * @file utils/Logger.h
 * @brief Logger class definition.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>

/**
 * @class Logger
 * @brief Provides logging functionality
 */
class Logger
{
 public:
   /**
    * @brief Retrieves Logger instance.
    * @return Shared pointer to Logger instance.
    */
   static std::shared_ptr<spdlog::logger> &getInstance()
   {
      static std::shared_ptr<spdlog::logger> logger =
          spdlog::stdout_color_mt("console");
      return logger;
   }

   /**
    * @brief Sets the logging level.
    * @param level The logging level to set.
    */
   static void set_level(spdlog::level::level_enum level)
   {
      getInstance()->set_level(level);
   }

   /**
    * @brief Logs an error message.
    * @param message The message to log.
    */
   static void error(std::string message)
   {
      getInstance()->error(message);
   }

   /**
    * @brief Logs a warning message.
    * @param message The message to log.
    */
   static void warn(std::string message)
   {
      getInstance()->warn(message);
   }

   /**
    * @brief Logs an info message.
    * @param message The message to log.
    */
   static void info(std::string message)
   {
      getInstance()->info(message);
   }

   /**
    * @brief Logs a debug message.
    * @param message The message to log.
    */
   static void debug(std::string message)
   {
      getInstance()->debug(message);
   }

   /**
    * @brief Logs a trace message.
    * @param message The message to log.
    */
   static void trace(std::string message)
   {
      getInstance()->trace(message);
   }

   /**
    * @brief Outputs a message directly to the console.
    * @param message The message to output.
    */
   static void console(std::string message)
   {
      std::cout << message << std::endl;
   }

   /**
    * @brief Outputs a message directly to the console.
    * @param message The message to output.
    * @param newline Whether to append a newline.
    */
   static void console(std::string message, bool newline)
   {
      if (newline) {
         std::cout << message << std::endl;
      } else {
         std::cout << message;
      }
   }

 private:
   /**
    * @brief Singleton Constructor.
    */
   Logger();
};

#endif // LOGGER_H