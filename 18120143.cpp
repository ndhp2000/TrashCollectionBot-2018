#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <cstdlib>
#define oo 1000000000
struct Tpoint {
	int x, y;
};
using namespace std;
int a[20][20];
int M, N, K;
int S, coMask;
Tpoint Me, You;
string st;
void Doc() {
	cin >> M >> N >> K;
	cin >> Me.x >> Me.y >> You.x >> You.y;
	cin >> S >> coMask;
	for (int i = 1; i <= M; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cin >> st;
			if (st == "W") a[i][j] = -1 * ((coMask ? 0 : 1)); // co mat na xoa het vat can
			else
				if (st == "M") a[i][j] = -2;
				else a[i][j] = stoi(st);
		}
	}
}
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int d[20][20][20][20], w[20][20][20][20],d2[20][20][20][20],w2[20][20][20][20];
Tpoint trace[20][20][20][20];
int Count;
void BFS(Tpoint s) {
	Tpoint u, v;
	// khoi tao mang khoang cach
	for (int x = 1; x <= M; ++x)
		for (int y = 1; y <= N; ++y)
		{
			d[s.x][s.y][x][y] = oo;
			w[s.x][s.y][x][y] = -1;
		}
	u = s;

	if (a[u.x][u.y] == -1) return;

	queue <Tpoint> q;
	q.push(u);
	d[s.x][s.y][u.x][u.y] = 0; // khoang cac dau tien = 0
	w[s.x][s.y][u.x][u.y] = 0;

	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i)
		{
			v.x = u.x + dx[i];
			v.y = u.y + dy[i];
			if (v.x >= 1 && v.y >= 1 && v.x <= M && v.y <= N)  // ben trong man hinh
				if ((a[v.x][v.y] != -1)) // co canh noi
					if (d[s.x][s.y][v.x][v.y] == oo)
					{
						d[s.x][s.y][v.x][v.y] = d[s.x][s.y][u.x][u.y] + 1;
						w[s.x][s.y][v.x][v.y] = w[s.x][s.y][u.x][u.y] + a[v.x][v.y] * ((a[v.x][v.y] == -2) ? 0 : 1);
						trace[s.x][s.y][v.x][v.y] = u;
						q.push(v);
					}
					else if (d[s.x][s.y][v.x][v.y] == d[s.x][s.y][u.x][u.y] + 1)
					{
						if (w[s.x][s.y][u.x][u.y] + a[v.x][v.y] * ((a[v.x][v.y] == -2) ? 0 : 1) > w[s.x][s.y][v.x][v.y])
						{
							w[s.x][s.y][v.x][v.y] = w[s.x][s.y][u.x][u.y] + a[v.x][v.y] * ((a[v.x][v.y] == -2) ? 0 : 1);
							trace[s.x][s.y][v.x][v.y] = u;
						}
					}
		}
	}
}

void BFS_2(Tpoint s, int d[20][20][20][20], int w[20][20][20][20])
{
Tpoint u, v;
// khoi tao mang khoang cach
for (int x = 1; x <= M; ++x)
for (int y = 1; y <= N; ++y)
{
	d[s.x][s.y][x][y] = oo;
	w[s.x][s.y][x][y] = -1;
}
u = s;
queue <Tpoint> q;
q.push(u);
d[s.x][s.y][u.x][u.y] = 0; // khoang cac dau tien = 0
w[s.x][s.y][u.x][u.y] = 0;

while (!q.empty()) {
	u = q.front();
	q.pop();
	for (int i = 0; i < 4; ++i)
	{
		v.x = u.x + dx[i];
		v.y = u.y + dy[i];
		if (v.x >= 1 && v.y >= 1 && v.x <= M && v.y <= N)  // ben trong man hinh
			//if ((a[v.x][v.y] != -1)) // co canh noi
				if (d[s.x][s.y][v.x][v.y] == oo)
				{
					d[s.x][s.y][v.x][v.y] = d[s.x][s.y][u.x][u.y] + 1;
					w[s.x][s.y][v.x][v.y] = w[s.x][s.y][u.x][u.y] + a[v.x][v.y] * min(1,max(0,a[v.x][v.y]));
					q.push(v);
				}
				else if (d[s.x][s.y][v.x][v.y] == d[s.x][s.y][u.x][u.y] + 1)
				{
					if (w[s.x][s.y][u.x][u.y] + a[v.x][v.y] * min(1, max(0, a[v.x][v.y])) > w[s.x][s.y][v.x][v.y])
					{
						w[s.x][s.y][v.x][v.y] = w[s.x][s.y][u.x][u.y] + a[v.x][v.y] * min(1, max(0, a[v.x][v.y]));
					}
				}
	}
}
}

int Sum = 0;
int Avg;

void Init() {
	for (int x = 1; x <= M; ++x)
		for (int y = 1; y <= N; ++y)
		{
			if (a[x][y] >= 0) Sum += a[x][y];
			Tpoint temp;
			temp.x = x;
			temp.y = y;
			BFS(temp);
			BFS_2(temp, d2, w2);
		}
	Avg = ceil(float(Sum)*0.08);
}

//// Init is oke
bool Check(int x, int y) // Check xem co di lay duoc mat na hay k <3 
{
	for (int u =1;u<=M;++u)
		for (int v= 0; v <= N; ++v)
		{
			if ((a[u][v] == -2 && d[x][y][u][v]<=K*ceil(0.75))) return 1;
		}
	return 0;
}
void Xuli1()
{
	// Tim o trong tot nhat:
	int x, y, bestx, besty;
	double bestavg0 = 0;
	for (int x = 1; x<=M;++x)
		for (int y = 1; y <= N; ++y)
			if (a[x][y]==0 && Check(x,y)) // dat duoc ne
		{
			double temp = 0;
			for (int u = 1; u <= M; ++u)
				for (int v = 1; v <= N; ++v)
					if (d[x][y][u][v] <= ceil(K*0.8))
					{
						temp = max(temp, pow(double(w[x][y][u][v]),1.7) / (1.5*d[x][y][u][v]));
					}
			if (temp > bestavg0)
			{
				bestavg0 = temp;
				bestx = x;
				besty = y;
			}
		}
	// bestx besty bestavg0 la vi tri dat de an khi chua them lay mask
	// Danh gia mat na 1
	int bestu = 0, bestv = 0, bestd = oo, bestw = -1;
	bool Found = 0;
	double bestavg=0;
	for (x = 1; x <= M; ++x)
	{
		for (y = 1; y <= N; ++y)
		{
			if (a[x][y] == -2) Found = 1;
			if (Found) break;
		}
		if (Found) break;
	}

	for (int u = 1; u <= M; ++u)
		for (int v = 1; v <= N; ++v)
			if (a[u][v] == 0)
			{
				if (d[x][y][u][v] < bestd)
				{
					bestu = u;
					bestv = v;
					bestd = d[x][y][u][v];
					bestw = w[x][y][u][v];
				}
				else if ((d[x][y][u][v] == bestd) && (w[x][y][u][v] > bestw))
				{
					bestu = u;
					bestv = v;
					bestd = d[x][y][u][v];
					bestw = w[x][y][u][v];
				}
			}
	bestavg = 0;
	for (int u =1; u<=M;++u)
		for (int v = 1; v <= N; ++v)
			if (d2[x][y][u][v] < ceil(K*0.8))
			{
				bestavg = max(bestavg, pow(double(w2[x][y][u][v]),1.7) / (1.5*d2[x][y][u][v]));
			}
	
	/////////////////////////////////////
	Found = 0;
	for (x = M; x >= 1; --x)
	{
		for (y = N; y >= 1; --y)
		{
			if (a[x][y] == -2) Found = 1;
			if (Found) break;
		}
		if (Found) break;
	}
	int bestu2 = 0, bestv2 = 0, bestd2 = oo, bestw2 = -1;
	for (int u = 1; u <= M; ++u)
		for (int v = 1; v <= N; ++v)
			if (a[u][v] == 0)
			{
				if (d[x][y][u][v] < bestd2)
				{
					bestu2 = u;
					bestv2 = v;
					bestd2 = d[x][y][u][v];
					bestw2 = w[x][y][u][v];
				}
				else if ((d[x][y][u][v] == bestd2) && (w[x][y][u][v] > bestw2))
				{
					bestu2 = u;
					bestv2 = v;
					bestd2 = d[x][y][u][v];
					bestw2 = w[x][y][u][v];
				}
			}
	double bestavg2 = 0;
	for (int u = 1; u <= M; ++u)
		for (int v = 1; v <= N; ++v)
			if (d2[x][y][u][v] < ceil(K*0.8))
			{
				bestavg2 = max(bestavg2, pow(double(w2[x][y][u][v]),1.7) / (1.5*d2[x][y][u][v]));
			}

	double Score1 = pow((double)bestw,1.9) / double(bestd) + bestavg;
	double Score2 = pow((double)bestw,1.9) / double(bestd2) + bestavg2;
	double Score = Score1;
	// co mask tot nhat r ne.
	if (Score2 > Score1) { bestu = bestu2; bestv = bestv2; bestw = bestw2; bestd = bestd2; bestavg = bestavg2; Score = Score2; }
	if (bestavg0 > Score) {
		bestu = bestx;
		bestv = besty;
	}
	cout << bestu << " " << bestv;
}
void Xuli2()
{
	if (coMask == 0)
	{
		int x, y, Maskx, Masky;
		// tim mat na tot nhat
		// Tim mat na 1
		bool Found = 0;
		double bestavg = 0;
		for (x = 1; x <= M; ++x)
		{
			for (y = 1; y <= N; ++y)
			{
				if (a[x][y] == -2) Found = 1;
				if (Found) break;
			}
			if (Found) break;
		}

		Maskx = x; Masky = y;
		// x, y la toa do mat na
		bestavg = 0;
		for (int u = 1; u <= M; ++u)
			for (int v = 1; v <= N; ++v)
				if (d2[x][y][u][v] <= ceil(0.8*K))
				{
					bestavg = max(bestavg, pow(double(w2[x][y][u][v]),1.7) / (1.5*d2[x][y][u][v]));
				}
		double Score1 = (pow(double(w[Me.x][Me.y][x][y]),1.9) / (d[Me.x][Me.y][x][y])) + bestavg;

		////////////////
		Found = 0;
		for (x = M; x >= 1; --x)
		{
			for (y = N; y >= 1; --y)
			{
				if (a[x][y] == -2) Found = 1;
				if (Found) break;
			}
			if (Found) break;
		}

		double bestavg2 = 0;
		for (int u = 1; u <= M; ++u)
			for (int v = 1; v <= N; ++v)
				if (d2[x][y][u][v] < ceil(0.8*K))
				{
					bestavg2 = max(bestavg2, pow(double(w2[x][y][u][v]),1.7) / (1.5*d2[x][y][u][v]));
				}
		double Score2 = (pow(double(w[Me.x][Me.y][x][y]),1.9) / (d[Me.x][Me.y][x][y])) + bestavg2;

		if (Score2 > Score1)
		{
			Score1 = Score2;
			Maskx = x;
			Masky = y;
		}

		// Tim duong di tot nhat duong that nha mn <3 
		x = Me.x; y = Me.y;
		int bestu = 0, bestv = 0;
		double bestd = -100; // duong di tot nhat

		for (int u = 1; u <= M; ++u)
			for (int v = 1; v <= N; ++v)
				if (d[x][y][u][v] <= ceil(K*0.8))
				{
					if (pow(double(w[x][y][u][v]),1.7) / (1.5*double(d[x][y][u][v])) > bestd)
					{
						bestu = u;
						bestv = v;
						bestd = (pow(double(w[x][y][u][v]),1.7) / (1.5*double(d[x][y][u][v])));
					}
				}

		// Kiem tra giua viec di lay mask voi di tiep no nhu the nao ne
		
		if (Score1>bestd)
		{
			bestu = Maskx;
			bestv = Masky;
		}

		Tpoint Res = trace[bestu][bestv][x][y];
		cout << Res.x << " " << Res.y;
	}
	else
	{
		int x = Me.x, y = Me.y;
		int bestu = 0, bestv = 0;
		float bestd = -100;
	
		for (int u = 1; u <= M; ++u)
			for (int v = 1; v <= N; ++v)
				if (d[x][y][u][v] <= ceil(K*0.9))
				{
					if (pow(float(w[x][y][u][v]),1.7) / float(d[x][y][u][v]) > bestd)
					{
						bestu = u;
						bestv = v;
						bestd = pow(float(w[x][y][u][v]),1.7) / float(d[x][y][u][v]);
					}
				}
		Tpoint Res = trace[bestu][bestv][x][y];
		cout << Res.x << " " << Res.y;
	}
}
int main() {
	freopen("MAP.INP", "r", stdin);
	freopen("MOVE.OUT", "w", stdout);
	Doc();
	Init();
	if (Me.x == Me.y && Me.y == You.x && You.x == You.y && You.y == 0) Xuli1();  else Xuli2();
	return 0;
}