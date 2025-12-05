#ifndef TOOL_H
#define TOOL_H

#include <string>

class Tool {
private:
    std::string toolName;
    std::string toolType;
    bool requiresCalibration;

public:
    Tool(const std::string& name, const std::string& type, bool calibration);
    
    void calibrate();
    bool checkCalibrationStatus() const;
    bool needsMaintenance() const;
    std::string getToolName() const;
    std::string getToolType() const;
};

#endif
