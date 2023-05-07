
#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<string>
using namespace std;

#define MaxInt 32767
#define MVNum 100
int path[100][100]={0};///graph[i][j]为0表示i, j两点之间不通，为1表示有一条路
int stack1[120], m=1;///存储路径

typedef struct message    
{
    int num;          //景点代码
    char name[100];    //景点名称
    char pro[500];      //简介
} message;

typedef message VerTexType;
typedef int ArcType;
typedef struct
{
    VerTexType vexs[MVNum];      //顶点 即为景点 
    ArcType arcs[MVNum][MVNum];   //边  即为景点之间的路径 
    int vexnum,arcnum;           //顶点数   边数 
} AMGraph;                 //邻接矩阵创建图 
AMGraph G;
//录入信息 
message  school[20]= {{1,"图书馆","学生借阅资料学习提升自己"},{2,"升旗广场","升旗仪式举办场所"},{3,"行政楼","老师办公场所"},
    {4,"正门","学生主要进出通道"},{5,"工程训练中心","学生进行工程训练场所"},{6,"教学楼","学生上课场所"},{7,"南区食堂","两个食堂中较好吃的一个"},
    {8,"实训中心","老师办公及学生做实验"},{9,"北区操场","学生体育锻炼场所"},{10,"大学生活动中心","大学生进行课外活动场所"}
};
message q[100] = {{1,"图书馆","学生借阅资料学习提升自己"},{2,"升旗广场","升旗仪式举办场所"},{3,"行政楼","老师办公场所"},
    {4,"正门","学生主要进出通道"},{5,"工程训练中心","学生进行工程训练场所"},{6,"教学楼","学生上课场所"},{7,"南区食堂","两个食堂中较好吃的一个"},
    {8,"实训中心","老师办公及学生做实验"},{9,"北区操场","学生体育锻炼场所"},{10,"大学生活动中心","大学生进行课外活动场所"}};

void CreatMap(AMGraph &G)   //初始化图 
{
	ifstream myfile("D:\\课设存盘\\新建 文本文档.txt");
    int i,j;
    G.vexnum=10;
    G.arcnum=12;
    for(i=0; i<G.vexnum; i++)
        for(j=0; j<G.vexnum; j++)
            G.arcs[i][j]=MaxInt;       //路径全部初始为最大值 
    if (!myfile.is_open())
	{
    	//输入已知路线长度
    	G.arcs[0][1]=1;
    	G.arcs[0][2]=9;
    	G.arcs[1][9]=9;
    	G.arcs[2][3]=2;
    	G.arcs[2][9]=2;
    	G.arcs[2][4]=7;
    	G.arcs[3][6]=9;
    	G.arcs[4][7]=7;
    	G.arcs[0][7]=2;
    	G.arcs[1][5]=5;
    	G.arcs[0][8]=8;
    	G.arcs[5][8]=9;
	}
	else 
	{
		ifstream infile("D:\\课设存盘\\新建 文本文档.txt", ios::in);
    	if(!infile.fail())
    	{
    		for(int i=0;i<G.vexnum ;i++)
    		{
    			for(int j=0;j<G.vexnum ;j++)
    			{
    				while(!infile.eof())
    	    		{
     	       			char s;
     	       			infile>>s;
     	       			s>>G.arcs[i][j];
     	   			}
				}
    		}
		}
		infile.close();
	}
    for(i=0; i<10; i++)
        G.vexs[i]=school[i];     //结合之前定义的数组school 
    for(i=0; i<G.vexnum; i++)
    {
	    for(j=0; j<G.vexnum; j++)
	    {
	    	G.arcs[j][i]=G.arcs[i][j];    //无向图 
	    	if(G.arcs[i][j]<MaxInt)
			{
				path[i][j]=path[j][i]=1;     //值为1表示有一条路 
			}
		}
	}
	
}

void Cunpan(AMGraph G)
{
	int i, j;
	ofstream  outFile;
	//  打开文件。  下面路径根据自己情况做修改。
	outFile.open("D:\\课设存盘\\新建 文本文档.txt");

	for (i = 0; i<G.vexnum; i++)    //写入数据
	{
		outFile << G.vexs[i].num;
		if (i == G.vexnum-1)
			outFile << endl;
	}
	//AMGraph G;
	for (i = 0; i<G.vexnum; ++i)
	{
		for (j = 0; j<G.vexnum; ++j)
		{
			if (G.arcs[i][j] != MaxInt)
				outFile << G.arcs[i][j];
			else
				outFile <<"#";
		}
		outFile << endl;
	}
	outFile.close();  //关闭文件
}

void Dupan()
{
	
    ifstream infile("D:\\课设存盘\\新建 文本文档.txt", ios::in);
    if(!infile.fail())
    {
    	int i=0;
        while(!infile.eof())
        {
            string s;
            infile>>s;
            cout<<endl;
            cout<<s<<"  ";
        }
    }
	infile.close();
}

void dfs(int x,int y,AMGraph &G)        //dfs求所有路径 
{
    int i, j;
    for(i=1; i<=G.arcnum ; i++)
    {
        if(path[x][i]==1)          //x顶点到i顶点存在路 
        {
            if(i == y)///如果深搜到了终点，就输出刚才经过的路径
            {
                for(j=0; j<m; j++)     //第一次循环m=1   stack1[m]模拟存储路径的栈 
                {
                    printf("%s-->", G.vexs[stack1[j]].name );     //输出栈内所有元素即中间路径 stack1存储路径  stack1[0]=x-1 
                }
                printf("%s\n\n", G.vexs[y].name);     //输出终点 
            }
            else///如果该点不是终点
            {
                path[x][i] = 0;    //不是终点将该路径置为0 
                stack1[m] = i;///将该点存起来  入栈 
                m++;
                dfs(i,y,G);///接着深搜   将i作为起点 
                path[x][i] = 1;
                m--;                  //出栈 
            }
        }
    }
}

void PrintMap()     //输出地图 
{
    cout<<"\n";
    cout<<"┍---------------------------------------------------------------------┑\n";
    cout<<"                         【学校地图】\n|\n";
    cout<<"  实训中心(8)--------北区操场(9)                      \n";
    cout<<"      |                  |                           \n";
    cout<<"  工程训练中心(5)------图书馆(1)---------大学生活动中心(10) \n";
    cout<<"      |                  |                  |      \n";
    cout<<"   行政楼(3)---------升旗广场(2)--------教学楼(6)--------南区食堂(7)\n\n";
    cout<<"┕---------------------------------------------------------------------┙\n";
    
}

void PrintPlace(AMGraph G,int num)
{
    cout<<"【景点编码】:"<<G.vexs[num-1].num<<"\n【景点名称】:"<<G.vexs[num-1].name<<"\n【景点简介】:"<<G.vexs[num-1].pro<<endl;
}

void SeePlace(AMGraph G)       //调用PrintPlace两个函数输出景点简介 
{   
    for(int i=0; i<G.vexnum; i++)
        PrintPlace(G,i+1);
}

void Menu(AMGraph &G)     //菜单函数  输出展示界面  反馈指令 
{
	system("color 70");  //白底黑字 
	int i,k=0;
 	printf("\n\t      *****************欢迎使用校园导航系统**************\n");
 	printf("\t__________________________________________________________________\n\n");
 	printf("\t\t场所名称\t\t|\t场所描述\n");
 	printf("\t________________________________|_________________________________\n\n");
 	for(i=0;i<G.vexnum ;i++)
 	{
		printf("\t%c (%2d)%-10s\t\t|\t%-25s%c\n",3,i+1,G.vexs[i].name  ,G.vexs[i].pro ,3); /* 输出场所列表 */
 		k=k+1;
 	}
 	printf("\t________________________________|_________________________________\n\n");
    cout<<"\t\t    ┍------------------------------------------------------------┑\n";
    cout<<"\t\t      \t（1）--查看学校平面图\n";
    cout<<"\t\t      \t（2）--查看两个场所之间的所有路径\n";
    cout<<"\t\t      \t（3）--运用迪杰斯特拉算法查看两个场所之间的最短路径\n";
    cout<<"\t\t      \t（4）--运用弗洛伊德算法查看两个场所之间的最短路径\n";
    cout<<"\t\t      \t（5）--增加新的顶点\n";
    cout<<"\t\t      \t（6）--删除指定路线\n";
    cout<<"\t\t      \t（7）--查看指定场所信息\n";
    cout<<"\t\t      \t（8）--更改场所相关信息\n";
	cout<<"\t\t      \t（9）--查看边的信息\n";
	cout<<"\t\t      \t（10）--更改两个场所之间的距离\n";
    cout<<"\t\t      \t（0）--退出程序\n";
    cout<<"\t\t   ┕------------------------------------------------------------┙\n";
    cout<<"请输入指令(0-10):";
}

int CheckNum(int num,AMGraph G)        //确认有这个序号
{
    for(int i=0; i<G.vexnum; i++)
        if(G.vexs[i].num==num)
            return 1;
    return 0;
}

void Change(AMGraph &G,int v,int n,int visited[])    //景点信息更改函数   v=0  n=num-1 
{
    if(n==v)
    {
        cout<<"请输入新的景点名称:";
        cin>>G.vexs[n].name;
        cout<<">景点名称更改为:"<<G.vexs[n].name<<endl;
        cout<<"请输入新的景点简介:";
        cin>>G.vexs[n].pro;
        cout<<">景点简介更改为:"<<G.vexs[n].pro<<endl;
        cout<<"景点信息更改完成."<<endl;
    }
    visited[v]=1;
    for(int w=0; w<G.vexnum; w++)
        if((G.arcs[v][w]!=0)&&(!visited[w]))
            Change(G,w,n,visited);
    Cunpan(G);
}

void NewPlace(AMGraph &G)    //景点信息增加函数 
{
    int new_num,num,n = 0,i,j;
    cout<<"输入新景点编码:";
    cin>>school[G.vexnum].num;
    if(CheckNum(school[G.vexnum].num,G))
    {
        cout<<"景点编码已存在!\n";
        return;
    }
    cout<<"输入新景点名称:";
    cin>>school[G.vexnum].name;
    cout<<"输入新景点简介:";
    cin>>school[G.vexnum].pro;
    G.vexs[G.vexnum]=school[G.vexnum];
    //cout<<G.vexs[G.vexnum].num<<' '<<G.vexs[G.vexnum].name<<"\n";
    for(int i=0; i<=G.vexnum; i++)
        G.arcs[i][G.vexnum]=MaxInt;
    cout<<"输入新景点相关路线信息(应包含两端点以及路线长度,输入0 0结束):\n";
    cin>>new_num>>num;
    while(new_num!=0)
    {
        new_num=new_num-1;
        num=num-1;
        n++;//增加边数
        cin>>G.arcs[new_num][num];
        G.arcs[num][new_num]=G.arcs[new_num][num];//注意编码比数组坐标大1！
        cin>>new_num>>num;
    }
    cout<<"景点【"<<school[G.vexnum].name<<"】创建成功";
    for(i=0; i<=G.vexnum; i++)
        for(j=0; j<=G.vexnum; j++)
            G.arcs[j][i]=G.arcs[i][j];
    G.vexnum++;
    G.arcnum=G.arcnum+n;
    Cunpan(G);
}

void DeleteRoad(AMGraph &G)       //景点信息删除函数 
{
    int num1,num2;
    cout<<"输入删除路线端点:";
    cin>>num1>>num2;
    num1--;
    num2--;
    G.arcs[num1][num2]=MaxInt;
    G.arcs[num2][num1]=MaxInt;
    cout<<"删除【"<<G.vexs[num1].name<<"】到【"<<G.vexs[num2].name<<"】路线成功\n";
    Cunpan(G);
}

#define inf 99999999
using namespace std;
void kaishidaohang();
int map[110][110],book[110],dis[110];
 

 
void cuntu()		//存储景点信息、同时存图，各边信息 
{
	int i,j;
	strcpy(q[1].name,"图书馆");strcpy(q[1].pro,"学生借阅资料学习提升自己");
	strcpy(q[2].name,"升旗广场");strcpy(q[2].pro,"升旗仪式举办场所");
	strcpy(q[3].name,"行政楼");strcpy(q[3].pro,"老师办公场所"); 
	strcpy(q[4].name,"正门");strcpy(q[4].pro,"学生主要进出通道");
	strcpy(q[5].name,"工程训练中心");strcpy(q[5].pro,"学生进行工程训练场所"); 
	strcpy(q[6].name,"教学楼");strcpy(q[6].pro,"学生上课场所");
	strcpy(q[7].name,"南区食堂");strcpy(q[7].pro,"两个食堂中较好吃的一个");
	strcpy(q[8].name,"实训中心");strcpy(q[8].pro,"老师办公及学生做实验");
	strcpy(q[9].name,"北区操场");strcpy(q[9].pro,"学生体育锻炼场所");
	strcpy(q[10].name,"大学生活动中心");strcpy(q[10].pro,"大学生进行课外活动场所");

	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
		{
			if(i==j)
				map[i][j]=0;
			else
				map[i][j]=inf;
		}
		map[1][2]=1;
    	map[1][3]=9;
    	map[2][10]=9;
    	map[3][4]=2;
    	map[3][10]=2;
    	map[3][5]=7;
    	map[4][7]=9;
    	map[5][8]=7;
    	map[1][8]=2;
    	map[2][6]=5;
    	map[1][9]=8;
    	map[6][9]=9;

    	map[2][1]=1;
    	map[3][1]=9;
    	map[10][2]=9;
    	map[4][3]=2;
    	map[10][3]=2;
    	map[5][3]=7;
    	map[7][4]=9;
    	map[8][5]=7;
    	map[8][1]=2;
    	map[6][2]=5;
    	map[9][1]=8;
    	map[9][6]=9;

	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
			map[j][i]=map[i][j];
}
 
 
 //迪杰斯特拉求最短路径，并输出路线
void Dijkstra(int v0,int s)		 
{
	int min,i,j,u,v;
	int p[110],l[110];
	memset(p,-1,sizeof(p));
	memset(l,0,sizeof(l));
	memset(book,0,sizeof(book));
	for(i=1;i<=10;i++)
	{
		dis[i]=map[v0][i];
		if(dis[i]<inf)			//v0能直接到达，即上一站点为v0 
			p[i]=v0;
	}
		
	book[v0]=1;
	
	for(i=1;i<10;i++)
	{
		min=inf;
		for(j=1;j<=10;j++)			//每次找出距离v0最近点 
		{
			if(book[j]==0&&dis[j]<min)
			{
				min=dis[j];
				u=j;
			}
		}
		book[u]=1;			//标记该点 
		for(v=1;v<=10;v++)
		{
			if(book[v]==0&&dis[v]>dis[u]+map[u][v])			//通过最近点更新其他边 
			{
				p[v]=u;					//存储更新的边，即为路线 
				dis[v]=dis[u]+map[u][v];
			}
		}
	}
	v=s;
	i=1;
	while(p[v]!=v0)			//将路线存入栈中，正序输出 
	{	
		l[i++]=p[v];
		v=p[v];
	}
	printf("\n");
	u=i-1;
	printf("路线为：\n");
	printf("%s--->",q[v0].name);
	for(i=u;i>=1;i--)
		printf("%s--->",q[l[i]].name); 
	printf("%s\n",q[s].name);
	printf("最短路径长度为：%d00 米\n",dis[s]);
}
 
//迪杰斯特拉 
void DJS()
{
	int x,m,n,u,v,i,j;
	char c[100];

	printf("请输入起点景点编号：\n");
	scanf("%d",&n);
	printf("\n请输入终点景点编号：\n");
	scanf("%d",&m);
	while(1)
		{
		if(n>=1&&n<=10&&m>=1&&m<=10&&n!=m)
		{
			Dijkstra(n,m);
			break;
			}
		else
			{
				printf("\n输入不合法！请重新输入！\n\n");
				printf("请输入起点景点编号：\n");
				scanf("%d",&n);
				printf("\n请输入终点景点编号：\n");
				scanf("%d",&m);
				}
			}
	
}


//用弗洛伊德算法求最短路径，并输出路线
void ShortestPath_Floyd(AMGraph G)
{
    int i,j,k;
	int D[MVNum][MVNum],path[MVNum][MVNum];    //D数组与S数组  D数组存最短的路径  S[i][j]=k即i到j最短路径经过k 
    int place[MVNum];
    int v0,v1;                  //起点与终点 
    for(i=0; i<G.vexnum; i++)
        for(j=0; j<G.vexnum; j++)
        {
            D[i][j]=G.arcs[i][j];      //初始化两个二维数组 
            if(D[i][j]<MaxInt&&i!=j)
                path[i][j]=i;//j前驱为i  
            else
                path[i][j]=-1;//j前驱为-1 不存在路置为-1 
        }
    for(k=0; k<G.vexnum; k++)                 //三层循环 
        for(i=0; i<G.vexnum; i++)
            for(j=0; j<G.vexnum; j++)
                if(D[i][k]+D[k][j]<D[i][j])//从i到k,再到j路径更短
                {
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=path[k][j];
                }
    for(i=0; i<G.vexnum; i++)
        for(j=0; j<G.vexnum; j++)
            if(i==j)
                D[i][j]=D[j][i]=0;
    cout<<"请输入起点:";
    cin>>v0;
    cout<<"请输入终点:";
    cin>>v1;
    if(v0==0)
    {
    	cout<<"起点输入错误，请重新输入起点";
		cin>>v0; 
	}
	if(v1==0)
    {
    	cout<<"终点输入错误，请重新输入终点";
		cin>>v1; 
	}
    v0--;
    v1--;//下标从0开始
    int t=v1;//v1接下来会改变,寄存给t
    i=0;
    cout<<"【"<<G.vexs[v0].name<<"】到【"<<G.vexs[v1].name<<"】的最短距离为 "<<D[v0][v1]<<"00  m\n";
    cout<<"\n其最短路线为 :【"<<G.vexs[v0].name<<"】<->";
    while(path[v0][v1]!=v0)
    {
        place[i]=path[v0][v1];
        i++;
        v1=path[v0][v1];         //一个一个将所有的中转结点存入place[]数组中 
    }
    i--;
    for(i; i>=0; i--)
        cout<<"【"<<G.vexs[place[i]].name<<"】<->";
    cout<<"【"<<G.vexs[t].name<<"】"<<endl;
}




void changedis()
{
	int i,j,n,p;
	printf("请输入起点景点编号：\n");
	scanf("%d",&n);
	printf("\n请输入终点景点编号：\n");
	scanf("%d",&m);

	
	for(i=1;i<=10;i++){
		for(j=1;j<=10;j++)
		{
			if(n==i&&m==j&&map[i][j]>0&&map[i][j]<inf){
				cout << "有直接路径，可以修改"<<endl;
				cout<<"修改前直接路径长度："<<map[i][j]<<"00 m"<<endl;
				cout<<"请输入修改长度："<<endl;
				scanf("%d",&p);
				map[i][j] = p/100;
				cout << "修改后距离:" << map[i][j]<<"00 m"<< endl;
				cout<<"修改成功" <<endl;
			}
			else if(n==i&&m==j)
				cout << "无直接路径，不可修改"<<endl;
		}
	}

}



void Edgemessage()
{
	int i,j,n,p;
	printf("请输入起点景点编号：\n");
	scanf("%d",&n);
	printf("\n请输入终点景点编号：\n");
	scanf("%d",&m);

	
	for(i=1;i<=10;i++){
		for(j=1;j<=10;j++)
		{
			if(n==i&&m==j&&map[i][j]>0&&map[i][j]<inf){
				cout<<"有连接通路"<<endl;
				cout<<"边的信息："<<endl;
				printf("%s--->",q[i].name);
				printf("%s\n",q[j].name);
				printf("连接长度为：%d00 米\n",map[i][j]);
			}
			else if(n==i&&m==j)
				cout << "无连接通路"<<endl;
		}
	}

}



void Order(AMGraph G)    //收到指令调用各个子函数 
{
    while(1)
    {
        int x,num,visited[MVNum]= {0};;
        Menu(G);
        cin>>x;
        switch(x)
        {
        case 0:
            cout<<"\n成功退出程序...\n";
            return;
            break;

        case 1:
            PrintMap();
            system("pause");
            system("cls");
            break;
            
        case 2:
            int x,y;
            cout<<"请输入起点：  ";
			cin>>x;
			cout<<"请输入终点：  ";
			cin>>y;
			y=y-1;
			stack1[0] = x-1;
			dfs(x,y,G); 
            system("pause");
            system("cls");
            break;

		case 3:
			cuntu();
			DJS();
			system("pause");
            system("cls");
			break;

        case 4:
            ShortestPath_Floyd(G);
            system("pause");
            system("cls");
            break;

        case 5:
            NewPlace(G);
            system("pause");
            system("cls");
            break;

        case 6:
            DeleteRoad(G);
            system("pause");
            system("cls");
            break;

        case 7:
            cout<<"请输入查找景点编码:";
            cin>>num;
            if(!CheckNum(num,G))
                cout<<"无效编码！"<<endl;
            else
                PrintPlace(G,num);
            system("pause");
            system("cls");
            break;

        case 8:
            cout<<"要更改的景点编码:";
            cin>>num;
            if(!CheckNum(num,G))
                cout<<"无效编码！"<<endl;
            else
                Change(G,0,num-1,visited);
            system("pause");
            system("cls");
            break;

		case 9:
			cuntu();
			Edgemessage();
			system("pause");
            system("cls");
            break;

		case 10:
			cuntu();
			changedis();
			system("pause");
            system("cls");
            break;
        default:
            system("pause");
            system("cls");
        }
    }
}

int main()
{
    AMGraph G;
    CreatMap(G);
    Cunpan(G);
    Order(G);
    
    return 0;
}