#pragma once


class PlayerResources
{
public:

	int food = 0;
	int wood = 0;
	int iron = 0;

	PlayerResources operator + (PlayerResources r2)
	{

		PlayerResources result = {
			this->food + r2.food,
			this->wood + r2.wood,
			this->iron + r2.iron,
		};

		return result;
	}

	PlayerResources operator - (PlayerResources r2)
	{

		PlayerResources result = {
			this->food - r2.food,
			this->wood - r2.wood,
			this->iron - r2.iron,
		};

		return result;
	}

	PlayerResources operator * (int i)
	{

		PlayerResources result = {
			this->food * i,
			this->wood * i,
			this->iron * i,
		};

		return result;
	}

	// ���������� ������� �� ������� ��������
	PlayerResources lacks();
	
	// ��������� ��� �� ������������� ��������
	bool enough();

};
