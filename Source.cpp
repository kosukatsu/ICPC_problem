#include<iostream>
#include<vector>
#include<cmath>
#define PROBLEM2_COLS 5
void Problem1_2007();
int calcTax(int x, int y, int s);
void Problem1_2014();
void Problem2_2014();
void Problem3_2014();
class problem3_building {
private:
	int x_left, x_right, height;
public:
	problem3_building();
	problem3_building(int x_left, int x_right, int height);
	int getxleft();
	int getxright();
	int getheight();
};
problem3_building::problem3_building() {
	x_left = 0;
	x_right = 0;
	height = 0;
}
problem3_building::problem3_building(int x_left, int x_right, int height) {
	this->x_left = x_left;
	this->x_right = x_right;
	this->height = height;
}
int problem3_building::getxleft() {
	return x_left;
}
int problem3_building::getxright() {
	return x_right;
}
int problem3_building::getheight() {
	return height;
}
class problem3_Sun {
private:
	int x, r;
	double y;
	double getY(double x);
	
public:
	problem3_Sun();
	problem3_Sun(int r);
	void addY(double dy);
	double getY() { return this->y; }
	int getR() {return this->r;}
	double getX(double y);
	int isBlockOffSunLight(problem3_building b);
	int isBlockOffSunLight(problem3_building b,double x);
};
problem3_Sun::problem3_Sun() {
	x = 0;
	r = 0;
	y = 0.0;
}
problem3_Sun::problem3_Sun(int r) {
	this->x = 0;
	this->r = r;
	this->y = (double)-r;
}
void problem3_Sun::addY(double dy) {
	y += dy;
}
double problem3_Sun::getY(double x) {
	return std::sqrt((double)r*r - x*x) + y;
}
double problem3_Sun::getX(double y) {
	return std::sqrt((double)r*r-(y-this->y)*(y-this->y));
}
int problem3_Sun::isBlockOffSunLight(problem3_building b) {
	if (getY((double)b.getxleft()) > b.getheight())
		return 0;
	if (getY((double)b.getxright()) > b.getheight())
		return 0;
	if (b.getxleft() < 0 && b.getxright()>0 && r + y > b.getheight())
		return 0;
	return 1;
}
int problem3_Sun::isBlockOffSunLight(problem3_building b, double x) {
	if (b.getxleft() <= x && b.getxright() >= x&& b.getheight() >= getY(x))
		return 1;
	else
		return 0;
}
int main() {
	//Problem1_2007();
	//Problem1_2014();
	//Problem2_2014();
	Problem3_2014();
	return 0;
}
void Problem1_2007() {
	int answer[20],n,m;
	int sum, max, min,i,j;
	for (i=0,std::cin >> n; n != 0; std::cin >> n,++i) {
		sum = 0;
		for (j = 0; j < n; ++j) {
			std::cin >> m;
			sum += m;
			if (j == 0) {
				max = m;
				min = m;
			}
			else if (max < m) {
				max = m;
			}
			else if (min > m) {
				min = m;
			}
		}
		sum -= max + min;
		answer[i] = sum / (n - 2);
	}
	for (j = 0; j < i; ++j) {
		std::cout << answer[j] << std::endl;
	}
	return;
}
int calcTax(int x, int y, int s){
	int max = 0;
	int preChangedTaxIncludedPlace,n,m;
	for (int i = 1; i <= s/2; ++i) {
		preChangedTaxIncludedPlace = s - (int)((double)i*(100+x)/100);
		for (int j = 1; (n=(int)((double)j*(100 + x) / 100)) <= preChangedTaxIncludedPlace; ++j) {
			if (n != preChangedTaxIncludedPlace)
				continue;
			m = (int)((double)i*(100 + y) / 100) + (int)((double)j*(100 + y) / 100);
			if (max < m) {
				max = m;
			}
		}
	}
	return max;
}
void Problem1_2014() {
	int x, y, z;
	std::vector<int> answer;
	for (std::cin >> x >> y >> z; !(x== 0 && y==0 && z==0); std::cin >> x >> y >> z) {
		answer.push_back(calcTax(x, y, z));
	}
	for (auto itr = answer.begin(); itr != answer.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
	return;
}
void Problem2_2014() {
	std::vector<int> answer;
	int h;
	int **puzzle;
	int score = 0;
	int isfinish = false;
	int start, end;
	int temp;
	for (std::cin >> h; h != 0; std::cin >> h) {
		
		/*�p�Y���f�[�^���͂���э쐬*/
		puzzle = new int*[h];
		for (int i = 0; i < h; ++i) {
			puzzle[i] = new int[PROBLEM2_COLS];
			for (int j = 0; j < PROBLEM2_COLS; ++j) {
				std::cin >> puzzle[i][j];
			}
		}

		score = 0;
		isfinish = false;
		while (1) {
			isfinish = true;
			
			//�p�Y������
			for (int i = 0; i < h; ++i) {
				end = 0;
				for (int j = 0; j < PROBLEM2_COLS;++j) {
					start = j;
					if (puzzle[i][j] == 0) {
						++j;
						continue;
					}
					while (j < PROBLEM2_COLS-1 && puzzle[i][j] == puzzle[i][1 + j]) {
						end = j+1;
						++j;
					}
					if (end - start >= 2) {
						isfinish = false;
						score += (end - start + 1)*puzzle[i][start];

						for (int k = start; k <= end; ++k)
							puzzle[i][k] = 0;
					}

				}
			}
			if (isfinish)
				break;
			//���Ƃ�
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j <h; ++j) {
					if (puzzle[j][i] == 0) {
						for (int k = j; k > 0; --k) {
							temp = puzzle[k][i];
							puzzle[k][i] = puzzle[k - 1][i];
							puzzle[k - 1][i] = temp;
						}
					}
				}
			}
			/*
			for (int i = 0; i < h; ++i) {
				for (int j = 0; j < PROBLEM2_COLS; ++j) {
					std::cout << ' ' << puzzle[i][j];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			*/
		}
		answer.push_back(score);
		
		for (int i = 0; i < h; ++i) {
			delete[] puzzle[i];
		}
		delete[] puzzle;
	}
	for (auto itr = answer.begin(); itr != answer.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
	return;
}
void Problem3_2014() {//�~
	int r, buildNum;
	int xr, xl, h;
	double t;
	double x;
	problem3_building *build;
	problem3_Sun sun;
	int isblocksunlight;
	std::vector<double> answer;
	const int vy = 1;
	const double dt = 0.001;
	for (std::cin >> r >> buildNum; !(r == 0 && buildNum == 0); std::cin >> r >> buildNum) {
		build = new problem3_building[buildNum];
		sun =problem3_Sun(r);
		isblocksunlight = true;
		//�r���̏�����
		for (int i = 0; i < buildNum; ++i) {
			std::cin >> xl >> xr >> h;
			build[i] = problem3_building(xl, xr, h);
		}
		for (t = 0.0;; t += dt) {
			sun.addY((double)vy*dt);
			for (double h = sun.getY() + sun.getR();h>0; h -= vy*dt) {
				x = sun.getX(h);
				isblocksunlight = true;
				for (int i = 0; i < buildNum; ++i) {
					if (!(sun.isBlockOffSunLight(build[i], x)&& sun.isBlockOffSunLight(build[i], -x))) {
						isblocksunlight = false;
						break;
					}
				}
				if (!isblocksunlight){
					break;
				}
			}
			if (!isblocksunlight) {
				break;
			}
		}
		answer.push_back(t);
	}
	for (auto itr = answer.begin(); itr != answer.end(); ++itr)
		std::cout << *itr << std::endl;
	return;
}