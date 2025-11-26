#pragma once

/// @file bEngineUtilities.h
/// @brief a collection of utility functions and macros which may be useful to the user as well as internally

#include <exception> // for the bEngineException base class (std::exception)
#include <format>    // for formatting assertion messages and info/warning/error messages
#include <string>    // for strings for use in exceptions

#ifdef DEBUG
#    include <iostream> // we only print to the console in debug mode, so only need to include it there!

#    define ANSI_RESET_CODE  "\033[0m"  // to reset the style
#    define ANSI_GREEN_CODE  "\033[32m" // to switch to green text color
#    define ANSI_YELLOW_CODE "\033[33m" // to switch to yellow text color
#    define ANSI_RED_CODE    "\033[31m" // to switch to red text color

/// @brief info message decorator, outputs an info message to the console AND outputs an info message to the log
/// @param msg the message to be output/logged
#    define INFO_MSG(msg) std::cout << std::format("{}[INFO]{} - {}\n", ANSI_GREEN_CODE, ANSI_RESET_CODE, msg)

/// @brief warning message decorator, outputs a warning message to the console AND outputs a warning message to the log
/// @param msg the message to be output/logged
#    define WARNING_MSG(msg) std::cout << std::format("{}[WARNING]{} - {}\n", ANSI_YELLOW_CODE, ANSI_RESET_CODE, msg)

/// @brief error message decorator, outputs an error message to the console AND outputs an error message to the log
/// @param msg the message to be output/logged
#    define ERROR_MSG(msg) std::cout << std::format("{}[ERROR]{} - {}\n", ANSI_RED_CODE, ANSI_RESET_CODE, msg)
#else
/// @brief info message decorator, outputs an info message to the log
/// @param msg the message to be logged
#    define INFO_MSG(msg)
/// @brief warning message decorator, outputs a warning message to the log
/// @param msg the message to be logged
#    define WARNING_MSG(msg)
/// @brief error message decorator, outputs an error message to the log=
/// @param msg the message to be logged
#    define ERROR_MSG(msg)
#endif // DEBUG

/// @brief an assertion that works in debug AND release mode; throws a bEngineException with the reason for failure
/// @param cond the condition to assert is true
/// @param msg the message to use in the assertion failure message, accessible in the thrown exception (or printed to
/// the console in debug mode)
#define bENGINE_ASSERT(cond, msg)                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(cond))                                                                                                   \
        {                                                                                                              \
            const auto formattedMsg{                                                                                   \
                std::format("Assertion Failed!\n\tReason: {}\n\tFile: {}\n\tLine: {}", msg, __FILE__, __LINE__)};      \
            ERROR_MSG(formattedMsg);                                                                                   \
            throw bEngine::bEngineException{msg};                                                                      \
        }                                                                                                              \
    } while (0)

namespace bEngine
{
    /// @brief struct representing a bEngineException (i.e. an unrecoverable error)
    ///
    /// these should be used sparingly, and practically never by the user. They may be removed from forward facing API,
    /// but that might necessitate making a "privateUtilities" header which seems like an even worse idea than leaving a
    /// very basic exception class that offers no interactivity with the application public!
    struct bEngineException : public std::exception
    {
        inline static const std::string s_defaultMsg{"An unknown exception has occured."};
        /// @brief the message associateds with the exception, used for logging/printing
        const std::string m_msg{s_defaultMsg};

        /// @brief default ctor is acceptable
        bEngineException() = default;

        /// @brief ctor which takes a message to set as the exception's message
        /// @param msg the message to set as the exception's message
        bEngineException(std::string &&msg)
            : std::exception{},
              m_msg{msg.empty() ? std::string{s_defaultMsg} : msg} { };

        /// @brief gets the exception's message as a c_str
        /// @return the exception's message as a c_str
        virtual char const *what() const override final { return m_msg.c_str(); };
    };

    /// @brief houses methods related to utilities associated with the library, including meta-information about the
    /// library itself
    namespace Utils
    {
        /// @brief allows the user to check against a certain version of the bEngine library for use in their program
        ///
        /// while this method will not actually "crash" or "fail" if the correct version is not met, it is useful as a
        /// means of reporting whether app initialization should even attempt to proceed.
        /// @param major the desired major version which must match exactly (1.X.Y is incompatible with 2.Q.R)
        /// @param minor the desired minor version which must be the minimum acceptable if not exactly matching
        /// @param patch the desired patch number which must be the minimum acceptable if not exactly matching
        /// @param allowNewer true if newer versions (of the same major version) are acceptable, false if the version
        /// must match exactly
        /// @return true if the compiled version of bEngine satisfies the criteria, false if not
        const bool check_version(
            const unsigned int major,
            const unsigned int minor      = 0,
            const unsigned int patch      = 0,
            const bool         allowNewer = true);

        /// @brief gets the string associated with the bEngine version which was compiled
        ///
        /// the version string is in the format described as follows:
        ///     "X.Y.Z(+)"
        /// where:
        /// - X is the major version
        /// - Y is the minor version
        /// - Z is the patch number
        /// - + (if present) indicates a "dirty" local repository
        /// @return the version string formatted according to semantic versioning (plus a "dirty" tag)
        const char *const get_version_string();

        /// @brief gets the major version number associated with the compiled bEngine version
        /// @return the major version number associated with the compiled bEngine version
        const unsigned int get_major_version();

        /// @brief gets the minor version number associated with the compiled bEngine version
        /// @return the minor version number associated with the compiled bEngine version
        const unsigned int get_minor_version();

        /// @brief gets the patch number associated with the compiled bEngine version
        /// @return the patch number associated with the compiled bEngine version
        const unsigned int get_patch_number();

        /// @brief gets the commit hash associated with the compiled bEngine version
        /// @return the commit hash associated with the compiled bEngine version
        const char *const get_commit_hash();
    } // namespace Utils
} // namespace bEngine