#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include<fstream>
#include "Function.h"
using namespace std;
#define MaxKT 10 //Max Khoang Trang
#define MaxCN 100 //Max Cot Ngang
enum Menu_Libpro { SignIn_Libpro = 1, SignUp_Libpro, SearchBook_Libpro,SeeBook_Libpro, Stop_Libpro };
enum Check_User { USER_NAME, USER_NO, MSSV, EMAIL};
enum Sign_Fail {SignIn,SignUp};

//Các hàm nằm trong Function.h
bool CheckInt(string str);//Hàm kiểm tra chuỗi có phải là chuỗi số không
bool Check_Choice(string str, int Total_Choice);//Hàm kiểm tra số nguyên và có thuộc các lựa chọn của menu hay không
void CanhLe(int Max);//Lùi đầu dòng Max ký tự ' '
void Text_Giua(string str);//Ghi dòng chữ chính giữa hàng
void Text_Menu(string str);//Ghi các lựa chọn của Menu
void VeHang(int SoKyTu);//In ra hàng ngang cua bảng gồm SoKyTu ký tự '~'
bool Check_Date(string str);

//Các hàm nằm dưới hàm main.
void Menu_Libpro();
void SignIn_User();
void SignUp_User();
void Sign_User_Fail(int what_fail, string str, string fail);
void Write_User(string user_no, string user_name, string mssv, string birth, string job, string email);
bool Check_Infomation_User(int what_check, string str);


class User
{
public:
	string getuser_no()
	{
		string getuser_no;
		CanhLe(2 * MaxKT);	cout << "So thu tu nguoi dung: ";
		getline(cin, getuser_no);
		user_no = getuser_no;
		return getuser_no;
	}
	string getuser_name()
	{
		string getuser_name;
		CanhLe(2 * MaxKT);	cout << "Ho va ten nguoi dung: ";
		getline(cin, getuser_name);
		user_name = getuser_name;
		return getuser_name;
	}
	void setuser(string setuser_no, string setuser_name)
	{
		setuser_name = user_name;
		setuser_no = user_no;
		fstream file;
		file.open("user.txt", ios::out | ios::app);
		file << setuser_no << "; " << setuser_name << endl;
		file.close();
	}


private:
	string user_no;
	string user_name;
};

int main()
{
	Menu_Libpro();

	system("pause");
	return 0;
}


void Menu_Libpro()
{
	int  Choice;
	string SChoice;//String Choice 
	bool Check;
	do
	{
		// In ra Menu Libpro
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO");
		VeHang(MaxCN);
		Text_Menu("1. Dang nhap nguoi dung.");
		Text_Menu("2. Dang ki nguoi dung (cho nguoi quan ly xet duyet).");
		Text_Menu("3. Tim sach.");
		Text_Menu("4. Xem sach.");
		Text_Menu("5. Thoat.");
		VeHang(MaxCN);
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);
		Check = true;
		Check = Check_Choice(SChoice,5);
		stringstream(SChoice) >> Choice;
		if (Check == false)
		{
			cout << setw(MaxKT) << right << " " << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
	} while (Check == false);

	switch (Choice)
	{
	case SignIn_Libpro:
		system("cls");
		SignIn_User();
		break;
	case SignUp_Libpro:
		SignUp_User();
		break;
	case SearchBook_Libpro:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case SeeBook_Libpro:
		CanhLe(MaxKT);	cout << "Chua cap nhat" << endl;
		break;
	case Stop_Libpro:
		break;
	}
}
void SignIn_User()
{
	string user_name, user_no;//String Password User
	bool Check;

	do
	{
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO");
		VeHang(MaxCN);
		Text_Giua("DANG NHAP NGUOI DUNG");
		VeHang(MaxCN);

		User user;
		user_name = user.getuser_name();// Nhập vào tên
		user_no = user.getuser_no();
		Check = true;
		Check = CheckInt(user_no);
		if (Check == false)//Nếu không phải là số nguyên yêu cầu nhập lại
		{
			Sign_User_Fail(SignIn,"So thu tu nhap khong dung dinh dang !!!", "Dang nhap");
			break;
		}
		Check = Check_Infomation_User(USER_NO, user_no);
		if (Check == true)//user_no khong ton tai trong data
		{
			Sign_User_Fail(SignIn,"So thu tu nguoi dung khong co trong du lieu !!!", "Dang nhap");
			break;
		}
		else//User_no ton tai trong data. 
		{
			Check = Check_Infomation_User(USER_NAME, user_name);
			if (Check == true)
			{
				Sign_User_Fail(SignIn, " So thu tu nhap dung nhung ten nguoi dung khong dung !!!", "Dang nhap");
				break;
			}
			else
			{
				cout << "Dang nhap thanh cong" << endl;
				break;
			}
		}
	} while (Check == false);
}


bool Check_Infomation_User(int what_check,string str)
{
	string line;
	bool Check = true;
	fstream file;
	file.open("information_user.txt", ios::in);
	switch (what_check)
	{
	case USER_NAME:
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Doc so thu tu
				getline(file, line);//Doc ten
				if (line == str)
				{
					Check = false;
					break;
				}
			}
		}
		break;
	case USER_NO:
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Doc so thu tu
				int nu_str, nu_line;//number string
				stringstream(str) >> nu_str;
				stringstream(line) >> nu_line;
				if (nu_line == nu_str)
				{
					Check = false;
					break;
				}
			}
		}
		break;
	case MSSV:
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Doc so thu tu
				getline(file, line);//Doc ten
				getline(file, line);//Doc mssv
				int nu_str, nu_line;//number string
				stringstream(str) >> nu_str;
				stringstream(line) >> nu_line;
				if (nu_line == nu_str)
				{
					Check = false;
					break;
				}
			}
		}
		break;
	case EMAIL:
		while (!file.eof())
		{
			getline(file, line);
			if (line == "{")
			{
				getline(file, line);//Doc so thu tu
				getline(file, line);//Doc ten
				getline(file, line);//Doc mssv
				getline(file, line);//Doc Birth
				getline(file, line);//Read Job
				getline(file, line);// Read Email
				if (line == str)
				{
					Check = false;
					break;
				}
			}
		}
		break;
	}
	file.close();
	return Check;
}
void SignUp_User()
{
	string user_name,user_no, Mssv, Birth, Job, Email;
	bool Check;
	User user;

	do
	{
		system("cls");
		VeHang(MaxCN);
		Text_Giua("MENU LIBPRO");
		VeHang(MaxCN);
		Text_Giua("DANG KY NGUOI DUNG");
		VeHang(MaxCN);

		User user;
		Check = true;

		user_name = user.getuser_name();//Họ và tên người dùng
		if (user_name.empty())
		{
			Sign_User_Fail(SignUp,"Day la thong tin bat buoc phai ghi !!!","Dang ki");
			break;
		}

		user_no = user.getuser_no();//Số thứ tự người dùng
		Check = CheckInt(user_no);
		if (Check == false)
		{
			Sign_User_Fail(SignUp, "So thu tu nguoi dung nhap sai !!!", "Dang ki");
			break;
		}
		Check = Check_Infomation_User(USER_NO,user_no);
		if (Check == false)
		{
			Sign_User_Fail(SignUp, "So thu tu nguoi dung da ton tai trong he thong !!!", "Dang ki");
			break;
		}	

		CanhLe(2*MaxKT); cout << "Ma so sinh vien cua nguoi dung: ";//Mã số sinh viên người dùng
		getline(cin, Mssv);
		Check = CheckInt(Mssv);
		if (Check == false)
		{
			Sign_User_Fail(SignUp, "Ma so sinh vien nhap sai !!!", "Dang ki");
			break;
		}
		Check = Check_Infomation_User(MSSV, Mssv);
		if (Check == false)
		{
			Sign_User_Fail(SignUp, "MSSV cua ban da co nguoi dung dang ki !!!", "Dang ki");
			break;
		}

		CanhLe(2*MaxKT); cout << "Ngay, thang, nam sinh (dd-mm-yyyy) : ";//Ngày tháng năm sinh
		getline(cin, Birth);
		Check = Check_Date(Birth);
		if (Check == false)
		{
			Sign_User_Fail(SignUp, "Ngay thang nam sinh nhap khong dung dinh dang !!!", "Dang ki");
			break;
		}

		CanhLe(2*MaxKT); cout << "Nghe nghiep: ";//Nghề nghiệp
		getline(cin, Job);
		if (Job.empty())
		{
			Sign_User_Fail(SignUp, "Day la thong tin bat buoc phai ghi !!!", "Dang ki");
			break;
		}

		CanhLe(2*MaxKT); cout << "Email(@gmail.com, @gmail.com.vn, @yahoo.com, @hcmut.edu.vn): ";//Email
		getline(cin, Email);
		if (Email.empty())
		{
			Sign_User_Fail(SignUp, "Day la thong tin bat buoc phai ghi !!!", "Dang ki");
			break;
		}
		int x = Email.rfind("@");
		string str = Email.substr(x, Email.length() - x);
		if (str != "@gmail.com" && str != "@gmail.com.vn" && str != "@hcmut.edu.vn"&&str != "@yahoo.com")
		{
			Check = false;
			Sign_User_Fail(SignUp, "Email nhap khong dung dinh dang !!!", "Dang ki");
			break;
		}
		Check = Check_Infomation_User(EMAIL, Email);
		if (Check == false)
		{
			Sign_User_Fail(SignUp, "Email cua ban da co nguoi dung dang ki !!!", "Dang ki");
			break;
		}

		user.setuser(user_no, user_name);
		Write_User(user_no, user_name, Mssv, Birth, Job, Email);
	} while (Check == false);
}

void Write_User(string user_no, string user_name,string mssv,string birth,string job,string email)
{
	fstream file;
	file.open("information_user.txt", ios::out | ios::app);
	file << "{\n" << user_no << "\n" << user_name << "\n" << mssv
		<< "\n" << birth << "\n" << job << "\n" << email << "\n}" << endl;
	file.close();
}
void Sign_User_Fail(int what_fail,string str,string fail)
{
	int  Choice;
	string  SChoice;//String Choice 
	bool Check;
	do
	{
		//In ra Menu va chon
		CanhLe(MaxKT);	cout << str << endl;
		CanhLe(2 * MaxKT);	cout << "1. "<< fail <<" lai.\n";
		CanhLe(2 * MaxKT);	cout << "2. Tro lai.\n";
		CanhLe(MaxKT);	cout << "Lua chon cua ban: ";
		getline(cin, SChoice);

		Check = true;
		Check = Check_Choice(SChoice, 2);
		stringstream(SChoice) >> Choice;

		if (Check == false)// Nếu kiểm tra biến nhập vào ko phù hợp thì yêu cầu nhập lại
		{
			CanhLe(MaxKT);	cout << "Ban da nhap sai. Moi ban nhap lai !\n ";
			system("pause");
			system("cls");
			continue;
		}
		else if (Choice == 1)
		{
			system("cls");
			switch (what_fail)
			{
			case SignIn:
				SignIn_User();
				break;
			case SignUp:
				SignUp_User();
				break;
			}
			
		}
		else if (Choice == 2)//Trở lại Menu Libpro
		{
			system("cls");
			Menu_Libpro();
			break;
		}
	} while (Check == false);
}
