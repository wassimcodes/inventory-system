#pragma once
#include "InventoryItem.h"

#define SLOT_COUNT 5

class Character
{
private:
    EquipmentItem* m_equipment[5];

public:
    Character();
    ~Character();
    EquipmentItem* GetEquipment(EquipmentSlot slot);
    EquipmentItem* EquipItem(EquipmentItem* item);
    void DisplayEquipment();
};
