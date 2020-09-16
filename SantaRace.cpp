#include <bangtal.h>

using namespace bangtal;

int main() {

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	//장면 생성
	auto scene = Scene::create("산타레이스", "Images/background.png");

	auto santa = Object::create("Images/santa.png", scene, 0, 500);
	auto santaX = 0;

	auto startButton = Object::create("Images/start.png", scene, 590, 70);
	auto endButton = Object::create("Images/end.png", scene, 590, 20);
	auto playButton = Object::create("Images/play.png", scene, 610, 30, false);

	auto timer = Timer::create(10.f);
	showTimer(timer);
	//타이머가 알아서 종료되면 0이면 이벤트가 발생할때
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("선물 배달 실패 ㅠㅠ");

		playButton->hide();
		startButton->setImage("Images/restart.png");
		startButton->show();
		endButton->show();

		return 0;
		});


	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();
		playButton->show();
		santaX = 0;
		santa->locate(scene, santaX, 500);
		timer->set(10.f);
		timer->start();

		return 0;
		});
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return 0;
		});

	playButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//산타를 x축으로 30만큼 이동하고, 산타의 값을 저장해놓아야 이동가능.
		santaX = santaX + 30;
		santa->locate(scene, santaX, 500);

		if (santaX > 1280) {
			showMessage("선물 배달 성공~~!");
			timer->stop();

			playButton->hide();
			startButton->setImage("Images/restart.png");
			startButton->show();
			endButton->show();
		}

		return 0;
		});


	//게임시작
	startGame(scene);
	return 0;
}
