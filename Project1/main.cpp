#include <graphics.h>
// 胜利
bool CheckWin(char c) {

	return false;
}
// 平局
bool CheckDraw() {

	return false;
}
void DrawBoard() {
	line(0, 0, 0, 300);
	line(100, 0, 100, 300);
}
void DrawPiece() {

}

void DrawTipText() {

}
int main() {
	initgraph(300, 300, 4);
	char[3][3] board;
	bool running = true;
	ExMessage msg;
	BeginBatchDraw();
	DrawBoard()
	while (running) {
		while (peekmessage(&msg)) {

		}
		if (CheckWin('X')) {
			MessageBox(GetHWnd(), _T("X 玩家获胜"), _T("游戏结束"), MB_OK);
			running = false;
		}else if (CheckWin('O')) {
			MessageBox(GetHWnd(), _T("O 玩家获胜"), _T("游戏结束"), MB_OK);
			running = false;
		}else if (CheckDraw()) {
			MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
			running = false;
		}
		cleardevice();
		DrawBoard();
		DrawTipText();                                                                                             
		FlushBatchDraw();

	}
	EndBatchDraw();
}