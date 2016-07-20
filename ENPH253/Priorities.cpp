/*
 * An outline of priorities and a guess as to how we'd do this.
 */
int collisionState = 0;
int state = 1;
boolean carryingPassenger = 0;
int direction = 1;

loop() {

    //detect Collisions first
    int collisionState = detectCollision();
    if (collisionState != 0) {
        collided(collisionState);
    }

    //Navigate and find passengers next
    if (passengerDetected() && !carryingPassenger) {
        state = 1;
    } 
    else if (DropOff()) {
        state = 2;
    }
    else {
        state = 3;
    }

    switch (state) {
    // Pick up passenger
    case 1:
        pickUpPassenger();
        carryingPassenger = 1;
        break;

    // Drop off passenger
    case 2:
        navigate();
        dropOffPassenger();
        break;

    // Passenger detected
    case 3:
        if (detectIntersection()) {
            navigate();
        }
        line follow();
        break;
    }
    }