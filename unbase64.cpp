#include <iostream>
#include < fstream>
#include <string.h>
using namespace std;

unsigned char char_base64(char d){
/*	if(d=='A') return 0;
	if(d=='B') return 1;
	if(d=='C') return 2;
	if(d=='D') return 3;
	if(d=='E') return 4;
	if(d=='F') return 5;
	if(d=='G') return 6;
	if(d=='H') return 7;
	if(d=='I') return 8;
	if(d=='J') return 9;
	if(d=='K') return 10;
	if(d=='L') return 11;
	if(d=='M') return 12;
	if(d=='N') return 13;
	if(d=='O') return 14;
	if(d=='P') return 15;
	if(d=='Q') return 16;
	if(d=='R') return 17;
	if(d=='S') return 18;
	if(d=='T') return 19;
	if(d=='U') return 20;
	if(d=='V') return 21;
	if(d=='W') return 22;
	if(d=='X') return 23;
	if(d=='Y') return 24;
	if(d=='Z') return 25;
	if(d=='a') return 26;
	if(d=='b') return 27;
	if(d=='c') return 28;
	if(d=='d') return 29;
	if(d=='e') return 30;
	if(d=='f') return 31;
	if(d=='g') return 32;
	if(d=='h') return 33;
	if(d=='i') return 34;
	if(d=='j') return 35;
	if(d=='k') return 36;
	if(d=='l') return 37;
	if(d=='m') return 38;
	if(d=='n') return 39;
	if(d=='o') return 40;
	if(d=='p') return 41;
	if(d=='q') return 42;
	if(d=='r') return 43;
	if(d=='s') return 44;
	if(d=='t') return 45;
	if(d=='u') return 46;
	if(d=='v') return 47;
	if(d=='w') return 48;
	if(d=='x') return 49;
	if(d=='y') return 50;
	if(d=='z') return 51;
	if(d=='0') return 52;
	if(d=='1') return 53;
	if(d=='2') return 54;
	if(d=='3') return 55;
	if(d=='4') return 56;
	if(d=='5') return 57;
	if(d=='6') return 58;
	if(d=='7') return 59;
	if(d=='8') return 60;
	if(d=='9') return 61;
	if(d=='+') return 62;
	if(d=='/') return 63;*/



	if((d>='A')&&(d<='Z')) return d-'A';
	if((d>='a')&&(d<='z')) return (d-'a'+26);
	if((d>='0')&&(d<='9')) return (d-'0'+52);
	if (d=='+') return 62;
	return 63;
}

int Base64Encode(char *InStr, char *OutStr, int Len){
	int index_input=0, index_output=0;
	unsigned char a1, a2, a3;
	unsigned char b1, b2, b3, b4;
	bool fl3,fl4;
	for(index_output=0; index_output<Len; index_output+=4){
		a1=a2=a3=b1=b2=b3=b4=0;
		b1=InStr[index_output];
		b2=InStr[index_output+1];
		b3=InStr[index_output+2];
		b4=InStr[index_output+3];
		b1=char_base64(b1);
		b2=char_base64(b2);
		fl3=false;fl4=false;
		if (b3!='=') {b3=char_base64(b3);} else {fl3=true;}
		if (b4!='=') {b4=char_base64(b4);} else {fl4=true;}
		
		a1=(b1<<2)|(b2>>4);		OutStr[index_output++]=a1;
		if(fl3==false){
			a2=(b2<<4)|(b3>>2);
			OutStr[index_output++]=a2;
		}
		if(fl4==false){
			a3=(b3<<6)|b4;
			OutStr[index_output++]=a3;
		}
		return index_output;
	}
}


void strcopy(char *d1, char *d2){
	int l;
	l=(int)strlen(d2);
	for(int i=0;i<=l;++i) d1[i]=d2[i];
}

int main(int argc, char* argv[]){
	ifstream f1; char fname1[256];
	ofstream f2; char fname2[256];
//	strcopy(&fname1,&argv[1]);
	if (argc>1) strcpy(fname1,argv[1]); else{

//	{
		cout<<"Input file name:";cin.getline(fname1,256);
//		cin.ignore();
	}
	strcpy(fname2,fname1); fname2[strlen(fname2)-3]=0;
	f1.open(fname1);
	if(f1==NULL){cout<<"Can not open file:" << fname1<<endl; system("pause"); return 0;}
	f2.open(fname2, ios::binary);
	if(f2==NULL){f1.close(); cout<<"Can not open file:" << fname2<<endl; system("pause"); return 0;}
	
	char tmp[]={0,0,0,0,0};
	char otv_i[]={0,0,0,0};
	char tmp_0[151];
	int l,l_i;
	while(f1.eof()==false){
		f1.getline(tmp_0,150);
		l=strlen(tmp_0);
//		cout<<tmp_0<<endl;
		for(int i=0;i<l;i+=4){
			tmp[0]=tmp[1]=tmp[2]=tmp[3]=otv_i[0]=otv_i[1]=otv_i[2]=0;
			tmp[0]=tmp_0[i];
			tmp[1]=tmp_0[i+1];
			tmp[2]=tmp_0[i+2];
			tmp[3]=tmp_0[i+3];
			l_i=Base64Encode(tmp,otv_i,4);
//			cout<<otv_i;
			f2<<otv_i[0];
			if (l_i>1) f2<<otv_i[1];
			if (l_i>2) f2<<otv_i[2];
		}
	}
	f2.close();
	f1.close();
/*	cout<<"HELP!!!!!!!!!!!!!!!!!\n";
	l_i=Base64Encode("YWJj",otv_i,4);
	cout<<otv_i<<endl;*/
	cout<<"OK!   ";
	system("pause");
	return 0;
}