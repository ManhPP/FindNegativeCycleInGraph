#include<iostream>
#include<vector>
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
int nv, ne;
const int INF = 1000000000;
vector<edge> e;
int **mt;
bool flag = true;
void setData(); //nhap du lieu tu ban phim
void dataFromFile(); //nhap du lieu tu file
void randomData(); //nhap du lieu ngau nhien
void displayData(); // hien thi du lieu
void solveFW(); //giai bai toan bang thuat toan floyd-Warshall
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
		cout << "\tCHUONG TRINH MO PHONG THUAT TOAN Floyd-Warshall\n";
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
		else if (ch == '6') solveFW();
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
	int i = 0, j = 0;
	edge tmp;
	cout << "nhap so dinh cua do thi: "; cin >> nv;
	cout << "\nnhap so canh cua do thi: "; cin >> ne;
	mt = new int *[nv];
	for (i = 0; i < nv; i++) {
		mt[i] = new int[nv];
	}
	for (i = 0; i < nv; i++) {
		for (j = 0; j < nv; j++) {
			if (i == j) mt[i][j] = 0;
			else mt[i][j] = INF;
		}
	}
	for (i = 0; i < ne; i++) {
		cout << "\nnhap canh thu " << i + 1 << endl;
		cout << "\ndinh nguon: "; cin >> tmp.src;
		cout << "\ndinh dich: "; cin >> tmp.des;
		cout << "\ntrong so: "; cin >> tmp.cost;
		e.push_back(tmp);
		mt[tmp.src][tmp.des] = tmp.cost;
	}
}

void dataFromFile() {
	//dong dau la so dinh, dong thu 2 la so canh, tiep theo la danh sach ke
	char tf[60];
	fstream file;
	int i = 0, j = 0;
	edge tmp;

	cout << "nhap ten file: ";
	fflush(stdin);
	cin.getline(tf, 60);
	file.open(tf);
	if (!file.is_open()) {
		cout << "mo file khong thanh cong" << endl;
		return;
	}
	file >> nv;
	file >> ne;
	mt = new int *[nv];
	for (i = 0; i < nv; i++) {
		mt[i] = new int[nv];
	}
	for (i = 0; i < nv; i++) {
		for (j = 0; j < nv; j++) {
			if (i == j) mt[i][j] = 0;
			else mt[i][j] = INF;
		}
	}
	for (i = 0; i < ne; i++) {
		file >> tmp.src;
		file >> tmp.des;
		file >> tmp.cost;
		e.push_back(tmp);
		mt[tmp.src][tmp.des] = tmp.cost;
	}
	file.close();
	cout << "nhap du lieu tu file vao thanh cong" << endl;
}

void randomData() {
	int i = 0, j = 0;
	edge tmpe;
	srand(time(NULL));
	cout << "nhap so dinh: "; cin >> nv;
	cout << "nhap so canh: "; cin >> ne;
	/*nv = 5 + rand() % 20;
	int tmp = fact(nv) / (fact(nv - 2) * 2);
	ne = rand() % (tmp - 1) + 1;*/
	mt = new int *[nv];
	for (i = 0; i < nv; i++) {
		mt[i] = new int[nv];
	}
	for (i = 0; i < nv; i++) {
		for (j = 0; j < nv; j++) {
			if (i == j) mt[i][j] = 0;
			else mt[i][j] = INF;
		}
	}
	i = 0;
	while (i<ne) {
		tmpe.src = rand() % (nv - 1);
		tmpe.des = rand() % (nv - 1);
		tmpe.cost = rand() % (RAND_MAX) - (RAND_MAX / 2);
		if (e.empty() && tmpe.src != tmpe.des) {
			e.push_back(tmpe);
			mt[tmpe.src][tmpe.des] = tmpe.cost;
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
				mt[tmpe.src][tmpe.des] = tmpe.cost;
				i++;
			}
		}
	}
	cout << "tao du lieu ngau nhien thanh cong" << endl;
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

void solveFW() {
	//double tim;
	//clock_t beg, fin;
	//beg = clock();
	if (e.empty()) cout << " chua co du lieu" << endl;
	else {
		int i = 0, j = 0, k = 0;
		for (i = 0; i < nv; i++) {
			for (j = 0; j < nv; j++) {
				for (k = 0; k < nv; k++) {
					if ((mt[j][i] + mt[i][k]) < mt[j][k] && mt[j][i] != INF && mt[i][k] != INF) {
						mt[j][k] = mt[j][i] + mt[i][k];
					}
				}
			}
		}
		flag = true;
		for (i = 0; i < nv; i++) {
			for (j = 0; j < nv; j++) {
				if (i != j)
					for (k = 0; k < nv; k++) {
						if (mt[i][k] < INF && mt[k][k] < 0 && mt[k][j] < INF) {
							mt[i][j] = -INF;
							flag = false;
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
	cout << "da ghi du lieu ra file thanh cong" << endl;
}

void writeResult() {
	int i = 0;
	char tf[30];
	ofstream file;
	cout << "nhap ten file: ";
	fflush(stdin);
	cin.getline(tf, 30);
	file.open(tf);
	if (flag == true) file << "do thi khong ton tai chu trinh am, luon ton tai duong di ngan nhat giua cac dinh." << endl;
	else {
		int i = 0, j = 0;
		file << "Khong ton tai duong di ngan nhat giua cac dinh:" << endl;
		for (i = 0; i < nv; i++) {
			for (j = i; j < nv; j++) {
				if (mt[i][j] == -INF) file << i << " va " << j << endl;
			}
		}
	}
	cout << "da ghi ket qua ra file thanh cong" << endl;
}

void displayResult() {
	if (flag == true) cout << "do thi khong ton tai chu trinh am, luon ton tai duong di ngan nhat giua cac dinh." << endl;
	else {
		int i = 0, j = 0;
		cout << "\nKhong ton tai duong di ngan nhat giua cac dinh:" << endl;
		for (i = 0; i < nv; i++) {
			for (j = i; j < nv; j++) {
				if (mt[i][j] == -INF) cout << i << " va " << j << endl;
			}
		}
	}
}

void viewInterResult() {
	cout << "ma tran khoang cach la: " << endl;
	int i = 0, j = 0, k = 0, m = 0, n = 0;
	for (i = 0; i < nv; i++) {
		for (j = 0; j < nv; j++) {
			for (k = 0; k < nv; k++) {
				if ((mt[j][i] + mt[i][k]) < mt[j][k] && mt[j][i] != INF && mt[i][k] != INF) {
					mt[j][k] = mt[j][i] + mt[i][k];
				}
			}
		}
		cout << "\ngiai doan " << i + 1 << ": " << endl;
		for (m = 0; m < nv; m++) {
			for (n = 0; n < nv; n++) {
				if(mt[m][n]!=INF) cout << setw(7) << mt[m][n];
				else cout << setw(7) << "INF";
			}
			cout << endl;
		}
		_getch();
	}
	cout << "\ntinh ma tran xac dinh cac dinh khong ton tai duong di nho nhat: " << endl;
	flag = true;
	for (i = 0; i < nv; i++) {
		for (j = 0; j < nv; j++) {
			if (i != j)
				for (k = 0; k < nv; k++) {
					if (mt[i][k] < INF && mt[k][k] < 0 && mt[k][j] < INF) {
						mt[i][j] = -INF;
						flag = false;
					}
				}
		}
		cout << "\ngiai doan " << i + 1 << ": " << endl;
		for (m = 0; m < nv; m++) {
			for (n = 0; n < nv; n++) {
				if (mt[m][n] == INF) cout << setw(7) << "INF";
				else if (mt[m][n] == -INF) cout << setw(7) << "-INF";
				else cout << setw(7) << mt[m][n];
			}
			cout << endl;
		}
		_getch();
	}
}

void resetData() {
	delete(mt);
	e.clear();
	cout << "da khoi phuc du lieu thanh cong" << endl;
}

int fact(int n) {
	int i = 1, tmp = 1;
	if (n == 1 || n == 0) return 1;
	for (i = 1; i <= n; i++) {
		tmp *= i;
	}
	return tmp;
}
