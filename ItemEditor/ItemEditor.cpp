#include "ItemEditor.h"

//아이템 생성 함수 구현 
void CreateItem(Item* Array, int& Count)  //아이템 저장 개수 수정을 위해 call by reference 
{
	//Item* item = new Item;  //동적할당을 이용할수도 있다. 
	
	//화면 출력
	//1. 이름 입력
	system("cls");
	std::cout << "============= 아이템 생성 =============" << std::endl;
	std::cout << "이름 : ";

	// 구조체 포인터는 -> 이용해서 참조하는 대상의 멤버에 접근할 수도 있다. 
	//std::cin >> item->Name;
	std::cin >> Array[Count].Name;

	//2. 아이템 종류 선택
	system("cls");
	std::cout << "1. 무기" << std::endl;
	std::cout << "2. 방어구" << std::endl;
	std::cout << "아이템 종류를 선택하세요 : ";
	int	ItemType = 0;
	std::cin >> ItemType;

	Array[Count].Type = (EItemType)(ItemType - 1); // 0 = 무기 , 1 = 방어구 이기에 맞춰줌

	//3. 가격 
	std::cout << "Price : ";
	std::cin >> Array[Count].Price;

	//4. 팔 때
	std::cout << "Sell : ";
	std::cin >> Array[Count].Sell;

	//아이템 저장 개수 ++1
	++Count;
}

// 아이템 리스트 출력 
void OutputItemList(Item* Array, int Count)
{
	// 개수에 따른 반복 
	for (int i = 0; i < Count; ++i)
	{
		//이름 출력 
		std::cout << "이름 : " << Array[i].Name << "\t종류 : ";

		//종류 출력 
		switch (Array[i].Type)
		{
		case EItemType::Weapon:
			std::cout << "무기\n";
			break;
		case EItemType::Armor:
			std::cout << "방어구\n";
			break;
		}

		//가격 출력
		std::cout << "Price : " << Array[i].Price << "\tSell : " 
			<< Array[i].Sell << std::endl;
	}
	system("pause");
}

// 파일 저장 
void SaveItemList(Item* Array, int Count)
{
	//임시 저장 파일 주소 초기화
	FILE* FileStream = nullptr;

	//ItemList.itl 파일에 (쓰기,바이너리)
	fopen_s(&FileStream, "ItemList.itl", "wb");

	//FileStream에 값이 있으면 수행
	if (FileStream)
	{
		//fwrite(쓰고 싶은 데이터가 저장된 메모리 시작주소, 데이터 사이즈, 몇개의 데이터 저장할지, 데이터를 쓸 파일 포인터)
		fwrite(&Count, sizeof(Count), 1, FileStream); //아이템 정보
		fwrite(Array, sizeof(Item), Count, FileStream); //아이템 정보
			
		fclose(FileStream);
	}
}

//파일 불러오기 
void LoadItemList(Item* Array, int& Count)
{
	//임시 저장 파일 주소 초기화
	FILE* FileStream = nullptr;

	//ItemList.itl 파일에 (읽기,바이너리)
	fopen_s(&FileStream, "ItemList.itl", "rb");

	//FileStream에 값이 있으면 수행
	if (FileStream)
	{
		//fread(읽고 싶은 데이터가 저장된 메모리 시작주소, 데이터 사이즈, 몇개의 데이터 저장할지, 데이터를 쓸 파일 포인터)
		fread(&Count, sizeof(Count), 1, FileStream);
		fread(Array, sizeof(Item), Count, FileStream);

		fclose(FileStream);
	}
}

void DeleteItem(Item* Array, int& Count)
{
	//임시 저장 파일 주소 초기화
	FILE* FileStream = nullptr;

	//ItemList.itl 파일에 (쓰기,바이너리)
	fopen_s(&FileStream, "ItemList.itl", "wb");

	//FileStream에 값이 있으면 수행
	if (FileStream)
	{
		//fwrite(쓰고 싶은 데이터가 저장된 메모리 시작주소, 데이터 사이즈, 몇개의 데이터 저장할지, 데이터를 쓸 파일 포인터)
		*Array = {};
		fwrite(&Count, sizeof(Count), 1, FileStream); //아이템 정보
		fwrite(Array, sizeof(Item), Count, FileStream); //아이템 정보
		Count = NULL;

		fclose(FileStream);
	}
}

void ModifyItem(Item* Array, int Count)
{
	system("cls");

	// 저장된 아이템 리스트 출력 
	for (int i = 0; i < Count; ++i)
	{
		//이름 출력 
		std::cout << "이름 : " << Array[i].Name << "\t종류 : ";

		//종류 출력 
		switch (Array[i].Type)
		{
		case EItemType::Weapon:
			std::cout << "무기\n";
			break;
		case EItemType::Armor:
			std::cout << "방어구\n";
			break;
		}

		//가격 출력
		std::cout << "Price : " << Array[i].Price << "\tSell : "
			<< Array[i].Sell << std::endl;
	}

	std::cout << "=========수정할 아이템 이름을 입력하시오========" << std::endl;
	std::cout << "이름 : ";

	
	Item	Modify[100] = {};

	std::cin >> Modify[0].Name;

	//2. 아이템 종류 선택
	system("cls");
	std::cout << "1. 무기" << std::endl;
	std::cout << "2. 방어구" << std::endl;
	std::cout << "아이템 종류를 선택하세요 : ";
	int	ItemType = 0;
	std::cin >> ItemType;

	Modify[0].Type = (EItemType)(ItemType - 1); // 0 = 무기 , 1 = 방어구 이기에 맞춰줌

	//3. 가격 
	std::cout << "Price : ";
	std::cin >> Modify[0].Price;

	//4. 팔 때
	std::cout << "Sell : ";
	std::cin >> Modify[0].Sell;
 
	for (int i = 0; i < Count; i++)
	{
		if (*Array[i].Name == *Modify[0].Name)
		{
			*Array[i].Name = *Modify[0].Name;
			Array[i].Type = Modify[0].Type;
			Array[i].Price = Modify[0].Price;
			Array[i].Sell = Modify[0].Sell;

			break;
		}
	}

}


