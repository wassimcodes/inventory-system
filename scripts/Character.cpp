#include "Character.h"
#include <iostream>

Character::Character()
{
    for (int i = 0; i < SLOT_COUNT; ++i)
    {
        m_equipment[i] = nullptr;
    }
	std::cout << "Character created." << std::endl;
}

Character::~Character()
{
    for (int i = 0; i < SLOT_COUNT; ++i)
    {
        delete m_equipment[i];
    }
	std::cout << "Character destroyed." << std::endl;
}

EquipmentItem* Character::GetEquipment(EquipmentSlot slot)
{
    return m_equipment[static_cast<int>(slot)];
}

EquipmentItem* Character::EquipItem(EquipmentItem* item)
{
    EquipmentSlot slot = item->GetSlot();
    EquipmentItem* previous = m_equipment[static_cast<int>(slot)];
    m_equipment[static_cast<int>(slot)] = item;

    std::cout << item->GetName() << " has been equipped on the " << item->GetSlotName();
    if (previous)
    {
        std::cout << " " << previous->GetName() << " has been returned to the inventory.";
    }
    std::cout << std::endl;

    return previous;
}

void Character::DisplayEquipment()
{
    std::string slotNames[] = { "Torso", "Head", "Legs", "Weapon1", "Weapon2" };
    for (int i = 0; i < SLOT_COUNT; ++i)
    {
        if (m_equipment[i])
        {
            std::cout << slotNames[i] << ": " << m_equipment[i]->ToString() << std::endl;
        }
        else
        {
            std::cout << slotNames[i] << ": nothing" << std::endl;
        }
    }
}
