/*#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// 특정 너비(width) 안에서 텍스트를 중앙에 위치시키는 함수
void printCenterInBox(string text, int width) {
    int len = text.length();
    // ※ 한글이 포함된 경우 실제 출력 길이를 보정해야 할 수도 있습니다.

    int space = (width - len) / 2;
    if (space > 0) cout << string(space, ' '); // 왼쪽 공백 채우기
    cout << text;
    if (space > 0) cout << string(width - len - space, ' '); // 오른쪽 공백 채우기
}


void renderFrame(int turn, float erosion, string gameLine, string realLine) {
    // 1. 이전 화면 지우기
    system("cls");

    int totalWidth = 101;
    int halfWidth = totalWidth / 2;

    string leftTop = "[" + to_string(turn) + "번째 취조]";
    string rightTop = "[Sync Error : " + to_string(erosion).substr(0, 4) + "%]";

    cout << setfill('=') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');

    // 1단계: 왼쪽 절반(45칸) 안에서 중앙 정렬
    printCenterInBox(leftTop, halfWidth - 1);

    cout << "|"; // 중앙 구분선

    // 2단계: 오른쪽 절반(45칸) 안에서 중앙 정렬
    printCenterInBox(rightTop, halfWidth);
    cout << endl;

    cout << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    // 3. 대사 영역
    // 좌측 [게임] 대사와 우측 [현실] 대사를 나란히 출력
    // setw를 써서 중간의 '|' 선 위치를 고정하면 대사 길이에 상관없이 틀이 유지됩니다.
    cout << left << setw(totalWidth / 2 - 1) << ("[게임] " + gameLine) << "|";
    cout << "[현실] " << realLine << endl;

    // 4. 세로 구분선 (분위기용)
    for (int i = 0; i < 10; i++) {
        cout << setw(totalWidth / 2 - 1) << "" << "|" << endl;
    }
    // 5. UI 하단 영역
    cout << setfill('=') << setw(totalWidth) << "" << endl;
    cout << "[시스템 메시지]" << endl;
    cout << "시스템 메시지 예시입니다." << endl;
    cout << setfill('-') << setw(totalWidth) << "" << endl;
    cout << "[선택지]" << endl;
    cout << "1. 선택지1 \n2. 선택지2" << endl;
    cout << setfill('-') << setw(totalWidth) << "" << endl;
    cout << "입력: ";
    int selection;
    cin >> selection;
}

int main() {
    int turn = 10;
    float erosion = 12.34;
    renderFrame(turn, erosion, "게임 대사 예시입니다.", "현실 대사 예시입니다.");
    return 0;
}*/