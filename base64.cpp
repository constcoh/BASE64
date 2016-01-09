#include <iostream>
#include < fstream>
using namespace std;

char Base64Char(unsigned char b){
	b&=0x3F;
	if (b<26) return 'A'+b;
	if (b<52) return 'a'+(b-26);
	if (b<62) return '0'+(b-52);
	if (b==62) return '+';
	return '/';
}

int Base64Encode(char *InStr,char* OutStr, int Len){
	int index_input=0,index_output=0;
	unsigned char a1,a2,a3, b1,b2,b3,b4;
	for(index_input=0;index_input<Len;index_input+=3){
		a1=a2=a3=b1=b2=b3=b4=0;
		a1=InStr[index_input];
		if (index_input+1<Len) a2=InStr[index_input+1];
		if (index_input+2<Len) a3=InStr[index_input+2];

		b1=a1>>2;
		b2=((a1&0x3)<<4)|(a2>>4);
		b3=((a2&0xF)<<2)|(a3>>6);
		b4=a3&0x3F;

		OutStr[index_output++]=Base64Char(b1);
		OutStr[index_output++]=Base64Char(b2);
		if (index_input+1<Len) OutStr[index_output++]=Base64Char(b3); else OutStr[index_output++]='=';
		if (index_input+2<Len) OutStr[index_output++]=Base64Char(b4); else OutStr[index_output++]='=';

	}
	return index_output;
}


int main(int argc, char* argv[]){
	char fname[256];
	if (argc>1){
		strcpy(fname, argv[1]);
	}else{
		cout<<"Input file name: "; cin.getline(fname,256);
	}
	ifstream inFile(fname, ios_base::binary);
	if(!inFile){
		cout<<"Ne mogu otkrit fail\n";
		system("pause");
		return 1;
	}
	strcat(fname,".b64");
	ofstream outFile(fname);
	if(!inFile){
		cout<<"Ne mogu otkrit fail\n";
		system("pause");
		return 2;
	}
	char inStr[3],outStr[4];
	int s, counter=0;
	while(inFile.peek()!=EOF){
		inFile.read(inStr,3);
		s=inFile.gcount();//Kolichestvo poslednich otdanich simvolov
		s=Base64Encode(inStr,outStr,s);
		counter+=s;
		if(counter>=80) {outFile<<endl; counter=s;}
		outFile.write(outStr, s);
	}
	inFile.close();
	outFile.close();
	cout<<"Encoding - OK"<<endl;


	system("pause");
	return 0;
}