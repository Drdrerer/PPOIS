#include <iostream>
#include "Tool.h"

Tool::Tool(const std::string& name, const std::string& type, bool calibration)
    : toolName(name), toolType(type), requiresCalibration(calibration) {}

void Tool::calibrate() {
    std::cout << "Calibrating tool: " << toolName << std::endl;
}

bool Tool::checkCalibrationStatus() const {
    return !requiresCalibration;
}

bool Tool::needsMaintenance() const {
    return false; 
}

std::string Tool::getToolName() const {
    return toolName;
}

std::string Tool::getToolType() const {
    return toolType;
}
