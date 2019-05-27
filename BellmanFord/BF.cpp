#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<conio.h>
#include<time.h>
#include <algorithm>

using namespace std;

struct edge {
	int src, des, cost;
	//dinh nguon, dinh dich, va trong so
};

int nv, ne; //so dinh va so canh cua do thi
const int INF = 1000000000;
vector<edge> e; //mang luu danh sach cac canh
vector<int> d(nv); //mang luu khoang cach tu nguon toi cac dinh
vector<int> p(nv, -1); //mang luu cac dinh ke truoc
int flag;//co kiem tra co chu trinh am hay khong

void setData(); //nhap du lieu tu ban phim
void dataFromFile(); //nhap du lieu tu file
void randomData(); //nhap du lieu ngau nhien
void displayData(); // hien thi du lieu
void solveBF(); //giai bai toan bang thuat toan Bellman-Ford
void writeData(); //ghi du lieu ra file
void writeResult(); //ghi ket qua ra file
void displayResult(); // hien thi ket qua
void viewInterResult();//xem ket qua trung gian
void resetData();//dat lai du lieu
int fact(int n); // tinh n giai thua,ham nay duoc dung trong truong hop so dinh va so canh tao ngau nhien

int main() {
	char ch;
	while (true)
	{
		system("cls");
		cout << "\n\n\t\t=============================\n";
		cout << "\tCHUONG TRINH MO PHONG THUAT TOAN BELLMAN FORD\n";
		cout << "\n\t\t=============================\n";
		cout << "Xin moi chon chuc nang: " << endl;
		cout << "1. Nhap du lieu tu ban phim.\n";
		cout << "2. Nhap du lieu tu file (ten file vao tu ban phim).\n";//dong dau tien la so dinh, tiep theo den khoang cach giua cac dinh theo ma tran ke
		cout << "3. Tao du lieu ngau nhien.\n";
		cout << "4. Xem du lieu tren man hinh.\n";
		cout << "5. Ghi du lieu ra file (ten file nhap tu ban phim).\n";
		cout << "6. Thuc hien thuat toan.\n";
		cout << "7. Xem ket qua tren man hinh.\n";
		cout << "8. Ghi ket qua ra file.\n";
		cout << "9. xem ket qua trung gian.\n";
		cout << "r. dat lai du lieu.\n";
		cout << "0. Thoat khoi chuong trinh.\n";
		cout << "\n\t\t=============================\n";
		fflush(stdin);
		ch = _getch();
		if (ch == '1') setData();
		else if (ch == '2') dataFromFile();
		else if (ch == '3') randomData();
		else if (ch == '4') displayData();
		else if (ch == '5') writeData();
		else if (ch == '6') solveBF();
		else if (ch == '7') displayResult();
		else if (ch == '8') writeResult();
		else if (ch == '9') viewInterResult();
		else if (ch == 'r') resetData();
		else if (ch == '0') exit(0);
		else cout << "chuc nang duoc chon khong dung, moi chon lai!";
		cout << endl;
		system("pause");
	}
}


void setData() {
	int i = 0;
	edge tmp;
	cout << "nhap so dinh cua do thi: "; cin >> nv;
	cout << "\nnhap so canh cua do thi: "; cin >> ne;
	d.resize(nv);
	p.resize(nv, -1);
	for (i = 0; i < ne; i++) {
		cout << "\nnhap canh thu " << i + 1 << endl;
		cout << "\ndinh nguon: "; cin >> tmp.src;
		cout << "\ndinh dich: "; cin >> tmp.des;
		cout << "\ntrong so: "; cin >> tmp.cost;
		e.push_back(tmp);
	}
}

void dataFromFile() {
	//dong dau la so dinh, dong thu 2 la so canh, tiep theo la danh sach ke
	char tf[30];
	fstream file;
	edge tmp;
	int i = 0;

	cout << "nhap ten file: ";
	fflush(stdin);
	cin.getline(tf, 30);
	file.open(tf);
	if (!file.is_open()) {
		cout << "mo file khong thanh cong" << endl;
		return;
	}
	file >> nv;
	file >> ne;
	d.resize(nv);
	p.resize(nv, -1);
	for (i = 0; i < ne; i++) {
		file >> tmp.src;
		file >> tmp.des;
		file >> tmp.cost;
		e.push_back(tmp);
	}
	file.close();
	cout << "nhap du lieu vao tu file thanh cong" << endl;
}

void randomData() {
	int i = 0, j = 0;
	edge tmpe;
	srand(time(NULL));
	cout << "nhap so dinh: "; cin >> nv;
	cout << "nhap so canh: "; cin >> ne;
	//nv = 5 + rand() % 20;
	//int tmp = fact(nv) / (fact(nv - 2) * 2);
	//ne = rand() % (tmp - 1) + 1;
	d.resize(nv);
	p.resize(nv, -1);
	while (i<ne){
		tmpe.src = rand() % (nv - 1);
		tmpe.des = rand() % (nv - 1);
		tmpe.cost = rand() % (RAND_MAX / 2) - (RAND_MAX / 4);
		if (e.empty() && tmpe.src != tmpe.des) {
			e.push_back(tmpe);
			i++;
		}
		else {
			bool flag = true;
			size_t t = e.size();
			for (j = 0; j < t; j++) {
				if ((tmpe.src == e[j].src && tmpe.des == e[j].des) || tmpe.src == tmpe.des) {
					flag = false;
					break;
				}
			}
			if (flag) {
				e.push_back(tmpe);
				i++;
			}
		}
	}
	cout << "da tao du lieu ngau nhien thanh cong" << endl;
}

void displayData() {
	if (e.empty()) cout << "chua co du lieu" << endl;
	else {
		int i = 0;
		cout << "so dinh: " << nv;
		cout << "\nso canh: " << ne << endl;
		cout << setw(6) << " from" << setw(6) << " to" << setw(6) << " cost" << endl;
		for (i = 0; i < ne; i++) {
			cout << setw(6) << e[i].src << setw(6) << e[i].des << setw(6) << e[i].cost << endl;
		}
	}
}

void solveBF() {
	//double tim;
	//clock_t beg, fin;
	//beg = clock();
	if (e.empty()) cout << "chua co du lieu" << endl;
	else {
		int i = 0, j = 0;
		for (i = 0; i < nv; i++) {
			flag = -1;
			for (j = 0; j < ne; j++) {
				if (d[e[j].src] < INF) {
					if (d[e[j].des] > d[e[j].src] + e[j].cost) {
						d[e[j].des] = d[e[j].src] + e[j].cost;
						p[e[j].des] = e[j].src;
						flag = e[j].des;
					}
				}
			}
		}
	}
	//fin = clock();
	//tim = (double)(fin - beg) / CLOCKS_PER_SEC;
	//cout << " thoi gian thuc hien la: " << tim;
	cout << "thuc hien xong." << endl;
}

void writeData() {
	int i = 0;
	char tf[30];
	ofstream file;
	cout << "nhap ten file: ";
	fflush(stdin);
	cin.getline(tf, 30);
	file.open(tf);
	file << nv << "\n" << ne;
	for (i = 0; i < ne; i++) {
		file << "\n" << e[i].src << " " << e[i].des << " " << e[i].cost;
	}
	file.close();
	cout << "da ghi du lieu thanh cong ra file" << endl;
}

void writeResult() {
	int i = 0;
	char tf[30];
	ofstream file;
	cout << "nhap ten file: ";
	fflush(stdin);
	cin.getline(tf, 30);
	file.open(tf);
	if (flag == -1) {
		file << "khong co chu trinh am!" << endl;
	}
	else {
		int tmp = flag;
		for (i = 0; i < nv; i++) {
			tmp = p[tmp];
		}
		vector<int> path;
		for (i = tmp;; i = p[i]) {
			path.push_back(i);
			if (i == tmp && path.size() > 1) break;
		}
		reverse(path.begin(), path.end());
		file << "chu trinh am la: " << "\n";
		for (i = 0; i < path.size(); i++) {
			file << path[i] << ' ';
		}
	}
	cout << "da ghi ket qua thanh cong ra file" << endl;
}

void displayResult() {
	int i = 0;
	if (flag == -1) {
		cout << "khong co chu trinh am!" << endl;
	}
	else {
		int tmp = flag;
		for (i = 0; i < nv; i++) {
			tmp = p[tmp];
		}
		vector<int> path;
		for (i = tmp;; i = p[i]) {
			path.push_back(i);
			if (i == tmp && path.size() > 1) break;
		}
		reverse(path.begin(), path.end());
		cout << "chu trinh am la: " << endl;
		for (i = 0; i < path.size(); i++) {
			cout << path[i] << ' ';
		}
	}
}

void resetData() {
	d.clear();
	e.clear();
	p.clear();
	cout << "da dat lai du lieu" << endl;
}

void viewInterResult() {
	int i = 0, j = 0, k = 0;
	for (i = 0; i < nv; i++) {
		flag = -1;
		for (j = 0; j < ne; j++) {
			if (d[e[j].src] < INF) {
				if (d[e[j].des] > d[e[j].src] + e[j].cost) {
					d[e[j].des] = d[e[j].src] + e[j].cost;
					p[e[j].des] = e[j].src;
					flag = e[j].des;
				}
			}
		}
		cout << "giai doan " << i+1 << ": " << endl;
		for (k = 0; k < nv; k++) {
			cout << setw(7) << "d[" << k << "]" << " ";
		}
		cout << endl;
		for (k = 0; k < nv; k++) {
			cout << setw(9) << d[k] << " ";
		}
		cout << "\n" << endl;
		for (k = 0; k < nv; k++) {
			cout << setw(7) << "p[" << k << "]" << " ";
		}
		cout << endl;
		for (k = 0; k < nv; k++) {
			cout << setw(9) << p[k] << " ";
		}
		cout << endl;
		_getch();
	}
}

int fact(int n) {
	int i = 1, tmp = 1;
	if (n == 1 || n == 0) return 1;
	for (i = 1; i <= n; i++) {
		tmp *= i;
	}
	return tmp;
}
