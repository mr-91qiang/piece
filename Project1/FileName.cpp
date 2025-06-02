#include <graphics.h>

#include <string>

#include <chrono>
#include <thread>
#include "FileName.h"
constexpr int BOARD_SIZE = 3;
constexpr int CELL_SIZE = 100;
constexpr int BOARD_OFFSET = 100;
constexpr int WINDOW_SIZE = 500;

char board[BOARD_SIZE][BOARD_SIZE];

// 胜利
bool CheckWin(char c) {
	// 检查棋盘上是否有横竖斜的三个棋子相连
	for (int i = 0; i < 3; i++) {
		// 检查行
		if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return true;
		// 检查列
		if (board[0][i] == c && board[1][i] == c && board[2][i] == c) return true;
	}
	// 检查斜线
	if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;
	if (board[2][0] == c && board[1][1] == c && board[0][2] == c) return true;
	return false;
}
// 平局
bool CheckDraw() {
	// 检查是否放满
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '-') return false; // 如果有空格，返回 false
		}
	}
	return true;
}

// 画棋盘
void DrawBoard() {
	setlinecolor(RGB(101, 67, 33));   // 棋盘线条颜色 (深棕)
	setfillcolor(RGB(222, 184, 135));  // 棋盘背景色 (米黄)
	fillrectangle(0, 0, 600, 600);     // 先填充背景
	// 渐变背景
	for (int y = 100; y <= 400; y++) {
		int r = 150 + y / 8;
		int g = 200 - y / 8;
		int b = 150 + y / 12;
		setlinecolor(RGB(r, g, b));
		line(100, y, 400, y);
	}

	// 装饰性网格线
	setlinecolor(RGB(255, 255, 255));
	for (int i = 100; i <= 400; i += 100) {
		line(100, i, 400, i);
		line(i, 100, i, 400);
	}
}
void initBoard() {
	//遍历数组
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '-'; // 初始化棋盘为空
		}
	}
}
void DrawPiece() {
	// 使用宽字符字符串
	std::wstring circle = L"○";  // 空心圆
	std::wstring cross = L"×";   // 乘号

	// 设置字体样式（高度50，宽度自动）
	settextstyle(50, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// 计算当前格子的中心坐标
			int centerX = j * 100 + 150;  // 100是格子宽度，150是起始偏移
			int centerY = i * 100 + 150;

			// 设置文本绘制区域（以中心点向四周扩展）
			RECT r = {
				centerX - 40,  // left
				centerY - 40,  // top
				centerX + 40,  // right
				centerY + 40   // bottom
			};

			if (board[i][j] == 'X') {
				setcolor(RED);
				drawtext(cross.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else if (board[i][j] == 'O') {
				setcolor(BLUE);
				drawtext(circle.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
} 
void DrawTipText(char c) {
	RECT r = { 0, 0, 500,100 };
	TCHAR text[32];

	swprintf_s(text, 32, L"轮到玩家 %c", c); // 安全版本，第二个参数是缓冲区大小
	if (c == 'X') {
		setcolor(RED);
	}
	else {
		setcolor(BLUE);
	}
	drawtext(text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
int main() {
	initgraph(500, 500, 4); // 创建一个 500x500 的窗口，4 表示不显示控制台窗口
	bool running = true;
	ExMessage msg;
	BeginBatchDraw();
	initBoard();
	setbkmode(OPAQUE);
	// 当前玩家
	char pre = 'X'; // 假设 X 先手
	while (running) {
		DWORD start = GetTickCount();
		while (peekmessage(&msg, EX_MOUSE)) {
			if (!running){
				break;
			}
			// 放置棋子
			// 根据点击事件确定棋子位置
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x < 100 || msg.x > 400 || msg.y < 100 || msg.y > 400) continue; // 点击区域限制
				int x = (msg.x - 100) / 100;
				int y = (msg.y - 100) / 100;
				if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[y][x] == '-') {
					board[y][x] = pre; // 假设当前玩家是 X
				}
				if (pre == 'X'){
					pre = 'O';
				}else{
					pre = 'X';
				}
			}
			cleardevice();
			setcolor(WHITE);
			DrawBoard();
			DrawPiece();
			DrawTipText(pre);
			FlushBatchDraw();
			if (CheckWin('X')) {
				MessageBox(GetHWnd(), _T("X 玩家获胜"), _T("游戏结束"), MB_OK);
				running = false;
			}
			else if (CheckWin('O')) {
				MessageBox(GetHWnd(), _T("O 玩家获胜"), _T("游戏结束"), MB_OK);
				running = false;
			}
			else if (CheckDraw()) {
				MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
				running = false;
			}
			DWORD end = GetTickCount();
			DWORD elapsed = (end >= start) ? (end - start) : (UINT_MAX - start + end);
			if (1000 / 60 > elapsed) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60 - elapsed));
			}
		}
	}
	EndBatchDraw();
	closegraph(); // 关闭图形窗口
	return 0;
}