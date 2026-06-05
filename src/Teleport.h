#pragma once

#include <geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

/**
 * @class LevelTeleporter
 * @brief Handles teleportation between levels based on level ID
 * 
 * This class manages the logic for teleporting the player from one level
 * to another, including validation, error handling, and state management.
 */
class LevelTeleporter {
public:
    /**
     * @brief Initialize teleporter system
     * @return true if initialization successful
     */
    static bool init();

    /**
     * @brief Teleport player to a specific level by ID
     * @param levelID The ID of the target level
     * @return true if teleport successful, false otherwise
     */
    static bool teleportToLevel(int levelID);

    /**
     * @brief Validate if a level ID is valid and accessible
     * @param levelID The level ID to validate
     * @return true if level exists and is accessible
     */
    static bool isValidLevelID(int levelID);

    /**
     * @brief Get the name of a level by its ID
     * @param levelID The level ID
     * @return The level name, or empty string if not found
     */
    static std::string getLevelName(int levelID);

    /**
     * @brief Check if player has access to a level
     * @param levelID The level ID to check
     * @return true if level is accessible
     */
    static bool canAccessLevel(int levelID);

    /**
     * @brief Handle teleport errors
     * @param levelID The target level ID
     * @param errorCode The error code
     */
    static void handleTeleportError(int levelID, int errorCode);

    /**
     * @brief Get the last teleport error message
     * @return Error message string
     */
    static std::string getLastErrorMessage();

private:
    static std::string m_lastErrorMessage;
    
    // Error codes
    enum class ErrorCode : int {
        SUCCESS = 0,
        INVALID_LEVEL_ID = 1,
        LEVEL_NOT_FOUND = 2,
        ACCESS_DENIED = 3,
        TELEPORT_FAILED = 4,
        UNKNOWN_ERROR = 5
    };

    /**
     * @brief Internal teleport implementation
     * @param levelID The target level ID
     * @return true if successful
     */
    static bool performTeleport(int levelID);

    /**
     * @brief Get error message from error code
     * @param errorCode The error code
     * @return Error message string
     */
    static std::string getErrorMessage(ErrorCode errorCode);

    // Private constructor - static class only
    LevelTeleporter() = delete;
};
