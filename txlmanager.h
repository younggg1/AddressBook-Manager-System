#include <iostream>
#include "string.h"
#include <fstream>
using namespace std;
#define MAX 1000
#ifndef TXLMANAGER_TXLMANAGER_H
#define TXLMANAGER_TXLMANAGER_H

#endif //TXLMANAGER_TXLMANAGER_H
//联系人结构体
struct Person {
    string Name;
    int Age;
    int Sex;
    string Phone;
    string Addr;
};
//存放联系人通讯录结构体
struct AddressBook {
    struct Person PersonArray[MAX]; //通讯录当前保存的联系人数组
    int Size; //通讯录当前记录联系人个数
};
struct User {
    string username;
    string password;
};

//显示菜单
void showMenu() {
    cout << "***** " << "1.添加联系人" << " *****" << endl;
    cout << "***** " << "2.显示联系人" << " *****" << endl;
    cout << "***** " << "3.删除联系人" << " *****" << endl;
    cout << "***** " << "4.查找联系人" << " *****" << endl;
    cout << "***** " << "5.修改联系人" << " *****" << endl;
    cout << "***** " << "6.清空联系人" << " *****" << endl;
    cout << "***** " << " 7-删除用户" << "  *****" << endl;
    cout << "***** " << "0.退出通讯录" << " *****" << endl;
    cout << "**** ************ ****" << endl;
}

//登录显示菜单
void showLogin(){
    cout << "***** " << "1-用户登录" << " *****" << endl;
    cout << "***** " << "2-创建用户" << " *****" << endl;
    cout << "*****  " << "0-退出" << "  *****" << endl;
}


bool loginUser() {
    string username, password;
    cout << "输入用户名: ";
    cin >> username;
   cout << "输入密码: ";
    cin >> password;

    ifstream inFile("..\\UserData.txt");
    if (inFile.is_open()) {
        string fileUsername, filePassword;
        while (inFile >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                inFile.close();
                cout << "登陆成功\n";

                return true;
            }
        }
        inFile.close();
        cout << "用户名或密码错误\n";
        return false;
    } else {
        std::cerr << "未能读取文件\n";
        return false;
    }
}

void addUser() {
    User user;
    cout << "输入用户名: ";
    cin >> user.username;
    cout << "输入密码: ";
    cin >> user.password;

    ofstream outFile("..\\UserData.txt", ios::out | ios::app);
    if (outFile.is_open()) {
        outFile << user.username << " " << user.password << "\n";
        outFile.close();
        cout << "创建成功\n";
    } else {
        cerr << "创建失败.\n";
    }
}

void deleteUser() {
        cout <<"输入要删除的用户名:";
        string username;
        cin >> username;
        ifstream inFile("..\\UserData.txt");
        ofstream outFile("..\\temp.txt");
        bool userDeleted = false;
        if (inFile.is_open() && outFile.is_open()) {
            string fileUsername, filePassword;
            while (inFile >> fileUsername >> filePassword) {
                if (fileUsername == username) {
                    userDeleted = true; // 标记用户已删除
                    break;
                } else {
                    outFile << fileUsername << " " << filePassword << "\n";
                }
            }
            inFile.close();
            outFile.close();

            remove("..\\UserData.txt"); // 删除原文件
            rename("..\\temp.txt", "..\\UserData.txt"); // 重命名临时文件

            if (userDeleted) {
                cout << "删除成功\n";
            } else {
                cout << "用户不存在\n";
            }
        } else {
            cerr << "未能读取文件\n";
        }


}



//添加联系人
void addPerson(AddressBook *abs) {
//    判断是否满人
    if (abs->Size == MAX) {
        cout << "通讯录已满，无法添加" << endl;
        return;
    } else {
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        abs->PersonArray[abs->Size].Name = name;
        cout << "请输入年龄：" << endl;
        int age = 0;
        //        限制错误年龄输入
        while (true) {
            cin >> age;
            if (age > 0 && age < 150) {
                abs->PersonArray[abs->Size].Age = age;
                break;
            } else {
                cout << "输入有误，请重新输入" << endl;
            }
        };
        abs->PersonArray[abs->Size].Age = age;
        cout << "请输入性别：" << endl;
        cout << "1---男" << endl;
        cout << "2---女" << endl;
        char sex;
//        限制错误输入
        while (true) {
            cin >> sex;
            if (sex == '1' || sex == '2') {
                abs->PersonArray[abs->Size].Sex = sex;
                break;
            } else {
                cout << "输入有误，请重新输入" << endl;
            }
        };
        cout << "请输入电话：" << endl;
        string phone;
        cin >> phone;
        abs->PersonArray[abs->Size].Phone = phone;
        cout << "请输入地址：" << endl;
        string address;
        cin >> address;
        abs->PersonArray[abs->Size].Addr = address;
        abs->Size++; //更新通讯录人数
        cout << "添加成功" << endl;
//        system("pause");//请按任意键继续
//        system("cls");//清屏操作
    }

}

//显示所有联系人信息
void showPerson(AddressBook *abs) {
//    判断通讯录里的人数
    if (abs->Size == 0) {
        cout << "联系人为空" << endl;
        return;
    } else {
        for (int i = 0; i < abs->Size; i++) {
            cout << "姓名:" << abs->PersonArray[i].Name << "\t";
            cout << "年龄:" << abs->PersonArray[i].Age << "\t";
            cout << "性别:" << (abs->PersonArray[i].Sex == 1 ? "女" : "男") << "\t";
            cout << "电话:" << abs->PersonArray[i].Phone << "\t";
            cout << "住址:" << abs->PersonArray[i].Addr << endl;


        }
    }
    //        system("pause");//请按任意键继续
//        system("cls");//清屏操作

}

//检测联系人是否存在，存在就返回所在位置，不存在返回-1
int isExist(AddressBook *abs, string name) {
    for (int i = 0; i < abs->Size; i++) {
//        找到用户输入姓名
        if (abs->PersonArray[i].Name == name) {
            return i;
        }
    }
    return -1;
}

//删除指定联系人
void deletePerson(AddressBook *abs) {
    cout << "请输入要删除联系人的姓名" << endl;
    string name;
    cin >> name;
    int ret = isExist(abs, name);
    if (ret != -1) {
        // 删除操作
        for (int i = ret; i < abs->Size; ++i) {
            abs->PersonArray[i] = abs->PersonArray[i + 1]; //数据前移
            abs->Size--; //更新通讯录中的人员数
            cout << "删除成功" << endl;
            // system("pause");//请按任意键继续
            //system("cls");//清屏操作
        }
    } else {
        cout << "联系人不存在" << endl;
        // system("pause");//请按任意键继续
        // system("cls");//清屏操作
    }

}

//查找指定联系人信息
void findPerson(AddressBook *abs) {
    cout << "请输入你要查找的联系人" << endl;
    string name;
    cin >> name;
//    判断指定联系人是否存在
    int ret = isExist(abs, name);
    if (ret != -1) {//找的的情况
        cout << "找到联系人" << "\t";
        cout << "姓名:" << abs->PersonArray[ret].Name << "\t";
        cout << "年龄:" << abs->PersonArray[ret].Age << "\t";
        cout << "性别:" << abs->PersonArray[ret].Sex << "\t";
        cout << "电话:" << abs->PersonArray[ret].Phone << "\t";
        cout << "住址:" << abs->PersonArray[ret].Addr << endl;
    } else {
        cout << "联系人不存在" << endl;
        // system("pause");//请按任意键继续
        // system("cls");//清屏操作
    }
}

void showModifyMenu() {
    cout << "1-姓名:" << "\t";
    cout << "2-年龄:" << "\t";
    cout << "3-性别:" << "\t";
    cout << "4-电话:" << "\t";
    cout << "5-住址:" << endl;
}

//修改指定联系人信息
void modifyPerson(AddressBook *abs) {
    cout << "请输入你要修改的联系人" << endl;
    string name;
    cin >> name;
//    判断指定联系人是否存在
    int ret = isExist(abs, name);
    if (ret != -1) {//找的的情况
//        通过无限循环可选择重复修改单项或退出当前
        for (;;) {
            cout << "请选择需要修改的信息 0退出当前界面" << endl;
            showModifyMenu();
            int Cmodify;
            cin >> Cmodify;
            if (Cmodify == 0) {
                break;
            } else {
                switch (Cmodify) {
                    case 1:
//                添加联系人
                    {
                        string name;
                        cout << "请输入姓名：" << endl;
                        cin >> name;
                        abs->PersonArray[ret].Name = name;
                    }
                        cout << "修改成功" << endl;
                        break;
                    case 2: {
                        cout << "请输入年龄：" << endl;
                        int age = 0;
                        //        限制错误年龄输入
                        while (true) {
                            cin >> age;
                            if (age > 0 && age < 150) {
                                abs->PersonArray[abs->Size].Age = age;
                                break;
                            } else {
                                cout << "输入有误，请重新输入" << endl;
                            }
                        };
                        abs->PersonArray[ret].Age = age;
                    }//    展示联系人
                        cout << "修改成功" << endl;
                        break;
                    case 3: {
                        cout << "请输入性别：" << endl;
                        cout << "1---男" << endl;
                        cout << "2---女" << endl;
                        char sex;
//        限制错误输入
                        while (true) {
                            cin >> sex;
                            if (sex == '1' || sex == '2') {
                                abs->PersonArray[ret].Sex = sex;
                                break;
                            } else {
                                cout << "输入有误，请重新输入" << endl;
                            }
                        };
                    }
                        cout << "修改成功" << endl;
                        break;
                    case 4: {
                        cout << "请输入电话：" << endl;
                        string phone;
                        cin >> phone;
                        abs->PersonArray[ret].Phone = phone;
                        cout << "修改成功" << endl;
                    }
                        break;
                    case 5: {
                        cout << "请输入地址：" << endl;
                        string address;
                        cin >> address;
                        abs->PersonArray[ret].Addr = address;
                        cout << "修改成功" << endl;
                    }
                        break;
                }
            }


        }
    } else {
        cout << "联系人不存在" << endl;
        // system("pause");//请按任意键继续
        // system("cls");//清屏操作
    }
}
//清空所有联系人
void cleanPerson(AddressBook *abs){
    abs->Size = 0;
    cout<< "通讯录已清空" << endl;
    // system("pause");//请按任意键继续
    // system("cls");//清屏操作
}


//登录成功后展示
void selectLogin(){
    //    创建选择变量
    int select = 0;
    bool flag = true;
    AddressBook abs; //创建通讯录结构体变量
    abs.Size = 0; //初始化通讯录当前人员个数
    while (flag) {
        //    菜单调用
        showMenu();
        cin >> select;

        switch (select) {
            case 1:
//                添加联系人
                addPerson(&abs);
                break;
            case 2:
                showPerson(&abs);//    展示联系人
                break;
            case 3:
                deletePerson(&abs);
                break;
            case 4:
                findPerson(&abs);
                break;
            case 5:
                modifyPerson(&abs);
                break;
            case 6:
                cleanPerson(&abs);
                break;
            case 7:deleteUser();
                break;
            case 0:
                flag = false;
                cout << "欢迎下次使用" << endl;
                break;
            default:
               cout << "没有这个选项\n";
        }
    }


}