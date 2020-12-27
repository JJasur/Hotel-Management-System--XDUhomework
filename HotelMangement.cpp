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
            name = "������";
        }
        else if (type == standard) {
            price = 200;
            name = "��׼��";
        }
        else if (type == ordinary) {
            price = 100;
            name = "��ͨ��";
        }
    };
    room() {};
    //��ʾ���䵱ǰ��Ϣ
    void showInformation() {
        cout << "����ţ�" << roomID << endl;
        cout << "���ͣ�" << name << endl;
        if(roomStatus == 0)
            cout << "��ǰ״̬���п�" <<endl;
        else if(roomStatus == 1)
            cout << "��ǰ״̬���ѱ�ԤԼ" << endl;
        else
            cout << "��ǰ״̬���շ���" << endl;
        cout << endl;

    }
    //������ס
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
    //�����˷�
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
        cout << "��ֱ�������ס2-4�죬5-8���9�����ϵ��Ż����ߣ���1����С����ʾ��������" << endl;
        cin >> a >> b >> c;
        Room1.setPolity(a, b, c);
        cout << "���óɹ�" << endl;
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
            cout << "Ԥ���ɹ���ʱ�䣺" << begin.year << "��" << begin.month << "��" << begin.day << "��---" << end.year << "��" << end.month << "��" << end.day << "��" << endl;
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
                cout << "�Żݴ�" << polity * 10 << "��" << endl;
        }
        else {
            cout << "�����Ѿ���Ԥ������ѡ����������" << endl;
        }
        return Room;
    }
    int getID() {
        return NO;
    }
    room CheckOut(room Room) {
        float money = Room.checkOut();
        cout << "�˷��ɹ�" << endl;
        cout << "��֧����" << money << "Ԫ"<<endl;
        return Room;
    }
    room Reserved(Time begin, Time end, room Room) {
        if (Room.showstatus() == empty1) {
            Room.roomReserved(begin, end);
            cout << "Ԥ���ɹ���ʱ�䣺" << begin.year << "��" << begin.month << "��" << begin.year << "��---" << end.year << "��" << end.month << "��" << end.day << "��" << endl;
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
                cout << "�Żݴ�" << polity * 10 << "��" << endl;
        }
        else {
            cout << "�����Ѿ���Ԥ������ѡ����������" << endl;
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
        cout << "ע��ɹ���" << endl;
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
        cout << "��ӭ�����Ƶ�Ԥ��ϵͳ���������ǣ�" << endl;
        cout << "1.����Ա  2.ǰ̨   3.�ͻ�" << endl;
        cout << "�����룺" << endl;
        cin >> user;
        if (user == 1) {    //����Աѡ��
            cout << "���������Ա���룺" << endl;
            int key;
            cin >> key;
            if (rightkey == key) {
                cout << "��ӭ��������Աƽ̨��ӭ����" << endl;
                while (true) {
                    cout << "1.��ѯ��ס���   2.���ÿͷ��Ż�  3.��������  0.�˳�" << endl;
                    int selection;
                    cout << "�����룺" << endl;
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
                        cout << "���봴������ķ���ź����ͣ�1��������䣬2�����׼�䣬3������ͨ�䣩" << endl;
                        cin >> Rno >> entry;
                        if (entry == 1)
                            Room[Baseroom.getRoomnumber()] = jasur.roomcreate(Rno, luxury);
                        else if (entry == 2)
                            Room[Baseroom.getRoomnumber()] = jasur.roomcreate(Rno, standard);
                        else if (entry == 3)
                            Room[Baseroom.getRoomnumber()] = jasur.roomcreate(Rno, ordinary);
                        cout << "�����ɹ�" << endl << endl;
                    }
                    else if (selection == 0) {
                        break;
                    }
                }
            }
        }
        else if (user == 2) {
            cout << "��ӭ����ǰ̨����ƽ̨" << endl;
            while (true) {
                fuwu:
                cout << wmn.getID() << "�ŷ���ԱΪ�����񣬱�ƽ̨Ϊ���ṩ�����¹��ܣ�1.��ѯ�ͷ���Ϣ  2.������ס  3.��ǰԤԼ  4.�����˷�  0.�˳�" << endl;
                cout << "��ѡ����Ҫ�ķ���" << endl;
                int selection;
                cin >> selection;
                if (selection == 1) {
                    cout << "�ͷ���Ϣ���£�" << endl;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        wmn.checkInformation(Room[i + 1]);
                    }
                }
                else if (selection == 2) {
                    Time begin, end;
                    int Rno, index;
                    cout << "����ͻ���סʱ�䣺";
                    cin >> begin.year >> begin.month >> begin.day;
                    cout << "����ͻ��뿪ʱ�䣺";
                    cin >> end.year >> end.month >> end.day;
                    cout << "�ͷ���Ϣ���£�" << endl;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        wmn.checkInformation(Room[i + 1]);
                    }
                    cout << "��������ס�ͷ��ţ�";
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
                    cout << "����ͻ���סʱ�䣺";
                    cin >> begin.year >> begin.month >> begin.day;
                    cout << "����ͻ��뿪ʱ�䣺";
                    cin >> end.year >> end.month >> end.day;
                    cout << "�ͷ���Ϣ���£�" << endl;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        wmn.checkInformation(Room[i + 1]);
                    }
                    cout << "������ԤԼ�ͷ��ţ�";
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
                    cout << "�������˷�����ţ�";
                    cin >> Rno;
                    for (int i = 0; i < Baseroom.getRoomnumber(); i++) {
                        if (Room[i + 1].getRno() == Rno) {
                            index = i + 1;
                        }
                    }
                    Room[index] = wmn.CheckOut(Room[index]);
                    cout << "��ӭ���������������飺" << endl;
                    cin >> comments[index];
                }
                else if (selection == 0) {
                    break;
                }
            }
        }
        else if (user == 3) {
            cout << "�û���ã���ӭ���������Ƶ�" << endl;
            while (true) {
                cout << "�������б�ƽ̨���˺���û�п���ע��һ��Ŷ��" << endl;
                cout << "1.���Ѿ����˺���    2.ע��     0.�˳�" << endl;
                int selection;
                cin >> selection;
                if (selection == 1) {
                    int count, key, rightcount, index = -1;
                x:
                    cout << "�������˺ţ�" << endl;
                    cin >> count;
                    for (int i = 0; i < baseCusomer.getnumber(); i++) {
                        if (Customer[i].getcount() == count) {
                            index = i;
                        }
                    }
                    if (index == -1) {
                        cout << "�����ڴ��˺�" << endl;
                        goto x;
                    }
                y:
                    cout << "���������룺";
                    cin >> key;
                    for (int i = 0; i < baseCusomer.getnumber(); i++) {
                        if (Customer[index].getkey() == key) {
                            cout << "��¼�ɹ���" << endl;
                            goto fuwu;
                        }
                        else {
                            cout << "�������" << endl;
                            goto y;
                        }
                    }
                }
                else if (selection == 2) {
                    int count, key, virity;
                    cout << "������ע���˺ţ�";
                    cin >> count;
                    cout << endl;
                a:
                    cout << "���������룺";
                    cin >> key;
                    cout << "��ȷ�����룺";
                    cin >> virity;
                    if (key == virity) {
                        customer base(count, key);
                        Customer[baseCusomer.getnumber() - 1] = base;
                    }
                    else {
                        cout << "�������벻��ȣ���������" << endl;
                        goto a;
                    }

                }
                else if (selection == 0) {
                    break;
                }

            }
        }
        else {
            cout << "��Ч��ѡ������ѡ��";
        }
    }

    return 0;
}

