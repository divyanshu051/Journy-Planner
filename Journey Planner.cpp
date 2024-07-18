#include<bits/stdc++.h>
#include<fstream>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
map<string,ll>M;
char color[200][200]={'\0'};
class comparedis
{
	public:bool operator()(pair<ll,ll> &p,pair<ll,ll> &q)
		{
			return (p.se > q.se); // For min heap use > sign
		}
};
vector< pair<ll,ll> > v[100010];//Adjacency matrix
ll N;// N is no of vertices M is edges
string station[200];
map <string,string> tourm;
void recharge()
{
	fstream f;
	ll amt,ini,cid,fin,x;
	ll c_id,amount;
	f.open("paisa.txt",ios::in|ios::out);
	if(!f)
		cout<<"Not Found\n"<<endl;
	f.seekg(0);
	cout<<endl;
	cout<<"Enter Card Id\n";
	cin>>c_id;
	cout<<"Enter Amount\n";
	cin>>amount;
	f.clear();
	while(!f.eof())
	{
		ini=f.tellg();
		f.ignore();
		f>>cid;
		f>>amt;
		fin=f.tellg();
		if(c_id==c_id)
		{
			x=amt+amount;
			f.seekg(ini);
			f<<endl<<c_id<<endl<<x;
			cout<<"Recharge Details\n";
			cout<<"\nCard Id: "<<c_id<<endl;
			cout<<"Initial Balance: "<<amt<<endl;
			cout<<"Recharge Amount: "<<amount<<endl;
			cout<<"Total Balance: "<<x<<endl;
			break;
		}
	}
	f.close();
}
void gettour()
{
	ifstream fin;
	string s1,s2;
	fin.open("tourplace.txt",ios::in);
	if(!fin)
		cout<<"Not Found\n";
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s1);
		getline(fin,s2);
		tourm[s1]=s2;
	//	cout<<tourm[s1]<<endl;
	}
	fin.close();
}
//Given below code will print the path
void disp(ll src,ll dest,ll par[])
{
	ll i,x,y,cn=0,ci=0;
	stack<ll> st;
	st.push(dest);
	i=dest;
	while(par[i]!=-1)
	{
		i=par[i];
		st.push(i);				
	}
	char col='\0';
	while(!st.empty())
	{
		x=st.top();
		st.pop();
		if(!st.empty())
			y=st.top();
		cout<<station[x]<<" ";
		cn++;
		if(col=='\0')
			col=color[x][y];
		else if(col!='\0'&&col!=color[x][y])
		{
			char c=color[x][y];
			ci++;
			if(c=='b')
				cout<<"\t\tChange to Route01";
			else if(c=='y')
				cout<<"\t\tChange to Route02";
			else if(c=='o')
				cout<<"\t\tChange to Route07";
			else if(c=='g')
				cout<<"\t\tChange to Route04";
			else if(c=='r')
				cout<<"\t\tChange to Route03";
			else if(c=='v')
				cout<<"\t\tChange to Route05";
			col=c;
		}		
		cout<<endl;
	}
	cout<<endl<<"No of stops ="<<cn<<endl;
	cout<<"No of interchange  ="<<ci-1<<endl;
	cout<<endl;
}
//To find shotest path
void bfs(ll src,ll dest) 
{
	bool vis[100010]={false};
	ll par[100010];
	for(ll i=0;i<N;i++)
		par[i]=-1;
	queue<ll> q;
	q.push(src);
	vis[src]=true;
	while(!q.empty())
	{
		ll x=q.front();
		q.pop();
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			if(!vis[y])
			{
				par[y]=x;
				vis[y]=true;
				q.push(y);
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
}
//To less interchange path
void dijkstra(ll src,ll dest)
{
	bool vis[100010]={false};
	ll dist[100010], par[100010];
	for(ll i=0;i<N;i++)
	{
		dist[i]=LLONG_MAX;
		par[i]=-1;
	}
	priority_queue< pair<ll,ll>,vector< pair<ll,ll> >,comparedis > pq;
	pq.push(mp(src,0));
	dist[src]=0;
	par[src]=-1;
	vis[src]=true;
	while(!pq.empty())
	{
		pair<ll,ll> k=pq.top();
		pq.pop();
		ll x=k.fi;
		if(x==dest)
			break;
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			ll w=v[x][i].se;
			if(dist[x]+w < dist[y])
			{
				par[y]=x;
				dist[y]=dist[x]+w;
			}
			if(!vis[y])
			{
				vis[y]=true;
				pq.push(mp(y,dist[y]));
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
}
void consmap()//To assign values to stop
{
	ifstream fin;
	string s;
	fin.open("list.txt",ios::in);
	ll l=0;
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		M[s]=l;
		station[l]=s;
		l++;
	}
	N=l-1;
	fin.close();
	map<string,ll> ::iterator it;
	for(it=M.begin();it!=M.end();it++)
		cout<<it->se<<" "<<it->fi<<endl;
}
void addedge(char fname[],ll w)//To add edges
{
	ifstream fin;
	string s;
	ll x,y;
	fin.open(fname,ios::in);
	fin.seekg(0);
	getline(fin,s);
	x=M[s];
	char c=fname[0];
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		y=M[s];
		v[x].pb(mp(y,w));
		v[y].pb(mp(x,w));
		color[x][y]=c;
		color[y][x]=c;
		x=y;
	}
	fin.close();
}
void consgraph()//To construct edges
{
	string s;
	addedge("Route01.txt",0);
	addedge("Route02.txt",0);
	addedge("Route03.txt",0);
	addedge("Route04.txt",0);
	addedge("Route05.txt",0);
	addedge("Route06.txt",0);
	addedge("Route07.txt",1);
}
int main()
{
	string source,destination;
	ll i,x,y,w,src,dest,k,choice,dec;
	char ch;
	gettour();
	consmap();
	do
	{
		cout<<endl;
		cout<<"1.FOR   ******       To Route between two Destination                 ******\n";
		cout<<"                           _____________________                                       \n";
			cout<<"                                                               \n";
	//	cout<<"2.FOR   ^^^^^^  To check nearest Destination stop to a tourist place  ^^^^^^\n";
	//		cout<<"                           _____________________                                       \n";
	//		cout<<"                                                               \n";
		cout<<"2.FOR   ******       To Recharge your Monthly pass                    ******\n";
			cout<<"                           _____________________                                       \n";
			cout<<"                                                               \n";
		cin>>dec;
		switch(dec)
		{
			case 1:
					do
					{
						consgraph();//To build the adjacency matrix
						cout<<"||  Enter Start Stop  || \n";
						getline(cin,source);
						getline(cin,source);
						//cout<<source<<endl;
						cout<<"||  Enter Destination  ||\n";
						getline(cin,destination);
						//cout<<destination<<endl;
						src=M[source];
						dest=M[destination];
							cout<<"                                                                 \n";
			cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                                              \n";
						cout<<"1.For Less interchanging path\n";
						cout<<"2.For shortest path\n";
							cout<<"                                                                 \n";
			cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                                              ";	
						cin>>choice;
				cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                                              ";			
						switch(choice)
						{
							case 1:dijkstra(src,dest);
									break;
							case 2:bfs(src,dest);
									break;
						}
						cout<<"Do you wish to check for any other stop\n";
						cin>>ch;
					}while(ch=='Y'||ch=='y');	
					break;	
		//	case 2:
					do
					{
						string place;
						cout<<"Enter a place\n";
						getline(cin,place);
						getline(cin,place);
						string st;
						st=tourm[place];
						cout<<st<<endl;
						cout<<"Do you wish to check for any other place\n";
						cin>>ch;
					}while(ch=='Y'||ch=='y');
					break;
			case 2:
					do
					{
						recharge();
						cout<<"Do you wish to recharge some other Monthly pass\n";
						cin>>ch;
					}while(ch=='Y'||ch=='y');
					break;
		}
		cout<<"Do you wish to go back to main menu\n";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	return 0;
}
