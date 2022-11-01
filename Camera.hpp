#pragma once
#include "Framework.hpp"

#include "Vector2.hpp"


// 1 gracz 2 algorytmy mo¿e byæ tak ¿eby siê ³¹czy³y 2 osie 2 rózne algorytmy.

namespace Camera {

	// This can be read from somewhere....
	const Vector2<int> screenSize{ 920 , 360 };


	// Detection square and the amount\max we move after are 2 different things.
	const SDL_Rect boundry { screenSize.x / 10, screenSize.y / 10, screenSize.x - (screenSize.x / 10), screenSize.y - (screenSize.y / 10) };
	//const SDL_Rect boundry = { 0, 0, 920, 360 };
	const Vector2<float> cameraBoundryMove{ boundry.w - boundry.x, boundry.h - boundry.y };

	struct Camera {
		Vector2<Sint32> position, size;
	};

	ErrorCode CameraMoveBoundry(Camera& camera, const Vector2<float>& actorPosition) {
		
		//printf("%f\n", actorPosiiton.x);

		//if (actorPosition.x > boundry.x && actorPosition.x < boundry.w) {
		//	printf("We're in the rectangle\n");
		//}
		//
		//if (actorPosition.x < boundry.x) {
		//	camera.position.x += cameraBoundryMove.x;
		//	printf("We're to the left of rectangle\n");
		//}
		//
		//if (actorPosition.x > boundry.w) {
		//	camera.position.x -= cameraBoundryMove.x;
		//	printf("We're to the right of rectangle\n");
		//}
		
		if (actorPosition.y < boundry.y) {
			camera.position.y += cameraBoundryMove.y;
			printf("We're up of rectangle\n");
		}
		
		if (actorPosition.y > boundry.h) {
			camera.position.y -= cameraBoundryMove.y;
			printf("We're down of rectangle\n");
		}

		return success;
	}

	ErrorCode CameraFollowBoundry(Camera& camera, Vector2<float>& actorPosition, const float& actorSize, const float& speed) {

		//printf("%f\n", actorPosiiton.x);

		//if (actorPosition.x > boundry.x && actorPosition.x < boundry.w) {
		//	printf("We're in the rectangle\n");
		//}

		if (actorPosition.x - (actorSize / 2) < boundry.x) {
			camera.position.x += speed;
			printf("We're to the left of rectangle\n");
		}

		if (actorPosition.x + (actorSize / 2) > boundry.w) {
			camera.position.x -= speed;
			printf("We're to the right of rectangle\n");
		}

		//if (actorPosition.y - (actorSize / 2) < boundry.y) {
		//	camera.position.y += speed;
		//	printf("We're up of rectangle\n");
		//}
		//
		//if (actorPosition.y + (actorSize / 2) > boundry.h) {
		//	camera.position.y -= speed;
		//	printf("We're down of rectangle\n");
		//}

		return success;
	}

	//ErrorCode LogicUpdate(const float& deltaTime, Camera& camera, const Uint8* const keyboard) {
	//
	//	if (keyboard[SDL_SCANCODE_W]) camera.position.y -= 1;
	//	if (keyboard[SDL_SCANCODE_D]) camera.position.x += 1;
	//	if (keyboard[SDL_SCANCODE_S]) camera.position.y += 1;
	//	if (keyboard[SDL_SCANCODE_A]) camera.position.x -= 1;
	//
	//
	//	return success;
	//}

}


