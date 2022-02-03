#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <boost/numeric/mtl/mtl.hpp>

/*Implementation of Stern algorithm */

using namespace std;

	using namespace mtl;	

const int  n=8;
const int  k=4;
const int  weight=3; //O(sqrt(n*log n))

typedef dense_vector<int>  Vector;


bool lnz_column(mtl::multi_vector<Vector> &A, Vector &b, int j)
{
	//check columns for linear independance
	bool l=true;
	Vector v(k,1);
	v=0;
	int first=0;
	while(first < k )
	{
		if (b[first]==1)
			break;
		first++;
	}
	if(j==0) 
		{A.vector(first)=b; return l;}
	while ((A.vector(first)!=v)&&(b!=v))
	{
		if (A.vector(first)==b) 
		 {l=false; return l;}
		for( int e=0; e<k; e++)
			b[e]^=A.vector(first)[e];
		while(first < k )
		{
			if (b[first]==1)
				break;
			first++;
		}
	}	
	if (b==v)
		{l=false; return l;}
	for( int i=first-1; i>=0; i--)
		if (A.vector(i)[first]==1)
		{
			for( int e=0; e<k; e++)
			A.vector(i)[e]^=b[e];
		}
	for( int i=first+1; i<n-k; i++)
		if (b[i]==1)
		{
			for( int e=0; e<k; e++)
			b[e]^=A.vector(i)[e];
		}
	if (b==v)
		{l=false; return l;}
	A.vector(first)=b;
	first=0;
	return l;
}

void set_12 (set<int> &X, set<int> &Y,set<int> &Z)
{
	//set X and Y creation
	set<int> c;
	int t;
	srand(time(0));
    for (int i=0; i< n; i++)
		c.insert(i);
	for (int i=0; i< n; i++)
		if (Z.count(i)!=0)
			c.erase(i);
	set <int>::iterator it;
	do{
		X.clear(); Y.clear();
		for(it=c.begin(); it!=c.end(); it++)
		{
			t=rand() % 2;
			if(t==0)
				{X.insert(*it); }
			else
				{Y.insert(*it); }
		}
	}while(X.empty() || Y.empty());
	cout<<"column set X:  ";
	copy(X.begin(),X.end(),ostream_iterator<int>(cout, " "));
	cout<<endl;
	cout<<"column set Y:  ";
	copy(Y.begin(),Y.end(),ostream_iterator<int>(cout, " "));
	cout<<endl;
}

void identity(mtl::multi_vector<Vector> &H, set<int> &Z)
{
	//make submatrix of H identity
	mtl::multi_vector<Vector>  H_new(k, n);
	set <int>::iterator it=Z.begin();
	H_new=H;
	int num=0,tmp; bool first=true;
	while(it != Z.end())
	{
		for(int i=0; i<n-k; i++)
		{
			if( H_new.vector(*it)[i]==1)
			{
				if ((i < num) && ( H_new.vector(*it)[num]==1))
					for(int j=0; j<n; j++)
						H_new.vector(j)[i] ^=H_new.vector(j)[num];
				
				if (first)
				{
					if( i > num )
						for(int j=0; j<n; j++)
						{
							tmp=H_new.vector(j)[num];
							H_new.vector(j)[num]=H_new.vector(j)[i];
							H_new.vector(j)[i]=tmp;
						}
				}
				else
				{
					if ((H_new.vector(*it)[num]==1)&&(i!=num))
						for(int j=0; j<n; j++)
							H_new.vector(j)[i] ^=H_new.vector(j)[num];
					else if (i > num)
						for(int j=0; j<n; j++)
						{
							tmp=H_new.vector(j)[num];
							H_new.vector(j)[num]=H_new.vector(j)[i];
							H_new.vector(j)[i]=tmp;
						}
				}
				first=false;
			}
		}
		it++; num++; first=true;
	}
	it = Z.begin(); num=0;
	while(it != Z.end())
	{
		for(int i=n-k-1; i>=0; i--)
		{
			if( (H_new.vector(*it)[i]==1)&&(i<num))
				for(int j=0; j<n; j++)
					H_new.vector(j)[i] ^=H_new.vector(j)[num];
		}
		it++; num++;
	}
	std::cout << "H_new is \n" << H_new << "\n";
	H=H_new;
}


void choose_column (mtl::multi_vector<Vector> &H,set<int> &Z)
{
	//set Z creation: randomly choose columns
	set<int> c;
	int t;
    bool b;
    srand(time(0));
    for (int i=0; i< n; i++)
		c.insert(i);
	mtl::multi_vector<Vector>  A(k, n-k);
	mtl::multi_vector<Vector>  B(k, n-k);
	A=0; B=0;
	int j=0;
	Vector v(k,1);
	Vector v1(k,1);
	v=0;
    for (int i=0; i< n-k; i++)  
    {
		b=true;
		do
		{
			t=rand() % n;
			if  ((c.count(t)==0) || (H.vector(t)==v))
				{	b=false; 
					if (H.vector(t)==v) c.erase(t);}
			else
			{
				v1= H.vector(t); 
				b=lnz_column(A,v1,j);
				if(b)
					{Z.insert(t); c.erase(t); j++; }
				else 
					{c.erase(t);}
			}
			if(c.size()==0) 
			{throw "can`t choose columns \n";}
		}while(!b );		
	}
	cout<<"column set Z:  "; 
	copy(Z.begin(),Z.end(),ostream_iterator<int>(cout, " "));
	cout<<endl;
	//identity_matrix
	identity(H,Z);
}


void comb(vector<int> &s, int i,int m, int* D, int k, int n,vector<int> &res)
{
	vector <int>::iterator it=s.begin();
	if(m==k)
	{
		for(int i = 0; i < k; i++)
			res.push_back(s[i]);
	}
	else
		for (int j=i; j<n; j++ )
		{
			s.push_back(D[j]); 
			comb(s,j+1,m+1,D,k,n,res);
			s.pop_back();
		}
}

int subset (vector<int> &res, set<int> &X , size_t sz,unsigned int p, unsigned int l)
{
	//every subset  of X with p elements
	set <int> :: iterator it = X.begin();
	unsigned int  t1=p, t2=sz;
	int count=1;
	int d[sz]={0};
	if(sz!=1)
	{
		if(2*t1>sz) 
			t1 = sz-t1;
		for(unsigned int i=0; i<t1; i++) count = count*t2--/(i+1);
	}
	vector<int> s;
	for(unsigned int i=0; i<X.size(); i++)
		{d[i]=*it; it++;}	

	if(p < sz)
	{comb(s,0,0,d,p,sz,res); } 
	else
	{
		for(unsigned int i=1; i<=sz; i++)
			res.push_back(d[i-1]);
	}
	return count;
}


void H1_gen(mtl::multi_vector<Vector> &H, multimap <vector<int>, Vector> &list,  vector<int> &res, 
            unsigned int p, unsigned int l, int count)
{
	//H1-submatrix from selected rows and columns
	mtl::multi_vector<Vector>  H1(l, p);
    Vector pi(l,0);
	H1=0;
	set<int> c;
	set<int> c1;
	vector<int> v;
	int t=0;
	srand(time(0));
	for (unsigned int i=0; i< n-k; i++) 
		c.insert(i);
	//raws select
	for(unsigned int e=0; e<l; e++)
	{
		do
		{t=rand() % (n-k);} 
		while (c.count(t)==0); 
		c.erase(t); c1.insert(t);
	}
	cout<<"rows:  ";
	copy(c1.begin(),c1.end(),ostream_iterator<int>(cout, " "));
	cout<<endl;
	set <int> :: iterator it=c1.begin(); int e=0;
	int j=0;
	while(j<count)
	{
		for(unsigned int i=0; i<p; i++)
		{ 
			while(it!=c1.end())
			{
				H1.vector(i)[e]=H.vector(res[j*p+i])[*it]; 
				it++; e++;
			}
			v.push_back(res[j*p+i]);
			e=0; it=c1.begin();	
		}
		//l-bit vector compute
		for(unsigned int i=0; i<p; i++)
			for(unsigned int j=0; j<l; j++)
				pi[j]=H1.vector(i)[j] ^ pi[j];
		
		list.insert(pair< vector<int>,Vector > (v,pi));
		H1=0; pi=0; v.clear();
		j++;
	}
}

unsigned int weight_v ( Vector &v)
{
	//computes weight of the vector
	unsigned int t=0;
	for(unsigned int i=0; i<n-k; i++)
		if(v[i]==1)
			t++;
	return t;
}
	
//common vectors pi(A) = pi (B)
void collision(multimap <vector<int>, Vector> &list1, multimap <vector<int>, Vector> &list2, mtl::multi_vector<Vector> &H, 
set<int> &Z, Vector &v, unsigned int p)
{
	Vector end (n,0);
	Vector sum(n-k,0);
	vector<int> tmp;
	auto it1 = list1.begin();
	auto it2 = list2.begin();
	vector <int> :: iterator it3 = tmp.begin();
	set <int> :: iterator it4 = Z.begin();
	for(it1 = list1.begin(); it1 != list1.end(); it1++)
	{
		while (it2 != list2.end()) 
		{
			if (it1->second==it2->second)
			{
				cout<<endl;
				cout<<"collision vector:"<<it2->second<<endl;
				for (unsigned int i=0; i<p; i++)
					tmp.push_back(it1->first[i]);
				for (unsigned int i=0; i<p; i++)
					tmp.push_back(it2->first[i]);
				cout<<"subets with collision vectors:"<<endl;
				for (unsigned int i=0; i<2*p; i++)
				cout<<tmp[i]<<' ';
				cout<<endl;
				
				for (unsigned int i=0; i<2*p; i++)
				{ 
					for( int j=0; j<n-k; j++)
					{
						sum[j] ^= H.vector(tmp[i])[j];
					}
				}
				std::cout << "sum is \n" << sum << "\n";
				if (weight_v(sum)== weight-2*p)
				{
					for( it3 = tmp.begin(); it3 != tmp.end(); it3++)
						end[*it3]=1;
					for( int j=0; j<n-k; j++)
					{
						if (sum[j]==1)
							end[*it4]=1;
						it4++;
					}
					cout <<"result" << end <<endl; v=end;
				}
				sum=0; end=0; it4 = Z.begin();
			}
			it2++; tmp.clear();
		}
		it2=list2.begin();
	}
}

//main algorithm
void low_weight (mtl::multi_vector<Vector> &H, Vector &x,unsigned  int p,unsigned  int l)
{
	
	set<int> Z;
	set<int> X;
	set<int> Y;
	vector<int> res;
    multi_vector<Vector>  H_n(k, n);
    H_n=H;
    multimap <vector<int>, Vector > list1;
    multimap <vector<int>, Vector > list2;
    try
    {
		// chosing sets Z,X,Y
	        choose_column(H_n,Z);
		set_12(X,Y,Z);
	    
		size_t sz1=X.size(), sz2=Y.size();
		if (sz1<p || sz2 < p)
			throw "bad column choice \n";
		//l-bit vector compute
		int count=subset(res,X,sz1,p,l);
		H1_gen(H_n, list1, res, p,l,count);
		res.clear();
		count=subset(res,Y,sz2,p,l);
		H1_gen(H_n, list2,res, p,l,count);
		collision(list1,list2,H_n, Z, x, p);
	}
	catch(const char *s)
	{cout<<s<<endl;}
}

int main()
{
	Vector v (n,0);
    mtl::multi_vector<Vector>  H(k, n);
    srand(time(0));
	// generates random matrix
    for( int i=0; i<n; i++)
		for( int j=0; j<k; j++)
			H.vector(i)[j]=rand() % 2;
    
    unsigned int p,l;
    cout<<"p,l?"<<endl;
    cin>>p; cin>>l;
    std::cout << "H is \n" << H << endl;
    std::cout << "p : " << p << endl;
    std::cout << "l : " << l << endl;
    std::cout << "w : " << weight << endl;
    low_weight(H,v,p,l);
	cout <<"result" <<v<<endl; 
    return 0;
}

