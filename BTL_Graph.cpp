//https://gist.github.com/pluralism/11291780
//https://gist.github.com/macroxela/11234996
#include<bits/stdc++.h>
#define INF 10000
using namespace std;
//template <class T>
class Vertex{
	int inform;
	Vertex *next;
//	list<pair<Vertex,float>> list;
//	List_adj adj;//danh sach cac dinh ke
//	bool visited;
	public:
		Vertex (int in){
			inform=in;
			next=NULL;
//			visited=false;
		};
		Vertex *getNext(){
			return next;
		}
		int &getInform(){
			return inform;
		}
		void setNext(Vertex *N){
			next=N;
		}
		void setInform(int inform){
			this->inform=inform;
		}
};
class List_adj{	// cai nay la list bieu dien danh sach ke cua do thi nen chi hien thi khi da co quan he ke cua cac dinh
	private:
		Vertex *head;// thuoc tinh cua List_adj la 1 con tro dau head
	public:
		List_adj(){// ham tao
			head=NULL;
		}
		Vertex *getHead(){//lay con tro cua list
			return head;
		}
		void insertVertex(int inform){// them 1 dinh vao danh sach ke
			Vertex *p=new Vertex(inform);// cap phat, khoi tao 1 con tro
			if(head!=NULL){
				p->setNext(head); //thiet lap lien ke giua p va head khi danh sach khac rong
				head=p;
			}
			else{
				head=p;// khoi tao node dau bang p
			}
		}
		void printf(){// in ra danh sach cac dinh ke voi dinh
			Vertex *p=head;// khai bao 1 con tro tro vao dau danh sach
			if(p!=NULL){// neu p khac null
				cout<<"[";
				while(p!=NULL){//in cho den khi nao p=null
					cout<<p->getInform();
					if(p->getNext()!=NULL)	cout<<"->";
					p=p->getNext();
				}
				cout<<"]";
			}
			else	cout<<"Khong co dinh nao ke voi dinh";
		}
		
};
class Edge {// lop canh giua 2 dinh u,v cua do thi
	private:
		int u;//dinh u
		int v;// dinh v
		float weight;// trong so
	public:
		Edge(){	};// khoi tao canh do thi khong doi
		Edge(int x, int y, float z){// khoi tao canh giua 2 dinh u,v co trong so weight
			u=x;v=y; weight=z;
			
		};
		float &getWeight(){//lay ra trong so cua canh [u,v]
			return weight;
		}
		int &getU(){//lay dinh U
			return u;
		}
		int &getV(){//lay dinh V
			return v;
		}
};
class Graph{
	int v;
	float a[100][100]={0};// khoi tao ma tran ke cua do thi
	int numEdge;//so canh cua do thi ban dau cho bang 0
//	Edge *adjEdge;// mang cac canh cua do thi 
	vector<List_adj> adj; //vector chua cac dinh cua do thi; trong do cac dinh la dinh dau cua 1 list chua cac dinh ke voi no;
	vector<Edge> edge;//khoi tao 1 vector chua cac canh cua do thi
	public:
		Graph(int n,int m){//khoi tao do thi ban dau
			numEdge=m;
			v=n;
			adj.resize(v);//khoi tao kich thuoc cua vecto ban dau, neu khong khoi tao se bi loi
		}
		void InsertVertex(){	// them 1 dinh moi vao do thi			
			int x; float w;
			
			List_adj p;	//khai bao 1 list danh sach ke voi dinh de them list nay vao vector chua cac dinh cua do thi
			adj.push_back(p);// them list vao vector chua danh sach ke cua cac dinh
			v=v+1;
			do{
				cout<<"Nhap dinh ke voi dinh "<<v-1<<" (gia tri cua dinh nam trong khoan"<<0<<"->"<<v-1<<") v=";
				cin>>x;
				cout<<"Nhap trong so cua cung ("<<v-1<<","<<x<<")= ";
				cin>>w;
				InsertEdge(v-1,x,w);			
			} while(x<0&&x>v-1);
			// khi do so dinh cua do thi da tang len 1;
		}
		void InsertEdge(int u,int v,float weight){
			Edge edges(u,v,weight);//khoi tao 1 canh co dinh la u,v trong so la weight
			adj[u].insertVertex(v);// thiet lap 1 node ke voi node truoc va lap lien ke giua 2 node
			adj[v].insertVertex(u);// thiet lap node ke voi node va lap lien ket giua 2 node tai sao lai phai thiet
			//thiet lap 2 chieu la vi khi ta xet den node thu thu 2 thi se bo sot liet ket voi node truoc
			edge.push_back(edges);// them 1 1 cung giua 2 dinh
			
		}
		float getWeight(int u,int v){// lay trong so cua canh
			float weight;
			vector<Edge>::iterator it;//khai bao 1 con tro  lap
			for(it=edge.begin();it!=edge.end();it++){ //duyet tat cac cac canh trong vector
				if((it->getU()==u&&it->getV()==v)||(it->getU()==v&&it->getV()==u)){ //lay ra canh noi 2 dinh la u va v
					 weight=it->getWeight();
				}				
			}
			return weight;
			
		}	
		void displayGraph_adjacency(){// hien thi danh sach ke
			cout<<"->Do thi duoc bieu dien bang danh sach ke la:\n";
			for(int i=0;i<v;i++){
				cout<<i<<"->";
				adj[i].printf();// goi phuong thuc in cua List_adj
				cout<<"\n";
			}
		}
		void ConVert_to_Matrix(){// chuyen tu danh sach ke sang ma tran ke de tim duong di ngan nhat bang dijkstra
			vector<Edge>::iterator it;// khai bao 1 con tro de duyet vector chua cac canh cua do thi
			it=edge.begin();// khoi tao con tro tro vao vi tri dau cua vector chua canh
			for(;it!=edge.end();it++){
				for(int i=0;i<v;i++)
					for(int j=0;j<v;j++){
						if((it->getU()==i&&it->getV()==j)||(it->getU()==j&&it->getV()==i)){
							 a[i][j]=it->getWeight();
						}				
					}
			}		
		}
		void displayGraph_matrix(){// in ra ma tran ke co trong so cua do thi
			cout<<"->Do thi duoc bieu dien thanh ma tran ke co trong so la:\n";
			for(int i=0;i<v;i++){
				for(int j=0;j<v;j++){
					cout<<a[i][j]<<" ";
				}
				cout<<"\n";
			}
		}
// thuat toan dijkstra		
		void dijkstra(int s,int t){
			int *truoc;float *d; // mang truoc[]: luu dinh truoc no; mang d[]:luu do dai ngan nhat tu dinh s toi Vi
			bool *chuaxet; // mang chuaxet[]: danh dau cac dinh da duyet
			truoc=new int[v+1];//cap phat dong
			d=new float[v+1];//cap phat dong
			chuaxet=new bool[v+1];// cap phat dong
			int u;// dinh co khoang cach ngan nhat tu dinh s den V[i]
			int min;// bien min de luu khoan cach ngan nhat tu s den V[i] trong cac dinh V[i];
			// dung de tim khoang cach nho nhat tu s den cac dinh V[i]
			for(int i=0;i<v;i++)
				for(int j=0;j<v;j++){
					if(a[i][j]==0)
						a[i][j]=INF; // do dai tu dinh i-> dinh j la vo cung neu khong phai dinh ke 
				}
				
//			 khoi tao nhan tam thoi cho cac dinh:
			cout<<"->Thu tu cac buoc tim duong di ngan nhat la:"; cout<<"voi (x,y)=(truoc[i],d[i])\n";
			cout<<"Buoc "<<" Duyet u ";
			for(int i=0;i<v;i++){
//				cout<<" \t "<<i<<"\t ";//in ra cac dinh chua duyet
				printf("  %8d  ",i);
			}
			cout<<endl;
			for(int i=0;i<v;i++){
				d[i]=INF;	// khoi tao khoang cach ngan nhat tu s den V[i]
				truoc[i]=s;// khoi tao truoc cua V[i] la s
				chuaxet[i]=false;// cho tat ca cac dinh la chua duyet
			}
			d[s]=0;	//khoi tao khoang cach ngan nhat tu s->s la 0
			int j=0;	//bien de luu cac buoc thuc hien
			cout<<j<<"\t"<<0<<"\t";	
			for(int i=0;i<v;i++){
//				cout<<"   ("<<s<< ","<< d[i]<<")\t";
				printf("(%2d,%-5.0f)  ",s,d[i]);
			}// in ra buoc 0 thuc hien cong viec gi
			
			cout<<endl;	
			chuaxet[s]=true;// danh dau dinh s da duyet		
			while(!chuaxet[t]){// xet tat ca cac dinh chua duyet
				min=INF;// khoi tao do dai nho nhat tu dinh s den V[i]
				//tim dinh u sao cho d[u]; tuc la khoang cach ngan nhat tu s den V[i]
				for(int i=0;i<v;i++){
					if((!chuaxet[i])&&(min>d[i])){
						u=i;
						min=d[i];
					}
				}
				j=j+1;
				cout<<endl;
				if(u!=t){// neu dinh u khong thuoc t thi in ra
//					printf("%-10d")
					cout<<j<<"\t"<<u<<"\t";
				}							
				chuaxet[u]=true;// danh dau dinh u
				if(!chuaxet[t]){// neu dinh t chua xet
					//gan lai nhan cho cac dinh:
					for(int i=0;i<v;i++){
						if(!chuaxet[i]&&(d[u]+a[u][i]<d[i])){// xet inh i neu chua danh dau, khoang cach tu s den V[i]>canh[i,u]+d[u]
						// tuc la tim dc con duong khac co khoang cach nho hon con duong tim duoc truoc do gan do dai
							d[i]=d[u]+a[u][i];// thay doi khoang cach ngan nhat tu s den V[i]
							truoc[i]=u;// luu truoc cua dinh V[i]
						}
//						cout<<"   ("<<truoc[i]<< ","<< d[i]<<")\t   ";// in ra tung buoc thuc hien	
						printf("(%2d,%-5.0f)  ",truoc[i],d[i]);
					}
					cout<<endl;
				}				
			}
			if(d[t]==INF)	cout<<"Khong ton tai duong di tu"<<s<<"->"<<t<<endl;
			else{
				cout<<"->Duong di ngan nhat tu"<<s<<"->"<<t<<"la: "<<d[t]<<endl;//in ra khoang cac nho nhat cua s-> t
			//in duong di ngan nhat tu s den t
				cout<<t<<"<-";
				int i=truoc[t];
				while (i != s){
	 				 cout<<i<<"<-";//in ra duong di ngan nhat tu cua 2 dinh.
	 				 i = truoc[i];
	 				}
	 			cout<<s;
			}		
		}
		int getV(){// lay so dinh cua do thi
			return v;
		}
};
// 
int main(){
//	Graph g(7,11);
//	g.InsertEdge(0,1,7);
//	g.InsertEdge(0,3,1);
//	g.InsertEdge(0,4,2);
//	g.InsertEdge(1,2,5);
//	g.InsertEdge(1,5,2);
//	g.InsertEdge(1,4,3);
//	g.InsertEdge(2,6,2);
//	g.InsertEdge(2,5,1);
//	g.InsertEdge(3,4,4);
//	g.InsertEdge(4,5,1);
//	g.InsertEdge(5,6,2);
//doc file:
	int n,m,x,y;// x,y la canh noi tu x den y
	float z;// trong so
 	ifstream fi("graph_input.txt");//nhap thong tin tu file
 	fi>>n>>m;//nhap so dinh, so canh
 	Graph g(n,m);
 	for(int i=0;i<m;i++){
 		fi>>x>>y>>z;// nhap vao thong tin 1 canh
 		g.InsertEdge(x,y,z);//them 1 canh
	 }
	cout<<"->So dinh hien tai cua do thi la n="<<n<<endl;
	g.displayGraph_adjacency();//in do thi duoi dang danh sach ke
	int luachon;
	do{
		cout<<"------------Nhap them diem-----------\n";
		cout<<"De them 1 dinh-Moi nhap so bat ki!\n";
		cout<<"De thoat-Moi nhap 0!\n";	
		cout<<"->Moi ban nhap:";
		cin>>luachon;
		cout<<"-------------------------------------\n";
		if(luachon!=0)	g.InsertVertex();		
	}while(luachon!=0);	
	cout<<"->So dinh hien tai cua do thi la:"<<g.getV()<<endl;
	g.displayGraph_adjacency();
	g.ConVert_to_Matrix();//chuyen doi tu danh sach ke sang ma tran ke
	g.displayGraph_matrix();// in ma tran ke
	int u,v;
	cout<<"Nhap vao hai dinh muon lay khoang cach:(u,v)=";
	cin>>u>>v;
	if(g.getWeight(u,v)==0)	cout<<"->Hai dinh khong ke nhau\n";	
	else cout<<"->Khoang cach cua 2 dinh("<<u<<","<<v<<")= "<<g.getWeight(u,v)<<endl;
	int s,t;
	cout<<"Nhap vao hai dinh muon tim khoang cach nho nhat"<<"(hai dinh nam trong khoang"<<0<<"->"<<g.getV()-1<<"):(u,v)=";
	cin>>s>>t;
	cout<<"->Qua trinh thuc hien thuat toan dijkstra :\n";
	g.dijkstra(s,t);
//	g.InserVertex();
}
