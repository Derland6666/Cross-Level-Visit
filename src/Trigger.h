#pragma once

#include <geode/Geode.hpp>

using namespace geode::prelude;

/**
 * @class CrossLevelTrigger
 * @brief Handles the Cross-level teleport trigger
 */
class CrossLevelTrigger {
public:
    static void onEffectGameObject(EffectGameObject* obj);
    
    static const int TRIGGER_OBJECT_ID;
    
private:
    CrossLevelTrigger() = delete;
};
