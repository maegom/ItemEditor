#pragma once

#include <iostream>

//아이템 타입
enum class EItemType
{
	Weapon,
	Armor
};

// 아이템 정보 (이름, 타입, 가격, 팔때)
struct Item
{
	char	Name[32];
	EItemType	Type;
	int		Price;
	int		Sell;
};


