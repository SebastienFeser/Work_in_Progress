// CreatureSimulationBadCode.cpp : Defines the entry point for the console application.
//


/*
Cet exercice regroupe le 8.2, 8.3 et 8.4

J'ai pu terminer le 8.2, mais je n'ai pas réussi à faire le 8.3 et je n'ai réussi à terminer le 8.4


*/

#include "pch.h"
#include <array>
#include <string>
#include <iostream>
#include <memory>
#include <random>
#include <list>


struct Vector2D {
	Vector2D(int x, int y) :x(x), y(y) {

	}
	Vector2D() {
		x = 0;
		y = 0;
	}
	int x;
	int y;
};



const int MAP_SIZE = 10;
class Map;
class Simulation;
class Creature;
class Food;


class  GameObjectBuilder {
public:
	static Creature * buildCreature(Simulation & simulation);
	static Food * buildFood(Simulation & simulation);

};


class GameObject {

public:
	GameObject(Simulation * simulation, Vector2D position) :simulation(simulation), position(position) {

	}


	GameObject(Simulation * simulation) :simulation(simulation) {
		isDestroyed = false;
	}

	virtual void update() {

	}

	virtual void start() {

	}

	virtual char getImage() {
		return '?';
	}

	Vector2D getPosition() {
		return position;
	}

	void setPosition(Vector2D position) {
		this->position = position;
	}

	bool isObjectDestroyed() {
		return isDestroyed;
	}

	void destroy() {
		isDestroyed = true;
	}


protected:
	Vector2D position;
	Simulation * simulation;
	bool isDestroyed;

};


class Food : public GameObject {
public:
	Food(Simulation * simulation) :GameObject(simulation) {

	}

	char getImage() {
		return 'F';
	}

};

class Map {
public:
	Map() {
		for (auto & row : map) {
			row.fill(nullptr);
		}

	}

	bool AddGameObjectAt(GameObject * gameObject) {
		Vector2D position = gameObject->getPosition();
		return AddGameObjectAt(gameObject, position.x, position.y);
	}

	bool AddGameObjectAt(GameObject * gameObject, int positionX, int positionY) {
		GameObject * mapPosition = map[positionX][positionY];
		if (mapPosition == nullptr) {
			map[positionX][positionY] = gameObject;
			gameObjectsForUpdate.push_back(gameObject);
			return true;
		}

		return false;
	}

	GameObject & getContentAtPosition(Vector2D position) {
		return *map[position.x][position.y];
	}

	template<typename T> bool gameObjectOfTypeExistAt(Vector2D position) {
		if (map[position.x][position.y] == nullptr) {
			return false;
		}
		T * gameObject = dynamic_cast<T*>(map[position.x][position.y]);
		return gameObject != nullptr;
	}


	bool gameObjectExistAt(Vector2D position) {
		return map[position.x][position.y] != nullptr;
	}

	bool RemoveObjectAt(Vector2D position) {
		if (map[position.x][position.y] != nullptr) {
			delete map[position.x][position.y];
			map[position.x][position.y] = nullptr;
			return true;
		}
		return false;
	}

	bool MoveGameObjetTo(GameObject & gameObject, int positionX, int positionY) {
		if (positionX >= map.size() || positionY >= map[0].size()) {
			return false;
		}
		if (map[positionX][positionY] != nullptr)
		{
			return false;
		}
		Vector2D currentPosition = gameObject.getPosition();
		map[currentPosition.x][currentPosition.y] = nullptr;
		map[positionX][positionY] = &gameObject;
		gameObject.setPosition(Vector2D(positionX, positionY));

		return true;
	}

	void update() {
		for (auto & gameObject : gameObjectsForUpdate) {
			gameObject->update();

		}
		//Destroy element 

		//Destroy map elements 
		for (auto & gameObject : gameObjectsForUpdate) {
			if (gameObject->isObjectDestroyed()) {
				RemoveObjectAt(gameObject->getPosition());
			}
		}
		//Destroy updates elements 
		gameObjectsForUpdate.remove_if([](GameObject * gameObject) {return gameObject->isObjectDestroyed(); });
	}

	void DisplayMap() {
		system("cls");

		std::cout << "-------------------------" << std::endl;

		for (int x = 0; x < map.size(); x++) {
			std::cout << "|";
			for (int y = 0; y < map[x].size(); y++) {
				if (gameObjectExistAt(Vector2D(x, y))) {
					std::cout << map[x][y]->getImage();
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << "|" << std::endl;
		}
		std::cout << "-------------------------" << std::endl;

		system("Pause");
	}

	int countCreaturesInMap() {
		int counter = 0;
		for (int x = 0; x < map.size(); x++) {
			for (int y = 0; y < map[x].size(); y++) {
				if (gameObjectOfTypeExistAt<Creature>(Vector2D(x, y))) {
					counter++;
				}
			}

		}

		return counter;
	}

private:
	std::array<std::array<GameObject*, MAP_SIZE>, MAP_SIZE> map;
	std::list<GameObject * > gameObjectsForUpdate;




};

class Simulation {
public:

	Map map;



	Simulation(int seed) :random(seed) {

	}

	void init() {
		//Create 5 creatures
		for (int i = 0; i < 5; i++) {
			map.AddGameObjectAt((GameObject*)GameObjectBuilder::buildCreature(*this));
		}


		//Create 6 foods 
		for (int i = 0; i < 6; i++) {
			map.AddGameObjectAt((GameObject*)GameObjectBuilder::buildFood(*this));
		}

	}
	void star() {
		while (isEndSimulation()) {
			update();
			map.DisplayMap();
		}
		std::cout << std::endl << "------ END OF SIMULATION -------------" << std::endl;
		system("Pause");
	}

	int getValueRandom(int min, int max) {									//ok donc il permet d'avoir une valeur random...
		std::uniform_int_distribution<int> distribution(min, max);
		int randomValue = distribution(random);
		return randomValue;
	}




private:

	int nbrCreatures;
	int nbrHunters;
	int nbrFoodStuff;

	std::default_random_engine random;



	void update() {

		map.update();


	}

	bool isEndSimulation() {
		return map.countCreaturesInMap();
	}


};



class Creature : public GameObject
{
public:

	Creature(Simulation * simulation, int hungerSpeedIncrement) :GameObject(simulation), hungerSpeedIncrement(hungerSpeedIncrement) {				//initialise la valeur creature en lui donnant 0% de faim			
		hungerPourcent = 0;


	}




	void update() {
		if (isDestroyed) {
			return;
		}
		randomMove();
		incrementHunger();
		if (hungerPourcent >= 100) {
			die();
			return;
		}

		Vector2D * foodPosition = &findnearbyFoodPosition();
		if (foodPosition->x >= 0) {

			GameObject & gameObject = simulation->map.getContentAtPosition(*foodPosition);
			if (!gameObject.isObjectDestroyed()) {
				gameObject.destroy();
				hungerPourcent = 0;
			}
		}

		//TODO Implement reproduction method
		Vector2D * creaturePosition = &findnearbyCreaturePosition();
		if (creaturePosition->x >= 0) {


		}


	}
	char getImage() {
		return 'C';
	}


private:

	int hungerPourcent;
	int hungerSpeedIncrement;

	//Return position. If food is not find, we return the value (-1,-1)
	Vector2D findnearbyFoodPosition() {
		Vector2D positionCentral = position;
		for (int x = positionCentral.x - 1; x < positionCentral.x + 3; x++) {
			if (x < 0 || x >= MAP_SIZE) {
				continue;
			}
			for (int y = positionCentral.y - 1; y < positionCentral.y + 3; y++) {
				if (y < 0 || y >= MAP_SIZE) {
					continue;
				}
				Vector2D currentPosition(x, y);
				if (simulation->map.gameObjectOfTypeExistAt<Food>(currentPosition)) {

					return currentPosition;
				}
			}
		}

		return Vector2D(-1, -1);
	}

	//Return position. If creature is not find, we return the value (-1,-1)
	Vector2D findnearbyCreaturePosition() {
		Vector2D positionCentral = position;
		for (int x = positionCentral.x - 1; x < positionCentral.x + 3; x++) {
			if (x < 0 || x >= MAP_SIZE) {
				continue;
			}
			for (int y = positionCentral.y - 1; y < positionCentral.y + 3; y++) {
				if (y < 0 || y >= MAP_SIZE) {
					continue;
				}
				Vector2D currentPosition(x, y);
				if (simulation->map.gameObjectOfTypeExistAt<Creature>(currentPosition)) {

					return currentPosition;
				}
			}
		}

		return Vector2D(-1, -1);

	}



	void randomMove() {
		int positionXMin = position.x - 1;
		if (positionXMin < 0)
			positionXMin = 0;
		int positionXMax = position.x + 1;
		if (positionXMax >= MAP_SIZE)
			positionXMax = MAP_SIZE - 1;

		int positionYMin = position.y - 1;
		if (positionYMin < 0)
			positionYMin = 0;
		int positionYMax = position.y + 1;
		if (positionYMax >= MAP_SIZE)
			positionYMax = MAP_SIZE - 1;
		int newX = simulation->getValueRandom(positionXMin, positionXMax);
		int newY = simulation->getValueRandom(positionYMin, positionYMax);
		simulation->map.MoveGameObjetTo(*this, newX, newY);
	}
	void die() {

		isDestroyed = true;
	}

	void incrementHunger() {
		hungerPourcent += hungerSpeedIncrement;
	}


};



Creature *  GameObjectBuilder::buildCreature(Simulation & simulation) {
	Creature * creature = new Creature(&simulation, 20);
	int x = simulation.getValueRandom(0, MAP_SIZE - 1);
	int y = simulation.getValueRandom(0, MAP_SIZE - 1);
	creature->setPosition(Vector2D(x, y));

	return creature;


}


Food * GameObjectBuilder::buildFood(Simulation & simulation) {
	Food * food = new Food(&simulation);
	int x = simulation.getValueRandom(0, MAP_SIZE - 1);
	int y = simulation.getValueRandom(0, MAP_SIZE - 1);
	food->setPosition(Vector2D(x, y));
	return food;
}



void simulate() {
	Simulation simulation(445);
	simulation.init();
	simulation.star();

	std::cout << "Simulation ended" << std::endl;
}


int main()
{

	simulate();

	return 0;
}

