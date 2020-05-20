#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <boost/numeric/mtl/mtl.hpp>

using namespace std;

	using namespace mtl;

const int  n=150;
const int  k=75;
typedef dense_vector<int>   Vector;

void matr_gen(dense2D<int> &H)
{
	int t=0,r=n/2;
	char c;
	ifstream m ("/home/maria/diplom/svedenie/data/row6");
	if(!m.is_open()) 
		cout<<"no"<<endl;
	else
	{
		m.get(c);
		while(m)
		{
			if ((c=='0')|| (c=='1'))
				{H[0][t]=c-'0'; t++;}
			m.get(c);
		}
	}
	for( int j=1; j<k; j++)
	{
		H[j][0]=H[j-1][r-1];
		for( int i=1; i< r; i++)
		{
			H[j][i]=H[j-1][i-1];
		}
		H[j][r]=H[j-1][n-1];
		for( int i=r+1; i< n; i++)
		{
			H[j][i]=H[j-1][i-1];
		}
		m.close();
	}
}

int syst(dense2D<int> &H, Vector &y, int l, int k, int first)
{
	Vector x (n);
	int *a= new int[n+3];
	int *z= new int[n/2+1];
	int j=3;
	stringstream conv;
	string s1,s2,s3;
	for (int i=0; i<n+2; i++)
	{
		a[i]=i+1;
		if (i< n/2-1) 
			z[i]=n+i+3+first;
	}
	if (first!=0)
		a[n] += first+1;
	for (int i=0; i<n/2-1; i++)
		cout <<z[i]<<' ';
	cout<<endl;
	ofstream f( "result6", ios::app);
	stringstream s;
	string row;
	
	conv<<a[0]; s1=conv.str(); conv.str("");
	conv<<a[1]; s2=conv.str(); conv.str("");
	conv<<a[2]; s3=conv.str(); conv.str(""); 
	{s<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<z[0]<<' '<<'0'<<endl;
	row=s.str(); s.str("");
	if (H[l][0]==0)  row.erase (row.find(s1),s1.length()+1);
	if (H[l][1]==0)  row.erase (row.find(s2),s2.length()+1);
	if (H[l][2]==0)  row.erase (row.find(s3),s3.length()+1); f<<row; k++;}
	
	if (H[l][2] !=0) 
		{s<<a[0]<<' '<<a[1]<<' '<<'-'<<a[2]<<' '<<'-'<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); 
		if (H[l][0]==0)  row.erase (row.find(s1),s1.length()+1);
		if (H[l][1]==0)  row.erase (row.find(s2),s2.length()+1); f<<row; k++;}
	if (H[l][1] !=0)
		{s<<a[0]<<' '<<'-'<<a[1]<<' '<<a[2]<<' '<<'-'<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); 
		if (H[l][0]==0)  row.erase (row.find(s1),s1.length()+1);
		if (H[l][2]==0)  row.erase (row.find(s3),s3.length()+1); f<<row; k++;}
	if ((H[l][1] !=0) && (H[l][2] !=0))
		{s<<a[0]<<' '<<'-'<<a[1]<<' '<<'-'<<a[2]<<' '<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); 
		if (H[l][0]==0)  row.erase (row.find(s1),s1.length()+1); f<<row; k++;}
	if (H[l][0] !=0) 
		{s<<'-'<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<'-'<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); 
		if (H[l][1]==0)  row.erase (row.find(s2),s2.length()+1);
		if (H[l][2]==0)  row.erase (row.find(s3),s3.length()+1);  f<<row; k++;}
	if ((H[l][0] !=0) && (H[l][2] !=0))
		{s<<'-'<<a[0]<<' '<<a[1]<<' '<<'-'<<a[2]<<' '<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); 
		if (H[l][1]==0)  row.erase (row.find(s2),s2.length()+1); f<<row; k++;}
	if ((H[l][0] !=0) && (H[l][1] !=0))
		{s<<'-'<<a[0]<<' '<<'-'<<a[1]<<' '<<a[2]<<' '<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); 
		if (H[l][2]==0)  row.erase (row.find(s3),s3.length()+1); f<<row; k++;}
	if ((H[l][0] !=0) && (H[l][1] !=0) && (H[l][2] !=0))
		{s<<'-'<<a[0]<<' '<<'-'<<a[1]<<' '<<'-'<<a[2]<<' '<<'-'<<z[0]<<' '<<'0'<<endl;
		row=s.str(); s.str(""); f<<row; k++;}
		
	for(int i=1; i< n/2-1; i++)
	{
		{if ((H[l][j]==0) && (H[l][j+1]==0) )
			f<<z[i-1]<<' '<<z[i]<<' '<<'0'<<endl;	 
		else if (H[l][j]==0)  
			f<<z[i-1]<<' '<<a[j+1]<<' '<<z[i]<<' '<<'0'<<endl; 
		else if (H[l][j+1]==0)  
			f<<z[i-1]<<' '<<a[j]<<' '<<z[i]<<' '<<'0'<<endl; 
		else  f<<z[i-1]<<' '<<a[j]<<' '<<a[j+1]<<' '<<z[i]<<' '<<'0'<<endl; k++;}
		
		if (H[l][j+1] !=0) 
			{if (H[l][j]==0) f<<z[i-1]<<' '<<'-'<<a[j+1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl; 
			else	f<<z[i-1]<<' '<<a[j]<<' '<<'-'<<a[j+1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl;  k++;}
				
		if (H[l][j] !=0)	
			{if (H[l][j+1]==0) f<<z[i-1]<<' '<<'-'<<a[j]<<' '<<'-'<<z[i]<<' '<<'0'<<endl;
			else	f<<z[i-1]<<' '<<'-'<<a[j]<<' '<<a[j+1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl; k++;}
			
		if ((H[l][j] !=0) && (H[l][j+1] !=0))	
			{f<<z[i-1]<<' '<<'-'<<a[j]<<' '<<'-'<<a[j+1]<<' '<<z[i]<<' '<<'0'<<endl; k++;}
			
		{k++;
		if ((H[l][j]==0) && (H[l][j+1]==0))	
			f<<'-'<<z[i-1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl;
		else if (H[l][j]==0)  f<<'-'<<z[i-1]<<' '<<a[j+1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl;
		else if (H[l][j+1]==0)  f<<'-'<<z[i-1]<<' '<<a[j]<<' '<<'-'<<z[i]<<' '<<'0'<<endl;
		else f<<'-'<<z[i-1]<<' '<<a[j]<<' '<<a[j+1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl; }
		
		if (H[l][j+1] !=0)
			{if (H[l][j]==0)  f<<'-'<<z[i-1]<<' '<<'-'<<a[j+1]<<' '<<z[i]<<' '<<'0'<<endl; 
			else f<<'-'<<z[i-1]<<' '<<a[j]<<' '<<'-'<<a[j+1]<<' '<<z[i]<<' '<<'0'<<endl;  k++;}
			
		if (H[l][j] !=0)
			{if (H[l][j+1]==0)  f<<'-'<<z[i-1]<<' '<<'-'<<a[j]<<' '<<z[i]<<' '<<'0'<<endl;
			else f<<'-'<<z[i-1]<<' '<<'-'<<a[j]<<' '<<a[j+1]<<' '<<z[i]<<' '<<'0'<<endl; k++;}
			
		if ((H[l][j] !=0) && (H[l][j+1] !=0))	
			{f<<'-'<<z[i-1]<<' '<<'-'<<a[j]<<' '<<'-'<<a[j+1]<<' '<<'-'<<z[i]<<' '<<'0'<<endl; k++;}
		j+=2;
	}

	if (y[l] != 0)
		{if (H[l][n-1]==0) f<<z[n/2-2]<<' '<<'-'<<a[n]<<' '<<'0'<<endl;
		else  f<<z[n/2-2]<<' '<<a[n-1]<<' '<<'-'<<a[n]<<' '<<'0'<<endl; k++;}
	
	if ((H[l][n-1] != 0) ) 
		{if (y[l]==0)  f<<z[n/2-2]<<' '<<'-'<<a[n-1]<<' '<<'0'<<endl;
		else f<<z[n/2-2]<<' '<<'-'<<a[n-1]<<' '<<a[n]<<' '<<'0'<<endl; k++;}
		
	{k++; if ((H[l][n-1]==0) && (y[l]==0)) 
		f<<'-'<<z[n/2-2]<<' '<<'0'<<endl;
	else if (H[l][n-1]==0) f<<'-'<<z[n/2-2]<<' '<<a[n]<<' '<<'0'<<endl;
	else if (y[l]==0)  f<<'-'<<z[n/2-2]<<' '<<a[n-1]<<' '<<'0'<<endl;
	else f<<'-'<<z[n/2-2]<<' '<<a[n-1]<<' '<<a[n]<<' '<<'0'<<endl;}
	
	if ((y[l] != 0) && (H[l][n-1] !=0))
		{f<<'-'<<z[n/2-2]<<' '<<'-'<<a[n-1]<<' '<<'-'<<a[n]<<' '<<'0'<<endl; k++;}	

	if (y[l] == 1)
		{f<<a[n]<<' '<<'0'<<endl; k++;}
	if (y[l] == 0)
		{f<<'-'<<a[n]<<' '<<'0'<<endl; k++;}
    f.close();
    delete [] a; delete [] z;
    return k;
}
int main()
{
	double start_time =  clock();
	int count=0,first=0;
	Vector y (k,0);
    dense2D<int> H(k, n);
    matr_gen(H);
    
    srand(time(0));
    for( int i=1; i< k; i++)
		y[i]=rand() % 2;
		

	y[1]=1;	
   // std::cout << "H is \n" << H << "\n";
    std::cout << "y is \n" << y << "\n";
    ofstream m( "matr6",ios::app);
   // m<<H<<endl;
    m<<y<<endl;
    for (int i=0; i<k; i++)
    {
		count=syst(H,y,i,count,first);
		first+= n/2;
	}
	ofstream f( "result6", ios::app);
	f<<n+2<<' '<<'0'<<endl;  count++;
	f.close();
	cout<<"number of d:"<<count<<endl;
	double end_time = clock();
	double search_time=(double) (end_time-start_time);
    cout<<"time - "<<search_time/CLOCKS_PER_SEC<<endl;
    return 0;
}
