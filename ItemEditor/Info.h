#pragma once

#include <iostream>

//������ Ÿ��
enum class EItemType
{
	Weapon,
	Armor
};

// ������ ���� (�̸�, Ÿ��, ����, �ȶ�)
struct Item
{
	char	Name[32];
	EItemType	Type;
	int		Price;
	int		Sell;
};


