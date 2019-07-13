#include<iostream>
#include<vector>
#include<ctime>
#include<fstream>
#include<conio.h>
#include "windows.h"
using namespace std;
#define     KEY_LEFT    VK_LEFT
#define     KEY_RIGHT   VK_RIGHT
#define     KEY_UP      VK_UP
#define     KEY_DOWN    VK_DOWN
#define     KEY_ESC     VK_ESCAPE
#define     KEY_SPACE    VK_SPACE
int map[100][100];
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
 
// Ðat mau nen cho chu
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
 
// Ðat mau nen
void SetBGColor(WORD color){
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void ShowCur(bool CursorVisibility){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

bool checkKey(int key){
    return GetAsyncKeyState(key);
}
int _muc;
int _map;
string _tenDiem;
int _diem;
bool endGame;
struct ToaDo{
	int x,y;
	int x0,y0;
};
ToaDo huong;
class ThucAn;
class Ran{
	private:
		vector <ToaDo> ran;
		int tocDo;
	public:		
		Ran(){
		}
		friend class ThucAn;
		vector<ToaDo> getRan(){
			return this->ran;	
		}
		void setRan(vector<ToaDo> ran){
			this->ran=ran;
		}
		void setTocDo(int tocDo){
			this->tocDo=tocDo;
		}
		int getTocDo(){
			return this->tocDo;
		}
};

class ThucAn{
	private:
		ToaDo thucAn;
	public:
		ThucAn(){
			
		}
		void setThucAn(ToaDo thucAn){
			this->thucAn=thucAn;	
		}	
		ToaDo getThucAn(){
			return this->thucAn;
		}
};

class Map{
	private:
		int dai;
		int rong;
		int map;
	public:
		void setDai(int dai){
			this->dai=dai;
		}
		int getDai(){
			return this->dai;
		}
		void setRong(int rong){
			this->rong=rong;
			}
		int getRong(){
			return this->rong;
		}
		void setMap(int map){
			this->map=map;
			}
		int getMap(){
			return this->map;
		}
};
bool kt(ToaDo td,Map m){
	if(map[td.y][td.x]==1){
		return true;
	}
	return false;
}
void drawFood(ThucAn food) {
    SetColor(12);
    ToaDo tmp;
    tmp=food.getThucAn();
    gotoxy(tmp.x,tmp.y);
	cout<<"$";
}	

void drawSnake(Ran snake) {
	vector<ToaDo> r;
	r=snake.getRan();
    SetColor(14);
    gotoxy(r[0].x, r[0].y);
	cout<<(char)254;
    for (int i = 1; i <r.size(); i++) {
        gotoxy(r[i].x, r[i].y);
		cout<<(char)233;
    }
    gotoxy(r[r.size()-1].x0, r[r.size()-1].y0);
	cout<<" ";	
}

void chonMap(){
	int i=0;
	string a[100];
	fstream fin;
	if(_map==1){
		fin.open("map1.txt", ios :: in);
	}
	if(_map==2){
		fin.open("map2.txt", ios :: in);
	}
	if(_map==3){
		fin.open("map3.txt", ios :: in);
	}
	if(_map==4){
		fin.open("map4.txt", ios :: in);
	}
	if(_map==5){
		fin.open("map5.txt", ios :: in);
	}
	if(_map==6){
		fin.open("map6.txt", ios :: in);
	}
	if(_map==7){
		fin.open("map7.txt", ios :: in);
	}
	while(!fin.eof()){
		fflush(stdin);
		getline(fin, a[i]);
		i++;
	}
	for(int j = 0; j < i; j++){
		for(int k=0;k<a[j].length();k++){
			if(a[j][k]== '1'){
				map[j][k]=1;
			}
			else {
				map[j][k]=0;
			}
		}
	}
}

void veMap(){
	for(int i=0;i<20;i++){
		for(int j=0;j<70;j++){
			if(map[i][j]==1){
				gotoxy(j,i);
				SetBGColor(0);
				SetColor(7);
				cout<<(char)219;
			}
			else {
				gotoxy(j,i);
				SetBGColor(3);
				SetColor(7);
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

void moveSnake(ToaDo td,Ran &snake,Map map,ThucAn &food) {
    vector<ToaDo> r;
    r=snake.getRan();
    for (int i = 0; i < r.size(); i++) {
        if (i == 0) {
            r[0].x0 = r[0].x; r[0].y0 = r[0].y;
            r[0].x += td.x; r[0].y += td.y;
        }	
		else{
            r[i].x0 = r[i].x; r[i].y0 = r[i].y;
            r[i].x = r[i - 1].x0; r[i].y = r[i - 1].y0;
        }
        if (i != 0 && (r[0].x == r[i].x && r[0].y == r[i].y)) {
			endGame = true;
		}
		if(kt(r[0],map)){
			endGame = true;
		}
    }
    if (r[0].x >= map.getDai()) r[0].x = 0;
    if (r[0].x < 0) r[0].x = map.getDai() - 1;
    if (r[0].y >= map.getRong()) r[0].y = 0;
    if (r[0].y < 0) r[0].y = map.getRong() - 1;
    ToaDo tmp;
    tmp=food.getThucAn();
    if (r[0].x == tmp.x && r[0].y ==tmp.y){
        r.insert(r.begin(),tmp);
		srand( time(NULL) );
        ToaDo tmp;
        tmp.x = rand() % map.getDai(); 
        tmp.y = rand() % map.getRong(); 
        while(kt(tmp,map)){
        	tmp.x = rand() % map.getDai(); 
	        tmp.y = rand() % map.getRong(); 
		}
        food.setThucAn(tmp);
    }
	snake.setRan(r);
}

void XuLy(Ran &snake,Map map,ThucAn &food) {
    moveSnake(huong,snake,map,food);
	if (checkKey(KEY_SPACE)) {
        system("pause");
    } 
    if (checkKey(KEY_LEFT)) {
        if (huong.x != 1) {
            huong.x = -1; huong.y = 0;
        }
    }
    else if (checkKey(KEY_RIGHT)) {
        if (huong.x != -1) {
            huong.x = 1; huong.y = 0;
        }
    }
    else if (checkKey(KEY_UP)) {
        if (huong.y != 1) {
            huong.y = -1; huong.x = 0;
        }
    }
    else if (checkKey(KEY_DOWN)) {
        if (huong.y != -1) {
            huong.y = 1; huong.x = 0;
        }
    }
    if (checkKey(KEY_ESC)) {
        endGame = true;
    }
}

void DocDuLieu(){
	fstream fin;
	fin.open("setup.txt", ios :: in);
	fflush(stdin);
	fin>>_muc;
	fflush(stdin);
	fin>> _map;
	fflush(stdin);
	fin>> _tenDiem;
	fflush(stdin);
	fin>> _diem;
	fin.close();
}

void GhiDuLieu(){
	fstream fout;
	fout.open("setup.txt",ios ::out);
	fflush(stdin);
	fout<<_muc<<endl;
	fflush(stdin);
	fout<< _map<<endl;
	fflush(stdin);
	fout<< _tenDiem<<endl;
	fflush(stdin);
	fout<< _diem<<endl;
	fout.close();
	
}
void muc(Ran &r){
	XoaManHinh();
	system("cls");
	int x=1,dd=0;
	while(dd==0){
		XoaManHinh();
		SetBGColor(32);
		if(x==1){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\n\n\t\t\t\t\t\tEasy "<<endl;
		if(x==2){
			SetColor(27);	
		}
		else {
			SetColor(19);	 
		}
		cout<<"\t\t\t\t\t\tNormal"<<endl;
		if(x==3){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tHard"<<endl;
		if(x==4){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tVery Hard"<<endl;
		if(x==5){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tCome Back"<<endl;
		if(kbhit()){
			int c = toupper(getch());
			switch(c){
				case 80 : {
					x++;
					break;
				}
				case 72 : {
					x--;
					break;
				}
				case 13 : {
					dd=1;
					break;
				}
			}
		}
		if(x>5){
			x=1;
		}	
		if(x<0){
			x=5;
		}
	}
	if(x!=5){
		_muc=x;	
	}
}
void setMap(){
	XoaManHinh();
	system("cls");
	int x=1,dd=0;
	while(dd==0){
		XoaManHinh();
		SetBGColor(32);
		if(x==1){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\n\n\t\t\t\t\t\tNo Maze "<<endl;
		if(x==2){
			SetColor(27);	
		}
		else {
			SetColor(19);	 
		}
		cout<<"\t\t\t\t\t\tBox"<<endl;
		if(x==3){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tTunnel"<<endl;
		if(x==4){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tMill"<<endl;
		if(x==5){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tRails"<<endl;
		if(x==6){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tApartment"<<endl;
		if(x==7){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tPROPTIT"<<endl;
		if(x==8){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		cout<<"\t\t\t\t\t\tComeBack"<<endl;
		if(kbhit()){
			int c = toupper(getch());
			switch(c){
				case 80 : {
					x++;
					break;
				}
				case 72 : {
					x--;
					break;
				}
				case 13 : {
					dd=1;
					break;
				}
			}
		}
		if(x>8){
			x=1;
		}	
		if(x<0){
			x=8;
		}
	}
	if(x!=8){
		_map=x;
	}
}

void KhoiTao(Ran &ran,ThucAn &thucAn,Map &map){
	endGame = false;
	map.setDai(70);
	map.setRong(20);
	vector<ToaDo> r;
	ToaDo Dau;
	srand(time(NULL));
    Dau.x = rand() % map.getDai(); 
    Dau.y = rand() % map.getRong(); 
    while(kt(Dau,map)){
    	Dau.x = rand() % map.getDai(); 
        Dau.y = rand() % map.getRong(); 
	}
	r.push_back(Dau);
	ran.setRan(r);
	r.push_back(Dau);
	ToaDo food;
    food.x = rand() % map.getDai(); 
    food.y = rand() % map.getRong(); 
    while(kt(food,map)){
    	food.x = rand() % map.getDai(); 
        food.y = rand() % map.getRong(); 
	}
    thucAn.setThucAn(food);
	huong.x=1;
	huong.y=0;
	if(_muc==1){
		ran.setTocDo(200);
	}
	if(_muc==2){
		ran.setTocDo(100);
	}
	if(_muc==3){
		ran.setTocDo(50);
	}
	if(_muc==4){
		ran.setTocDo(35);
	}
	chonMap();
	veMap();
}


void drawGame(ThucAn food,Ran snake) {
    SetBGColor(3);
	drawFood(food);
    drawSnake(snake);
    vector<ToaDo> tmp=snake.getRan();
    SetBGColor(0);
    SetColor(12);
    gotoxy(80,4);
    printf("Huynh Trinh-CLB Lap Trinh PTIT <3");
    SetColor(10);
    gotoxy(80,6);
	cout<<"High score : "<<_tenDiem<<" : "<<_diem<<endl;
	gotoxy(80,8); 		
    cout<<"Your score : "<<(tmp.size()-1)*10;
    gotoxy(80,25);
}

int Menu(){
	XoaManHinh();
	system("cls");
	int x=1,dd=0;
	while(dd==0){
		XoaManHinh();
		SetBGColor(0);
		if(x==1){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		gotoxy(48,2);
		cout<<"Start Game"<<endl;
		if(x==2){
			SetColor(27);	
		}
		else {
			SetColor(19);	 
		}
		gotoxy(48,3);
		cout<<"Level"<<endl;
		if(x==3){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		gotoxy(48,4);
		cout<<"Map"<<endl;
		if(x==4){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		gotoxy(48,5);
		cout<<"Instructions and About"<<endl;
		if(x==5){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		gotoxy(48,6);
		cout<<"Hight score"<<endl;
		if(x==6){
			SetColor(27);	
		}
		else {
			SetColor(19);	
		}
		gotoxy(48,7);
		cout<<"Exit"<<endl;
		if(kbhit()){
			int c = toupper(getch());
			switch(c){
				case 80 : {
					x++;	
					break;
				}
				case 72 : {
					x--;
					break;
				}
				case 13 : {
					dd=1;
					break;
				}
			}
		}	
		if(x>6){
			x=1;
		}
		if(x<0){
			x=6;
		}
	}
	SetBGColor(7);
	SetColor(7);
	return x;
	
}

void ProPtit(){
	SetBGColor(00);
	string a[100];
	int i = 0;
	fstream fin;
	fin.open("text.txt", ios :: in);
	while(!fin.eof()){
		fflush(stdin);
		getline(fin, a[i]);
		i++;
	}
	for(int j = 0; j < i; j++){
		if(j<10){
			SetColor(27);
		}
		else if(j>20){
			SetColor(394);
		}
		else  {
			SetColor(361);
		}
		cout <<"\t\t\t"<<a[j]<<endl;
		Sleep(100);
	}
	SetColor(14);
	SetBGColor(0);
}
main(){
	DocDuLieu();
	ShowCur(false);
	ThucAn ta;
	Ran r;
	Map m;
	ProPtit();
	system("pause");
	while(true){
		int x;
		x= Menu();
		gotoxy(70,0);
		SetBGColor(2);
		if(x==1){
			KhoiTao(r,ta,m);
			while(true){
				SetBGColor(0);
				drawGame(ta,r);
				XuLy(r,m,ta);
				if(huong.x==0){
					Sleep((float)r.getTocDo()*1.4);	
				}	
				if(huong.y==0){
					Sleep(r.getTocDo());	
				}	
				if(endGame){
					SetColor(10);
					gotoxy(80,11);
					cout<<"Game over!!!";
					vector<ToaDo> ra=r.getRan();
					if((ra.size()-1)*10>_diem){
			    		SetColor(10);
					    gotoxy(80,12);
						cout<<"New high score...";
						gotoxy(80,13);
						cout<<"Press your Name: ";
						gotoxy(150,13);
						cin>>_tenDiem;
			    		_diem=(ra.size()-1)*10;
					}
					gotoxy(80,24);
					system("pause");
					GhiDuLieu();
					break;
				}
			}
		}
		if(x==2){
			SetBGColor(0);
			muc(r);
		}
		if(x==3){
			SetBGColor(0);
			XoaManHinh();
			system("cls");
			setMap();
		}
		if(x==4){
			SetBGColor(0);
			XoaManHinh();
			system("cls");
			SetColor(27);
			string s="Dung cac phim len,xuong,trai,phai de dieu khien,esc de ket thuc game,space de tam dung";
			string S="Coded by Huynh Trinh";
			cout<<"\n\n\t";
			for(int i=0;i<s.length();i++){
				cout<<s[i];
				Sleep(15);
			}
			cout<<"\n\n\n\t\t\t";
			for(int i=0;i<S.length();i++){
				cout<<S[i];
				Sleep(50);
			}
			cout<<endl<<endl<<endl;
			system("pause");
		}
		if(x==5){
			SetBGColor(0);
			XoaManHinh();
			system("cls");
			SetColor(27);
			cout<<"\n\n\t";
			cout<<_tenDiem<<"	"<<_diem<<endl;
			cout<<endl<<endl<<endl;
			system("pause");	
		}
		if(x==6){
			SetBGColor(0);
			SetColor(0);
			gotoxy(5,25);
			break;
		}
	}
	GhiDuLieu();
}
