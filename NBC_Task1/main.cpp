#include <iostream>
#include <string>

using namespace std;

//보유 포션 개수 설정
void SetPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
	(*p_HPPotion) = (*p_MPPotion) = count;
}

//포션을 사용하여 HP 또는 MP 회복
void UsePoiton(bool isHP, int* potions, int* status)
{
	int useFlag = isHP ? 0 : 1;

	if (potions[useFlag] > 0)
	{
		string usingText = isHP ? "HP" : "MP";
		cout << "* " << usingText << "가 20 회복되었습니다. 포션이 1개 차감됩니다.\n";
		status[useFlag] += 20;
		cout << "현재 " << usingText << " : " << status[useFlag] << "\n";
		cout << "남은 포션 수 : " << --potions[useFlag];
	}
	else
	{
		cout << "포션이 부족합니다.";
	}
}

//HP나 MP를 강화
void DuplicateStatus(bool isHP, int* status)
{
	int useFlag = isHP ? 0 : 1;
	string usingText = isHP ? "HP" : "MP";

	cout << "* " << usingText << "가 2배로 증가되었습니다.\n";

	status[useFlag] *= 2;
	cout << "현재 " << usingText << " : " << status[useFlag];
}

//공격
void Attack(int& mp)
{
	if (mp > 50)
	{
		cout << "* 스킬을 사용하여 MP가 50 소모되었습니다.\n";
		mp -= 50;
		cout << "현재 MP : " << mp;
	}
	else
	{
		cout << "스킬 사용이 불가합니다.";
	}
}

//필살기
void Ultimate(int& mp)
{
	cout << "* 스킬을 사용하여 MP가 50% 소모되었습니다.\n";
	mp = static_cast<int>(mp * 0.5f);
	cout << "현재 MP : " << mp;
}

int main()
{
	int* status = new int[4];//0 : HP, 1 : MP, 2 : ATK, 3 : DEF
	int* potions = new int[2];//0 : HP포션, 1 : MP포션

	//HP, MP 입력
	while (true)
	{
		cout << "HP와 MP를 입력해주세요 : ";
		cin >> status[0] >> status[1];

		if (status[0] < 50 || status[1] < 50)
			cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.\n";
		else
			break;
	}

	//공격력, 방어력 입력
	while (true)
	{
		cout << "공격력과 방어력을 입력해주세요 : ";
		cin >> status[2] >> status[3];

		if (status[2] < 1 || status[3] < 1)
			cout << "공격력이나 방어력의 값이 너무 작습니다. 다시 입력해주세요.\n";
		else
			break;
	}

	//포션 지급
	SetPotion(5, &potions[0], &potions[1]);
	cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 5개)\n";
	cout << "========================================\n";

	//게임 진행
	cout << "1. HP 회복\n";
	cout << "2. MP 회복\n";
	cout << "3. HP 강화\n";
	cout << "4. MP 강화\n";
	cout << "5. 공격 스킬 사용\n";
	cout << "6. 필살기 사용\n";
	cout << "7. 나가기\n";
	int select = 0;
	bool exit = false;
	while (!exit)
	{
		cout << endl << "번호를 선택해주세요 : ";
		cin >> select;
		switch (select)
		{
		case 1://1. HP 회복
			UsePoiton(true, potions, status);
			break;
		case 2://2. MP 회복
			UsePoiton(false, potions, status);
			break;
		case 3://3. HP 강화
			DuplicateStatus(true, status);
			break;
		case 4://4. MP 강화
			DuplicateStatus(false, status);
			break;
		case 5://5. 공격 스킬 사용
			Attack(status[1]);
			break;
		case 6://6. 필살기 사용
			Ultimate(status[1]);
			break;
		case 7://7. 나가기
			cout << "프로그램을 종료합니다.\n";
			exit = true;
			break;
		default://?
			break;
		}
	}

	delete[] status;
	delete[] potions;

	return 0;
}