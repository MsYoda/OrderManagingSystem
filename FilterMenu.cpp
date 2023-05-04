#include "FilterMenu.h"

FilterMenu::FilterMenu(QWidget* parent) : QWidget(parent)
{
}

void FilterMenu::SetupProductMenu(Product* left, Product* right)
{
}


void FilterMenu::SetupComputerElementMenu(ComputerElement*)
{
}

void FilterMenu::SetupHouseTechMenu(HouseTech* obj)
{
}

void FilterMenu::SetupExternalTechMenu(ExternalTech* obj)
{
}

void FilterMenu::SetupGPUMenu(GPU* obj)
{
}

void FilterMenu::SetupFridgeMenu(Fridge* obj)
{
}

void FilterMenu::SetupWashMachineMenu(Washmachine* obj)
{
}

void FilterMenu::SetupMouseMenu(Mouse* obj)
{
}

void FilterMenu::SetupKeyboardMenu(Keyboard* obj)
{
}

bool FilterMenu::SaveProductParams(Product* obj)
{
	return false;
}

bool FilterMenu::SaveComputerElementParams(ComputerElement* obj)
{
	return false;
}

bool FilterMenu::SaveHouseTechParams(HouseTech* obj)
{
	return false;
}

bool FilterMenu::SaveExternalTechParams(ExternalTech* obj)
{
	return false;
}

