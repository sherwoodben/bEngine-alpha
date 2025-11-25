#pragma once

/// @file bEngineUtilities.h
/// @brief a collection of utility functions and macros which may be useful to the user as well as internally

#pragma region UTILITY_MACROS

#include <format>
#include <stdexcept>

#ifdef DEBUG
#    include <iostream>

#    define ANSI_RESET_CODE  "\033[0m"
#    define ANSI_GREEN_CODE  "\033[32m"
#    define ANSI_YELLOW_CODE "\033[33m"
#    define ANSI_RED_CODE    "\033[31m"

#    define INFO_MSG(msg)    std::cout << std::format("{}[INFO]{} - {}\n", ANSI_GREEN_CODE, ANSI_RESET_CODE, msg)
#    define WARNING_MSG(msg) std::cout << std::format("{}[WARNING]{} - {}\n", ANSI_YELLOW_CODE, ANSI_RESET_CODE, msg)
#    define ERROR_MSG(msg)   std::cout << std::format("{}[ERROR]{} - {}\n", ANSI_RED_CODE, ANSI_RESET_CODE, msg)
#else
#    define INFO_MSG(...)
#    define WARNING_MSG(...)
#    define ERROR_MSG(...)
#endif // DEBUG

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

#pragma endregion UTILITY_MACROS

namespace bEngine
{
    /// @brief struct representing a bEngineException (i.e. an unrecoverable error)
    struct bEngineException : public std::exception
    {
        const std::string m_msg{"An unknown exception has occured."};

        bEngineException() = default;

        bEngineException(std::string &&msg)
            : std::exception{},
              m_msg{msg.empty() ? "An unknown exception has occured." : msg} { };

        const char *const what() { return m_msg.c_str(); };
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
