//#pragma once
//#include "Component.h"
//#include "IObserver.h"
//#include "Player.h"
//#include "TextureComponent.h"
//#include "TextComponent.h"
//
////todo: ask if this can be used as central comp?
//using namespace dae;
//class GameStatsDisplay : public Component, public IObserver<int> //todo: rename with component in name, forgot
//{
//public:
//	GameStatsDisplay();
//	//GameStatsDisplay(GameObject* pOwner, Player* pObservedPlayerComp, int startValue = 0);
//	~GameStatsDisplay();
//	void OnNotify(int stat) override;
//private:
//
//	void UpdateDisplay(int stat);
//	TextComponent* m_pTextComponent; //dont delete, not parent
//
//};
//
