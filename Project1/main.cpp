#include <graphics.h>
// ʤ��
bool CheckWin(char c) {

	return false;
}
// ƽ��
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
			MessageBox(GetHWnd(), _T("X ��һ�ʤ"), _T("��Ϸ����"), MB_OK);
			running = false;
		}else if (CheckWin('O')) {
			MessageBox(GetHWnd(), _T("O ��һ�ʤ"), _T("��Ϸ����"), MB_OK);
			running = false;
		}else if (CheckDraw()) {
			MessageBox(GetHWnd(), _T("ƽ��"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		cleardevice();
		DrawBoard();
		DrawTipText();                                                                                             
		FlushBatchDraw();

	}
	EndBatchDraw();
}