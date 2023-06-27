/*进入菜单2航空管理系统
  账号为1；
  密码为110；
  */ 

#include<iostream>  
#include<cstring> 
#include <fstream> 
#include<sstream> 
#include<iomanip> 
#include<stdlib.h>
using namespace std;  

class Book{
public: 
    int id; //航班号 
    string flytime; //起飞时间 
    string downtime;//降落时间
    string flyplace;//起飞城市
    string downplace; //降落城市
    Book(int nid=0,string ftime="0:00", string dtime="0:00",string fplace="no",string dplace="no")
    {   
        id=nid;
        flytime=ftime;
        downtime=dtime;
        flyplace=fplace;
        downtime=dplace;
    }
};

//用于存放飞机的数据 
class fly:virtual public Book{  
public:
	int  yvpiao; //余票
	fly *next; //指向下一结点的指针 
	fly(int ypiao=0)
	{   
		next=NULL;
		yvpiao=ypiao;
	} //构造函数，初始化变量
}; 

//用于存放客户信息
class customer:virtual public Book{  
public:
	string name;      		//客户姓名
	int seat;         		//座位号
	string no;        		//证件号
	int ps;           		//订票数
	customer *next;			//指向下一结点的指针
	customer(string nname="no",int sseat=0,string nno="no",int pps=0)
	{   
		next=NULL;
		name=nname;
		seat=sseat;
		no=nno;
		ps=pps;
	}
};

//Link类，把数据以链表的形式存储，链表的每个结点为一个Node对象 
class Link{  
private:  
	fly *head1;         					//链表1的头指针，为fly对象类型的指针 
	customer *head2;						//链表2的头指针，为customer对象类型的指针 
public :  
	Link()	{head1=NULL;head2=NULL;} 		//构造函数，初始化链表为空
	fly* getHead(int)	{ return head1; }   		//获取链表1头指针,将数据保存到文件时用到 
	customer* getHead()		{ return head2; }   		//获取链表2头指针,将数据保存到文件时用到 
	void linkClear()	{head1=NULL;}			//清空链表1航班中数据      
	bool linkIsEmpty(int)	{return(head1==NULL);}//判断链表1是否为空,空则返回true
	bool linkIsEmpty()		{return(head2==NULL);}//判断链表2是否为空,空则返回true
	void linkInsert(fly *newnode);			//向链表1中插入新的结点 
	void linkInsert(customer *newnode);			//向链表2中插入新的结点
	bool link_1Delete(int nid);		//从链表1中删除的结点 
	bool link_2Delete(int nid);				//从链表2中删除的结点 
	void linkView(int);						//查看链表1中数据 
	void linkView();						//查看链表2中数据 
	fly* link_1Find(int nid);				//在链表1中查找id结点，返回指向该结点的指针 
	customer* link_2Find(int nid);				//在链表2中查找id为nid结点，返回指向该结点的指针 
	
};

//类fly
class Do:public Link,public customer,public fly{        //继承fly类和customer类和Link类
private:  
	bool k;
	bool l;//记录数据是否被修改 
public:  
	Do(){Load1();k=false;Load2();l=false;}; 
	//下列函数按照顺序排列
	void showMenu();//显示菜单
	void showMenu1();//显示菜单1
	void showMenu2();//显示菜单2
	void dingpiao();  //声明订票函数
	void tuipiao();   //声明退票函数
	void Clear(); //清空航班记录 
	void Insert(); //插入飞机记录 
	void Delete(); //删除飞机记录 
	void Find(); //查找某航班号的记录 
	void View(); //显示所有航班的记录 
	void Load1(); //从文件中读取数据，创建链表1 fly 
	void Load2(); //从文件中读取数据，创建链表2 customer 
	void flySave(); //将飞机数据保存到文件 
	void customerSave(); //将乘客数据保存到文件 
	void Exit1();//退出航班管理系统
	void Exit2();//退出飞机订票系统 
	void showTip();//显示操作提示 
};
bool Link::link_1Delete(int nid)//删除结点，成功则返回true 
{
	fly *p; 
	if(head1==NULL)//链表为空的情况 
		return false; 
	if(head1->id==nid)//删除的为第一个结点的情况 
	{
		head1=head1->next; 
		return true; 
	} 
	p=head1; 
	while(p->next)//删除的为第二个及以后结点的情况 
	{
		if((p->next)->id==nid)
		{ 
			p->next=(p->next)->next; 
			return true; 
		} 
		p=p->next; 
	} 
	return false; 
}  
bool Link::link_2Delete(int nid)//删除结点，成功则返回true 
{
	customer *p; 
	if(head2==NULL)//链表为空的情况 
		return false; 
	if(head2->id==nid)//删除的为第一个结点的情况 
	{
		head2=head2->next; 
		return true; 
	} 
	p=head2; 
	while(p->next)//删除的为第二个及以后结点的情况 
	{
		if((p->next)->id==nid)
		{ 
			p->next=(p->next)->next; 
			return true; 
		} 
		p=p->next; 
	} 
	return false; 
}  

 void Link::linkInsert(fly *newfly)//按id值从小到大的顺序，插入新的结点
{ 
	fly *p1; 
	if(!head1)//链表为空的情况 
		head1=newfly; 
	else if((head1->id)>(newfly->id))//插入到第一个结点的情况 
	{
		newfly->next=head1; 
		head1=newfly; 
	} 
	else//插入到第二个及以后情况 
	{
		p1=head1; 
		while(1)
		{ 
			if(!(p1->next)) //插入到尾节点 
			{ 
				p1->next=newfly; 
				break; 
			} 
			else if((p1->next)->id>newfly->id) //插入到节点p1与下一个节点中 
			{ 
				newfly->next=p1->next; 
				p1->next=newfly; 
				break; 
			} 
			p1=p1->next; 
		} 
	}	 
} 
 void Link::linkInsert(customer *newcustomer)//按id值从小到大的顺序，插入新的结点
{ 
	customer *p1; 
	if(!head2)//链表为空的情况 
		head2=newcustomer; 
	else if((head2->id)>(newcustomer->id))//插入到第一个结点的情况 
	{
		newcustomer->next=head2; 
		head2=newcustomer; 
	} 
	else//插入到第二个及以后情况 
	{
		p1=head2; 
		while(1)
		{ 
			if(!(p1->next)) //插入到尾节点 
			{ 
				p1->next=newcustomer; 
				break; 
			} 
			else if((p1->next)->id>newcustomer->id) //插入到节点p1与下一个节点中 
			{ 
				newcustomer->next=p1->next; 
				p1->next=newcustomer; 
				break; 
			} 
			p1=p1->next; 
		} 
	}	 
} 

void Link::linkView(int g)//显示链表1数据 
{
	fly *p=head1; 
	cout<<setw(10)<<"航班号"<<setw(8)<<"起飞时间"<<setw(8)<<"降落时间"<<setw(8)<<"起飞城市"<<setw(8) <<"降落城市"<<setw(8) 
		<<"余票"<<endl; 
	while(p)
	{ 
		cout<<setw(10)<<p->id<<setw(8)<<p->flytime<<setw(8)<<p->downtime<<setw(8)<<p->flyplace<<setw(8)<<p->downplace
			<<setw(8)<<p->yvpiao<<endl; 
 		p=p->next; 
	} 
} 

void Link::linkView()//显示链表2数据 
{
	customer *p=head2; 
	cout<<setw(10)<<"客户名"<<setw(8)<<"座位号"<<setw(8)<<"航班号"<<setw(8)<<"证件号"<<setw(8)<<"订票数"<<setw(8)<<"起飞时间"<<setw(8)<<"降落时间"<<setw(8)<<"起飞城市"<<setw(8) <<"降落城市"<<setw(8) 
		<<"余票"<<endl; 
	while(p)
	{ 
		cout<<setw(10)<<p->name<<setw(8)<<p->seat<<setw(8)<<p->id<<setw(8)<<p->no<<setw(8)<<p->ps<<setw(8)<<p->flytime<<setw(8)<<p->downtime<<setw(8)<<p->flyplace<<setw(8)<<p->downplace
			<<endl; 
 		p=p->next; 
	} 
} 

fly* Link::link_1Find(int nid)//查找id值为nid的结点，返回该结点的指针
{                           
	fly *p=head1; 
	while(p)
	{ 
		if(p->id==nid) 
			break; 
		else 
			p=p->next; 
	} 
	return p; 
} 

customer* Link::link_2Find(int nid)//查找id值为nid的结点，返回该结点的指针
{                           
	customer *p=head2; 
	while(p)
	{ 
		if(p->id==nid) 
			break; 
		else 
			p=p->next; 
	} 
	return p; 
} 

//class Link 结束 

void Do::showMenu()
{
	cout<<"                "<<"|--------------------------- |"<<endl; 
	cout<<"                "<<"|          航空系统          |"<<endl;
	cout<<"                "<<"|--------------------------- |"<<endl;  
	cout<<"                "<<"|     1.进入飞机订票系统     |"<<endl; 
	cout<<"                "<<"|     2.航班管理系统         |"<<endl;
	cout<<"                "<<"|     0.退出                 |"<<endl;
}
void Do::showMenu1()
{	
	cout<<"                "<<"|--------------------------- |"<<endl; 
	cout<<"                "<<"|       飞机订票系统         |"<<endl;
	cout<<"                "<<"|--------------------------- |"<<endl; 
	cout<<"                "<<"| 1.         订票            |"<<endl; 
	cout<<"                "<<"| 2.         退票            |"<<endl; 
	cout<<"                "<<"| 3.      浏览航班信息       |"<<endl; 
	cout<<"                "<<"| 4.          保存           |"<<endl;  
	cout<<"                "<<"| 0.          退出           |"<<endl; 
	cout<<endl; 
}
void Do::showMenu2()
{ 
	cout<<"                "<<"|---------------------------|"<<endl; 
	cout<<"                "<<"|		航班管理系统		|"<<endl; 
	cout<<"                "<<"|---------------------------|"<<endl; 
	cout<<"                "<<"| 1. 清空：清除所有航班数据 |"<<endl; 
	cout<<"                "<<"| 2. 添加：插入一条航班数据 |"<<endl; 
	cout<<"                "<<"| 3. 删除：删除指定航班数据 |"<<endl; 
	cout<<"                "<<"| 4. 查找：查找指定航班数据 |"<<endl;  
	cout<<"                "<<"| 5. 显示：显示所有航班数据 |"<<endl;  
	cout<<"                "<<"| 0. 退出：安全的退出本系统 |"<<endl; 
	cout<<endl; 
} 

void Do::showTip()
{  
	cout<<endl; 
	cout<<"-------------------操作完成---------------------"<<endl;  
	cout<<"-----------------选择0－6继续-------------------"<<endl;  
	cout<<"请选择：";  
} 

void Do::Clear()//清空航班记录
{ 
	linkClear( ); 
	linkClear(); 
	cout<<"成功清空航班记录！"<<endl; 
} 

void Do::dingpiao( )
{   
	customer *q=new customer(); 
	int sign=0;
	cout<<"请输入你的姓名:"; 
	cin>>name;
	cout<<"请输入航 班 号:";
	cin>>id;
	cout<<"请输入预定票数:";
	cin>>ps;
	cout<<"请输入身份证号:";
	cin>>no;
	if(link_1Find(q->id))//判断航班是否存在 
	{
		linkInsert(q);  
		l=true; 	  
 		cout<<endl; 
	} 
	else cout<<"号为"<<q->id<<"的航班不存在，订票失败！"<<endl; 
} 

void Do::tuipiao()   //退票
{
	cout<<"请输入您的姓名:";
	cin>>name;
	cout<<"请输入航班号:";
	cin>>id;
		if(link_2Delete(id))
		{ 
			cout<<"成功退票！"<<endl; 
			l=true; 
		} 
		else 
			cout<<"你没有订票，退票失败"<<endl; 
}

void Do::Insert()//插入飞机记录 
{
	fly *p=new fly(); 
 	cout<<"请输入航班号："; 
	cin>>p->id; 
	if(!link_1Find(p->id))//判断航班是否存在 
	{
		linkInsert(p); 
		k=true; 	  
		cout<<"请输入起飞时间： "; 
		cin>>p->flytime; 
		cout<<"请输入降落时间："; 
		cin>>p->downtime; 
		cout<<"请输入起飞城市："<<endl; 
 	    cin>>p->flyplace;
 	    cout<<"请输入降落城市："<<endl; 
 	    cin>>p->downplace;
 	    cout<<"请输入票数："<<endl;
		 cin>>p->yvpiao; 
 		cout<<endl; 
	} 
	else cout<<"号为"<<p->id<<"的航班已存在，插入失败！"<<endl; 
} 

void Do::Delete()//删除航班记录 
{
	int i; 
	int g;
	if(linkIsEmpty(g))//链表1为空的情况 
		cout<<"没有航班记录！"<<endl; 
	else
	{ 
		cout<<"请输入航班号："; 
		cin>>i; 
		if(link_1Delete(i))
		{ 
			cout<<"成功删除航班号为"<<i<<"的飞机记录！"<<endl; 
			k=true; 
		} 
		else 
			cout<<"没有找到航班号为"<<i<<"的飞机！"<<endl; 
	} 
} 
void Do::Find()//查找某航班号的航班的记录 
{
	int n; 
	int g;
	fly *p; 
	if(linkIsEmpty(g))//链表1为空的情况 
		cout<<"没有航班记录！"<<endl; 
	else
	{ 
		cout<<"请输入要查找的航班："; 
		cin>>n; 
		p=link_1Find(n);//获得找到的结点的指针 
		if(p)//指针值不为NULL时 
		{
			cout<<setw(10)<<"航班号"<<setw(8)<<"起飞时间"<<setw(8)<<"降落时间"<<setw(8)<<"起飞城市"<<setw(8) <<"降落城市"<<setw(8) 
				<<"余票"<<endl;
			cout<<setw(10)<<p->id<<setw(8)<<p->flytime<<setw(8)<<p->downtime<<setw(8)<<p->flyplace<<setw(8)<<p->downplace
				<<setw(8)<<p->yvpiao<<endl; 
		} 
		else//指针值为NULL时 
			cout<<"没有找到航班号为"<<n<<"的航班记录！"<<endl; 
	} 
} 
void Do::View()//显示所有航班的记录 
{  
	int g;
	if(linkIsEmpty(g)) 
		cout<<"没有航班记录！"<<endl; 
	else 
		linkView(g); 
} 

void Do::Load1()//从文件中读入数据，创建链表1 fly
{
	fly *p; 
	int nid; 
	ifstream infile("fly.txt"); 
	if(!infile) 
		cerr<<"错误：数据文件不能打开!\n"; 
	else 
		while(infile>>nid)//读取航班，直到读空
		{ 
			p=new fly(); 
			p->id=nid; 
			infile>>p->id>>p->flytime>>p->downtime>>p->flyplace>>p->downplace>>p->yvpiao;//读取航班 
			linkInsert(p); 
		} 
	infile.close(); //关闭文件 
} 
void Do::flySave()//将航班数据保存到文件 
{
	int g;
	fly *p=getHead(g); 
	ofstream outfile("fly.txt"); 
	if(!outfile) 
		cerr<<"错误：数据文件不能打开!\n"; 
	else
	{ 
		if(k==true)
		{
			while(p)
			{ 
				outfile<<p->id<<' '<<p->flytime<<' '<<p->downtime<<' '<<p->flyplace<<' '<<p->downplace <<' '<<p->yvpiao<<' '<<endl; 
				p=p->next; 
			} 
			k=false; 
			cout<<"保存成功！"<<endl; 
	 	}
	 	else cout<<"数据未变动，保存失败！！！"<<endl; 
	} 
} 

void Do::Load2()//从文件中读入数据，创建链表2 customer
{
	customer *q; 
	int nid; 
	ifstream infile("customer.txt"); 
	if(!infile) 
		cerr<<"错误：数据文件不能打开!\n"; 
	else 
		while(infile>>nid)//读取乘客，直到读空
		{ 
			q=new customer(); 
			q->id=nid; 
			infile>>q->id>>q->name>>q->seat>>q->no>>q->ps>>flytime>>q->downtime>>q->flyplace>>q->downplace;//读取乘客
			linkInsert(q); 
		} 
	infile.close(); //关闭文件 
} 
void Do::customerSave()//将乘客数据保存到文件 
{
	customer *q=getHead(); 
	ofstream outfile("customer.txt"); 
	if(!outfile) 
		cerr<<"错误：数据文件不能打开!\n"; 
	else
	{ 
		if(l==true)
		{
			while(q)
			{ 
				outfile<<q->id<<' '<<q->name<<' '<<q->seat<<' '<<q->id<<' '<<q->no<<' '<<q->ps<<' '<<q->flytime<<' '<<q->downtime<<' '<<q->flyplace<<' '<<q->downplace 
				<<' '<<endl; 
				q=q->next; 
			} 
			l=false; 
			cout<<"保存成功！"<<endl; 
	 	}
	 	else cout<<"数据未变动，保存失败！！！"<<endl; 
	} 
} 

void Do::Exit1()
{ 
	char s='Y'; 
	if(k)//判断数据是否修改 
	{
		cout<<"数据已经改变，是否保存？(y/n)："; 
		cin>>s; 
		if(s=='y'||s=='Y') 
			flySave(); 
	} 
	cout<<"谢谢使用，已安全退出航班管理系统！"; 
	getchar();
	
} 
void Do::Exit2()
{ 
	char s='Y'; 
	if(l)//判断数据是否修改 
	{
		cout<<"数据已经改变，是否保存？(y/n)："; 
		cin>>s; 
		if(s=='y'||s=='Y') 
			customerSave(); 
	} 
	cout<<"谢谢使用，已安全退出飞机订票系统！"; 
	getchar();
	
} 

int main()
{ 
	cout<<"           ╭╮　╭☆╭──╮╭╮　　　☆╮　　　╭───╮  ╭╮"<<endl;
	cout<<"           ││　│││╭─★││　　　││　　　★╭─╮│  ││"<<endl;
	cout<<"           │╰─╯││╰╮　││　　　││　　　││　││  ││"<<endl;
	cout<<"           │╭─╮││╭╯　││      ││　    ╰╯    │  ││"<<endl;
	cout<<"           ││　│││╰─╮│╰──╮│╰──╮│╰─╯│  ││"<<endl;
	cout<<"           ╰★　╰╯╰──╯☆───╯★───╯╰───☆   ★"<<endl;
	cout<<" "<<endl;
	system("pause");
	Do f; 
	int n=0; 
	while(!n) 
 	{
	 	int m,a,b;
		system("cls"); 
 		f.showMenu();  //显示主菜单 
		cout<<"选择对应数字进行操作:"; 
  		cin>>m;  
  		switch(m)  
 		 {  
  			case 0:n=1;cout<<"**谢谢使用航空系统**"<<endl;break;  
  			case 1:
			  {
        	      system("cls"); f.showMenu1();//显示菜单1 
				  cin>>a;
				  switch(a)
				  {
				  	case 0:m=1;system("cls");f.Exit2();system("pause");break;  
  				    case 1:system("cls");f.dingpiao();system("pause");break;  
 		 	       	case 2:system("cls");f.tuipiao();system("pause");break;    
  			        case 3:system("cls");f.View();system("pause");break;  
  				    case 4:system("cls");f.customerSave();system("pause");break;  
  				    default:cout<<"输入错误，请重新选择！";system("pause");
			      } continue;
		     } 
 		 	case 2:
			  {
				    system("cls");
				    int a,b;
	    			cout<<"请输入账号"<<endl;
	    			cin>>a;
	    			cout<<"请输入密码"<<endl;
					cin>>b;
					if(a==1&&b==110) //验证密码 
					{     
						f.showMenu2();//显示菜单2 
				    	cin>>b;
						switch(b)
				    	{
				 		case 0:m=1;system("cls");f.Exit1();system("pause");break;
						case 1:system("cls");f.Clear();f.flySave();system("pause");break;
						case 2:system("cls");f.Insert();f.flySave();system("pause");break;
						case 3:system("cls");f.Delete();f.flySave();system("pause");break;
						case 4:system("cls");f.Find();system("pause");break;
						case 5:system("cls");f.View();system("pause");break;
                    	default:cout<<"输入错误，请重新选择!";system("pause");; 
						}break; 
					} 
					else
					{ 
						cout<<"对不起，你没有权限，请返回。"<<endl;system("pause");break;
					}
			 } 
			default: cout<<"请重新输入..."<<endl;system("pause");	
		}
	}
	return 0;		
}


