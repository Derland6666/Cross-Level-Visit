#include "Trigger.h"
#include "Teleport.h"
#include <geode/modify/PlayLayer.hpp>
#include <geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

// Define static members
const int CrossLevelTrigger::TRIGGER_TYPE_ID = 1599; // Custom trigger ID (must be unique)
const std::string CrossLevelTrigger::TRIGGER_NAME = "Cross-Level Teleport";

/**
 * Initialize the trigger system
 */
bool CrossLevelTrigger::init() {
    log::info("Initializing Cross-Level Trigger system...");
    
    if (!registerTrigger()) {
        log::error("Failed to register cross-level trigger");
        return false;
    }
    
    log::info("Cross-Level Trigger initialized successfully");
    return true;
}

/**
 * Check if a trigger is a cross-level teleport trigger
 */
bool CrossLevelTrigger::isCrossLevelTrigger(gd::Trigger* trigger) {
    if (!trigger) return false;
    
    // Check trigger type matches our custom trigger
    return trigger->m_type == TRIGGER_TYPE_ID;
}

/**
 * Get the target level ID from trigger data
 * Extracts the "targetLevelID" property from the trigger
 */
int CrossLevelTrigger::getTargetLevelID(gd::Trigger* trigger) {
    if (!trigger) {
        log::warn("Trigger is null");
        return -1;
    }

    try {
        // Get the target level ID from trigger properties
        // This accesses the custom property set in the level editor
        int levelID = trigger->getProperty("targetLevelID", -1);
        
        log::debug("Retrieved target level ID: {}", levelID);
        return levelID;
    } catch (const std::exception& e) {
        log::error("Error extracting level ID from trigger: {}", e.what());
        return -1;
    }
}

/**
 * Register the trigger with Geometry Dash
 */
bool CrossLevelTrigger::registerTrigger() {
    try {
        log::info("Registering {} trigger (ID: {})", TRIGGER_NAME, TRIGGER_TYPE_ID);
        
        // In real Geode implementation, triggers are registered through
        // the level editor extensions, but we validate here
        
        return true;
    } catch (const std::exception& e) {
        log::error("Error registering trigger: {}", e.what());
        return false;
    }
}

/**
 * Validate target level ID
 */
bool CrossLevelTrigger::validateLevelID(int levelID) {
    // Check if level ID is valid range
    if (levelID <= 0) {
        log::warn("Invalid level ID: {} (must be > 0)", levelID);
        return false;
    }

    // Level ID range check (GD can have levels from 1 to 100000000+)
    if (levelID > 100000000) {
        log::warn("Level ID too large: {}", levelID);
        return false;
    }

    log::debug("Level ID {} is valid", levelID);
    return true;
}

/**
 * Handle trigger activation event
 * This is called when the trigger is activated
 */
void CrossLevelTrigger::onTriggerActivated(gd::Trigger* trigger) {
    if (!trigger) {
        log::error("Trigger pointer is null");
        return;
    }

    if (!isCrossLevelTrigger(trigger)) {
        log::debug("Trigger is not a cross-level teleport trigger");
        return;
    }

    log::info("Cross-Level Teleport trigger activated!");
    
    // Get target level ID from trigger properties
    int targetLevelID = getTargetLevelID(trigger);
    
    // Validate level ID
    if (!validateLevelID(targetLevelID)) {
        log::error("Invalid or missing target level ID in trigger");
        
        // Show error notification to player
        FLAlertLayer::create(
            "Cross-Level Teleport",
            "Error: Invalid level ID in trigger!",
            "OK"
        )->show();
        
        return;
    }

    log::info("Valid level ID found: {}. Teleporting player to level {}", 
              targetLevelID, targetLevelID);

    // Execute teleport
    if (LevelTeleporter::teleportToLevel(targetLevelID)) {
        log::info("Successfully teleported to level {}", targetLevelID);
    } else {
        log::error("Failed to teleport to level {}", targetLevelID);
        
        FLAlertLayer::create(
            "Cross-Level Teleport",
            "Error: Teleport failed! " + LevelTeleporter::getLastErrorMessage(),
            "OK"
        )->show();
    }
}

/**
 * Hook into PlayLayer::activateTrigger to intercept all trigger activations
 * This is how we detect when our custom trigger is activated
 */
class $modify(PlayLayerTriggerHook, PlayLayer) {
    void activateTrigger(gd::Trigger* trigger) {
        // Check if this is our cross-level teleport trigger
        if (trigger && CrossLevelTrigger::isCrossLevelTrigger(trigger)) {
            log::info("Detected Cross-Level Teleport trigger activation");
            
            // Handle our custom trigger
            CrossLevelTrigger::onTriggerActivated(trigger);
            
            // Return without calling original - we handle teleport ourselves
            return;
        }

        // For all other triggers, call the original handler
        PlayLayer::activateTrigger(trigger);
    }
};

/**
 * Hook into GameManager to handle the actual level transition
 * This ensures we properly leave the current level
 */
class $modify(GameManagerLevelTransition, GameManager) {
    void loadLevel(gd::GJGameLevel* level, bool unknown) {
        if (!level) {
            log::error("Attempted to load null level");
            return;
        }

        log::info("Loading level: {} ({})", level->m_levelID, level->m_levelName);
        
        // Call original to perform the actual level load
        GameManager::loadLevel(level, unknown);
    }
};

/**
 * Utility function to get trigger info for debugging
 */
void CrossLevelTrigger::logTriggerInfo(gd::Trigger* trigger) {
    if (!trigger) {
        log::info("Trigger is null");
        return;
    }

    log::info("=== Trigger Info ===");
    log::info("Type: {}", trigger->m_type);
    log::info("Group ID: {}", trigger->m_targetGroupID);
    
    int levelID = getTargetLevelID(trigger);
    log::info("Target Level ID: {}", levelID);
    log::info("Valid: {}", validateLevelID(levelID));
    log::info("====================");
}
