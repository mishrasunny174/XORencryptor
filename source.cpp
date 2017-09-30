#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

class XOREncryptor
{
public:
    XOREncryptor(){}
    void encrypt(string fileName,string key);
    void decrypt(string fileName,string key);
};

int main(int argc,char* argv[])
{
    XOREncryptor xorEncryptor;
    string fileName,key,choice;
    if(argc==4)
    {
        fileName=argv[2];
        key=argv[3];
        choice=argv[1];
        if(choice=="encrypt")
            xorEncryptor.encrypt(fileName,key);
        else if(choice=="decrypt")
            xorEncryptor.decrypt(fileName,key);
        else
            cout<<"Usage: "<<argv[0]<<" <encrypt/decrypt> <filename> <key>"<<endl;
    }
    else
        cout<<"Usage: "<<argv[0]<<" <encrypt/decrypt> <filename> <key>"<<endl;
    cout<<"Enter any key to continue..."<<endl;
    cin.ignore();
    cin.get();
    return 0;
}

void XOREncryptor::encrypt(string fileName,string key)
{
    ifstream iFile;
    ofstream oFile;
    string outFile=fileName+".xre";
    int i=0;
    char temp;
    char *charptr=&temp;
    try
    {
        iFile.open(fileName,ios::binary|ios::in);
        oFile.open(outFile,ios::binary|ios::out|ios::trunc);
        if(!(oFile.is_open()||iFile.is_open()))
            throw 1;
        cout<<"Encrypting File... Please Wait!"<<endl;
        while(iFile.read(charptr,1))
        {
            temp=temp^key[(i++)%key.length()];
            oFile.put(temp);
        }
        iFile.close();
        oFile.close();
    }
    catch(int error)
    {
        cout<<"ERROR during opening file."<<endl;
        exit(1);
    }
    cout<<"File encrypted successfully!!!"<<endl;
}

void XOREncryptor::decrypt(string fileName,string key)
{
    ifstream iFile;
    ofstream oFile;
    string outFile;
    outFile=fileName.substr(0,fileName.length()-4);
    int i=0;
    char temp;
    char *charptr=&temp;
    try
    {
        iFile.open(fileName,ios::binary|ios::in);
        oFile.open(outFile,ios::binary|ios::out|ios::trunc);
        if(!(oFile.is_open()||iFile.is_open()))
            throw 1;
        cout<<"Decrypting File... Please Wait!"<<endl;
        while(iFile.read(charptr,1))
        {
            temp=temp^key[(i++)%key.length()];
            oFile.put(temp);
        }
        iFile.close();
        oFile.close();
    }
    catch(int error)
    {
        cout<<"ERROR during opening file."<<endl;
        exit(1);
    }
    cout<<"File decrypted successfully!!!"<<endl;
}
