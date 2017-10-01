#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef long unsigned int filePosition; //to index the file

class XOREncryptor
{
    void showProgressBar(filePosition ,filePosition); //it will display progress bar
    filePosition getFileSize(string); //to get the complete file size to calculate progress
public:
    XOREncryptor(){}
    void encrypt(string ,string);
    void decrypt(string ,string);
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
    cout<<"Press enter to continue..."<<endl;
    cin.get();
    return 0;
}

void XOREncryptor::encrypt(string fileName,string key)
{
    ifstream iFile;
    ofstream oFile;
    string outFileName=fileName+".xre";
    int i=0;
    char temp;
    char *charptr=&temp;
    filePosition fullFileSize=getFileSize(fileName);
    try
    {
        iFile.open(fileName,ios::binary|ios::in);
        oFile.open(outFileName,ios::binary|ios::out|ios::trunc);
        if(!(oFile.is_open()||iFile.is_open()))
            throw 1;
        cout<<"Encrypting File... Please wait!!!"<<endl;
        while(iFile.read(charptr,1))
        {
            temp=temp^key[(i++)%key.length()];
            oFile.put(temp);
            showProgressBar(iFile.tellg(),fullFileSize);
        }
        iFile.close();
        oFile.close();
    }
    catch(int error)
    {
        cout<<"ERROR during opening file."<<endl;
        exit(1);
    }
    cout<<"\nFile encrypted successfully!!!"<<endl;
}

void XOREncryptor::decrypt(string fileName,string key)
{
    ifstream iFile;
    ofstream oFile;
    string outFileName;
    outFileName=fileName.substr(0,fileName.length()-4);
    int i=0;
    char temp;
    char *charptr=&temp;
    filePosition fullFileSize=getFileSize(fileName);
    try
    {
        iFile.open(fileName,ios::binary|ios::in);
        oFile.open(outFileName,ios::binary|ios::out|ios::trunc);
        if(!(oFile.is_open()||iFile.is_open()))
            throw 1;
        cout<<"Decrypting File... Please wait!!!"<<endl;
        while(iFile.read(charptr,1))
        {
            temp=temp^key[(i++)%key.length()];
            oFile.put(temp);
            showProgressBar(iFile.tellg(),fullFileSize);
        }
        iFile.close();
        oFile.close();
    }
    catch(int error)
    {
        cout<<"ERROR during opening file."<<endl;
        exit(1);
    }
    cout<<"\nFile decrypted successfully!!!"<<endl;
}

void XOREncryptor::showProgressBar(filePosition completed,filePosition total)
{
    float progress=static_cast<float>(completed)/total;
    int width=50;
    cout<<"[";
    for(int i=1;i<width;i++)
    {
        if(i<width*progress)
            cout<<"=";
        else
            cout<<" ";
    }
    cout<<"] "<<static_cast<int>(progress*100)<<"%\r";
}

filePosition XOREncryptor::getFileSize(string fileName)
{
    ifstream file(fileName,ios::in|ios::ate|ios::binary);
    return file.tellg();
}
