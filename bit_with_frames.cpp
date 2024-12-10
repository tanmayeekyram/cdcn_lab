#include<bits/stdc++.h>
#include<iostream>
#include<fstream>

using namespace std;

int main(){
string str;
cout<<"SENDER SIDE\n";
cout<<"user data: ";
getline(cin,str);

string l="";
vector<string>v;
v.push_back("flag");
  for(int i=0;i<=str.length();i++){
  if(str[i]==' '||i==str.length()){
  if(l=="flag"||l=="esc"){
v.push_back("esc");
}
v.push_back(l);
l="";
}else{
l+=str[i];
}
}
v.push_back("flag");


string res="";
for(int i=0;i<v.size()-1;i++){
res+=v[i]+" ";
}
res+=v[v.size()-1];
cout<<"after Byte Stuffing: "<<res;
ofstream fp("lala.txt");
fp<<res;
fp.close();

cout<<"\ndone saving!! \n\n\nRECIEVER SIDE\n";
//DESTUFFING
string frames;
ifstream fpp("lala.txt");
if(fpp.is_open()){
getline(fpp,frames);
}
cout<<"Recieved frames: "<<frames<<endl;
stringstream ss(frames);
string word,output="";
bool f=false;
while(ss>>word){
if(word=="esc"&&f==false){
f=true;
continue;
}
if(f==true){
f=false;
}
output+=word+" ";
}
output.erase(0,5);
output.erase(output.length()-5,5);
cout<<"After Byte Destuffing "<<output<<endl;
}
