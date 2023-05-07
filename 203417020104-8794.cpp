
#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<string>
using namespace std;

#define MaxInt 32767
#define MVNum 100
int path[100][100]={0};///graph[i][j]Ϊ0��ʾi, j����֮�䲻ͨ��Ϊ1��ʾ��һ��·
int stack1[120], m=1;///�洢·��

typedef struct message    
{
    int num;          //�������
    char name[100];    //��������
    char pro[500];      //���
} message;

typedef message VerTexType;
typedef int ArcType;
typedef struct
{
    VerTexType vexs[MVNum];      //���� ��Ϊ���� 
    ArcType arcs[MVNum][MVNum];   //��  ��Ϊ����֮���·�� 
    int vexnum,arcnum;           //������   ���� 
} AMGraph;                 //�ڽӾ��󴴽�ͼ 
AMGraph G;
//¼����Ϣ 
message  school[20]= {{1,"ͼ���","ѧ����������ѧϰ�����Լ�"},{2,"����㳡","������ʽ�ٰ쳡��"},{3,"����¥","��ʦ�칫����"},
    {4,"����","ѧ����Ҫ����ͨ��"},{5,"����ѵ������","ѧ�����й���ѵ������"},{6,"��ѧ¥","ѧ���Ͽγ���"},{7,"����ʳ��","����ʳ���нϺóԵ�һ��"},
    {8,"ʵѵ����","��ʦ�칫��ѧ����ʵ��"},{9,"�����ٳ�","ѧ��������������"},{10,"��ѧ�������","��ѧ�����п�������"}
};
message q[100] = {{1,"ͼ���","ѧ����������ѧϰ�����Լ�"},{2,"����㳡","������ʽ�ٰ쳡��"},{3,"����¥","��ʦ�칫����"},
    {4,"����","ѧ����Ҫ����ͨ��"},{5,"����ѵ������","ѧ�����й���ѵ������"},{6,"��ѧ¥","ѧ���Ͽγ���"},{7,"����ʳ��","����ʳ���нϺóԵ�һ��"},
    {8,"ʵѵ����","��ʦ�칫��ѧ����ʵ��"},{9,"�����ٳ�","ѧ��������������"},{10,"��ѧ�������","��ѧ�����п�������"}};

void CreatMap(AMGraph &G)   //��ʼ��ͼ 
{
	ifstream myfile("D:\\�������\\�½� �ı��ĵ�.txt");
    int i,j;
    G.vexnum=10;
    G.arcnum=12;
    for(i=0; i<G.vexnum; i++)
        for(j=0; j<G.vexnum; j++)
            G.arcs[i][j]=MaxInt;       //·��ȫ����ʼΪ���ֵ 
    if (!myfile.is_open())
	{
    	//������֪·�߳���
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
		ifstream infile("D:\\�������\\�½� �ı��ĵ�.txt", ios::in);
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
        G.vexs[i]=school[i];     //���֮ǰ���������school 
    for(i=0; i<G.vexnum; i++)
    {
	    for(j=0; j<G.vexnum; j++)
	    {
	    	G.arcs[j][i]=G.arcs[i][j];    //����ͼ 
	    	if(G.arcs[i][j]<MaxInt)
			{
				path[i][j]=path[j][i]=1;     //ֵΪ1��ʾ��һ��· 
			}
		}
	}
	
}

void Cunpan(AMGraph G)
{
	int i, j;
	ofstream  outFile;
	//  ���ļ���  ����·�������Լ�������޸ġ�
	outFile.open("D:\\�������\\�½� �ı��ĵ�.txt");

	for (i = 0; i<G.vexnum; i++)    //д������
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
	outFile.close();  //�ر��ļ�
}

void Dupan()
{
	
    ifstream infile("D:\\�������\\�½� �ı��ĵ�.txt", ios::in);
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

void dfs(int x,int y,AMGraph &G)        //dfs������·�� 
{
    int i, j;
    for(i=1; i<=G.arcnum ; i++)
    {
        if(path[x][i]==1)          //x���㵽i�������· 
        {
            if(i == y)///������ѵ����յ㣬������ղž�����·��
            {
                for(j=0; j<m; j++)     //��һ��ѭ��m=1   stack1[m]ģ��洢·����ջ 
                {
                    printf("%s-->", G.vexs[stack1[j]].name );     //���ջ������Ԫ�ؼ��м�·�� stack1�洢·��  stack1[0]=x-1 
                }
                printf("%s\n\n", G.vexs[y].name);     //����յ� 
            }
            else///����õ㲻���յ�
            {
                path[x][i] = 0;    //�����յ㽫��·����Ϊ0 
                stack1[m] = i;///���õ������  ��ջ 
                m++;
                dfs(i,y,G);///��������   ��i��Ϊ��� 
                path[x][i] = 1;
                m--;                  //��ջ 
            }
        }
    }
}

void PrintMap()     //�����ͼ 
{
    cout<<"\n";
    cout<<"��---------------------------------------------------------------------��\n";
    cout<<"                         ��ѧУ��ͼ��\n|\n";
    cout<<"  ʵѵ����(8)--------�����ٳ�(9)                      \n";
    cout<<"      |                  |                           \n";
    cout<<"  ����ѵ������(5)------ͼ���(1)---------��ѧ�������(10) \n";
    cout<<"      |                  |                  |      \n";
    cout<<"   ����¥(3)---------����㳡(2)--------��ѧ¥(6)--------����ʳ��(7)\n\n";
    cout<<"��---------------------------------------------------------------------��\n";
    
}

void PrintPlace(AMGraph G,int num)
{
    cout<<"��������롿:"<<G.vexs[num-1].num<<"\n���������ơ�:"<<G.vexs[num-1].name<<"\n�������顿:"<<G.vexs[num-1].pro<<endl;
}

void SeePlace(AMGraph G)       //����PrintPlace����������������� 
{   
    for(int i=0; i<G.vexnum; i++)
        PrintPlace(G,i+1);
}

void Menu(AMGraph &G)     //�˵�����  ���չʾ����  ����ָ�� 
{
	system("color 70");  //�׵׺��� 
	int i,k=0;
 	printf("\n\t      *****************��ӭʹ��У԰����ϵͳ**************\n");
 	printf("\t__________________________________________________________________\n\n");
 	printf("\t\t��������\t\t|\t��������\n");
 	printf("\t________________________________|_________________________________\n\n");
 	for(i=0;i<G.vexnum ;i++)
 	{
		printf("\t%c (%2d)%-10s\t\t|\t%-25s%c\n",3,i+1,G.vexs[i].name  ,G.vexs[i].pro ,3); /* ��������б� */
 		k=k+1;
 	}
 	printf("\t________________________________|_________________________________\n\n");
    cout<<"\t\t    ��------------------------------------------------------------��\n";
    cout<<"\t\t      \t��1��--�鿴ѧУƽ��ͼ\n";
    cout<<"\t\t      \t��2��--�鿴��������֮�������·��\n";
    cout<<"\t\t      \t��3��--���õϽ�˹�����㷨�鿴��������֮������·��\n";
    cout<<"\t\t      \t��4��--���ø��������㷨�鿴��������֮������·��\n";
    cout<<"\t\t      \t��5��--�����µĶ���\n";
    cout<<"\t\t      \t��6��--ɾ��ָ��·��\n";
    cout<<"\t\t      \t��7��--�鿴ָ��������Ϣ\n";
    cout<<"\t\t      \t��8��--���ĳ��������Ϣ\n";
	cout<<"\t\t      \t��9��--�鿴�ߵ���Ϣ\n";
	cout<<"\t\t      \t��10��--������������֮��ľ���\n";
    cout<<"\t\t      \t��0��--�˳�����\n";
    cout<<"\t\t   ��------------------------------------------------------------��\n";
    cout<<"������ָ��(0-10):";
}

int CheckNum(int num,AMGraph G)        //ȷ����������
{
    for(int i=0; i<G.vexnum; i++)
        if(G.vexs[i].num==num)
            return 1;
    return 0;
}

void Change(AMGraph &G,int v,int n,int visited[])    //������Ϣ���ĺ���   v=0  n=num-1 
{
    if(n==v)
    {
        cout<<"�������µľ�������:";
        cin>>G.vexs[n].name;
        cout<<">�������Ƹ���Ϊ:"<<G.vexs[n].name<<endl;
        cout<<"�������µľ�����:";
        cin>>G.vexs[n].pro;
        cout<<">���������Ϊ:"<<G.vexs[n].pro<<endl;
        cout<<"������Ϣ�������."<<endl;
    }
    visited[v]=1;
    for(int w=0; w<G.vexnum; w++)
        if((G.arcs[v][w]!=0)&&(!visited[w]))
            Change(G,w,n,visited);
    Cunpan(G);
}

void NewPlace(AMGraph &G)    //������Ϣ���Ӻ��� 
{
    int new_num,num,n = 0,i,j;
    cout<<"�����¾������:";
    cin>>school[G.vexnum].num;
    if(CheckNum(school[G.vexnum].num,G))
    {
        cout<<"��������Ѵ���!\n";
        return;
    }
    cout<<"�����¾�������:";
    cin>>school[G.vexnum].name;
    cout<<"�����¾�����:";
    cin>>school[G.vexnum].pro;
    G.vexs[G.vexnum]=school[G.vexnum];
    //cout<<G.vexs[G.vexnum].num<<' '<<G.vexs[G.vexnum].name<<"\n";
    for(int i=0; i<=G.vexnum; i++)
        G.arcs[i][G.vexnum]=MaxInt;
    cout<<"�����¾������·����Ϣ(Ӧ�������˵��Լ�·�߳���,����0 0����):\n";
    cin>>new_num>>num;
    while(new_num!=0)
    {
        new_num=new_num-1;
        num=num-1;
        n++;//���ӱ���
        cin>>G.arcs[new_num][num];
        G.arcs[num][new_num]=G.arcs[new_num][num];//ע���������������1��
        cin>>new_num>>num;
    }
    cout<<"���㡾"<<school[G.vexnum].name<<"�������ɹ�";
    for(i=0; i<=G.vexnum; i++)
        for(j=0; j<=G.vexnum; j++)
            G.arcs[j][i]=G.arcs[i][j];
    G.vexnum++;
    G.arcnum=G.arcnum+n;
    Cunpan(G);
}

void DeleteRoad(AMGraph &G)       //������Ϣɾ������ 
{
    int num1,num2;
    cout<<"����ɾ��·�߶˵�:";
    cin>>num1>>num2;
    num1--;
    num2--;
    G.arcs[num1][num2]=MaxInt;
    G.arcs[num2][num1]=MaxInt;
    cout<<"ɾ����"<<G.vexs[num1].name<<"������"<<G.vexs[num2].name<<"��·�߳ɹ�\n";
    Cunpan(G);
}

#define inf 99999999
using namespace std;
void kaishidaohang();
int map[110][110],book[110],dis[110];
 

 
void cuntu()		//�洢������Ϣ��ͬʱ��ͼ��������Ϣ 
{
	int i,j;
	strcpy(q[1].name,"ͼ���");strcpy(q[1].pro,"ѧ����������ѧϰ�����Լ�");
	strcpy(q[2].name,"����㳡");strcpy(q[2].pro,"������ʽ�ٰ쳡��");
	strcpy(q[3].name,"����¥");strcpy(q[3].pro,"��ʦ�칫����"); 
	strcpy(q[4].name,"����");strcpy(q[4].pro,"ѧ����Ҫ����ͨ��");
	strcpy(q[5].name,"����ѵ������");strcpy(q[5].pro,"ѧ�����й���ѵ������"); 
	strcpy(q[6].name,"��ѧ¥");strcpy(q[6].pro,"ѧ���Ͽγ���");
	strcpy(q[7].name,"����ʳ��");strcpy(q[7].pro,"����ʳ���нϺóԵ�һ��");
	strcpy(q[8].name,"ʵѵ����");strcpy(q[8].pro,"��ʦ�칫��ѧ����ʵ��");
	strcpy(q[9].name,"�����ٳ�");strcpy(q[9].pro,"ѧ��������������");
	strcpy(q[10].name,"��ѧ�������");strcpy(q[10].pro,"��ѧ�����п�������");

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
 
 
 //�Ͻ�˹���������·���������·��
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
		if(dis[i]<inf)			//v0��ֱ�ӵ������һվ��Ϊv0 
			p[i]=v0;
	}
		
	book[v0]=1;
	
	for(i=1;i<10;i++)
	{
		min=inf;
		for(j=1;j<=10;j++)			//ÿ���ҳ�����v0����� 
		{
			if(book[j]==0&&dis[j]<min)
			{
				min=dis[j];
				u=j;
			}
		}
		book[u]=1;			//��Ǹõ� 
		for(v=1;v<=10;v++)
		{
			if(book[v]==0&&dis[v]>dis[u]+map[u][v])			//ͨ���������������� 
			{
				p[v]=u;					//�洢���µıߣ���Ϊ·�� 
				dis[v]=dis[u]+map[u][v];
			}
		}
	}
	v=s;
	i=1;
	while(p[v]!=v0)			//��·�ߴ���ջ�У�������� 
	{	
		l[i++]=p[v];
		v=p[v];
	}
	printf("\n");
	u=i-1;
	printf("·��Ϊ��\n");
	printf("%s--->",q[v0].name);
	for(i=u;i>=1;i--)
		printf("%s--->",q[l[i]].name); 
	printf("%s\n",q[s].name);
	printf("���·������Ϊ��%d00 ��\n",dis[s]);
}
 
//�Ͻ�˹���� 
void DJS()
{
	int x,m,n,u,v,i,j;
	char c[100];

	printf("��������㾰���ţ�\n");
	scanf("%d",&n);
	printf("\n�������յ㾰���ţ�\n");
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
				printf("\n���벻�Ϸ������������룡\n\n");
				printf("��������㾰���ţ�\n");
				scanf("%d",&n);
				printf("\n�������յ㾰���ţ�\n");
				scanf("%d",&m);
				}
			}
	
}


//�ø��������㷨�����·���������·��
void ShortestPath_Floyd(AMGraph G)
{
    int i,j,k;
	int D[MVNum][MVNum],path[MVNum][MVNum];    //D������S����  D�������̵�·��  S[i][j]=k��i��j���·������k 
    int place[MVNum];
    int v0,v1;                  //������յ� 
    for(i=0; i<G.vexnum; i++)
        for(j=0; j<G.vexnum; j++)
        {
            D[i][j]=G.arcs[i][j];      //��ʼ��������ά���� 
            if(D[i][j]<MaxInt&&i!=j)
                path[i][j]=i;//jǰ��Ϊi  
            else
                path[i][j]=-1;//jǰ��Ϊ-1 ������·��Ϊ-1 
        }
    for(k=0; k<G.vexnum; k++)                 //����ѭ�� 
        for(i=0; i<G.vexnum; i++)
            for(j=0; j<G.vexnum; j++)
                if(D[i][k]+D[k][j]<D[i][j])//��i��k,�ٵ�j·������
                {
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=path[k][j];
                }
    for(i=0; i<G.vexnum; i++)
        for(j=0; j<G.vexnum; j++)
            if(i==j)
                D[i][j]=D[j][i]=0;
    cout<<"���������:";
    cin>>v0;
    cout<<"�������յ�:";
    cin>>v1;
    if(v0==0)
    {
    	cout<<"�����������������������";
		cin>>v0; 
	}
	if(v1==0)
    {
    	cout<<"�յ�������������������յ�";
		cin>>v1; 
	}
    v0--;
    v1--;//�±��0��ʼ
    int t=v1;//v1��������ı�,�Ĵ��t
    i=0;
    cout<<"��"<<G.vexs[v0].name<<"������"<<G.vexs[v1].name<<"������̾���Ϊ "<<D[v0][v1]<<"00  m\n";
    cout<<"\n�����·��Ϊ :��"<<G.vexs[v0].name<<"��<->";
    while(path[v0][v1]!=v0)
    {
        place[i]=path[v0][v1];
        i++;
        v1=path[v0][v1];         //һ��һ�������е���ת������place[]������ 
    }
    i--;
    for(i; i>=0; i--)
        cout<<"��"<<G.vexs[place[i]].name<<"��<->";
    cout<<"��"<<G.vexs[t].name<<"��"<<endl;
}




void changedis()
{
	int i,j,n,p;
	printf("��������㾰���ţ�\n");
	scanf("%d",&n);
	printf("\n�������յ㾰���ţ�\n");
	scanf("%d",&m);

	
	for(i=1;i<=10;i++){
		for(j=1;j<=10;j++)
		{
			if(n==i&&m==j&&map[i][j]>0&&map[i][j]<inf){
				cout << "��ֱ��·���������޸�"<<endl;
				cout<<"�޸�ǰֱ��·�����ȣ�"<<map[i][j]<<"00 m"<<endl;
				cout<<"�������޸ĳ��ȣ�"<<endl;
				scanf("%d",&p);
				map[i][j] = p/100;
				cout << "�޸ĺ����:" << map[i][j]<<"00 m"<< endl;
				cout<<"�޸ĳɹ�" <<endl;
			}
			else if(n==i&&m==j)
				cout << "��ֱ��·���������޸�"<<endl;
		}
	}

}



void Edgemessage()
{
	int i,j,n,p;
	printf("��������㾰���ţ�\n");
	scanf("%d",&n);
	printf("\n�������յ㾰���ţ�\n");
	scanf("%d",&m);

	
	for(i=1;i<=10;i++){
		for(j=1;j<=10;j++)
		{
			if(n==i&&m==j&&map[i][j]>0&&map[i][j]<inf){
				cout<<"������ͨ·"<<endl;
				cout<<"�ߵ���Ϣ��"<<endl;
				printf("%s--->",q[i].name);
				printf("%s\n",q[j].name);
				printf("���ӳ���Ϊ��%d00 ��\n",map[i][j]);
			}
			else if(n==i&&m==j)
				cout << "������ͨ·"<<endl;
		}
	}

}



void Order(AMGraph G)    //�յ�ָ����ø����Ӻ��� 
{
    while(1)
    {
        int x,num,visited[MVNum]= {0};;
        Menu(G);
        cin>>x;
        switch(x)
        {
        case 0:
            cout<<"\n�ɹ��˳�����...\n";
            return;
            break;

        case 1:
            PrintMap();
            system("pause");
            system("cls");
            break;
            
        case 2:
            int x,y;
            cout<<"��������㣺  ";
			cin>>x;
			cout<<"�������յ㣺  ";
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
            cout<<"��������Ҿ������:";
            cin>>num;
            if(!CheckNum(num,G))
                cout<<"��Ч���룡"<<endl;
            else
                PrintPlace(G,num);
            system("pause");
            system("cls");
            break;

        case 8:
            cout<<"Ҫ���ĵľ������:";
            cin>>num;
            if(!CheckNum(num,G))
                cout<<"��Ч���룡"<<endl;
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