#ifndef CLIENTBLACKLISTEDEXCEPTION_H
#define CLIENTBLACKLISTEDEXCEPTION_H

#include <stdexcept>
#include <string>

class ClientBlacklistedException : public std::runtime_error {
public:
    ClientBlacklistedException() : std::runtime_error("Client is blacklisted") {}
};

#endif
