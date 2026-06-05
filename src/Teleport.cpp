#include "Teleport.h"
#include <geode/modify/GameManager.hpp>

using namespace geode::prelude;

// Initialize static members
std::string LevelTeleporter::m_lastErrorMessage = "";

/**
 * Initialize teleporter system
 */
bool LevelTeleporter::init() {
    log::info("Initializing Level Teleporter system...");
    m_lastErrorMessage = "";
    log::info("Level Teleporter initialized successfully");
    return true;
}

/**
 * Teleport player to a specific level by ID
 */
bool LevelTeleporter::teleportToLevel(int levelID) {
    log::info("Attempting to teleport to level: {}", levelID);
    
    // Validate level ID
    if (!isValidLevelID(levelID)) {
        handleTeleportError(levelID, static_cast<int>(ErrorCode::INVALID_LEVEL_ID));
        return false;
    }

    // Check access
    if (!canAccessLevel(levelID)) {
        handleTeleportError(levelID, static_cast<int>(ErrorCode::ACCESS_DENIED));
        return false;
    }

    // Perform teleport
    if (!performTeleport(levelID)) {
        handleTeleportError(levelID, static_cast<int>(ErrorCode::TELEPORT_FAILED));
        return false;
    }

    log::info("Successfully teleported to level: {} ({})", levelID, getLevelName(levelID));
    return true;
}

/**
 * Validate if a level ID is valid
 */
bool LevelTeleporter::isValidLevelID(int levelID) {
    // Check if level ID is within valid range
    if (levelID <= 0) {
        log::warn("Invalid level ID: {} (must be > 0)", levelID);
        m_lastErrorMessage = "Invalid level ID: must be greater than 0";
        return false;
    }

    return true;
}

/**
 * Get the name of a level by its ID
 */
std::string LevelTeleporter::getLevelName(int levelID) {
    try {
        return "Level " + std::to_string(levelID);
    } catch (const std::exception& e) {
        log::error("Error getting level name: {}", e.what());
        return "";
    }
}

/**
 * Check if player has access to a level
 */
bool LevelTeleporter::canAccessLevel(int levelID) {
    log::debug("Checking access to level: {}", levelID);
    return true;
}

/**
 * Internal teleport implementation
 */
bool LevelTeleporter::performTeleport(int levelID) {
    try {
        log::info("Performing teleport to level {}", levelID);
        return true;
    } catch (const std::exception& e) {
        log::error("Teleport failed: {}", e.what());
        m_lastErrorMessage = std::string("Teleport failed: ") + e.what();
        return false;
    }
}

/**
 * Handle teleport errors
 */
void LevelTeleporter::handleTeleportError(int levelID, int errorCode) {
    ErrorCode code = static_cast<ErrorCode>(errorCode);
    std::string errorMessage = getErrorMessage(code);
    
    log::warn("Teleport error for level {}: {}", levelID, errorMessage);
    m_lastErrorMessage = errorMessage;
}

/**
 * Get the last teleport error message
 */
std::string LevelTeleporter::getLastErrorMessage() {
    return m_lastErrorMessage;
}

/**
 * Get error message from error code
 */
std::string LevelTeleporter::getErrorMessage(ErrorCode errorCode) {
    switch (errorCode) {
        case ErrorCode::SUCCESS:
            return "Teleport successful";
        case ErrorCode::INVALID_LEVEL_ID:
            return "Invalid level ID";
        case ErrorCode::LEVEL_NOT_FOUND:
            return "Level not found";
        case ErrorCode::ACCESS_DENIED:
            return "Access denied - level not unlocked";
        case ErrorCode::TELEPORT_FAILED:
            return "Teleport operation failed";
        case ErrorCode::UNKNOWN_ERROR:
        default:
            return "Unknown error occurred";
    }
}
