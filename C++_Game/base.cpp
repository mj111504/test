#include <iostream>
#include <string>
#include <cstdlib> 
#include <thread> 
#include <chrono> 
#include <iomanip>
#include "Character.h"

using namespace std;


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






//용의자 클래스
class Suspect : public Character {
public:
    Suspect() : Character("용의자 X") {}

    void speak(const string& dialogue) override {
        cout << "[좌측 화면 - " << name << "] : " << dialogue << endl;
    }

    void updateAppearance(float erosion) override {
        // 침식도에 따른 좌측 게임 이미지/텍스트 변화 로직
    }
};

//여자친구 클래스
class Girlfriend : public Character {
public:
    Girlfriend() : Character("여자친구") {}

    void speak(const string& dialogue) override {
        cout << "[우측 화면 - " << name << "] : " << dialogue << endl;
    }

    void updateAppearance(float erosion) override {
        // 침식도에 따른 여자 친구 이미지/텍스트 변화 로직
    }
};


//게임 매니저 클래스 (전체 시퀀스 제어)
class GameManager {
private:
    float erosion;           // 침식도
    int interrogationCount;  // 취조 횟수
	Character* suspect; // 용의자 캐릭터 포인터
	Character* girlfriend; // 여자친구 캐릭터 포인터
	


public:
	// 생성자에서 캐릭터 객체 초기화
    GameManager() : erosion(0.0f), interrogationCount(0) {
        suspect = new Suspect();
        girlfriend = new Girlfriend();
        
    }
	// 소멸자에서 캐릭터 객체 메모리 해제
    ~GameManager() {
        delete suspect;
		delete girlfriend;
    }

    // 침식도 증가 로직 (한 번 올라간 수치는 내려가지 않음) 
    void increaseErosion(float amount) {
        erosion += amount;
        if (erosion >= 100.0f) erosion = 100.0f; // 최대치 고정

        cout << "\n[시스템] Sync Error: " << erosion << "%..." << endl;
    }

    // 엔딩 판별 로직 
    void checkEnding() {
        cout << "\n===================================" << endl;
        if (erosion < 30.0f) {
            cout << ">> 해피 엔딩: 연결 해제 성공" << endl;
        }
        else if (erosion < 100.0f) {
            cout << ">> 노멀 엔딩: 불완전한 동기화" << endl;
        }
        else {
            cout << ">> 배드 엔딩: Connection Established... 게임 오버" << endl;
        }
    }

    // 메인 게임 루프
    void runGameLoop() {
        cout << "게임을 시작합니다...\n" << endl;

        // 총 10회의 취조 루프
        while (interrogationCount < 10 && erosion < 100.0f) {
            interrogationCount++;
            cout << "\n--- [취조 " << interrogationCount << " 회차] ---" << endl;

            // 대사 출력 예시 (기획안 오프닝 참조)
			renderFrame(interrogationCount, erosion, "왜 그랬어?", "왜 그랬어?");
			
            this_thread::sleep_for(chrono::seconds(1));

            // TODO: 플레이어 입력(cin) 및 선택지 분기 구현부
            // 임시로 매 턴마다 침식도가 무작위 혹은 선택에 의해 오르는 상황 가정
            increaseErosion(1.0f);
        }

        // 루프 종료 후 엔딩 분기
        checkEnding();
    }
};

int main() {
    GameManager game;
    game.runGameLoop();

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
