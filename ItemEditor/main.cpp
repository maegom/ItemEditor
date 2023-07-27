#include "ItemEditor.h"

//ùȭ�� �Է°� 
enum class EMainMenu
{
	None, //��
	CreateItem, //1. ������ ����
	DeleteItem, //2. ������ ����
	ModifyItem, //3. ������ ����
	OutputItem, //4. ������ ��� ���
	SaveItem,   //5. ������ ������� ���� 
	LoadItem,   //6. ������ ������� �ҷ�����
	Exit        //7. ����
};

int main()
{
	// ������ �������
	Item	item[100] = {};

	// ������ ����
	int		Count = 0;

	while (true)
	{
		system("cls");

		//ùȭ�� ��°� �� �Է� �ޱ�
		std::cout << "1. ������ ����" << std::endl;
		std::cout << "2. ������ ����" << std::endl;
		std::cout << "3. ������ ����" << std::endl;
		std::cout << "4. ������ ��� ���" << std::endl;
		std::cout << "5. ������ ������� ����" << std::endl;
		std::cout << "6. ������ ������� �ҷ�����" << std::endl;
		std::cout << "7. ����" << std::endl;
		std::cout << "�޴��� �����ϼ��� : ";
		int	Input;
		std::cin >> Input;

		// 7 �� ����
		if (Input == (int)EMainMenu::Exit)
			break;

		// �ٸ� ���� �Է��� ���Է� 
		else if (Input <= (int)EMainMenu::None || Input > (int)EMainMenu::Exit)
			continue;

		// 1 ~ 7 ���� �Լ� ����
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