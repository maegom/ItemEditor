#pragma once

#include <iostream>

//아이템 타입
enum class EItemType
{
	Weapon,
	Armor
};

//장착 타입
enum EEquipType
{
	Equip_None = -1,
	Equip_Weapon,
	Equip_Armor,
	Equip_End
};

// 아이템 정보  
struct Item
{
	EItemType	Type; //타입
	char	Name[32]; //이름	
	EEquipType	EquipType; //장착 타입
	int			Option; //옵션값
	int		Price; //살때가격
	int		Sell; //판매가격
};


