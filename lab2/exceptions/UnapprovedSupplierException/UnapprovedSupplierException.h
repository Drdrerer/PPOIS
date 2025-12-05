#ifndef UNAPPROVEDSUPPLIEREXCEPTION_H
#define UNAPPROVEDSUPPLIEREXCEPTION_H

#include <stdexcept>
#include <string>

class UnapprovedSupplierException : public std::runtime_error {
public:
    UnapprovedSupplierException() : std::runtime_error("Supplier not approved") {}
};

#endif
