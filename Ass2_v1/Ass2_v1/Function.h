#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang


//Hàm kiểm tra chuỗi có phải là chuỗi số không
bool CheckInt(string str)
{
	bool Check = true;
	for (unsigned int i = 0;i < str.length();i++)
	{
		if ('0' > str[i] || str[i] > '9')
		{
			Check = false;
			break;
		}
	}
	if (str.empty()) Check = false;
	return Check;
}

//Hàm kiểm tra số nguyên và có thuộc các lựa chọn của menu hay không
bool Check_Choice(string str, int Total_Choice)
{
	bool Check = CheckInt(str);
	if (Check == true)
	{
		int Choice;
		stringstream(str) >> Choice;
		Check = false;
		int NuChoice[20]; // Menu chi toi da 20 lua chon
		for (int i = 1;i <= Total_Choice;i++)
		{
			NuChoice[i - 1] = i;
		}
		for (int i = 0;i < Total_Choice;i++)
		{
			if (Choice == NuChoice[i])
			{
				Check = true;
				break;
			}
		}
	}
	if (str.empty()) Check = false;
	return Check;
}

//Lùi đầu dòng Max ký tự ' '
void CanhLe(int Max)
{
	cout << setw(Max) << right << " ";
}

//In ra hàng ngang cua bảng gồm SoKyTu ký tự '*'
void VeHang(int SoKyTu)
{
	CanhLe(MaxKT);
	for (int i = 0;i < SoKyTu;i++)
	{
		cout << "~";
	}
	cout << "\n";
}

//Ghi dòng chữ chính giữa hàng
void Text_Giua(string str)
{
	int DoDai;
	if (str.length() % 2 == 0)DoDai = str.length();
	else DoDai = str.length() + 1;
	CanhLe(MaxKT);
	cout << "|" << setw((MaxCN - DoDai) / 2 + DoDai) << right << str
		<< setw((MaxCN - DoDai) / 2) << right << "|\n";
}

//Ghi các lựa chọn của Menu
void Text_Menu(string str)
{
	CanhLe(MaxKT);
	cout << "|" << str << setw(MaxCN - str.length()) << right << "|\n";
}

//Hàm kiểm tra ngày, tháng năm có đúng định dạng không
bool Check_Date(string str)
{
	bool Check = true;

	int Nu_Date, Nu_Month, Nu_Year;

	if (str.length() != 10 || str[2] != '-' || str[5] != '-')		Check = false;
	else
	{
		string Date = str.substr(0, 2);
		string Month = str.substr(3, 2);
		string Year = str.substr(6, 4);
		stringstream(Date) >> Nu_Date;
		stringstream(Month) >> Nu_Month;
		stringstream(Year) >> Nu_Year;
		if (CheckInt(Date) == false)				Check = false;
		else if (CheckInt(Month) == false)			Check = false;
		else if (CheckInt(Year) == false)			Check = false;
		else if ((Nu_Year % 4 == 0 && Nu_Year % 100 != 0) || Nu_Year % 400 == 0)//Nam nhuan
		{
			int End_Date[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
			int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			for (int i = 0;i < 12;i++)
			{
				if (Nu_Month <= 12 || Nu_Month >= 1)//Kiem tra thang
				{
					if (Nu_Month == Arr_Month[i])
					{
						if (Nu_Date<1 || Nu_Date>End_Date[i])//Kiem tra ngay
						{
							Check = false;
							break;
						}
						else break;
					}
				}
				else
				{
					Check = false;
					break;
				}
			}

		}
		else//Nam khong nhuan
		{
			int End_Date[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
			int Arr_Month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			for (int i = 0;i < 12;i++)
			{
				if (Nu_Month <= 12 || Nu_Month >= 1)//Kiem tra thang
				{
					if (Nu_Month == Arr_Month[i])//Kiem tra ngay
					{
						if (Nu_Date<1 || Nu_Date>End_Date[i])
						{
							Check = false;
							break;
						}
						else break;
					}
				}
				else
				{
					Check = false;
					break;
				}
			}
		}
	}
	return Check;
}