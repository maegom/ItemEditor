#pragma once

#include "Info.h"

//������ ���� 
void CreateItem(Item* Array, int& Count);
//������ ��� ���
void OutputItemList(Item* Array, int Count);
//������ ��� ����
void SaveItemList(Item* Array, int Count);
//������ ��� �ҷ�����
void LoadItemList(Item* Array, int& Count);
//������ �����
void DeleteItem(Item* Array, int& Count);
//������ ����
void ModifyItem(Item* Array, int Count);