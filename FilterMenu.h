#pragma once
#include <qwidget.h>
#include "Products.h"

class FilterMenu :
    public QWidget
{
    Q_OBJECT
    FilterMenu(QWidget* parent = nullptr);

    void SetupProductMenu(Product* left, Product* right);

    void SetupComputerElementMenu(ComputerElement* left, ComputerElement* right);

    void SetupHouseTechMenu(HouseTech* left, HouseTech* right);
    void SetupExternalTechMenu(ExternalTech* left, ExternalTech* right);

    void SetupCPUMenu(CPU* obj);
    void SetupGPUMenu(GPU* obj);

    void SetupFridgeMenu(Fridge* obj);
    void SetupWashMachineMenu(Washmachine* obj);

    void SetupMouseMenu(Mouse* obj);
    void SetupKeyboardMenu(Keyboard* obj);


    bool SaveProductParams(Product* obj);

    bool SaveComputerElementParams(ComputerElement* obj);
    bool SaveHouseTechParams(HouseTech* obj);
    bool SaveExternalTechParams(ExternalTech* obj);

    bool SaveCPUParams(CPU* obj);
    bool SaveGPUParams(GPU* obj);

    bool SaveFridgeParams(Fridge* obj);
    bool SaveWashMachineParams(Washmachine* obj);

    bool SaveMouseParams(Mouse* obj);
    bool SaveKeyboardParams(Keyboard* obj);
};

