#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include "../RepairOrder/RepairOrder.h"

class Review {
private:
    int rating;
    std::string comment;
    RepairOrder* relatedOrder;

public:
    Review(int rating, const std::string& comment, RepairOrder* order);
    
    bool moderateReview();
    void publishReview();
    bool isValidRating() const;
    int getRating() const;
    std::string getComment() const;
};

#endif
