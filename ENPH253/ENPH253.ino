#include <phys253.h>
#include <LiquidCrystal.h>

#include "Graph.cpp"

void setup() {
  #include <phys253setup.txt>
  Serial.begin(9600);
}

void loop() {
	LCD.clear();
    LCD.setCursor(0,0);
	const uint8_t * adjacents = getAdjacent(2);
	LCD.print(*adjacents); LCD.print(" "); LCD.print(*(adjacents+1));
}

