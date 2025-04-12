#pragma once

#include <iostream>
#include "Inventory.h"
#include "Character.h"

enum class InputKey
{
    NavigatePrevious = 'A',
    NavigateNext = 'D',
    AddItem = 'I',
    RemoveItem = 'R',
    DisplayEquipment = 'P',
    IncreaseStack = '+',
    DecreaseStack = '-',
    EquipItem = 'E',
    Quit = 'Q'
};


void DisplayMenu();
void HandleAddItem(Inventory& inventory, Character& character, int maxStack);
void HandleStacks(Inventory& inventory, bool increase);
void HandleUserInput(char userInput, Inventory& inventory, Character& character, int maxStack);
void RunInventoryApplication();
