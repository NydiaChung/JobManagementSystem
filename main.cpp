#include <iostream>
#include <fstream>//�ļ��������
#include<iomanip>//���������ʽ
#include<string>
#include<time.h>//ʱ�����
using namespace std;
//��ҵ��
class Book
{
protected:
    string code,name,author,press,time;
    int deadline;//�ύ����
    bool Is_Submit;//��ҵ�Ƿ��ύ
public:
    bool Is_teacher;
    static int Book_Number;
    Book(string c,string n,string a,string p,double pr)
    {
        code=c;name=n;Is_Submit=0;Book_Number++;
    };
    Book(){Is_Submit=false;}
    string Gettime(){return time;}
    string GetCode(){return code;}
    string GetName(){return name;}

    int GetDeadline(){return deadline;}

    bool GetIs_Submit(){return Is_Submit;}
    void SetDeadline(int);
    void SetTime(string);
    void SetIs_Submit(bool);
    void SetCode(string);
    void SetName(string);
    void Display();
    friend const std::string getCurrentSystemTime();//��ȡ���ڵ�ʱ��
    friend istream& operator >> (istream &stream,Book &b);//���ز�����>>
    friend ostream& operator << (ostream &stream,Book &b);//���ز�����<<
};
ostream &operator << (ostream &stream,Book &b)
{
    stream<<"���"<<setw(9)<<b.code<<" ��ҵ��:"<<setw(9)<<b.name<<endl;
    return stream;
}
istream &operator >> (istream &stream,Book &b)
{
    cout<<"��������:";
    stream>>b.code;
    cout<<"��������ҵ��:";
    return stream;
}
//��ȡϵͳ��ǰʱ��ĺ���.
const string getCurrentSystemTime()
{
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);//תΪʱ��ṹ��
    char date[60] = {0};
    sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
            (int)lt->tm_year + 1900,(int)lt->tm_mon + 1,(int)lt->tm_mday,
            (int)lt->tm_hour,(int)lt->tm_min,(int)lt->tm_sec);
    return string(date);
}
void Book::SetDeadline(int a){deadline =a;}
void Book::SetTime(string a){time =a;}
void Book::SetIs_Submit(bool a){Is_Submit =a;}
void Book::Display()//����չʾ��ƷҲ�ύ���
{
    cout<<"���"<<setw(9)<<GetCode()<<" ��ҵ��:"<<setw(9)
    <<GetName()<<" ����ʱ��:"<<setw(10)<<Gettime()
    <<" �ύ����:"<<GetDeadline()<<"��"<<endl;
}
void Book::SetCode(string code1)
{code=code1;}
void Book::SetName(string name1)
{name=name1;}

int Book::Book_Number=0;

static string LogName;//��¼��ǰ��½�û����û���
//�û���
class User
{
protected:
    string name;//�û�����
    string key;//�û�����
    bool Is_Admin,Is_XueWei,Is_Student;//ʲô�û�����
public:
    void key_change(User *U);//�޸��û�����
    int  Judge();//�ж��û�����
    static int User_Number;
    User(){Is_Admin=0;Is_XueWei=0;Is_Student=1;};//Ĭ��ѧ������
    void Setname(string name1);
    void Setkey(string key1);
    void SetIdentity(bool ad,bool li,bool re )//�����û�����
    {Is_Admin=ad;Is_Student=re;Is_XueWei=li;}
    string Getname(){return name;}
    string Getkey(){return key;}
    bool GetisAd(){return Is_Admin;}
    bool Getisli(){return Is_XueWei;}
    bool Getisre(){return Is_Student;}
};
void User::key_change(User *U)
{
    int find=0;string key,key1;
    for(int i=0;i<User::User_Number;i++)
    {
        if(U[i].Getname()==LogName)
        {
            find=i;break;
        }
    }
    cout<<"������ԭ����:";
    cin>>key;
    if(key==U[find].Getkey())
    {
        cout<<"������������:";
        cin>>key;
        cout<<"������һ��������:";
        cin>>key1;
        if(key==key1)
        {
            U[find].Setkey(key);
            cout<<"�޸ĳɹ���"<<endl;
        }
        else
        {
            cout<<"�����������벻һ��,�޸�ʧ��!"<<endl;
        }
    }
    else
    {
        cout<<"�������"<<endl;
    }
}
int User::Judge()
{
    if(Is_XueWei==1)return 5;
    else if(Is_Admin==1)return 6;
    else return 7;
};
void User::Setname(string name1)
{
    name=name1;
};
void User::Setkey(string key1)
{
    key=key1;
};

int User::User_Number=0;
class Log
{
public:
    User tp;//�洢��½�ɹ����û�����Ϣ
    int number;//�洢��ǰ�û���Ϣ��Ӧ��User�����±�ֵ
    void Login(User *p);//��½
    void SignIN(User *p);//ע��
    Log(){number=0;};
    bool Is_Log;//�ж��Ƿ��½�ɹ���
};

void Log::SignIN(User *p)
{
    int f1;string a,b,bb;
    while(1)
    {
        f1=1;
        cout<<"�������û�����";
        cin>>a;
        for(int i=0;i<=User::User_Number;i++)
        {
            if(p[i].Getname()==a)
            {
                cout<<"�û����Ѵ��ڣ�����������."<<endl;f1=0;
            }
        }
        if(f1==0){};
        if(f1==1) {break;}
    }
    while(1)
    {
        cout<<"����������:";
        cin>>b;
        cout<<"�ٴ���������:";
        cin>>bb;
        if(bb!=b)
        {
            cout<<"�������벻һ�£�����������."<<endl;
        }
        if(bb==b)
        {
            break;
        }
    }
    //��ע��ɹ����û���Ϣ�洢��user���
    (p+User::User_Number)->Setname(a);
    (p+User::User_Number)->Setkey(b);
    (p+User::User_Number)->SetIdentity(0, 0, 1);
    tp.Setname(a);
    number=User::User_Number;
    User::User_Number++;
};
void Log::Login(User *p)
{
    string a,b;int flag=0;
    cout<<"�������˺�:"<<endl;
    cin>>a;
    cout<<"����������:"<<endl;
    cin>>b;
    for(int i=0;i<User::User_Number;i++)
    {
        if(a==p[i].Getname()&&b==p[i].Getkey())
        {
            tp.SetIdentity(p[i].GetisAd(), p[i].Getisli(), p[i].Getisre());
            flag=1;tp.Setname(a);tp.Setkey(b);number=i;break;
        }
    }
    if(flag)
    {   if(tp.Judge()==7)
    {   LogName=tp.Getname();
        cout<<"��½�ɹ���"<<endl;Is_Log=true;
        cout<<"�𾴵�ͬѧ"<<tp.Getname()<<",���ã�"<<endl;
    }
    else if(tp.Judge()==5)
    {   LogName=tp.Getname();
        cout<<"��½�ɹ���"<<endl;Is_Log=true;
        cout<<"�𾴵�ѧί"<<tp.Getname()<<",���ã�"<<endl;
    }
    else if(tp.Judge()==6)
    {   LogName=tp.Getname();
        cout<<"��½�ɹ���"<<endl;Is_Log=true;
        cout<<"�𾴵�ϵͳ����Ա"<<tp.Getname()<<",���ã�"<<endl;
    }
    }
    else {cout<<"�˺Ż��������"<<endl;Is_Log=false;}
}

//ѧί
class Librarian:public User,public Log
{
public:
    static int Librarian_Number;
    void zc(User *U,Log a,Librarian *L)
    {
        a.SignIN(U);
        cout<<"ע��ɹ���"<<endl;
        Librarian_Number++;
        U[a.number].SetIdentity(0, 1, 0);
        SetIdentity(0, 1, 0);
        User::name=a.tp.Getname();
        User::key=a.tp.Getkey();
        L[Librarian::Librarian_Number].Setname(a.tp.Getname());
    }
    Librarian(){SetIdentity(0, 1, 0);}
    Librarian(string name1,string key1,User *U)
    {
        U[User_Number].Setname(name1);U[User_Number].Setkey(key1);
        U[User_Number].SetIdentity(0, 1, 0);
        SetIdentity(0, 1, 0);
        U->User_Number++;
        name=name1;
        key=key1;
    }
    void Book_Add(Book *B);//������ҵ
    void Book_Dele(Book *B);//ɾ����ҵ
    void Book_Alter(Book *B);//�޸���ҵ
    void Book_Find(Book *B);//������ҵ
    void Book_AddUp(Book *B);//ͳ����ҵ
};
//������ҵ
void Librarian::Book_Add(Book *B)
{
    string aa;
    cout<<"---------------�����ҵ---------------"<<endl;
    while(1)
    {
        cin>>B[Book::Book_Number];
        ofstream bookmessage("Bookmessage.txt",ios::app);
        if(bookmessage.is_open())
        {
            bookmessage << getCurrentSystemTime();
            bookmessage << "����:������ҵ "<<endl;
            bookmessage <<B[Book::Book_Number]<<endl;
            bookmessage.close();
        }
        Book::Book_Number++;
        cout<<"�����ɹ���"<<endl;
        aa=cin.get();
        cout<<"�����������¼��(����'0'�ɷ������˵�)��";
        aa=cin.get();
        if(aa=="0")break;
    }
}

//ɾ����ҵ
void Librarian::Book_Dele(Book *B)
{
    cout<<"---------------ɾ����ҵ---------------"<<endl;
    string a;
    if(Book::Book_Number==0)cout<<"Ŀǰ����ҵ,���ȷ�����ҵ!"<<endl;
    else
    {
        cout<<"��������ҵ��Ż�����";
        cin>>a;int flag=0,find=0;
        for(int j=0;j<Book::Book_Number;j++)
        {
            if(a==B[j].GetCode()||a==B[j].GetName())
            {flag=1;find=j;break;}
        }
        if(flag==1)
        {
            char a;
            cout<<"�Ѿ��ҵ���ҵ����Ӧ���Ϊ:"<<B[find].GetCode()<<"��ҵ��Ϊ:"<<B[find].GetName()<<"���Ƿ�ѡ��ɾ����(y or n)"<<endl;
            cin>>a;if(a=='y')
            {
                for(int k=find;k<Book::Book_Number;k++)
                {
                    if(k==Book::Book_Number-1){Book::Book_Number--;break;}
                    B[k]=B[k+1];
                }
                ofstream bookmessage("Bookmessage.txt",ios::app);
                if(bookmessage.is_open())
                {
                    bookmessage << getCurrentSystemTime();
                    bookmessage << "����:ɾ����ҵ "<<endl;
                    bookmessage <<B[find]<<endl;
                    bookmessage.close();
                }
                cout<<"ɾ���ɹ���"<<endl;
            }
            else
            {
                cout<<"��ȡ��ɾ����";
            }
        }
        else
            cout<<"��ҵ�����ڣ���ȷ���Ƿ��Ѿ�������"<<endl;
    }
}

//�޸���ҵ
void DisplayAlter()
{
    cout<<"��ѡ���޸���:"<<endl;
    cout<<"1-�޸ı��"<<endl;
    cout<<"2-�޸�����"<<endl;
}
void Librarian::Book_Alter(Book *B)
{   string a;
    cout<<"---------------�޸���ҵ---------------"<<endl;
    if(Book::Book_Number==0)cout<<"Ŀǰ����ҵ,���ȷ�����ҵ"<<endl;
    else{
        cout<<"��������ҵ��Ż�����";
        cin>>a;int flag=0,find=0;
        for(int j=0;j<Book::Book_Number;j++)
        {
            if(a==B[j].GetCode()||a==B[j].GetName())
            {flag=1;find=j;break;}
        }
        if(flag==1)
        {
            char b;
            cout<<"�Ѿ��ҵ�����ҵ���Ƿ�ѡ���޸ģ�(y or n)"<<endl;
            cin>>b;
            if(b=='y')
            {
                DisplayAlter();
                int c;cin>>c;
                switch (c)
                {
                    case 1:
                    {while(1)
                    {
                        cout<<"�������޸ĺ�ı��:"<<endl;
                        int flag=1;
                        cin>>a;
                        for(int l=0;l<Book::Book_Number;l++)
                        {
                            if(B[l].GetCode()==a)
                            { flag=0;break;}
                        }
                        if(flag){B[find].SetCode(a);cout<<"���޸�!"<<endl;break;}
                        else cout<<"�Ѵ��ڸñ�ţ����޸�!"<<endl;
                    }
                        break;
                    }
                    case 2:{
                        cout<<"�������޸ĺ����ҵ��:"<<endl;
                        cin>>a;B[find].SetName(a);cout<<"���޸�!"<<endl;break;}

                    case 0:
                    {
                        break;
                    }
                    default: cout<<"��������ȷ����:"<<endl;
                }
                ofstream bookmessage("Bookmessage.txt",ios::app);
                if(bookmessage.is_open())
                {
                    bookmessage << getCurrentSystemTime();
                    bookmessage << "����:�޸���ҵ "<<endl;
                    bookmessage <<B[find]<<endl;
                    bookmessage.close();
                }
            }
        }
    }
}
//��ѯ��ҵ
void Librarian::Book_Find(Book *B)
{
    cout<<"-------��ѯ��ҵ-------"<<endl;
    cout<<"��������ҵ��Ż���ҵ��:";
    string a1;
    cin>>a1;int flag=0,count=0;
    for(int j=0;j<Book::Book_Number;j++)
    {
        if(a1==B[j].GetCode()||a1==B[j].GetName())
        {flag=1;cout<<B[j];count++;}
    }
    if(count==0)cout<<"δ�ҵ�����ҵ..."<<endl;
    else
        cout<<"���ҵ�"<<count<<"����ҵ��"<<endl;
}
//ͳ����ҵ
void Librarian::Book_AddUp(Book *B)
{
    cout<<"Ŀǰ����"<<Book::Book_Number<<"����ҵ��"<<endl;
    for(int i=0;i<Book::Book_Number;i++)
    {
        cout<<B[i];
    }
}
int Librarian::Librarian_Number=1;


//ѧ��
class Reader:public User,public Log,public Book
{
    Book s[100];
public:
    void zc(User *U,Log a,Reader *R)
    {
        a.SignIN(U);

        U[a.number].SetIdentity(0, 0, 1);
        SetIdentity(0, 0, 1);
        User::Setname(a.tp.Getname());
        User::Setkey(a.tp.Getkey());
        R[Reader::Reader_Number].Setname(a.tp.Getname());
        Reader::Reader_Number++;
    }
    static int Reader_Number;
    void Book_Lend(Book *B);
    void Book_Return(Book *B);
    void Book_LR();
    void Book_show(Book *B);
    Reader():User(){User::Is_Admin=0;User::Is_XueWei=0;User::Is_Student=1;}
};
void Reader::Book_show(Book *B)
{
    for(int i=0;i<Book::Book_Number;i++)
    {
        cout<<B[i];
    }
}
void Reader::Book_LR()
{

    cout<<"---------��ҵ�����Ϣ---------"<<endl;
    int ST=10,TE=20;
    int flag=0;

    for(int i=0;i<=s->Book_Number;i++)
    {
        if(s[i].GetIs_Submit()==true){flag=1;break;}
    }
    if(flag==0)cout<<"���ύ��ҵ��¼\n";
    else
    {
        int LendBookNumber=0;
        for(int i=0;i<=Book::Book_Number;i++)
        {
            if(s[i].GetIs_Submit()==true)
            { s[i].Display();
                LendBookNumber++;
            }
        }

    }
}
/*void Reader::Book_Lend(Book *B)
{
    for(int i=0;i<Book_Number;i++)
    {
        (s+i)->SetCode((B+i)->GetCode());
        (s+i)->SetName((B+i)->GetName());
        (s+i)->SetAuthor((B+i)->GetAuthor());
        (s+i)->SetPress((B+i)->GetPress());
        (s+i)->SetPrice((B+i)->GetPrice());
        (s+i)->Book_Number=(B+i)->Book_Number;
        if(Is_teacher==true)
            (s+i)->SetDeadline(60);
        else
            (s+i)->SetDeadline(30);
    }
    Book *b=B;string a;
    cout<<"---------�ύ��ҵ---------"<<endl;
    cout<<"��������Ҫ�ύ��ҵ�ı�Ż���ҵ��:";
    cin>>a;int Find=0,flag1=0;int LendBookNumber=0;
    for(int j=0;j<=Book::Book_Number;j++)
    {
        if((a==b[j].GetCode()||a==b[j].GetName())&&b[j].GetIs_Submit()==false)
        {
            flag1=1;Find =j;break;
        }
    }

    for(int i=0;i<=Book::Book_Number;i++)
    {
        if(s[i].GetIs_Submit()==true)
        {
            LendBookNumber++;
        }
    }
    if(!flag1)cout<<"��ҵ�����ڻ��Ѿ����ύ��!"<<endl;
    else
    {
        if(Is_teacher==true&&LendBookNumber==20){
            throw LendBookNumber;
        }
        else if(Is_teacher==false&&LendBookNumber==10){
            throw LendBookNumber;
        }
        cout<<"�ύ�ɹ�!"<<endl;
        b[Find].SetIs_Submit(true);
        s[Find].SetIs_Submit(true);
        s[Find].SetTime(getCurrentSystemTime());
        s[Find].SetDeadline(s[Find].GetDeadline());
        ofstream lendmessage("Lendmessage.txt",ios::app);
        if(lendmessage.is_open())
        {
            lendmessage << "����:"<<LogName<<endl;
            lendmessage << "    �ύ��ҵ���:"<<s[Find].GetCode();
            lendmessage << "    �ύ��ҵʱ��:"<<s[Find].Gettime()<<endl;
            lendmessage.close();
        }
    }
}
*/
void Reader::Book_Return(Book *B)
{
    Book *b=B;int flag=0,Find=0;
    cout<<"---------�ύ��ҵ---------"<<endl;
    string a;
    cout<<"��������Ҫ�ύ��ҵ�ı�Ż���ҵ��:";
    cin>>a;
    for(int j=0;j<Book::Book_Number;j++)
    {
        if(a==b[j].GetCode()||a==b[j].GetName())
        {
            flag=1;Find =j;break;
        }
    }
    if(flag==1){
        if(s[Find].GetIs_Submit()==true)
        {

            cout<<"�ύʱ��:"<<getCurrentSystemTime()<<endl;
            string lend_time=s[Find].Gettime();
            string return_time=getCurrentSystemTime();
            int mml,mmr,ddl,ddr;
            //�ж��Ƿ�ʱ
            mmr=return_time[6]-'0'+(return_time[5]-'0')*10;
            mml=lend_time[6]-'0'+(lend_time[5]-'0')*10;
            ddr=return_time[9]-'0'+(return_time[8]-'0')*10;
            ddl=lend_time[9]-'0'+(lend_time[8]-'0')*10;
            int day=0;
            if(Is_teacher==true) day=60;
            else day=30;
            if(mmr*30+ddr-mml*30-ddl<=day)
            {   s[Find].SetIs_Submit(false);
                b[Find].SetIs_Submit(false);
                ofstream lendmessage("Lendmessage.txt",ios::app);
                if(lendmessage.is_open())
                {
                    lendmessage << "����:"<<LogName<<endl;
                    lendmessage << "    �ύ��ҵ���:"<<s[Find].GetCode();
                    lendmessage << "    �ύ��ҵʱ��:"<<return_time<<endl;
                    lendmessage.close();
                }
                cout<<"�ύ�ɹ���"<<endl;}
            else
                throw mmr*30+ddr-mml*30-ddl-day;
        }
        else
        {
            cout<<"����ҵδ���ύ"<<endl;
        }
    }
    else
    {
        cout<<"δ�ҵ�����ҵ��"<<endl;
    }
}
int Reader::Reader_Number=0;


//ϵͳ����Ա
class Admin:public User,public Log
{
public:
    void Reader_Add(User *U,Reader *R);//���ѧ��
    void Reader_Dele(User *U,Reader *R);//ɾ��ѧ��
    void Librarian_Add(User *U,Librarian *L);//���ѧί
    void Librarian_Dele(User *U,Librarian *L);//ɾ��ѧί
    void Reader_Alter(Reader *R,User *U,Admin *A,Librarian *L);//ѧ��Ȩ�޸���
    void Librarian_Alter(Librarian *L,User *U,Admin *A,Reader *R);//ѧίȨ�޸���
    void User_keychange(User *U);//�޸��û�����
    static int Admin_Number;
    Admin(){Is_Admin=1;Is_XueWei=0;Is_Student=0;};
    Admin(string name1,string key1,User *U)
    {   U[U->User_Number].Setname(name1);
        U[U->User_Number].Setkey(key1);
        Is_Admin=1;Is_XueWei=0;Is_Student=0;
        U[U->User_Number].SetIdentity(1, 0, 0);
        U->User_Number++;
        name=name1;
        key=key1;
    }
};
void Admin::User_keychange(User *U)
{

    int find=0;string Name,key,key1;
    bool is_find=false;
    cout<<"�������û���:";
    cin>>Name;
    for(int i=0;i<User::User_Number;i++)
    {
        if(U[i].Getname()==Name)
        {
            find=i;is_find=true;break;
        }
    }

    if(is_find==true)
    {
        cout<<"������������:";
        cin>>key;
        cout<<"������һ��������:";
        cin>>key1;
        if(key==key1)
        {
            U[find].Setkey(key);
            cout<<"�޸ĳɹ���"<<endl;
        }
        else
        {
            cout<<"�����������벻һ��,�޸�ʧ��!"<<endl;
        }
    }
    else
    {
        cout<<"δ�ҵ����û�."<<endl;
    }
}
//ѧ��Ȩ���޸�
void Admin::Reader_Alter(Reader *R,User *U,Admin *A,Librarian *L)
{   string name,key;
    string a;cout<<"��������Ҫ���в�����ѧ���û���:";cin>>a;
    int flag=0,find=0;
    for(int i=0;i<Reader::Reader_Number;i++)
    {
        if(R[i].Getname()==a){
            flag=1;find=i;name=R[i].Getname();key=R[i].Getkey();break;
        }
    }

    if(flag)
    {
        int t=0;
        cout<<"��ѡ����Ҫ�����Ȩ������:"<<endl;
        cout<<"��ѧί"<<endl;
        cout<<"��ϵͳ����Ա"<<endl;
        cout<<"�۷���"<<endl;
        cin>>a;
        if(a=="1")
        {
            t=1;
        }
        else if(a=="2")
        {
            t=2;
        }
        else
        {
            cout<<"���سɹ�!"; t=0;
        }
        if(t==1||t==2)
        {
            for(int j=find;j<Reader::Reader_Number;j++)
            {
                if(j==Reader::Reader_Number-1){Reader::Reader_Number--;break;}
                R[j]=R[j+1];
            }
            if(t==1)
            {
                for(int j=0;j<U->User_Number;j++)
                {
                    if(U[j].Getname()==name){
                        U[j].SetIdentity(0, 1, 0);
                        break;}
                }
                L[Librarian::Librarian_Number].Setname(name);
                L[Librarian::Librarian_Number].Setkey(key);
                L[Librarian::Librarian_Number].SetIdentity(0, 1, 0);
                L->Librarian_Number++;
            }

            if(t==2)
            {
                for(int j=0;j<U->User_Number;j++)
                {
                    if(U[j].Getname()==name){
                        U[j].SetIdentity(1, 0, 0);
                        break;}
                }
                A[Admin::Admin_Number].Setname(name);
                A[Admin::Admin_Number].Setkey(key);
                A[Admin::Admin_Number].SetIdentity(1, 0, 0);
                A->Admin_Number++;
            }
            cout<<"����ɹ�!"<<endl;
        }
    }
    else    cout<<"ѧ���û������ڣ�"<<endl;
}
//ѧίȨ���޸�
void Admin::Librarian_Alter(Librarian *L,User *U,Admin *A,Reader *R)
{
    string name,key;
    string a;cout<<"��������Ҫ���в�����ѧί�û���:";cin>>a;
    int flag=0,find=0;
    for(int i=0;i<Librarian::Librarian_Number;i++)
    {
        if(L[i].Getname()==a){
            flag=1;find=i;name=L[i].Getname();key=L[i].Getkey();break;
        }
    }

    if(flag)
    {
        int t=0;
        cout<<"��ѡ����Ҫ�����Ȩ������:"<<endl;
        cout<<"��ѧ��"<<endl;
        cout<<"��ϵͳ����Ա"<<endl;
        cout<<"�۷���"<<endl;
        cin>>a;
        if(a=="1")
        {
            t=1;
        }
        else if(a=="2")
        {
            t=2;
        }
        else
        {
            cout<<"���سɹ�!"; t=0;
        }
        if(t==1||t==2)
        {
            for(int j=find;j<Librarian::Librarian_Number;j++)
            {
                if(j==Librarian::Librarian_Number-1){Librarian::Librarian_Number--;break;}
                L[j]=L[j+1];
            }
            if(t==1)
            {
                for(int j=0;j<U->User_Number;j++)
                {
                    if(U[j].Getname()==name){
                        U[j].SetIdentity(0, 0, 1);
                        break;}
                }
                R[Reader::Reader_Number].Setname(name);
                R[Reader::Reader_Number].Setkey(key);
                R[Reader::Reader_Number].SetIdentity(0, 0, 1);
                R->Reader_Number++;
            }

            if(t==2)
            {
                for(int j=0;j<U->User_Number;j++)
                {
                    if(U[j].Getname()==name){
                        U[j].SetIdentity(1, 0, 0);
                        break;}
                }
                A[Admin::Admin_Number].Setname(name);
                A[Admin::Admin_Number].Setkey(key);
                A[Admin::Admin_Number].SetIdentity(1, 0, 0);
                A->Admin_Number++;
            }
            cout<<"����ɹ�!"<<endl;
        }
    }
    else    cout<<"ѧ���û������ڣ�"<<endl;
}
//����ѧ��
void Admin::Reader_Add(User *U,Reader *R)
{   Log a;
    R[Reader::Reader_Number].zc(U, a,R);
}
//����ѧί
void Admin::Librarian_Add(User *U,Librarian *L)
{   Log a;
    L[Librarian::Librarian_Number].zc(U, a,L);
}
//ɾ��ѧ��
void Admin::Reader_Dele(User *U,Reader *R)
{
    string a;
    cout<<"��������Ҫ���в������û���:";cin>>a;
    int flag=0,find=0,find1=0;
    for(int i=0;i<Reader::Reader_Number;i++)
    {
        if(R[i].Getname()==a){
            flag=1;find=i;break;
        }
    }
    if(flag)
    {
        for(int j=find;j<Reader::Reader_Number;j++)
        {
            if(j==Reader::Reader_Number-1){Reader::Reader_Number--;break;}
            R[j]=R[j+1];
        }
        for(int j=0;j<U->User_Number;j++)
        {
            if(U[j].Getname()==a){find1=j;break;}
        }
        for(int j=find1;j<U->User_Number;j++)
        {
            if(j==U->User_Number-1){U->User_Number--;break;}
            U[j]=U[j+1];
        }
        cout<<"ɾ���ɹ���"<<endl;
    }
    else    cout<<"�û������ڣ�"<<endl;
}
//ɾ��ѧί
void Admin::Librarian_Dele(User *U,Librarian *L)
{
    string a;
    cout<<"��������Ҫ���в������û���:";cin>>a;
    int flag=0,find=0,find1=0;
    for(int i=0;i<Librarian::Librarian_Number;i++)
    {
        if(L[i].Getname()==a){
            flag=1;find=i;break;
        }

    }
    if(flag)
    {
        for(int j=find;j<Librarian::Librarian_Number;j++)
        {
            if(j==Librarian::Librarian_Number-1){Librarian::Librarian_Number--;break;}
            L[j]=L[j+1];
        }
        for(int k=0;k<U->User_Number;k++)
        {
            if(U[k].Getname()==a)
            {
                find1=k;break;
            }
        }
        for(int j=find1;j<U->User_Number;j++)
        {
            if(j==U->User_Number-1){U->User_Number--;break;}
            U[j]=U[j+1];
        }
        cout<<"ɾ���ɹ���"<<endl;
    }
    else    cout<<"�û������ڣ�"<<endl;
}
int Admin::Admin_Number=1;


void jiemian()//������
{   cout<<"|ѧί:L   ����:8  |  ϵͳ����Ա:A   ����:8|"<<endl;
    cout<<"|Ĭ��3����ҵ  ���:10000,��ҵ��:C++               |"<<endl;
    cout<<"|          ���:10001,��ҵ��:C                |"<<endl;
    cout<<"|          ���:10002,��ҵ��:C#               |"<<endl;
    cout<<"I����������������������������ҵ����ϵͳ3.0��������������������������������I"<<endl;
    cout<<"I����������������������������------ע��------������������������������I"<<endl;
    cout<<"I����������������������������------��½------������������������������I"<<endl;
    cout<<"I����������������������������------�˳�------������������������������I"<<endl;
}
void reajm()//ѧ������
{
    cout<<"��-------�鿴��ҵ"<<endl;
    cout<<"��-------�ύ��ҵ"<<endl;
    cout<<"��-------��ѯ�ύ��Ϣ"<<endl;
    cout<<"��-------�޸�����"<<endl;
    cout<<"��-------�˳�"<<endl;
}
void libjm()//ѧί����
{
    cout<<"��-------������ҵ"<<endl;//�٢ڢۢܢݢޢߢ��
    cout<<"��-------�޸���ҵ"<<endl;
    cout<<"��-------ɾ����ҵ"<<endl;
    cout<<"��-------��ѯ��ҵ"<<endl;
    cout<<"��-------ͳ����ҵ"<<endl;
    cout<<"��-------�޸�����"<<endl;
    cout<<"��-------�˳�"<<endl;
}
void admjm()//ϵͳ����Ա����
{
    cout<<"��-------����ѧ��"<<endl;//�٢ڢۢܢݢޢߢ��
    cout<<"��-------ɾ��ѧ��"<<endl;
    cout<<"��-------����ѧί"<<endl;
    cout<<"��-------ɾ��ѧί"<<endl;
    cout<<"��-------ѧ��Ȩ���޸�"<<endl;
    cout<<"��-------ѧίȨ���޸�"<<endl;
    cout<<"��-------�޸��û�����"<<endl;
    cout<<"��-------�޸�����"<<endl;
    cout<<"��-------�˳�"<<endl;
}
Book B[100]{Book("10000","C++","����","666",51.3),Book("10001","C","����","777",48.8),Book("10002","C#","����","888",59.9)};
User U[100];Reader R[100];Librarian L[100]{Librarian("L","8",U) };
Admin A[100]{Admin("A","8",U)};Log c;

int main(int argc, const char * argv[]) {
    while (1) {
        jiemian();
        int a;string aa;cin>>aa;//��ֹһ��ʼ�������������bug.
        if(aa=="1")a=1;
        else if(aa=="2")a=2;
        else if(aa=="3")a=3;
        else {
            cout<<"������1��3�ڵ�����"<<endl;continue;
        }
        switch (a) {
                //��װ������
            case 1:
            {cout<<"             ѧ��ע��"<<endl;
                R[Reader::Reader_Number].zc(U, c,R);
                break;}

                //��װ������
            case 2:
            {
                cout<<"             ��  ½"<<endl;
                c.Login(U);
                if(c.Is_Log==false)break;

                //��װ������
                if(c.tp.Judge()==5)//ѧί
                {
                    int n=1;
                    while (n) {
                        libjm();
                        int b;cin>>b;
                        switch (b) {
                            case 1:
                            {
                                L[c.number].Book_Add(B);
                                break;}
                            case 2:
                            {
                                L[c.number].Book_Alter(B);
                                break;}
                            case 3:
                            {
                                L[c.number].Book_Dele(B);
                                break;}
                            case 4:
                            {
                                L[c.number].Book_Find(B);
                                break;}
                            case 5:
                            {
                                L[c.number].Book_AddUp(B);
                                break;}
                            case 6:
                            {
                                L[c.number].key_change(U);
                                break;}
                            default:
                                n=0;
                        }
                    }
                }
                //��װ������
                else if(c.tp.Judge()==6)//ϵͳ����Ա
                {

                    int n=1;
                    while (n) {
                        admjm();
                        int b;cin>>b;
                        switch (b) {
                            case 1://����ѧ��
                            {
                                A[c.number].Reader_Add(U, R);
                                break;}
                            case 2://ɾ��ѧ��
                            {
                                A[c.number].Reader_Dele(U, R);
                                break;}
                            case 3://����ѧί
                            {
                                A[c.number].Librarian_Add(U,L);
                                break;
                            }
                            case 4://����ѧί
                            {
                                A[c.number].Librarian_Dele(U,L);
                                break;
                            }
                            case 5://ѧ��Ȩ���޸�
                            {
                                A[c.number].Reader_Alter(R,U, A, L);
                                break;
                            }
                            case 6://ѧίȨ���޸�
                            {
                                A[c.number].Librarian_Alter(L,U, A, R);
                                break;
                            }
                            case 7://�޸��û�����
                            {
                                A[c.number].User_keychange(U);
                                break;
                            }
                            case 8://�޸�����
                            {
                                A[c.number].key_change(U);
                                break;
                            }
                            default:
                                n=0;break;
                        }
                    }
                }
                //��װ������
                else if(c.tp.Judge()==7)//ѧ��
                {
                    int n=1;
                    while (n) {
                        reajm();
                        int b;cin>>b;
                        switch (b) {
                            case 1://��ҵ��չʾ
                            {
                                R[c.number].Book_show(B);
                                break;
                            }
  /*                          case 2://�ύ��ҵ
                            {
                                try{
                                    R[c.number].Book_Lend(B);
                                }
                                catch(int Num)
                                {
                                    cout<<"��������ύ��ҵ�������ύ��ҵʧ�ܡ�"<<endl;
                                }

                                break;}
*/
                            case 3://����ҵ
                            {
                                try{
                                    R[c.number].Book_Return(B);}

                                catch(int day)
                                {
                                    cout<<"�黹��ҵ��ʱ"<<day<<"��"<<"����50��"<<endl;
                                }
                                break;}

                            case 4://��ʾ�ύ����Ϣ
                            {
                                R[c.number].Book_LR();
                                break;
                            }
                            case 5://�޸�����
                            {
                                R[c.number].key_change(U);
                                break;
                            }
                            default:
                                n=0;
                        }
                    }
                }
                else break;
                break;}
                //��װ������
            case 3:
            {cout<<"             ϵͳ���˳�"<<endl;
                return 0;
                break;}
            default:
                break;
        }
        cin.get();//���ջس���
        cout<<"���س�������������\n";
        cin.get();
    }
    return 0;
}

