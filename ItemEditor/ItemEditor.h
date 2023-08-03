#pragma once

#include "Info.h"

//아이템 입력 받기
void SetItemData(Item* Array, int Index);
//아이템 생성 
void CreateItem(Item* Array, int& Count);
//아이템 목록 출력
void OutputItemList(Item* Array, int Count);
//아이템 목록 저장
void SaveItemList(Item* Array, int Count);
//아이템 목록 불러오기
void LoadItemList(Item* Array, int& Count);
//아이템 지우기
void DeleteItem(Item* Array, int& Count);
//아이템 수정
void ModifyItem(Item* Array, int Count);
