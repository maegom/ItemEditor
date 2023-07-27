#include "ItemEditor.h"

//������ ���� �Լ� ���� 
void CreateItem(Item* Array, int& Count)  //������ ���� ���� ������ ���� call by reference 
{
	//Item* item = new Item;  //�����Ҵ��� �̿��Ҽ��� �ִ�. 
	
	//ȭ�� ���
	//1. �̸� �Է�
	system("cls");
	std::cout << "============= ������ ���� =============" << std::endl;
	std::cout << "�̸� : ";

	// ����ü �����ʹ� -> �̿��ؼ� �����ϴ� ����� ����� ������ ���� �ִ�. 
	//std::cin >> item->Name;
	std::cin >> Array[Count].Name;

	//2. ������ ���� ����
	system("cls");
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ��" << std::endl;
	std::cout << "������ ������ �����ϼ��� : ";
	int	ItemType = 0;
	std::cin >> ItemType;

	Array[Count].Type = (EItemType)(ItemType - 1); // 0 = ���� , 1 = �� �̱⿡ ������

	//3. ���� 
	std::cout << "Price : ";
	std::cin >> Array[Count].Price;

	//4. �� ��
	std::cout << "Sell : ";
	std::cin >> Array[Count].Sell;

	//������ ���� ���� ++1
	++Count;
}

// ������ ����Ʈ ��� 
void OutputItemList(Item* Array, int Count)
{
	// ������ ���� �ݺ� 
	for (int i = 0; i < Count; ++i)
	{
		//�̸� ��� 
		std::cout << "�̸� : " << Array[i].Name << "\t���� : ";

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
			<< Array[i].Sell << std::endl;
	}
	system("pause");
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

void DeleteItem(Item* Array, int& Count)
{
	//�ӽ� ���� ���� �ּ� �ʱ�ȭ
	FILE* FileStream = nullptr;

	//ItemList.itl ���Ͽ� (����,���̳ʸ�)
	fopen_s(&FileStream, "ItemList.itl", "wb");

	//FileStream�� ���� ������ ����
	if (FileStream)
	{
		//fwrite(���� ���� �����Ͱ� ����� �޸� �����ּ�, ������ ������, ��� ������ ��������, �����͸� �� ���� ������)
		*Array = {};
		fwrite(&Count, sizeof(Count), 1, FileStream); //������ ����
		fwrite(Array, sizeof(Item), Count, FileStream); //������ ����
		Count = NULL;

		fclose(FileStream);
	}
}

void ModifyItem(Item* Array, int Count)
{
	system("cls");

	// ����� ������ ����Ʈ ��� 
	for (int i = 0; i < Count; ++i)
	{
		//�̸� ��� 
		std::cout << "�̸� : " << Array[i].Name << "\t���� : ";

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
			<< Array[i].Sell << std::endl;
	}

	std::cout << "=========������ ������ �̸��� �Է��Ͻÿ�========" << std::endl;
	std::cout << "�̸� : ";

	
	Item	Modify[100] = {};

	std::cin >> Modify[0].Name;

	//2. ������ ���� ����
	system("cls");
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ��" << std::endl;
	std::cout << "������ ������ �����ϼ��� : ";
	int	ItemType = 0;
	std::cin >> ItemType;

	Modify[0].Type = (EItemType)(ItemType - 1); // 0 = ���� , 1 = �� �̱⿡ ������

	//3. ���� 
	std::cout << "Price : ";
	std::cin >> Modify[0].Price;

	//4. �� ��
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


