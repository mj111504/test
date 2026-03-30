#pragma once
#include <iostream>
#include <string>

//캐릭터 기본 클래스 (메인 캐릭터용)
class Character {
protected:
    std::string name;

public:
    Character(std::string n);
    virtual ~Character(); // 다형성을 위한 가상 소멸자

    //순수 가상 함수 (자식 클래스에서 반드시 구현해야 함)
	virtual void speak(const std::string& dialogue) = 0; //정해진 위치에서 대사 출력
	virtual void updateAppearance(float erosion) = 0; //침식도에 따른 상태 변화
};  