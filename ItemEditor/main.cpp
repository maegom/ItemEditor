#include "ItemEditor.h"

//첫화면 입력값 
enum class EMainMenu
{
	None, //빈값
	CreateItem, //1. 아이템 생성
	DeleteItem, //2. 아이템 제거
	ModifyItem, //3. 아이템 수정
	OutputItem, //4. 아이템 목록 출력
	SaveItem,   //5. 아이템 목록파일 저장 
	LoadItem,   //6. 아이템 목록파일 불러오기
	Exit        //7. 종료
};

int main()
{
	// 아이템 저장공간
	Item	item[100] = {};

	// 아이템 개수
	int		Count = 0;

	while (true)
	{
		system("cls");

		//첫화면 출력값 및 입력 받기
		std::cout << "1. 아이템 생성" << std::endl;
		std::cout << "2. 아이템 제거" << std::endl;
		std::cout << "3. 아이템 수정" << std::endl;
		std::cout << "4. 아이템 목록 출력" << std::endl;
		std::cout << "5. 아이템 목록파일 저장" << std::endl;
		std::cout << "6. 아이템 목록파일 불러오기" << std::endl;
		std::cout << "7. 종료" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		// 7 은 종료
		if (Input == (int)EMainMenu::Exit)
			break;

		// 다른 숫자 입력은 재입력 
		else if (Input <= (int)EMainMenu::None || Input > (int)EMainMenu::Exit)
			continue;

		// 1 ~ 7 각각 함수 수행
		switch ((EMainMenu)Input)
		{
		case EMainMenu::CreateItem: //1
			CreateItem(item, Count);
			break;
		case EMainMenu::DeleteItem: //2
			DeleteItem(item, Count);
			break;
		case EMainMenu::ModifyItem: //3
			break;
			ModifyItem(item, Count);
		case EMainMenu::OutputItem: //4
			OutputItemList(item, Count);
			break;
		case EMainMenu::SaveItem:   //5
			SaveItemList(item, Count);
			break;
		case EMainMenu::LoadItem:   //6
			LoadItemList(item, Count);
			break;
		case EMainMenu::Exit:       //7
			break;
		}
	}

	return 0;
}