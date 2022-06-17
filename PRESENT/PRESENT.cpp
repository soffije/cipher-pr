#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "Header.h"
using namespace std;

int main()
{
	int box[64] = { 0X0000000000000000 };
	int box1[64] = { 0X0000000000000000 };
	int count = 0;
	int baff = 0;
	PRESENT_KEY key;		
	key.key_SHARE();		

	for (int round = 0; round < 31; ++round) //наш 31 раунд прокрутки 
	{
		baff = 0;
		//cout << "\n Round " << round << "\n";
		for (int step = 0; step < 64; ++step)		//XOR 
		{
			box[step] ^= key.k_share[round][step];
			box1[step] = box[step];
			cout << box[step];
		}
		cout << "\n";
		for (int step = 0; step < 64; ++step)		//SBOX 
		{
			count += pow(2, baff - 1) * box[step];
			baff++;
			if (baff != 0 && (baff % 4) == 0)
			{
				box[step] = key.sbox[count][4];
				box[step - 1] = key.sbox[count][3];
				box[step - 2] = key.sbox[count][2];
				box[step - 3] = key.sbox[count][1];
				box1[step] = box[step];
				box1[step - 1] = box[step - 1];
				box1[step - 2] = box[step - 2];
				box1[step - 3] = box[step - 3];
				baff = 0;
				count = 0;
			}
		}

		for (int step = 0; step < 63; ++step)		//линейно переставляем ключи
		{
			box[step] = box1[(step * 16) % 63];
		}

		for (int step = 0; step < 63; ++step)		//обновляем текст
		{
			box1[step] = box[step];
		}
	}

	for (int step = 0; step < 64; ++step)		//последний "31+1" раунд
	{
		box[step] ^= key.k_share[31][step];
		box1[step] = box[step];
	}
	cout << "\n The Cipher Text Is \n";
	for (int step = 0; step < 64; ++step)
	{
		cout << box[step];
	}

	return 0;
}
