#ifndef PAINTER_H
#define PAINTER_H

#include "../Master/Master.h"
#include <vector>
#include "../Tool/Tool.h"

enum class PaintType { OIL, WATER, ACRYLIC, EPOXY };

class Sprayer;

class Painter : public Master {
private:
    std::vector<PaintType> usedPaintTypes;
    std::vector<Sprayer*> sprayers;
    double paintConsumptionRate;

public:
    Painter(int id, const std::string& name, double salary, double consumptionRate);
    ~Painter();
    
    void performRepairWork() override;
    void paintSurface();
    void mixColors();
    void calculatePaintRequired(double area);
};

#endif
