#pragma once

#include <geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

/**
 * @class CrossLevelTrigger
 * @brief Handles the Cross-level teleport trigger for Geometry Dash
 * 
 * This class manages the creation, registration, and activation of
 * custom triggers that allow teleportation between levels.
 */
class CrossLevelTrigger {
public:
    /**
     * @brief Initialize the trigger system
     * @return true if initialization successful, false otherwise
     */
    static bool init();

    /**
     * @brief Check if a trigger is a cross-level teleport trigger
     * @param trigger Pointer to the trigger object
     * @return true if it's a cross-level teleport trigger
     */
    static bool isCrossLevelTrigger(gd::Trigger* trigger);

    /**
     * @brief Get the target level ID from trigger data
     * @param trigger Pointer to the trigger object
     * @return The target level ID, -1 if invalid
     */
    static int getTargetLevelID(gd::Trigger* trigger);

    /**
     * @brief Validate target level ID
     * @param levelID The level ID to validate
     * @return true if valid, false otherwise
     */
    static bool validateLevelID(int levelID);

    /**
     * @brief Register the trigger with Geometry Dash
     * @return true if registration successful
     */
    static bool registerTrigger();

    /**
     * @brief Handle trigger activation event
     * @param trigger Pointer to the activated trigger
     */
    static void onTriggerActivated(gd::Trigger* trigger);

    /**
     * @brief Utility function to log trigger information for debugging
     * @param trigger Pointer to the trigger object
     */
    static void logTriggerInfo(gd::Trigger* trigger);

public:
    static const int TRIGGER_TYPE_ID;
    static const std::string TRIGGER_NAME;

private:
    // Private constructor - static class only
    CrossLevelTrigger() = delete;
};
