#pragma once

#include <iostream>

//������ Ÿ��
enum class EItemType
{
	Weapon,
	Armor
};

//���� Ÿ��
enum EEquipType
{
	Equip_None = -1,
	Equip_Weapon,
	Equip_Armor,
	Equip_End
};

// ������ ����  
struct Item
{
	char	Name[32]; //�̸�
	EItemType	Type; //Ÿ��
	EEquipType	EquipType; //���� Ÿ��
	int			Option; //�ɼǰ�
	int		Price; //�춧����
	int		Sell; //�ǸŰ���
};


