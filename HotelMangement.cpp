#include<iostream>
using namespace std;
#include<string>

enum Type { luxury, standard, ordinary };
enum Status { used, reserved, empty1 };
struct Time {
    int year;
    int month;
    int day;
};

class room {
public:
    room(int roomNo, Type roomType) {
        roomID = roomNo;
        type = roomType;
        roomStatus = empty1;
        if (type == luxury) {
            price = 400;
            name = "豪华间";
        }
        else if (type == standard) {
            price = 200;
            name = "标准间";
        }
        else if (type == ordinary) {
            price = 100;
            name = "普通间";
        }
    };
    room() {};
    //显示房间当前信息
    void showInformation() {
        cout << "房间号：" << roomID << endl;
        cout << "类型：" << name << endl;
        if(roomStatus == 0)
            cout << "当前状态：有客" <<endl;
        else if(roomStatus == 1)
            cout << "当前状态：已被预约" << endl;
        else
            cout << "当前状态：空房间" << endl;
        cout << endl;

    }
    //办理入住
    void checkIn(Time beginTime, Time endTime) {
        this->begin = beginTime;
        this->end = endTime;
        this->roomStatus = used;
    }
    void roomReserved(Time beginTime, Time endTime) {
        roomStatus = reserved;
        begin = beginTime;
        end = endTime;
    };
    //办理退房
    float checkOut() {
        roomStatus = empty1;
        int day = (end.year - begin.year) * 365 + (end.month - begin.month) * 30 + (end.day - begin.day);
        float polity;
        if (day > 2 && day <= 4) {
            polity = polity1;
        }
        else if (day >= 5 && day <= 8) {
            polity = polity2;
        }
        else if (day >= 9) {
            polity = polity3;
        }
        else {
            polity = 1;
        }
        float money = ((end.year - begin.year) * 365 + (end.month - begin.month) * 30 + (end.day - begin.day))*price*polity;
        return money;
    }
    int showstatus() {
        return roomStatus;
    }
    int getRno(){
        return roomID;
    }
    void setPolity(float a, float b, float c) {
        polity1 = a;
        polity2 = b;
        polity3 = c;        
    }
    int getRoomnumber() {
        return roomnumber;
    }
    friend class manager;
    friend class reception;
private:
    int roomID;
    static float polity1;
    static float polity2;
    static float polity3;
    static int roomnumber;
    Type type;
    string name;
    float price;
    Status roomStatus;
    Time begin;
    Time end;
};

class manager {
public:
    manager() {};
    room roomcreate(int No, Type roomtype) {
        room Room(No, roomtype);
        Room.roomnumber++;
        return Room;
    }
    void checkInformation(room Room) {
        Room.showInformation();
    }
    void setPolity() {
        room Room1;
        float a, b, c;
        cout << "请分别设置入住2-4天，5-8天或9天以上的优惠政策，用1以内小数表示打折力度" << endl;
        cin >> a >> b >> c;
        Room1.setPolity(a, b, c);
        cout << "设置成功" << endl;
    };
};

class reception {
public:
    reception(int no) {
        NO = no;
    }
    void checkInformation(room Room) {
        Room.showInformation();
    }
    room CheckIn(Time begin, Time end, room Room) {
        if (Room.showstatus() == empty1) {
            Room.checkIn(begin, end);
            cout << "预定成功！时间：" << begin.year << "年" << begin.month << "月" << begin.day << "日---" << end.year << "年" << end.month << "月" << end.day << "日" << endl;
            int day = (end.year - begin.year) * 365 + (end.month - begin.month) * 30 + (end.day - begin.day);
            if (day > 2 && day <= 4) {
                polity = Room.polity1;
            }
            else if (day >= 5 && day <= 8) {
                polity = Room.polity2;
            }
            else if (day >= 9) {
                polity = Room.polity3;
            }
            else {
                polity = 1;
            }
            if (polity < 1)
                cout << "优惠打" << polity * 10 << "折" << endl;
        }
        else {
            cout << "房间已经被预定，请选择其他房间" << endl;
        }
        return Room;
    }
    int getID() {
        return NO;
    }
    room CheckOut(room Room) {
        float money = Room.checkOut();
        cout << "退房成功" << endl;
        cout << "请支付：" << money << "元"<<endl;
        return Room;
    }
    room Reserved(Time begin, Time end, room Room) {
        if (Room.showstatus() == empty1) {
            Room.roomReserved(begin, end);
            cout << "预定成功！时间：" << begin.year << "年" << begin.month << "月" << begin.year << "日---" << end.year << "年" << end.month << "月" << end.day << "日" << endl;
            int day = (end.year - begin.year) * 365 + (end.month - begin.month) * 30 + (end.day - begin.day);
            if (day > 2 && day <= 4) {
                polity = Room.polity1;
            }
            else if (day >= 5 && day <= 8) {
                polity = Room.polity2;
            }
            else if (day >= 9) {
                polity = Room.polity3;
            }
            else {
                polity = 1;
            }
            if (polity < 1)
                cout << "优惠打" << polity * 10 << "折" << endl;
        }
        else {
            cout << "房间已经被预定，请选择其他房间" << endl;
        }
        return Room;
    }
private:
    int NO;
    float polity;
};

class customer {
public:
    customer(){}
    customer(int Count, int Key) {
        count = Count;
        key = Key;
        customernumber++;
        cout << "注册成功！" << endl;
    }
    void signin() {};
    void checkin(reception rec, Time begin, Time end, room Room) {
        rec.CheckIn(begin, end, Room);
    }
    void reserve(reception rec, Time begin, Time end, room Room) {
        rec.Reserved(begin, end, Room);
    }
    void  checkout(reception rec, room Room) {
        rec.CheckOut(Room);
    }
    int getnumber() {
        return customernumber;
    }
    int getcount() {
        return count;
    }
    int getkey() {
        return key;
    }
private:
    int count;
    int key;
    static int customernumber;
};
int room::roomnumber = 0;
int customer::customernumber = 0;
float room::polity1 = 1;
float room::polity2 = 1;
float room::polity3 = 1;
int main() {

    int user;
    int rightkey = 123;
    manager jasur;
    reception wmn(1);
    room Baseroom;
    room Room[40];
    customer Customer[40];
    customer baseCusomer;
    string comments[40];

    while (true) {
        cout << "欢迎来到酒店预订系统，请问你是？" << endl;
        cout << "1.管理员  2.前台   3.客户" << endl;
        cout << "请输入：" << endl;
        cin >> user;
        if (user == 1) {    //管理员选项
            cout << "请输入管理员密码：" << endl;
            int key;
            cin >> key;
            if (rightkey == key) {
                cout << "欢迎来到管理员平台欢迎您！" << endl;
                while (true) {
                    cout << "1.查询入住情况   2.设置客房优惠  3.创建房间  0.退出" << endl;
                    int selection;
                    cout << "请输入：" << endl;
                    cin >> selection;
                    if (selection == 1) {
                        for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                            jasur.checkInformation(Room[i + 1]);
                        }
                    }
                    else if (selection == 2) {
                        jasur.setPolity();
                    }
                    else if (selection == 3) {
                        int entry, Rno;
                        cout << "输入创建房间的房间号和类型（1代表豪华间，2代表标准间，3代表普通间）" << endl;
                        cin >> Rno >> entry;
                        if (entry == 1)
                            Room[Baseroom.getRoomnumber()] = jasur.roomcreate(Rno, luxury);
                        else if (entry == 2)
                            Room[Baseroom.getRoomnumber()] = jasur.roomcreate(Rno, standard);
                        else if (entry == 3)
                            Room[Baseroom.getRoomnumber()] = jasur.roomcreate(Rno, ordinary);
                        cout << "操作成功" << endl << endl;
                    }
                    else if (selection == 0) {
                        break;
                    }
                }
            }
        }
        else if (user == 2) {
            cout << "欢迎来到前台服务平台" << endl;
            while (true) {
                fuwu:
                cout << wmn.getID() << "号服务员为您服务，本平台为您提供了如下功能：1.查询客房信息  2.办理入住  3.提前预约  4.办理退房  0.退出" << endl;
                cout << "请选择需要的服务" << endl;
                int selection;
                cin >> selection;
                if (selection == 1) {
                    cout << "客房信息如下：" << endl;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        wmn.checkInformation(Room[i + 1]);
                    }
                }
                else if (selection == 2) {
                    Time begin, end;
                    int Rno, index;
                    cout << "输入客户入住时间：";
                    cin >> begin.year >> begin.month >> begin.day;
                    cout << "输入客户离开时间：";
                    cin >> end.year >> end.month >> end.day;
                    cout << "客房信息如下：" << endl;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        wmn.checkInformation(Room[i + 1]);
                    }
                    cout << "请输入入住客房号：";
                    cin >> Rno;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        if (Room[i + 1].getRno() == Rno) {
                            index = i + 1;
                        }
                    }
                    Room[index] = wmn.CheckIn(begin, end, Room[index]);

                }
                else if (selection == 3) {
                    Time begin, end;
                    int Rno, index;
                    cout << "输入客户入住时间：";
                    cin >> begin.year >> begin.month >> begin.day;
                    cout << "输入客户离开时间：";
                    cin >> end.year >> end.month >> end.day;
                    cout << "客房信息如下：" << endl;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        wmn.checkInformation(Room[i + 1]);
                    }
                    cout << "请输入预约客房号：";
                    cin >> Rno;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        if (Room[i + 1].getRno() == Rno) {
                            index = i + 1;
                        }
                    }
                    Room[index] = wmn.Reserved(begin, end, Room[index]);
                }
                else if (selection == 4) {
                    int Rno,index;
                    cout << "请输入退房房间号：";
                    cin >> Rno;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        if (Room[i + 1].getRno() == Rno) {
                            index = i + 1;
                        }
                    }
                    Room[index] = wmn.CheckOut(Room[index]);
                    cout << "欢迎留言评论您的体验：" << endl;
                    cin >> comments[index];
                }
                else if (selection == 0) {
                    break;
                }
            }
        }
        else if (user == 3) {
            cout << "用户你好，欢迎您来到本酒店" << endl;
            while (true) {
                cout << "请问您有本平台的账号吗？没有可以注册一个哦！" << endl;
                cout << "1.我已经有账号了    2.注册     0.退出" << endl;
                int selection;
                cin >> selection;
                if (selection == 1) {
                    int count, key, rightcount, index = -1;
                x:
                    cout << "请输入账号：" << endl;
                    cin >> count;
                    for (int i = 0; i < baseCusomer.getnumber(); i++) {
                        if (Customer[i].getcount() == count) {
                            index = i;
                        }
                    }
                    if (index == -1) {
                        cout << "不存在此账号" << endl;
                        goto x;
                    }
                y:
                    cout << "请输入密码：";
                    cin >> key;
                    for (int i = 0; i < baseCusomer.getnumber(); i++) {
                        if (Customer[index].getkey() == key) {
                            cout << "登录成功！" << endl;
                            goto fuwu;
                        }
                        else {
                            cout << "密码错误！" << endl;
                            goto y;
                        }
                    }
                }
                else if (selection == 2) {
                    int count, key, virity;
                    cout << "请输入注册账号：";
                    cin >> count;
                    cout << endl;
                a:
                    cout << "请设置密码：";
                    cin >> key;
                    cout << "请确认密码：";
                    cin >> virity;
                    if (key == virity) {
                        customer base(count, key);
                        Customer[baseCusomer.getnumber() - 1] = base;
                    }
                    else {
                        cout << "两次密码不相等，重新输入" << endl;
                        goto a;
                    }

                }
                else if (selection == 0) {
                    break;
                }

            }
        }
        else {
            cout << "无效的选择，重新选择！";
        }
    }

    return 0;
}

