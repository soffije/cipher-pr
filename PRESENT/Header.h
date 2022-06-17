#pragma once
using namespace std;

class PRESENT_KEY
{
private:
	int key[80];	//��������� ���� 80 ���
	int round_key[80];	//��� ��������� ��������� ������
	int k[32][80]; 	//��������� ����� ������
	int s_box[16][4];	//sbox
	int fin;	
	int num;

public:
	int sbox[16][4];
	int k_share[32][80];	//��� ������ �������� �������
	PRESENT_KEY()	//�������������� ����� ����� ����� �������� �������
	{
		int sbox1[16][4] = { {1,1,0,0}, {0,1,0,1}, {0,1,1,0}, {1,0,1,1}, {1,0,0,1}, {0,0,0,0}, {1,0,1,0}, {1,1,0,1}, {0,0,1,1}, {1,1,1,0}, {1,1,1,1}, {1,0,0,0}, {0,1,0,0}, {0,1,1,1}, {0,0,0,1}, {0,0,1,0} };
		int sbox[16][4] = { {1,1,0,0}, {0,1,0,1}, {0,1,1,0}, {1,0,1,1}, {1,0,0,1}, {0,0,0,0}, {1,0,1,0}, {1,1,0,1}, {0,0,1,1}, {1,1,1,0}, {1,1,1,1}, {1,0,0,0}, {0,1,0,0}, {0,1,1,1}, {0,0,0,1}, {0,0,1,0} };

		for (int i = 0; i < 80; ++i)		//��������� ��������� �����
		{
			key[i] = rand() % 2;
			round_key[i] = key[i];
			k[0][i] = key[i];		//������ ��� ���� ������� ������� ����� ��
		}
		for (int j = 1; j < 32; ++j)		//��������� ����
		{
			for (int i = 0; i < 80; ++i)		//����� �����
			{
				k[j][i] = round_key[(i + 19) % 80];
			}

			fin = k[j][76] * 1 + k[j][77] * 2 + k[j][78] * 4 + k[j][79] * 8;		//������������ sbox
			for (int i = 76; i < 80; ++i)
			{
				k[j][i] = sbox1[fin][i - 76];
			}
			num = j;

			while (num > 0)		//������� XOR
			{
				fin = 15;
				k[j][fin] = k[j][fin] ^ (num % 2); //��������� XOR + �������
				fin++;
				num /= 2;
			}

			for (int i = 0; i < 80; ++i)	//��������� ���� �� ����������
			{
				round_key[i] = k[j][i];
			}
		}
	}
	void key_SHARE()	//��� ������ �������
	{
		for (int j = 0; j < 32; ++j)
		{
			for (int i = 0; i < 80; ++i)
			{
				k_share[j][i] = k[j][i];
			}
		}
	}
};