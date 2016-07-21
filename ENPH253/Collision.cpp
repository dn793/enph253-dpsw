#include "Collision.h"

unsigned char getCollisionState()
{
	unsigned char front = digitalRead(COLLISION_FRONT);
	unsigned char back = digitalRead(COLLISION_BACK);

	if (!front && !back) { return HIT_BOTH; }
	else if (!front) { return HIT_FRONT; }
	else if (!back) { return HIT_BACK; }
	else { return HIT_NONE; }
}

void collided(Drive *drive, unsigned char collisionState)
{
	switch (collisionState)
	{
		// Front collision detected, reverse and turn
		case HIT_FRONT:
		{
			// TODO: Test how long I have to reverse(4")
			unsigned char count;

			for (count = 0; count < 20; ++count)
			{
				reverse(SPEED_REVERSE);
				if (getCollisionState() == HIT_BOTH || getCollisionState() == HIT_FRONT)
				{
					stopNow();
					break;
				}
			}

			// Turn around
			unsigned char turnFailed = 0;
			for (count = 0; count < 50; ++count)
			{
				turnAroundLeft(drive);
				if ((getCollisionState() == HIT_BOTH || getCollisionState() == HIT_FRONT) && turnFailed == 0)
				{
					stopNow();
					turnFailed = count;
					break;
				}
				//direction = -1 * direction;
			}

			// If unable to turn one way, turn the other way
			if (turnFailed != 0)
			{
				for (count = 0; count < 50 + turnFailed; ++count) { turnAroundRight(drive); }
				//direction = -1 * direction;
			}
			break;
		}
		// Back collision detected, go forward a little
		case HIT_BACK:
		{
			while (getCollisionState() == HIT_BACK) { lineFollow(drive); }
			while (getCollisionState() == HIT_BOTH)
			{
				stopNow();
				delay(DELAY_HIT);
			}
			break;
		}
			
		// Collisions from both ends, stop
		case HIT_BOTH:
		{
			stopNow();
			delay(DELAY_HIT);
			break;
		}
	}
}