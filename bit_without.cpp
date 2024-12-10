//bit stuffing-1

#include<bits/stdc++.h>
using namespace std;

string TextToBinaryString(string words) {
    string la="";
    for(int i=0;i<words.length();i++){
    la+=bitset<8>(words[i]).to_string();
}
return la;
}


int main(){
    string str;
    cout<<"SENDER SIDE\n";
    cout<<"user data: ";
    getline(cin,str);
    string flag="01111110";
    string s=TextToBinaryString(str);
    int count=0;
    for(int i=0;i<s.length();i++){
        if(s[i]=='0')
        count=0;
        if(s[i]=='1'){
            count++;
        }
        if(count==5){
            s.insert(i+1,"0");
            count=0;
        }
    }
    s=flag+s+flag;
    cout<<s;
    cout<<"\n\n\nRECIEVER SIDE\nRecieved frames: "<<s<<endl;
    s.erase(0,8);
    s.erase(s.length()-8,8);  
    int c=0;
    for(int i=0;i<s.length();i++){
        if(s[i]=='1')
        c++;
        if(s[i]=='0')
        c=0;
        if(c==5){
            s.erase(i+1,1);
            c=0;
        }
    }
    cout<<"after destuffing: "<<s<<endl;
}

