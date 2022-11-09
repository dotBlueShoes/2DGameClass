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
	
	

	struct Camera {
		Vector2<Sint32> position;
		Vector2<Uint32> size;
		//Vector2<Uint32> zoomPoint;
		float zoom = 1;
	};

	// We're simply coverting range 1-0 where 0.5 is x2 zoom into 0-half_screen to propery move.
	constexpr const Vector2<float> GetCameraScaleMovePosition(const Camera& camera) {
		const float zoomMin = 1.0f, zoomMax = 0.0f, zoomRange(zoomMax - zoomMin), screenSizeMin = 0.0f;
		const Vector2<float> screenRange { (screenSize.x / 2) - screenSizeMin, (screenSize.y / 2) - screenSizeMin };
		return Vector2<float> { 
			(((camera.zoom - zoomMin)* screenRange.x) / zoomRange) + screenSizeMin,
			(((camera.zoom - zoomMin)* screenRange.y) / zoomRange) + screenSizeMin
		};

		// const float zoomMin = 1.0f, zoomMax = 0.0f, zoomRange(zoomMax - zoomMin), screenSizeMin = 0.0f;
		// const float screenXRange((screenSize.x / 2) - 0.0f);
		// const float screenYRange((screenSize.y / 2) - 0.0f);
		// const float newCameraPositionX((((camera.zoom - 1) * screenXRange) / zoomRange) + 0.0f);
		// const float newCameraPositionY((((camera.zoom - 1) * screenYRange) / zoomRange) + 0.0f);
		// return Vector2<float> { newCameraPositionX, newCameraPositionY };
	}

	ErrorCode CameraMoveBoundry(Camera& camera, const Vector2<float>& actorPosition) {
		
		//printf("%f\n", actorPosiiton.x);
		//if (actorPosition.x > boundry.x && actorPosition.x < boundry.w) {
		//	printf("We're in the rectangle\n");
		//}

		const Vector2<float> cameraMove { boundry.w - boundry.x, boundry.h - boundry.y };

		if (actorPosition.x < boundry.x) {
			camera.position.x += cameraMove.x;
			printf("We're to the left of rectangle\n");
		}
		
		if (actorPosition.x > boundry.w) {
			camera.position.x -= cameraMove.x;
			printf("We're to the right of rectangle\n");
		}
		
		if (actorPosition.y < boundry.y) {
			camera.position.y += cameraMove.y;
			printf("We're up of rectangle\n");
		}
		
		if (actorPosition.y > boundry.h) {
			camera.position.y -= cameraMove.y;
			printf("We're down of rectangle\n");
		}

		return success;
	}

	ErrorCode CameraFollowBoundry(Camera& camera, const Vector2<float>& actorPosition, const float& actorSize, const float& speed) {

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

		if (actorPosition.y - (actorSize / 2) < boundry.y) {
			camera.position.y += speed;
			printf("We're up of rectangle\n");
		}
		
		if (actorPosition.y + (actorSize / 2) > boundry.h) {
			camera.position.y -= speed;
			printf("We're down of rectangle\n");
		}

		return success;
	}

	ErrorCode CameraBothBoundry(Camera& camera, const Vector2<float>& actorPosition, const float& actorSize, const float& speed) {

		//printf("%f\n", actorPosiiton.x);
		//if (actorPosition.x > boundry.x && actorPosition.x < boundry.w) {
		//	printf("We're in the rectangle\n");
		//}

		const Vector2<float> cameraMove { boundry.w - boundry.x, boundry.h - boundry.y };

		if (actorPosition.x - (actorSize / 2) < boundry.x) {
			camera.position.x += speed;
			printf("We're to the left of rectangle\n");
		}

		if (actorPosition.x + (actorSize / 2) > boundry.w) {
			camera.position.x -= speed;
			printf("We're to the right of rectangle\n");
		}

		if (actorPosition.y < boundry.y) {
			camera.position.y += cameraMove.y;
			printf("We're up of rectangle\n");
		}

		if (actorPosition.y > boundry.h) {
			camera.position.y -= cameraMove.y;
			printf("We're down of rectangle\n");
		}

		return success;
	}

	ErrorCode Camera2ActorsBoundry(Camera& camera, const SDL_Rect& actor1, const SDL_Rect& actor2) {

		const Vector2<float> actor1Position { actor1.x, actor1.y }, actor2Position { actor2.x, actor2.y };
		const Vector2<float> actor1Size { actor1.w, actor1.h }, actor2Size { actor2.w, actor2.h };
		const Vector2<float> cameraMove { boundry.w - boundry.x, boundry.h - boundry.y };
		const float speed = 2 * 2; // Player1 speeed
		
		//if (actor1Position.x - (actor1Size.x / 2) > boundry.x && actor1Position.x - (actor1Size.x / 2) < boundry.w) {
		//	printf("We're in the rectangle\n");
		//}

		const float boundryExtra = 200;
		const float cameraMoveExtra = 4;

		//if (abs(actor1Position.x - actor2Position.x) >= boundry.w + boundryExtra) {
		//	printf("%f, %f\n", actor1Position.x, actor2Position.x);
		//	//printf("Thers one player in x rectangle\n");
		//	camera.zoom -= 0.01f;
		//} else if (abs(actor1Position.x - actor2Position.x) < boundry.w && camera.zoom != 1.0f) {
		//	printf("We should zoom in\n");
		//	camera.zoom += 0.01f;
		//	camera.position.x += speed + cameraMoveExtra;
		//}

		if (actor1Position.x - (actor1Size.x / 2) < boundry.x && actor2Position.x + (actor2Size.x / 2) > boundry.w) {
			//printf("Player1: We're to the left of rectangle, Player1: We're to the right of rectangle\n");
			camera.zoom -= 0.01f;
		} else if (actor2Position.x - (actor2Size.x / 2) < boundry.x && actor1Position.x + (actor1Size.x / 2) > boundry.w) {
			//printf("Player1: We're to the right of rectangle, Player1: We're to the left of rectangle\n");
			camera.zoom -= 0.01f;
		} else if (abs(actor1Position.x - actor2Position.x) < boundry.w - boundryExtra && camera.zoom != 1.0f) {
			printf("We should zoom in\n");
			camera.zoom += 0.01f;
			camera.position.x += speed + cameraMoveExtra;
		}

		// Player 1
		if (actor1Position.x - (actor1Size.x / 2) < boundry.x) {
			camera.position.x += speed;
			//printf("Player1: We're to the left of rectangle\n");
		}

		if (actor1Position.x + (actor1Size.x / 2) > boundry.w) {
			camera.position.x -= speed;
			//printf("Player1: We're to the right of rectangle\n");
		}

		// Player 2
		if (actor2Position.x - (actor2Size.x / 2) < boundry.x) {
			camera.position.x += speed;
			//printf("Player2: We're to the left of rectangle\n");
		}

		if (actor2Position.x + (actor2Size.x / 2) > boundry.w) {
			camera.position.x -= speed;
			//printf("Player2: We're to the right of rectangle\n");
		}

		if (actor1Position.y < boundry.y) {
			camera.position.y += cameraMove.y;
			printf("We're up of rectangle\n");
		}

		if (actor1Position.y > boundry.h) {
			camera.position.y -= cameraMove.y;
			printf("We're down of rectangle\n");
		}
		
		

		return success;
	}

	ErrorCode LogicUpdate(const float& deltaTime, Camera& camera, const Uint8* const keyboard) {
	
		if (keyboard[SDL_SCANCODE_W]) {
			camera.zoom += 0.02f;
			printf("Camera zoom inc %f\n", camera.zoom);
		}
		if (keyboard[SDL_SCANCODE_S]) {
			camera.zoom -= 0.02f;
			printf("Camera zoom dec %f\n", camera.zoom);
		}
	
		return success;
	}

}


