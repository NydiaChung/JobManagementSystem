#include <iostream>
#include <fstream>//文件输入输出
#include<iomanip>//控制输出格式
#include<string>
#include<time.h>//时间输出
using namespace std;
//作业类
class Book
{
protected:
    string code,name,author,press,time;
    int deadline;//提交期限
    bool Is_Submit;//作业是否被提交
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
    friend const std::string getCurrentSystemTime();//获取现在的时间
    friend istream& operator >> (istream &stream,Book &b);//重载操作符>>
    friend ostream& operator << (ostream &stream,Book &b);//重载操作符<<
};
ostream &operator << (ostream &stream,Book &b)
{
    stream<<"编号"<<setw(9)<<b.code<<" 作业名:"<<setw(9)<<b.name<<endl;
    return stream;
}
istream &operator >> (istream &stream,Book &b)
{
    cout<<"请输入编号:";
    stream>>b.code;
    cout<<"请输入作业名:";
    return stream;
}
//获取系统当前时间的函数.
const string getCurrentSystemTime()
{
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);//转为时间结构。
    char date[60] = {0};
    sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
            (int)lt->tm_year + 1900,(int)lt->tm_mon + 1,(int)lt->tm_mday,
            (int)lt->tm_hour,(int)lt->tm_min,(int)lt->tm_sec);
    return string(date);
}
void Book::SetDeadline(int a){deadline =a;}
void Book::SetTime(string a){time =a;}
void Book::SetIs_Submit(bool a){Is_Submit =a;}
void Book::Display()//用来展示作品也提交情况
{
    cout<<"编号"<<setw(9)<<GetCode()<<" 作业名:"<<setw(9)
    <<GetName()<<" 发布时间:"<<setw(10)<<Gettime()
    <<" 提交期限:"<<GetDeadline()<<"天"<<endl;
}
void Book::SetCode(string code1)
{code=code1;}
void Book::SetName(string name1)
{name=name1;}

int Book::Book_Number=0;

static string LogName;//记录当前登陆用户的用户名
//用户类
class User
{
protected:
    string name;//用户姓名
    string key;//用户密码
    bool Is_Admin,Is_XueWei,Is_Student;//什么用户类型
public:
    void key_change(User *U);//修改用户密码
    int  Judge();//判断用户类型
    static int User_Number;
    User(){Is_Admin=0;Is_XueWei=0;Is_Student=1;};//默认学生类型
    void Setname(string name1);
    void Setkey(string key1);
    void SetIdentity(bool ad,bool li,bool re )//设置用户类型
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
    cout<<"请输入原密码:";
    cin>>key;
    if(key==U[find].Getkey())
    {
        cout<<"请输入新密码:";
        cin>>key;
        cout<<"再输入一次新密码:";
        cin>>key1;
        if(key==key1)
        {
            U[find].Setkey(key);
            cout<<"修改成功！"<<endl;
        }
        else
        {
            cout<<"两次密码输入不一致,修改失败!"<<endl;
        }
    }
    else
    {
        cout<<"密码错误！"<<endl;
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
    User tp;//存储登陆成功的用户的信息
    int number;//存储当前用户信息对应的User类中下标值
    void Login(User *p);//登陆
    void SignIN(User *p);//注册
    Log(){number=0;};
    bool Is_Log;//判断是否登陆成功。
};

void Log::SignIN(User *p)
{
    int f1;string a,b,bb;
    while(1)
    {
        f1=1;
        cout<<"请输入用户名：";
        cin>>a;
        for(int i=0;i<=User::User_Number;i++)
        {
            if(p[i].Getname()==a)
            {
                cout<<"用户名已存在，请重新输入."<<endl;f1=0;
            }
        }
        if(f1==0){};
        if(f1==1) {break;}
    }
    while(1)
    {
        cout<<"请设置密码:";
        cin>>b;
        cout<<"再次输入密码:";
        cin>>bb;
        if(bb!=b)
        {
            cout<<"两次密码不一致，请重新输入."<<endl;
        }
        if(bb==b)
        {
            break;
        }
    }
    //将注册成功的用户信息存储到user类里。
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
    cout<<"请输入账号:"<<endl;
    cin>>a;
    cout<<"请输入密码:"<<endl;
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
        cout<<"登陆成功！"<<endl;Is_Log=true;
        cout<<"尊敬的同学"<<tp.Getname()<<",您好！"<<endl;
    }
    else if(tp.Judge()==5)
    {   LogName=tp.Getname();
        cout<<"登陆成功！"<<endl;Is_Log=true;
        cout<<"尊敬的学委"<<tp.Getname()<<",您好！"<<endl;
    }
    else if(tp.Judge()==6)
    {   LogName=tp.Getname();
        cout<<"登陆成功！"<<endl;Is_Log=true;
        cout<<"尊敬的系统管理员"<<tp.Getname()<<",您好！"<<endl;
    }
    }
    else {cout<<"账号或密码错误！"<<endl;Is_Log=false;}
}

//学委
class Librarian:public User,public Log
{
public:
    static int Librarian_Number;
    void zc(User *U,Log a,Librarian *L)
    {
        a.SignIN(U);
        cout<<"注册成功！"<<endl;
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
    void Book_Add(Book *B);//增加作业
    void Book_Dele(Book *B);//删除作业
    void Book_Alter(Book *B);//修改作业
    void Book_Find(Book *B);//查找作业
    void Book_AddUp(Book *B);//统计作业
};
//增加作业
void Librarian::Book_Add(Book *B)
{
    string aa;
    cout<<"---------------添加作业---------------"<<endl;
    while(1)
    {
        cin>>B[Book::Book_Number];
        ofstream bookmessage("Bookmessage.txt",ios::app);
        if(bookmessage.is_open())
        {
            bookmessage << getCurrentSystemTime();
            bookmessage << "操作:增加作业 "<<endl;
            bookmessage <<B[Book::Book_Number]<<endl;
            bookmessage.close();
        }
        Book::Book_Number++;
        cout<<"发布成功！"<<endl;
        aa=cin.get();
        cout<<"按任意键继续录入(输入'0'可返回主菜单)，";
        aa=cin.get();
        if(aa=="0")break;
    }
}

//删除作业
void Librarian::Book_Dele(Book *B)
{
    cout<<"---------------删除作业---------------"<<endl;
    string a;
    if(Book::Book_Number==0)cout<<"目前无作业,请先发布作业!"<<endl;
    else
    {
        cout<<"请输入作业编号或名称";
        cin>>a;int flag=0,find=0;
        for(int j=0;j<Book::Book_Number;j++)
        {
            if(a==B[j].GetCode()||a==B[j].GetName())
            {flag=1;find=j;break;}
        }
        if(flag==1)
        {
            char a;
            cout<<"已经找到作业，对应编号为:"<<B[find].GetCode()<<"作业名为:"<<B[find].GetName()<<"，是否选择删除？(y or n)"<<endl;
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
                    bookmessage << "操作:删除作业 "<<endl;
                    bookmessage <<B[find]<<endl;
                    bookmessage.close();
                }
                cout<<"删除成功！"<<endl;
            }
            else
            {
                cout<<"已取消删除。";
            }
        }
        else
            cout<<"作业不存在，请确认是否已经发布。"<<endl;
    }
}

//修改作业
void DisplayAlter()
{
    cout<<"请选择修改项:"<<endl;
    cout<<"1-修改编号"<<endl;
    cout<<"2-修改名称"<<endl;
}
void Librarian::Book_Alter(Book *B)
{   string a;
    cout<<"---------------修改作业---------------"<<endl;
    if(Book::Book_Number==0)cout<<"目前无作业,请先发布作业"<<endl;
    else{
        cout<<"请输入作业编号或名称";
        cin>>a;int flag=0,find=0;
        for(int j=0;j<Book::Book_Number;j++)
        {
            if(a==B[j].GetCode()||a==B[j].GetName())
            {flag=1;find=j;break;}
        }
        if(flag==1)
        {
            char b;
            cout<<"已经找到该作业，是否选择修改？(y or n)"<<endl;
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
                        cout<<"请输入修改后的编号:"<<endl;
                        int flag=1;
                        cin>>a;
                        for(int l=0;l<Book::Book_Number;l++)
                        {
                            if(B[l].GetCode()==a)
                            { flag=0;break;}
                        }
                        if(flag){B[find].SetCode(a);cout<<"已修改!"<<endl;break;}
                        else cout<<"已存在该编号，请修改!"<<endl;
                    }
                        break;
                    }
                    case 2:{
                        cout<<"请输入修改后的作业名:"<<endl;
                        cin>>a;B[find].SetName(a);cout<<"已修改!"<<endl;break;}

                    case 0:
                    {
                        break;
                    }
                    default: cout<<"请输入正确数字:"<<endl;
                }
                ofstream bookmessage("Bookmessage.txt",ios::app);
                if(bookmessage.is_open())
                {
                    bookmessage << getCurrentSystemTime();
                    bookmessage << "操作:修改作业 "<<endl;
                    bookmessage <<B[find]<<endl;
                    bookmessage.close();
                }
            }
        }
    }
}
//查询作业
void Librarian::Book_Find(Book *B)
{
    cout<<"-------查询作业-------"<<endl;
    cout<<"请输入作业编号或作业名:";
    string a1;
    cin>>a1;int flag=0,count=0;
    for(int j=0;j<Book::Book_Number;j++)
    {
        if(a1==B[j].GetCode()||a1==B[j].GetName())
        {flag=1;cout<<B[j];count++;}
    }
    if(count==0)cout<<"未找到此作业..."<<endl;
    else
        cout<<"共找到"<<count<<"门作业。"<<endl;
}
//统计作业
void Librarian::Book_AddUp(Book *B)
{
    cout<<"目前共有"<<Book::Book_Number<<"门作业。"<<endl;
    for(int i=0;i<Book::Book_Number;i++)
    {
        cout<<B[i];
    }
}
int Librarian::Librarian_Number=1;


//学生
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

    cout<<"---------作业完成信息---------"<<endl;
    int ST=10,TE=20;
    int flag=0;

    for(int i=0;i<=s->Book_Number;i++)
    {
        if(s[i].GetIs_Submit()==true){flag=1;break;}
    }
    if(flag==0)cout<<"无提交作业记录\n";
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
    cout<<"---------提交作业---------"<<endl;
    cout<<"请输入需要提交作业的编号或作业名:";
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
    if(!flag1)cout<<"作业不存在或已经被提交出!"<<endl;
    else
    {
        if(Is_teacher==true&&LendBookNumber==20){
            throw LendBookNumber;
        }
        else if(Is_teacher==false&&LendBookNumber==10){
            throw LendBookNumber;
        }
        cout<<"提交成功!"<<endl;
        b[Find].SetIs_Submit(true);
        s[Find].SetIs_Submit(true);
        s[Find].SetTime(getCurrentSystemTime());
        s[Find].SetDeadline(s[Find].GetDeadline());
        ofstream lendmessage("Lendmessage.txt",ios::app);
        if(lendmessage.is_open())
        {
            lendmessage << "姓名:"<<LogName<<endl;
            lendmessage << "    提交作业编号:"<<s[Find].GetCode();
            lendmessage << "    提交作业时间:"<<s[Find].Gettime()<<endl;
            lendmessage.close();
        }
    }
}
*/
void Reader::Book_Return(Book *B)
{
    Book *b=B;int flag=0,Find=0;
    cout<<"---------提交作业---------"<<endl;
    string a;
    cout<<"请输入需要提交作业的编号或作业名:";
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

            cout<<"提交时间:"<<getCurrentSystemTime()<<endl;
            string lend_time=s[Find].Gettime();
            string return_time=getCurrentSystemTime();
            int mml,mmr,ddl,ddr;
            //判断是否超时
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
                    lendmessage << "姓名:"<<LogName<<endl;
                    lendmessage << "    提交作业编号:"<<s[Find].GetCode();
                    lendmessage << "    提交作业时间:"<<return_time<<endl;
                    lendmessage.close();
                }
                cout<<"提交成功！"<<endl;}
            else
                throw mmr*30+ddr-mml*30-ddl-day;
        }
        else
        {
            cout<<"此作业未被提交"<<endl;
        }
    }
    else
    {
        cout<<"未找到此作业！"<<endl;
    }
}
int Reader::Reader_Number=0;


//系统管理员
class Admin:public User,public Log
{
public:
    void Reader_Add(User *U,Reader *R);//添加学生
    void Reader_Dele(User *U,Reader *R);//删除学生
    void Librarian_Add(User *U,Librarian *L);//添加学委
    void Librarian_Dele(User *U,Librarian *L);//删除学委
    void Reader_Alter(Reader *R,User *U,Admin *A,Librarian *L);//学生权限更改
    void Librarian_Alter(Librarian *L,User *U,Admin *A,Reader *R);//学委权限更改
    void User_keychange(User *U);//修改用户密码
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
    cout<<"请输入用户名:";
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
        cout<<"请输入新密码:";
        cin>>key;
        cout<<"再输入一次新密码:";
        cin>>key1;
        if(key==key1)
        {
            U[find].Setkey(key);
            cout<<"修改成功！"<<endl;
        }
        else
        {
            cout<<"两次密码输入不一致,修改失败!"<<endl;
        }
    }
    else
    {
        cout<<"未找到该用户."<<endl;
    }
}
//学生权限修改
void Admin::Reader_Alter(Reader *R,User *U,Admin *A,Librarian *L)
{   string name,key;
    string a;cout<<"请输入需要进行操作的学生用户名:";cin>>a;
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
        cout<<"请选择需要变更的权限类型:"<<endl;
        cout<<"①学委"<<endl;
        cout<<"②系统管理员"<<endl;
        cout<<"③返回"<<endl;
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
            cout<<"返回成功!"; t=0;
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
            cout<<"变更成功!"<<endl;
        }
    }
    else    cout<<"学生用户不存在！"<<endl;
}
//学委权限修改
void Admin::Librarian_Alter(Librarian *L,User *U,Admin *A,Reader *R)
{
    string name,key;
    string a;cout<<"请输入需要进行操作的学委用户名:";cin>>a;
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
        cout<<"请选择需要变更的权限类型:"<<endl;
        cout<<"①学生"<<endl;
        cout<<"②系统管理员"<<endl;
        cout<<"③返回"<<endl;
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
            cout<<"返回成功!"; t=0;
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
            cout<<"变更成功!"<<endl;
        }
    }
    else    cout<<"学生用户不存在！"<<endl;
}
//增加学生
void Admin::Reader_Add(User *U,Reader *R)
{   Log a;
    R[Reader::Reader_Number].zc(U, a,R);
}
//增加学委
void Admin::Librarian_Add(User *U,Librarian *L)
{   Log a;
    L[Librarian::Librarian_Number].zc(U, a,L);
}
//删除学生
void Admin::Reader_Dele(User *U,Reader *R)
{
    string a;
    cout<<"请输入需要进行操作的用户名:";cin>>a;
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
        cout<<"删除成功！"<<endl;
    }
    else    cout<<"用户不存在！"<<endl;
}
//删除学委
void Admin::Librarian_Dele(User *U,Librarian *L)
{
    string a;
    cout<<"请输入需要进行操作的用户名:";cin>>a;
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
        cout<<"删除成功！"<<endl;
    }
    else    cout<<"用户不存在！"<<endl;
}
int Admin::Admin_Number=1;


void jiemian()//主界面
{   cout<<"|学委:L   密码:8  |  系统管理员:A   密码:8|"<<endl;
    cout<<"|默认3本作业  编号:10000,作业名:C++               |"<<endl;
    cout<<"|          编号:10001,作业名:C                |"<<endl;
    cout<<"|          编号:10002,作业名:C#               |"<<endl;
    cout<<"I—————————————作业管理系统3.0————————————————I"<<endl;
    cout<<"I—————————————①------注册------————————————I"<<endl;
    cout<<"I—————————————②------登陆------————————————I"<<endl;
    cout<<"I—————————————③------退出------————————————I"<<endl;
}
void reajm()//学生界面
{
    cout<<"①-------查看作业"<<endl;
    cout<<"③-------提交作业"<<endl;
    cout<<"④-------查询提交信息"<<endl;
    cout<<"⑤-------修改密码"<<endl;
    cout<<"⑥-------退出"<<endl;
}
void libjm()//学委界面
{
    cout<<"①-------增加作业"<<endl;//①②③④⑤⑥⑦⑧⑨
    cout<<"②-------修改作业"<<endl;
    cout<<"③-------删除作业"<<endl;
    cout<<"④-------查询作业"<<endl;
    cout<<"⑤-------统计作业"<<endl;
    cout<<"⑥-------修改密码"<<endl;
    cout<<"⑦-------退出"<<endl;
}
void admjm()//系统管理员界面
{
    cout<<"①-------增加学生"<<endl;//①②③④⑤⑥⑦⑧⑨
    cout<<"②-------删除学生"<<endl;
    cout<<"③-------增加学委"<<endl;
    cout<<"④-------删除学委"<<endl;
    cout<<"⑤-------学生权限修改"<<endl;
    cout<<"⑥-------学委权限修改"<<endl;
    cout<<"⑦-------修改用户密码"<<endl;
    cout<<"⑧-------修改密码"<<endl;
    cout<<"⑨-------退出"<<endl;
}
Book B[100]{Book("10000","C++","张三","666",51.3),Book("10001","C","李四","777",48.8),Book("10002","C#","王五","888",59.9)};
User U[100];Reader R[100];Librarian L[100]{Librarian("L","8",U) };
Admin A[100]{Admin("A","8",U)};Log c;

int main(int argc, const char * argv[]) {
    while (1) {
        jiemian();
        int a;string aa;cin>>aa;//防止一开始输入序号输错出现bug.
        if(aa=="1")a=1;
        else if(aa=="2")a=2;
        else if(aa=="3")a=3;
        else {
            cout<<"请输入1～3内的数字"<<endl;continue;
        }
        switch (a) {
                //假装有条线
            case 1:
            {cout<<"             学生注册"<<endl;
                R[Reader::Reader_Number].zc(U, c,R);
                break;}

                //假装有条线
            case 2:
            {
                cout<<"             登  陆"<<endl;
                c.Login(U);
                if(c.Is_Log==false)break;

                //假装有条线
                if(c.tp.Judge()==5)//学委
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
                //假装有条线
                else if(c.tp.Judge()==6)//系统管理员
                {

                    int n=1;
                    while (n) {
                        admjm();
                        int b;cin>>b;
                        switch (b) {
                            case 1://增加学生
                            {
                                A[c.number].Reader_Add(U, R);
                                break;}
                            case 2://删除学生
                            {
                                A[c.number].Reader_Dele(U, R);
                                break;}
                            case 3://增加学委
                            {
                                A[c.number].Librarian_Add(U,L);
                                break;
                            }
                            case 4://增加学委
                            {
                                A[c.number].Librarian_Dele(U,L);
                                break;
                            }
                            case 5://学生权限修改
                            {
                                A[c.number].Reader_Alter(R,U, A, L);
                                break;
                            }
                            case 6://学委权限修改
                            {
                                A[c.number].Librarian_Alter(L,U, A, R);
                                break;
                            }
                            case 7://修改用户密码
                            {
                                A[c.number].User_keychange(U);
                                break;
                            }
                            case 8://修改密码
                            {
                                A[c.number].key_change(U);
                                break;
                            }
                            default:
                                n=0;break;
                        }
                    }
                }
                //假装有条线
                else if(c.tp.Judge()==7)//学生
                {
                    int n=1;
                    while (n) {
                        reajm();
                        int b;cin>>b;
                        switch (b) {
                            case 1://作业本展示
                            {
                                R[c.number].Book_show(B);
                                break;
                            }
  /*                          case 2://提交作业
                            {
                                try{
                                    R[c.number].Book_Lend(B);
                                }
                                catch(int Num)
                                {
                                    cout<<"超出最大提交作业数量，提交作业失败。"<<endl;
                                }

                                break;}
*/
                            case 3://还作业
                            {
                                try{
                                    R[c.number].Book_Return(B);}

                                catch(int day)
                                {
                                    cout<<"归还作业超时"<<day<<"天"<<"罚款50！"<<endl;
                                }
                                break;}

                            case 4://显示提交还信息
                            {
                                R[c.number].Book_LR();
                                break;
                            }
                            case 5://修改密码
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
                //假装有条线
            case 3:
            {cout<<"             系统已退出"<<endl;
                return 0;
                break;}
            default:
                break;
        }
        cin.get();//吸收回车符
        cout<<"按回车键返回主界面\n";
        cin.get();
    }
    return 0;
}

