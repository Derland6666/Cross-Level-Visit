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
     * @param triggerID The trigger ID to check
     * @return true if it's a cross-level teleport trigger
     */
    static bool isCrossLevelTrigger(int triggerID);

    /**
     * @brief Get the target level ID from trigger data
     * @param triggerID The trigger ID
     * @return The target level ID, -1 if invalid
     */
    static int getTargetLevelID(int triggerID);

    /**
     * @brief Register the trigger with Geometry Dash
     * @return true if registration successful
     */
    static bool registerTrigger();

    /**
     * @brief Handle trigger activation event
     * @param triggerID The ID of the activated trigger
     * @param levelID The target level ID
     */
    static void onTriggerActivated(int triggerID, int levelID);

private:
    static const int TRIGGER_TYPE_ID;
    static const std::string TRIGGER_NAME;
    
    // Private constructor - static class only
    CrossLevelTrigger() = delete;
};
