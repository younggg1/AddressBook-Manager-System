#include <iostream>

#include <fstream>
using namespace std;


#include "txlmanager.h"
int main() {
    
    bool flag = true;
    while (flag){
        showLogin();
        int loginChoice;
        cin>>loginChoice;
        if (loginChoice==0){
            break;
        } else{
            switch (loginChoice) {
                case 0:break;
                case 1:
                    if (loginUser()){
                        selectLogin();
                        flag=false;
                        break;
                    } else{
                        cout << "登录失败\n";
                    }
                    break;
                case 2:addUser();
                    break;

            }
        }

    }








    return 0;
}
