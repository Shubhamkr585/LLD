#include "ComputerDirector.hpp"

int main() {
    DesktopBuilder builder;
    ComputerDirector director;

    director.buildGamingPC(builder);
    Desktop* gamingPC = builder.build();
    gamingPC->showSpecs();

    director.buildOfficePC(builder);
    Desktop* officePC = builder.build();
    officePC->showSpecs();

    delete gamingPC;
    delete officePC;
}
