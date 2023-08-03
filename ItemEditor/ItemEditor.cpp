#include "ItemEditor.h"

//삭제 또는 수정시 숫자 or 이름으로 입력 받을지
enum class ESearchType
{
	None,
	Name,
	Number,
	End
};

//아이템 입력 받기
void SetItemData(Item* Array, int Index)
{
	//Item* item = new Item;  //동적할당을 이용할수도 있다. 

	//화면 출력
	//1. 이름 입력
	system("cls");
	
	std::cout << "이름 : ";

	// 구조체 포인터는 -> 이용해서 참조하는 대상의 멤버에 접근할 수도 있다. 
	//std::cin >> item->Name;
	std::cin >> Array[Index].Name;

	//2. 아이템 종류 선택
	std::cout << "1. 무기" << std::endl;
	std::cout << "2. 방어구" << std::endl;
	std::cout << "아이템 종류를 선택하세요 : ";
	int	ItemType = 0;
	std::cin >> ItemType;

	Array[Index].Type = (EItemType)(ItemType - 1); // 0 = 무기 , 1 = 방어구 이기에 맞춰줌

	//3. 가격 
	std::cout << "Price : ";
	std::cin >> Array[Index].Price;

	//4. 팔 때
	std::cout << "Sell : ";
	std::cin >> Array[Index].Sell;
}

//아이템 생성 함수 구현 
void CreateItem(Item* Array, int& Count)  //아이템 저장 개수 수정을 위해 call by reference 
{
	//아이템 입력 받기
	SetItemData(Array, Count);

	//아이템 저장 개수 ++1
	++Count;
}

// 아이템 리스트 출력 
void OutputItemList(Item* Array, int Count)
{
	std::cout << "============아이템 목록===========" << std::endl;
	// 개수에 따른 반복 
	for (int i = 0; i < Count; ++i)
	{
		//이름 출력 
		std::cout << std::endl << i + 1 << ". 이름 : " << Array[i].Name << "\t종류 : ";

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
			<< Array[i].Sell << std::endl << std::endl;
	}
	std::cout << "==========아이템 목록 끝===========" << std::endl;
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

//아이템 삭제
void DeleteItem(Item* Array, int& Count)
{
	//임시 저장 파일 주소 초기화
	FILE* FileStream = nullptr;

	while (true)
	{
		system("cls");
		std::cout << "1. 전체 삭제" << std::endl;
		std::cout << "2. 개별 삭제" << std::endl;
		std::cout << "3. 삭제 취소" << std::endl;

		int Select = 0;
		std::cin >> Select;

		if (Select < 1 || Select >3)
		{
			continue;
		}
		//전체 삭제
		if (Select == 1)
		{

			//ItemList.itl 파일에 (쓰기,바이너리)
			fopen_s(&FileStream, "ItemList.itl", "wb");

			//FileStream에 값이 있으면 수행
			if (FileStream)
			{
				//fwrite(쓰고 싶은 데이터가 저장된 메모리 시작주소, 데이터 사이즈, 몇개의 데이터 저장할지, 데이터를 쓸 파일 포인터)
				*Array = {};
				Count = NULL;
				fwrite(&Count, sizeof(Count), 1, FileStream); //아이템 정보
				fwrite(Array, sizeof(Item), Count, FileStream); //아이템 정보

				fclose(FileStream);
				break;
			}
		}
		//선택 삭제
		else if (Select == 2)
		{
			ESearchType	SearchType = ESearchType::None;
			while (true)
			{
				system("cls");
				std::cout << "============= 아이템 제거 =============" << std::endl;
				std::cout << "1. 이름 탐색" << std::endl;
				std::cout << "2. 번호 선택" << std::endl;
				std::cout << "메뉴를 선택하세요 : ";
				int	Input = 0;
				std::cin >> Input;

				if (Input > (int)ESearchType::None && Input < (int)ESearchType::End)
				{
					SearchType = (ESearchType)Input;
					break;
				}
			}

			//현재 목록 출력 

			std::cout << "============아이템 목록===========" << std::endl;

			OutputItemList(Array, Count);

			std::cout << "=========삭제할 아이템 정보를 입력하시오========" << std::endl;

			//지울 인덱스 초기화
			int	DeleteIndex = -1;

			//이름으로 삭제할지, 인덱스로 삭제할지
			switch (SearchType)
			{
				// 이름 입력으로 삭제
			case ESearchType::Name:
				std::cout << "이름을 입력하세요 : ";

				//이름 입력
				char	Name[32];
				std::cin >> Name;

				for (int i = 0; i < Count; ++i)
				{
					// 문자열 비교, 같으면 0
					if (strcmp(Array[i].Name, Name) == 0) //if (*Array[i].Name == *Name)
					{
						DeleteIndex = i;
						break;
					}
				}
				break;

				//인덱스로 입력 받을 때
			case ESearchType::Number:

				//번호 입력
				std::cout << "지울 번호를 선택하세요 : ";
				std::cin >> DeleteIndex;

				//번호 입력 예외 처리
				if (DeleteIndex < 1 || DeleteIndex > Count)
					DeleteIndex = -1;

				// 1번부터 번호가 시작하고 있다. 이를 인덱스로 만들기 위해 1을 빼주어서
				// 0부터 시작되는 인덱스로 만들어준다.
				--DeleteIndex;
				break;
			}

			//인덱스에 해당하는 정보 제거 
			// DeleteIndex가 -1이라면 잘못된 인덱스이다.
			if (DeleteIndex != -1)
			{
				if (DeleteIndex != Count - 1)
				{
				//memmove(붙여넣기될 메모리 가리키는 포인터,복사할 메모리 포인터,복사할 데이터 길이);
				memmove(&Array[DeleteIndex], &Array[DeleteIndex + 1],
					sizeof(Item) * (Count - DeleteIndex - 1));
				}
				//i+1 번째 정보를 i번째에 저장 //조금 더 느림
				/*for (int i = DeleteIndex; i < Count - 1; ++i)
				{
					Array[i] = Array[i + 1];
				}*/

				--Count; //하나 뺏으니 크기 줄인다. 
			}
			break;
		}

		//삭제 취소
		else if (Select == 3)
		{
			break;
		}
	}
}

//아이템 수정
void ModifyItem(Item* Array, int Count)
{
	//이름을 입력받아 수정할지, 숫자 입력받아 수정할지 
	ESearchType	SearchType = ESearchType::None;
	while (true)
	{
		system("cls");
		std::cout << "============= 아이템 수정 =============" << std::endl;
		std::cout << "1. 이름 탐색" << std::endl;
		std::cout << "2. 번호 선택" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input = 0;
		std::cin >> Input;

		if (Input > (int)ESearchType::None && Input < (int)ESearchType::End)
		{
			SearchType = (ESearchType)Input;
			break;
		}
	}

	system("cls");

	//현재 목록 출력 
	OutputItemList(Array, Count);
	//지울 인덱스 초기화
	int	ModifyIndex = -1;

	//이름으로 삭제할지, 인덱스로 삭제할지
	switch (SearchType)
	{
		// 이름 입력으로 삭제
	case ESearchType::Name:
		std::cout << "이름을 입력하세요 : ";

		//이름 입력
		char	Name[32];
		std::cin >> Name;

		for (int i = 0; i < Count; ++i)
		{
			// 문자열 비교, 같으면 0
			if (strcmp(Array[i].Name, Name) == 0) //if (*Array[i].Name == *Name)
			{
				ModifyIndex = i;
				break;
			}
		}
		break;

		//인덱스로 입력 받을 때
	case ESearchType::Number:

		//번호 입력
		std::cout << "지울 번호를 선택하세요 : ";
		std::cin >> ModifyIndex;

		//번호 입력 예외 처리
		if (ModifyIndex < 1 || ModifyIndex > Count)
			ModifyIndex = -1;

		// 1번부터 번호가 시작하고 있다. 이를 인덱스로 만들기 위해 1을 빼주어서
		// 0부터 시작되는 인덱스로 만들어준다.
		--ModifyIndex;
		break;
	}

	//인덱스에 해당하는 정보 제거 
	// DeleteIndex가 -1이라면 잘못된 인덱스이다.
	if (ModifyIndex != -1)
	{
		if (ModifyIndex != - 1)
		{
			SetItemData(Array, ModifyIndex);
		}
	}
	//Item	Modify[100] = {};

	//std::cin >> Modify[0].Name;

	////2. 아이템 종류 선택
	////system("cls");
	//std::cout << "1. 무기" << std::endl;
	//std::cout << "2. 방어구" << std::endl;
	//std::cout << "아이템 종류를 선택하세요 : ";
	//int	ItemType = 0;
	//std::cin >> ItemType;

	//Modify[0].Type = (EItemType)(ItemType - 1); // 0 = 무기 , 1 = 방어구 이기에 맞춰줌

	////3. 가격 
	//std::cout << "Price : ";
	//std::cin >> Modify[0].Price;

	////4. 팔 때
	//std::cout << "Sell : ";
	//std::cin >> Modify[0].Sell;

	//for (int i = 0; i < Count; i++)
	//{
	//	if (*Array[i].Name == *Modify[0].Name)
	//	{
	//		*Array[i].Name = *Modify[0].Name;
	//		Array[i].Type = Modify[0].Type;
	//		Array[i].Price = Modify[0].Price;
	//		Array[i].Sell = Modify[0].Sell;

	//		break;
	//	}
	//}
}