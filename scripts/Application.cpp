#include "Application.h"


void DisplayMenu()
{
    std::cout << "-------------------------------------------\n";
    std::cout << "Press '" << static_cast<char>(InputKey::NavigatePrevious) << "' to navigate to the previous item.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::NavigateNext) << "' to navigate to the next item.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::AddItem) << "' to add a new item.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::RemoveItem) << "' to remove the current item.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::DisplayEquipment) << "' to display the character's equipment.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::IncreaseStack) << "' to increase stack count.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::DecreaseStack) << "' to decrease stack count.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::EquipItem) << "' to equip the current item.\n";
    std::cout << "Press '" << static_cast<char>(InputKey::Quit) << "' to quit.\n";
    std::cout << "-------------------------------------------\n";
}

void HandleAddItem(Inventory& inventory, Character& character, int maxStack)
{
    std::string name;
    int cost;
    char userInput;

    std::cout << "Enter item type (C for Consumable, E for Equipment, B for Base): ";
    std::cin >> userInput;
    std::cout << "Enter item name: ";
    std::cin >> name;
    std::cout << "Enter item cost: ";
    std::cin >> cost;

    if (userInput == 'C')
    {
        int stack;
        std::cout << "Initial Stack: ";
        std::cin >> stack;
        while (stack > 0)
        {
            int currentStack;
            if (stack > maxStack)
            {
                currentStack = maxStack;
            }
            else
            {
                currentStack = stack;
            }
            inventory.InsertItemAfterCurrent(new ConsumableItem(name, cost, currentStack));
            inventory.SelectNextItem();
            stack -= currentStack;
        }
    }
    else if (userInput == 'E')
    {
        int slot;

        std::cout << "Enter equipment slot (0 for Torso, 1 for Head, 2 for Legs, 3 for Weapon1, 4 for Weapon2): ";
        std::cin >> slot;

        EquipmentItem* newItem = new EquipmentItem(name, cost, static_cast<EquipmentSlot>(slot));
        inventory.InsertItemAfterCurrent(newItem);

        EquipmentItem* unequipped = character.EquipItem(newItem);

        if (unequipped)
        {
            inventory.AddItem(unequipped);
        }
    }
    else if (userInput == 'B')
    {
        inventory.InsertItemAfterCurrent(new InventoryItem(name, cost, 1));
    }
}

void HandleStacks(Inventory& inventory, bool increase)
{
    ConsumableItem* consumable = dynamic_cast<ConsumableItem*>(inventory.GetCurrentItem());
    if (consumable)
    {
        if (increase)
        {
            int remainingStack = consumable->AddStack();
            while (remainingStack > 0)
            {
                int currentStack;
                if (remainingStack > 20)
                {
                    currentStack = 20;
                }
                else
                {
                    currentStack = remainingStack;
                }
                inventory.InsertItemAfterCurrent(new ConsumableItem(consumable->GetName(), consumable->GetCost(), currentStack));
                remainingStack -= currentStack;
            }
        }
        else
        {
            if (consumable->RemoveStack())
            {
                inventory.RemoveCurrentItem();
            }
        }
    }
}

void HandleUserInput(char userInput, Inventory& inventory, Character& character, int maxStack)
{
    switch (static_cast<InputKey>(userInput))
    {
    case InputKey::NavigatePrevious:
        inventory.SelectPreviousItem();
        break;
    case InputKey::NavigateNext:
        inventory.SelectNextItem();
        break;
    case InputKey::AddItem:
        HandleAddItem(inventory, character, maxStack);
        break;
    case InputKey::RemoveItem:
        inventory.RemoveCurrentItem();
        break;
    case InputKey::DisplayEquipment:
        character.DisplayEquipment();
        break;
    case InputKey::IncreaseStack:
        HandleStacks(inventory, true);
        break;
    case InputKey::DecreaseStack:
        HandleStacks(inventory, false);
        break;
    case InputKey::EquipItem:
        inventory.EquipCurrentItem(character);
        break;
    case InputKey::Quit:
        std::cout << "Exiting program..." << std::endl;
        break;
    default:
        std::cout << "Invalid input. Please try again." << std::endl;
        break;
    }
}

void RunInventoryApplication()
{
    Character player;
    Inventory inventory;
    char userInput;
    DisplayMenu();

    do
    {
        std::cin >> userInput;
        HandleUserInput(userInput, inventory, player, 20);
        inventory.DisplayAll();
    } while (static_cast<InputKey>(userInput) != InputKey::Quit);
}