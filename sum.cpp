#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include <boost/numeric/mtl/mtl.hpp>

using namespace std;

	using namespace mtl;

//parameters of system
const int  n=10;
const int  k=5;

/* 
* In Hx = y equation vector x has weight t, where t - parameter;
* Conversion to CNF equation: x1 + x2 +...+ xn = t, using summator
*/

int sum (int *x, int* y, int *s, int it, int k, int &first)
{
	int *q= new int[it];
	for (int i=0; i< it+1; i++)
		{s[i]=first; first++;}
	for (int i=0; i< it; i++)
		{q[i]=first; first++;}
		
	for (int i=0; i<it; i++)
		cout<<"x :"<<x[i]<<' ';
	cout<<endl;	
	for (int i=0; i<it; i++)
		cout<<"y :" <<y[i]<<' ';
	cout<<endl;
	for (int i=0; i<it; i++)
		cout<<"q :" <<q[i]<<' ';
	cout<<endl;
	for (int i=0; i<it+1; i++)
		cout<<"s :" <<s[i]<<' ';
	cout<<endl;	
	ofstream f("res1", ios::app);
	 
	f<<x[0]<<' '<<y[0]<<' '<<'-'<<s[0]<<' '<<'0'<<endl; k++;
	f<<'-'<<x[0]<<' '<<y[0]<<' '<<s[0]<<' '<<'0'<<endl; k++;
	f<<x[0]<<' '<<'-'<<y[0]<<' '<<s[0]<<' '<<'0'<<endl; k++;
	f<<'-'<<x[0]<<' '<<'-'<<y[0]<<' '<<'-'<<s[0]<<' '<<'0'<<endl; k++;
	
	f<<x[0]<<' '<<y[0]<<' '<<'-'<<q[0]<<' '<<'0'<<endl; k++;
	f<<'-'<<x[0]<<' '<<y[0]<<' '<<'-'<<q[0]<<' '<<'0'<<endl; k++;
	f<<x[0]<<' '<<'-'<<y[0]<<' '<<'-'<<q[0]<<' '<<'0'<<endl; k++;
	f<<'-'<<x[0]<<' '<<'-'<<y[0]<<' '<<q[0]<<' '<<'0'<<endl; k++;
	
	for(int j=1; j< it; j++)
	{
		f<< q[j-1] <<' '<< x[j] <<' ' << y[j]<<' '<<'-' << q[j] <<' '<<'0'<< endl;  k++;
		f << q[j-1] <<' '<< x[j]<<' '<<'-' << y[j]<<' '<< '-' << q[j] << ' '<<'0'<<endl;  k++;
		f << q[j-1] <<' '<< x[j] <<' '<< y[j]<<' '<<'-'<< q[j] << ' '<<'0'<<endl;  k++;
		f << q[j-1]<<' '<< '-' << x[j]<<' '<< '-' << y[j]<<' '<< q[j] <<' '<<'0'<<endl;  k++;
		f <<'-'<< q[j-1] <<' '<< x[j] <<' '<<y[j]<<' '<< '-' << q[j] <<' '<<'0'<< endl;  k++;
		f <<'-'<< q[j-1] <<' '<< x[j]<<' '<< '-' <<y[j] <<' '<< q[j] <<' '<<'0'<< endl;  k++;
		f <<'-'<< q[j-1]<<' ' << '-' << x[j] <<' '<<y[j] <<' '<< q[j] <<' '<<'0'<< endl;  k++;
		f <<'-'<< q[j-1] <<' '<< '-' << x[j]<<' '<<'-'<<y[j] << ' '<< q[j] <<' '<<'0'<< endl;  k++;
		
		f<< q[j-1] <<' '<< x[j] <<' ' << y[j]<<' '<<'-'<< s[j] <<' '<<'0'<< endl;  k++;
		f <<'-'<< q[j-1] <<' '<< x[j]<<' '<< y[j]<<' '<< s[j] << ' '<<'0'<<endl;  k++;
		f << q[j-1] <<' '<< x[j] <<' '<<'-'<< y[j]<<' '<< s[j] << ' '<<'0'<<endl;  k++;
		f << q[j-1]<<' '<<'-'<< x[j]<<' '<< y[j]<<' '<< s[j] <<' '<<'0'<<endl;  k++;
		f <<'-'<< q[j-1] <<' '<< x[j] <<' '<<'-'<<y[j]<<' '<< '-' << s[j] <<' '<<'0'<< endl;  k++;
		f <<'-'<< q[j-1] <<' '<< '-'<<x[j]<<' '<<y[j] <<' '<< '-'<<s[j] <<' '<<'0'<< endl;  k++;
		f <<'-'<< q[j-1]<<' ' << '-' << x[j] <<' '<<'-'<<y[j] <<' '<< s[j] <<' '<<'0'<< endl;  k++;
		f << q[j-1] <<' '<< '-' << x[j]<<' '<<'-'<<y[j] << ' '<<'-'<< s[j] <<' '<<'0'<< endl;  k++;
	}
	
	f<<s[it]<<' '<<'-'<<q[it-1]<<' '<<'0'<<endl; k++;
	f<<'-'<<s[it]<<' '<<q[it-1]<<' '<<'0'<<endl; k++;
	f.close();
	return k;
}


int main()
{
	int weight=5;
	vector<int*> list;
	bool alone =false;
	int count=0, i=0, pos=0;
	int it=1, first=17;
	ofstream f("res1", ios::app);
    int num=n/2;
    while (num>=1)
    {
		cout<<"num "<<num<<endl;
		for (int j=1; j<=num; j++)
		{
			if ((j==num) && (alone) && (num!=1))
			{
				int *s= new int[it+1];
				cout<<i<<endl;
				for (int t=0; t<it; t++)
					{s[t]=*(list[pos]+t);}
				s[it]=first; first++;
				pos++;	
				for (int i=0; i<it+1; i++)
					cout<<"s :" <<s[i]<<' ';
				cout<<endl;	
					
				alone=false; 
				f<<'-'<<s[it]<<' '<<'0'<<endl;
				//count=sum(c1,c2,s,it,count,first);
				//list.pop_back(); 
				list.push_back(s); i++;
			}
			else
			{
				int *c1= new int[it];
				int *c2= new int[it];
				if (it==1)
					{c1[0]=j*2-1; c2[0]=j*2;}
				else
				{
					for (int t=0; t<it; t++)
						{c1[t]=*(list[pos]+t); c2[t]=*(list[pos+1]+t);} 
					pos+=2;
				}				
				int *s= new int[it+1];
				count=sum(c1,c2,s,it,count,first);
				list.push_back(s); i++;
			}
		}
		cout<<"number of d:"<<count<<endl;
		if (num % 2==0)
			num /= 2;
		else if (num==1)
			break;
		else
			{num=(num+1)/2; alone=true;}
		
		it++;
	}
	cout<<i<<endl;
    for (int j=0; j<=it-1; j++)
    {
		cout<<*(list[i-1]+j)<<" ";
		if (weight % 2 ==1)
			f<<*(list[i-1]+j)<<' '<<'0'<<endl; //?
		else
			f<<'-'<<*(list[i-1]+j)<<' '<<'0'<<endl;
		count ++; weight /=2;
	}
	cout<<"number of d:"<<count<<endl;
	f.close();
	return 0;
}
