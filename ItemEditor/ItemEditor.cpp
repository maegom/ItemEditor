#include "ItemEditor.h"

//���� �Ǵ� ������ ���� or �̸����� �Է� ������
enum class ESearchType
{
	None,
	Name,
	Number,
	End
};

//������ �Է� �ޱ�
void SetItemData(Item* Array, int Index)
{
	//Item* item = new Item;  //�����Ҵ��� �̿��Ҽ��� �ִ�. 

	//ȭ�� ���
	//1. �̸� �Է�
	system("cls");
	
	std::cout << "�̸� : ";

	// ����ü �����ʹ� -> �̿��ؼ� �����ϴ� ����� ����� ������ ���� �ִ�. 
	//std::cin >> item->Name;
	std::cin >> Array[Index].Name;

	//2. ������ ���� ����
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ��" << std::endl;
	std::cout << "������ ������ �����ϼ��� : ";
	int	ItemType = 0;
	std::cin >> ItemType;

	Array[Index].Type = (EItemType)(ItemType - 1); // 0 = ���� , 1 = �� �̱⿡ ������

	//3. ���� 
	std::cout << "Price : ";
	std::cin >> Array[Index].Price;

	//4. �� ��
	std::cout << "Sell : ";
	std::cin >> Array[Index].Sell;
}

//������ ���� �Լ� ���� 
void CreateItem(Item* Array, int& Count)  //������ ���� ���� ������ ���� call by reference 
{
	//������ �Է� �ޱ�
	SetItemData(Array, Count);

	//������ ���� ���� ++1
	++Count;
}

// ������ ����Ʈ ��� 
void OutputItemList(Item* Array, int Count)
{
	std::cout << "============������ ���===========" << std::endl;
	// ������ ���� �ݺ� 
	for (int i = 0; i < Count; ++i)
	{
		//�̸� ��� 
		std::cout << std::endl << i + 1 << ". �̸� : " << Array[i].Name << "\t���� : ";

		//���� ��� 
		switch (Array[i].Type)
		{
		case EItemType::Weapon:
			std::cout << "����\n";
			break;
		case EItemType::Armor:
			std::cout << "��\n";
			break;
		}

		//���� ���
		std::cout << "Price : " << Array[i].Price << "\tSell : " 
			<< Array[i].Sell << std::endl << std::endl;
	}
	std::cout << "==========������ ��� ��===========" << std::endl;
}

// ���� ���� 
void SaveItemList(Item* Array, int Count)
{
	//�ӽ� ���� ���� �ּ� �ʱ�ȭ
	FILE* FileStream = nullptr;

	//ItemList.itl ���Ͽ� (����,���̳ʸ�)
	fopen_s(&FileStream, "ItemList.itl", "wb");

	//FileStream�� ���� ������ ����
	if (FileStream)
	{
		//fwrite(���� ���� �����Ͱ� ����� �޸� �����ּ�, ������ ������, ��� ������ ��������, �����͸� �� ���� ������)
		fwrite(&Count, sizeof(Count), 1, FileStream); //������ ����
		fwrite(Array, sizeof(Item), Count, FileStream); //������ ����
			
		fclose(FileStream);
	}
}



//���� �ҷ����� 
void LoadItemList(Item* Array, int& Count)
{
	//�ӽ� ���� ���� �ּ� �ʱ�ȭ
	FILE* FileStream = nullptr;

	//ItemList.itl ���Ͽ� (�б�,���̳ʸ�)
	fopen_s(&FileStream, "ItemList.itl", "rb");

	//FileStream�� ���� ������ ����
	if (FileStream)
	{
		//fread(�а� ���� �����Ͱ� ����� �޸� �����ּ�, ������ ������, ��� ������ ��������, �����͸� �� ���� ������)
		fread(&Count, sizeof(Count), 1, FileStream);
		fread(Array, sizeof(Item), Count, FileStream);

		fclose(FileStream);
	}
}

//������ ����
void DeleteItem(Item* Array, int& Count)
{
	//�ӽ� ���� ���� �ּ� �ʱ�ȭ
	FILE* FileStream = nullptr;

	while (true)
	{
		system("cls");
		std::cout << "1. ��ü ����" << std::endl;
		std::cout << "2. ���� ����" << std::endl;
		std::cout << "3. ���� ���" << std::endl;

		int Select = 0;
		std::cin >> Select;

		if (Select < 1 || Select >3)
		{
			continue;
		}
		//��ü ����
		if (Select == 1)
		{

			//ItemList.itl ���Ͽ� (����,���̳ʸ�)
			fopen_s(&FileStream, "ItemList.itl", "wb");

			//FileStream�� ���� ������ ����
			if (FileStream)
			{
				//fwrite(���� ���� �����Ͱ� ����� �޸� �����ּ�, ������ ������, ��� ������ ��������, �����͸� �� ���� ������)
				*Array = {};
				Count = NULL;
				fwrite(&Count, sizeof(Count), 1, FileStream); //������ ����
				fwrite(Array, sizeof(Item), Count, FileStream); //������ ����

				fclose(FileStream);
				break;
			}
		}
		//���� ����
		else if (Select == 2)
		{
			ESearchType	SearchType = ESearchType::None;
			while (true)
			{
				system("cls");
				std::cout << "============= ������ ���� =============" << std::endl;
				std::cout << "1. �̸� Ž��" << std::endl;
				std::cout << "2. ��ȣ ����" << std::endl;
				std::cout << "�޴��� �����ϼ��� : ";
				int	Input = 0;
				std::cin >> Input;

				if (Input > (int)ESearchType::None && Input < (int)ESearchType::End)
				{
					SearchType = (ESearchType)Input;
					break;
				}
			}

			//���� ��� ��� 

			std::cout << "============������ ���===========" << std::endl;

			OutputItemList(Array, Count);

			std::cout << "=========������ ������ ������ �Է��Ͻÿ�========" << std::endl;

			//���� �ε��� �ʱ�ȭ
			int	DeleteIndex = -1;

			//�̸����� ��������, �ε����� ��������
			switch (SearchType)
			{
				// �̸� �Է����� ����
			case ESearchType::Name:
				std::cout << "�̸��� �Է��ϼ��� : ";

				//�̸� �Է�
				char	Name[32];
				std::cin >> Name;

				for (int i = 0; i < Count; ++i)
				{
					// ���ڿ� ��, ������ 0
					if (strcmp(Array[i].Name, Name) == 0) //if (*Array[i].Name == *Name)
					{
						DeleteIndex = i;
						break;
					}
				}
				break;

				//�ε����� �Է� ���� ��
			case ESearchType::Number:

				//��ȣ �Է�
				std::cout << "���� ��ȣ�� �����ϼ��� : ";
				std::cin >> DeleteIndex;

				//��ȣ �Է� ���� ó��
				if (DeleteIndex < 1 || DeleteIndex > Count)
					DeleteIndex = -1;

				// 1������ ��ȣ�� �����ϰ� �ִ�. �̸� �ε����� ����� ���� 1�� ���־
				// 0���� ���۵Ǵ� �ε����� ������ش�.
				--DeleteIndex;
				break;
			}

			//�ε����� �ش��ϴ� ���� ���� 
			// DeleteIndex�� -1�̶�� �߸��� �ε����̴�.
			if (DeleteIndex != -1)
			{
				if (DeleteIndex != Count - 1)
				{
				//memmove(�ٿ��ֱ�� �޸� ����Ű�� ������,������ �޸� ������,������ ������ ����);
				memmove(&Array[DeleteIndex], &Array[DeleteIndex + 1],
					sizeof(Item) * (Count - DeleteIndex - 1));
				}
				//i+1 ��° ������ i��°�� ���� //���� �� ����
				/*for (int i = DeleteIndex; i < Count - 1; ++i)
				{
					Array[i] = Array[i + 1];
				}*/

				--Count; //�ϳ� ������ ũ�� ���δ�. 
			}
			break;
		}

		//���� ���
		else if (Select == 3)
		{
			break;
		}
	}
}

//������ ����
void ModifyItem(Item* Array, int Count)
{
	//�̸��� �Է¹޾� ��������, ���� �Է¹޾� �������� 
	ESearchType	SearchType = ESearchType::None;
	while (true)
	{
		system("cls");
		std::cout << "============= ������ ���� =============" << std::endl;
		std::cout << "1. �̸� Ž��" << std::endl;
		std::cout << "2. ��ȣ ����" << std::endl;
		std::cout << "�޴��� �����ϼ��� : ";
		int	Input = 0;
		std::cin >> Input;

		if (Input > (int)ESearchType::None && Input < (int)ESearchType::End)
		{
			SearchType = (ESearchType)Input;
			break;
		}
	}

	system("cls");

	//���� ��� ��� 
	OutputItemList(Array, Count);
	//���� �ε��� �ʱ�ȭ
	int	ModifyIndex = -1;

	//�̸����� ��������, �ε����� ��������
	switch (SearchType)
	{
		// �̸� �Է����� ����
	case ESearchType::Name:
		std::cout << "�̸��� �Է��ϼ��� : ";

		//�̸� �Է�
		char	Name[32];
		std::cin >> Name;

		for (int i = 0; i < Count; ++i)
		{
			// ���ڿ� ��, ������ 0
			if (strcmp(Array[i].Name, Name) == 0) //if (*Array[i].Name == *Name)
			{
				ModifyIndex = i;
				break;
			}
		}
		break;

		//�ε����� �Է� ���� ��
	case ESearchType::Number:

		//��ȣ �Է�
		std::cout << "���� ��ȣ�� �����ϼ��� : ";
		std::cin >> ModifyIndex;

		//��ȣ �Է� ���� ó��
		if (ModifyIndex < 1 || ModifyIndex > Count)
			ModifyIndex = -1;

		// 1������ ��ȣ�� �����ϰ� �ִ�. �̸� �ε����� ����� ���� 1�� ���־
		// 0���� ���۵Ǵ� �ε����� ������ش�.
		--ModifyIndex;
		break;
	}

	//�ε����� �ش��ϴ� ���� ���� 
	// DeleteIndex�� -1�̶�� �߸��� �ε����̴�.
	if (ModifyIndex != -1)
	{
		if (ModifyIndex != - 1)
		{
			SetItemData(Array, ModifyIndex);
		}
	}
	//Item	Modify[100] = {};

	//std::cin >> Modify[0].Name;

	////2. ������ ���� ����
	////system("cls");
	//std::cout << "1. ����" << std::endl;
	//std::cout << "2. ��" << std::endl;
	//std::cout << "������ ������ �����ϼ��� : ";
	//int	ItemType = 0;
	//std::cin >> ItemType;

	//Modify[0].Type = (EItemType)(ItemType - 1); // 0 = ���� , 1 = �� �̱⿡ ������

	////3. ���� 
	//std::cout << "Price : ";
	//std::cin >> Modify[0].Price;

	////4. �� ��
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