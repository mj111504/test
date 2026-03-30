#include "Character.h"

Character::Character(std::string n) : name(n) {} //생성자, 이름 초기화

Character::~Character() {}; //가상 소멸자, 다형성을 위해 필요