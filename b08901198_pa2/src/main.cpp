#include <iostream> 
#include <sstream>
#include <vector>
#include<string.h>
#include<fstream>
#include <cstring>
#include <typeinfo>
#include<algorithm> 
using namespace std;
vector<string> split(const string& str, const string& delim);
//int M(vector<vector<int>> m,vector<vector<int>> c,int N);
void findchord(int i,int j,vector<int>& c,vector<vector<int>>& check,int&count_line,vector<vector<int>>&res);
int M2(vector<vector<int>>& m,vector<int>& c,int i,int j,vector<vector<int>>& check);
int main(int argc, char* argv[]){
	//string line;
	int count=0;
	int N=12;
	int count_line=0;
	vector<vector<int>> res;
	vector<vector<int>> m;
	vector<vector<int>> check;
	vector<int>c(N,-1);

    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    //fin.open(argv[1],ios::in);
    fout.open(argv[2],ios::out);
    //fin.getline(buffer,200); 
    int k;
    int count_n=1;
    int count_ij=1;
    int count_0=0;
    int i,j;
    while(fin>>k){
    	//cout<<typeid(i).name();
     	if(count_n){
     		N=k;
     		c=vector<int>(N,-1);
     		m=vector<vector<int>>(N,vector<int>(N,-1));
     		check=vector<vector<int>>(N,vector<int>(N,-1));
     		//res=vector<vector<int>>(N,vector<int>(2,0));
     		count_n=0;
		 }
		else if(count_ij==1){
			i=k;
			if(k==0 && count_0!=1){
				count_0=1;
			}
			else if(k==0 &&count_0){
				int num=M2(m,c,0,N-1,check);
				cout<<num<<endl;
				res=vector<vector<int>>(num,vector<int>(2,0));
				findchord(0,N-1,c,check,count_line,res);
				sort(res.begin(),res.end());
				fout<<num<<endl;
				for(i=0;i<res.size();i++){
					fout<<res[i][0]<<" "<<res[i][1]<<endl;
				}
			}
			count_ij=2;
		}
	    else if(count_ij==2){
	    	j=k;
	    	if(k==0){
	    		count_0=1;
			}
	    	c[j]=i;
	    	c[i]=j;
	    	//cout<<i<<j<<endl;
	    	count_ij=1;
		}
		
	}
	return 0;
	
}
void findchord(int i,int j,vector<int>& c,vector<vector<int>>& check,int&count_line,vector<vector<int>>&res){
	while(j>i+1){
		if (check[i][j]==2){
			int k=c[j];
			//cout<<k<<" "<<j<<endl;
			//findchord(i,k-1,c,check);
			res[count_line][0]=k;
			res[count_line][1]=j;
			count_line++;
			findchord(k+1,j-1,c,check,count_line,res);
			j=k-1;
			//count_line++;
		}
		else if(check[i][j]==3){
			//cout<<i<<" "<<j<<endl;
			res[count_line][0]=i;
			res[count_line][1]=j;
			count_line++;
			findchord(i+1,j-1,c,check,count_line,res);
			j=i-1;
			//count_line++;
		}
		else {
			j--;
			
		}
	}
}
int M2(vector<vector<int>>& m,vector<int>& c,int i,int j,vector<vector<int>>& check){
	if(i>=j){
		return 0;
	}
	else if(m[i][j]!=-1){
		return m[i][j];
	}
	else if (c[j]>j || c[j]<i){
		m[i][j]=M2(m,c,i,j-1,check);
		check[i][j]=1;
		return m[i][j];
	}
	else{
		if(c[j]==i){
			m[i][j]=M2(m,c,i+1,j-1,check)+1;
			//cout<<i<<j<<endl;
			check[i][j]=3;
			return m[i][j];
			
		}
		else{
			int k=c[j];
		    //cout<<k<<j<<endl;
		    int x=M2(m,c,i,k-1,check)+1+M2(m,c,k+1,j-1,check);
		    int y=M2(m,c,i,j-1,check);
			m[i][j]=max(x,y);
			//check[i][j]=2;
			if (m[i][j]==x){
				//cout<<k<<j<<endl;
				check[i][j]=2;
			}
			return m[i][j];
		}
	}

	
}
vector<string> split(const string& str, const string& delim) {  
	vector<string> res;  
	if("" == str) return res;  
	//先將要切割的字串從string型別轉換為char*型別  
	char * strs = new char[str.length() + 1] ; //不要忘了  
	strcpy(strs, str.c_str());   

	char * d = new char[delim.length() + 1];  
	strcpy(d, delim.c_str());  

	char *p = strtok(strs, d);  
	while(p) {  
		string s = p; //分割得到的字串轉換為string型別  
		res.push_back(s); //存入結果陣列  
		p = strtok(NULL, d);  
	}  

	return res;  
} 
