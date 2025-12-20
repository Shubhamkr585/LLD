#ifndef COMPUTER_DIRECTOR_HPP
#define COMPUTER_DIRECTOR_HPP

#include "DesktopBuilder.hpp"

class ComputerDirector {
public:
    void buildGamingPC(DesktopBuilder& builder);
    void buildOfficePC(DesktopBuilder& builder);
};

#endif
