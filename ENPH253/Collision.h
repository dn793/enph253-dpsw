/*
* Collision Detection
* TODO: Assumes reading FALSE when collision is detected
* HOW IS ARE THE LINE FOLLOWING THINGS WORKING?!?!?!
*/

/*
* Returns 0 if no collision detected, 1 if front, 2 if back, 3 if both
*/
int detectCollision() {
    boolean front = digitalRead(COLLISION_FRONT);
    boolean back = digitalRead(COLLISION_BACK);
	if (!front && !back) {
		return 3;
	}
	if (!front) {
		return 1;
	}
	if (!back) {
		return 2;
	}
	return 0;
}

/*
* Either moves forwards or backwards depending on the state inputed (1, 2, 3)
* This prevents having to look for a lost digital signal
*/
void collided(int collisionstate) {
	switch (collisionstate) {

		/*
		*  Front collision detected, reverse and turn
		*  TODO: dependent on the drive function
		*/
	case 1:
		/*
		* TODO: what is line following called?
		* TODO: Test how long I have to reverse (4")
		*/
		for (int count = 0; count < 20; count++) {
			lineFollowingReverse();
            if (detectCollision() == 3 || detectCollision() == 1) {
                drive(0, 0);
                break;
            }
		}
		/*
		* TODO: Turn 180
		*/
        int turnFailed = 0;
		for (int count = 0; count < 50; count++) {
			drive(0, -255);
            if (detectCollision() == 3 || detectCollision() == 1 && turnFailed == 0) {
                drive(0, 0);
                turnFailed = count;
                break;
            }
            direction = -1*direction;
		}
        //If unable to turn one way, turn the other way
        if (turnFailed!=0) {
            for (int count = 0; count < 50 + turnFailed; count++) {
                drive(0, 255);
            }
            direction = -1 * direction;
        }
        break;

	/*
	*  Back collision detected, go forward a little
    *  TODO: change function call
	*/
	case 2:
        while (detectCollision() == 2) {
            lineFollow();
        }
        while (detectCollision() == 3) {
            drive(0, 0);
            delay(200);
        }
        break;

	/*
	* Collisions from both ends, stop
	*/
	case 3:
		/*
		* TODO: what's the drive function and make it stop
		*/
		drive(0, 0);
        delay(200);
        break;
	}
}
