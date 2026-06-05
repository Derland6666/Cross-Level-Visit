#include "Trigger.h"
#include "Teleport.h"
#include <geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Define static members
const int CrossLevelTrigger::TRIGGER_TYPE_ID = 9999;
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
bool CrossLevelTrigger::isCrossLevelTrigger(int triggerID) {
    return triggerID == TRIGGER_TYPE_ID;
}

/**
 * Get the target level ID from trigger data
 */
int CrossLevelTrigger::getTargetLevelID(int triggerID) {
    log::debug("Getting target level ID for trigger: {}", triggerID);
    
    // TODO: Extract from trigger properties in Geometry Dash
    return 0;
}

/**
 * Register the trigger with Geometry Dash
 */
bool CrossLevelTrigger::registerTrigger() {
    try {
        log::info("Registering {} trigger", TRIGGER_NAME);
        return true;
    } catch (const std::exception& e) {
        log::error("Error registering trigger: {}", e.what());
        return false;
    }
}

/**
 * Handle trigger activation event
 */
void CrossLevelTrigger::onTriggerActivated(int triggerID, int levelID) {
    if (!isCrossLevelTrigger(triggerID)) {
        log::debug("Trigger {} is not a cross-level trigger", triggerID);
        return;
    }

    log::info("Cross-Level trigger activated! Target level: {}", levelID);
    
    if (levelID <= 0) {
        log::warn("Invalid level ID: {}", levelID);
        return;
    }

    if (LevelTeleporter::teleportToLevel(levelID)) {
        log::info("Successfully teleported to level {}", levelID);
    } else {
        log::error("Failed to teleport to level {}", levelID);
    }
}

/**
 * Hook into PlayLayer to detect trigger activation
 */
class $modify(PlayLayerTriggerHook, PlayLayer) {
    void onTrigger(gd::Trigger* trigger) {
        if (trigger) {
            int triggerType = trigger->m_type;
            
            if (triggerType == CrossLevelTrigger::TRIGGER_TYPE_ID) {
                int targetLevelID = CrossLevelTrigger::getTargetLevelID(triggerType);
                CrossLevelTrigger::onTriggerActivated(triggerType, targetLevelID);
                return;
            }
        }
        
        PlayLayer::onTrigger(trigger);
    }
};
