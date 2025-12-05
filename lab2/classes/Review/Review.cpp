#include <iostream>
#include "Review.h"

Review::Review(int rating, const std::string& comment, RepairOrder* order)
    : rating(rating), comment(comment), relatedOrder(order) {}

bool Review::moderateReview() {
    return rating >= 1 && rating <= 5 && comment.length() < 1000;
}

void Review::publishReview() {
    std::cout << "Published review with rating: " << rating << std::endl;
}

bool Review::isValidRating() const {
    return rating >= 1 && rating <= 5;
}

int Review::getRating() const {
    return rating;
}

std::string Review::getComment() const {
    return comment;
}
