// hw2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

//Спроектируйте приложение, используя паттерн «абстрактная фабрика», который будет симулировать животную жизнь на разных континентах земного шара.
//В программе весь животный мир будет разделен на части : травоядные и хищники(абстрактные продукты).
//Добавьте к абстрактному продукту «хищник» метод «кушать», который будет принимать в себя объект «травоядного»(абстрактный продукт).
//Наследники класса «Континент»(абстрактная фабрика) будут порождать конкретные объекты с именами и функциями, присущими их флоре и фауне.
//Всеми процессами в программе будет управлять класс «мир животных»(клиент).
//Конкретные объекты :
// Континент(Continent) - абстрактная фабрика;
//o Африка(Africa) - конкретная фабрика;
//o Северная Америка(North America) - конкретная фабрика;  Травоядноеживотное(Herbivore) - абстрактныйпродукт;
//o Антилопа Гну(Wildebeest) - конкретный продукт;
// Вес(Weight) - свойство травоядного животного;
// Кушать траву(Eat grass) - метод конкретного продукта
//(добавляют к весу + 10);
// Жизнь(Life) - свойство животного(характеризует живое
//    ли существо);
//o Бизон(Bison) - конкретный продукт;
// Вес(Weight) - свойство травоядного животного;
// Кушать траву(Eat grass) - метод конкретного продукта
//(добавляют к весу + 10);
// Жизнь(Life) свойство животного(характеризует живое ли
//    существо);
// Плотоядноеживотное(Carnivore) - абстрактныйпродукт;
//o Лев(Lion) - конкретный продукт;
// Сила(Power) - свойство плотоядного животного;
// Кушать травоядное животное(Eat) - метод конкретного продукта, при выполнении которого проверяется, является ли сила плотоядного животного больше, чем вес травоядного, которого он съедает.Если является, то хищник получает + 10 к силе, иначе, если сила меньше, чем вес травоядного животного, то сила плотоядного
//уменьшаются на - 10.
//o Волк(Wolf) - конкретный продукт;
// Мирживотных(AnimalWorld)–клиент;
//o Питание травоядных(Meals herbivores) - метод клиента, который инициирует всех травоядных приступить к кормежке;
//o Питание плотоядных(Nutrition carnivores) - метод клиента, который заставит всех плотоядных охотится на травоядных.
//Постройте данную программу на паттерне «абстрактная фабрика».
//Дополните данное приложение, добавив новый континент «Евразия», в котором травоядным будет «Лось»(Elk), а плотоядным - «Тигр»(Tiger).


class Herbivore {  //абстрактный класс
public:
	string name;
	int weight;
	bool isLive;
	
	void eatGrass() {
		weight += 10;
	}

	int getWeight() {
		return weight;
	}
	bool setLife(bool status) {
		isLive = status;
		return isLive;
	}
};



class Bison : public Herbivore { //конкретный продукт
public:
	Bison() {
		name = "bison";
		weight = 650;
		isLive = true;
		cout << "bison is created" << endl;
	}
};

class Wildebeest : public Herbivore { //травоядное животное
public:
	Wildebeest() {
		name = "wildebeest";
		weight = 200;
		isLive = true;
		cout << "wildebeest is created" << endl;
	}
};

class Elk : public Herbivore { //конкретный продукт
public:
	Elk() {
		name = "elk";
		weight = 500;
		cout << "elk is created" << endl;
	}
};




class Predator { //абстрактный класс
public:
	string name;
	int power;

	void Eat(Herbivore& her){
		if (her.getWeight() < this -> power) {
			power += 10;
			her.setLife(false);
		}
		else {
			power -= 10;
		}
		
	}
};

class Lion : public Predator { //конкретный продукт
public:
	Lion() {
		name = "lion";
		power = 10;
		cout << "lion is created" << endl;
	}
};

class Wolf : public Predator { //конкретный продукт
public:
	Wolf() {
		name = "wolf";
		power = 7;
		cout << "wolf is created" << endl;
	}
};


class Tiger : public Predator { //конкретный продукт
public:
	Tiger() {
		name = "wolf";
		power = 7;
		cout << "tiger is created" << endl;
	}
};


class Continent abstract { //абстрактная фабрика
public:
	virtual Herbivore* CreateHerbivore() abstract = 0;
	virtual Predator* CreatePredator() abstract = 0;

};

class Africa: public Continent { //конкретная фабрика
public:
	Herbivore* CreateHerbivore() override {
		return new Bison();
	}
	Predator* CreatePredator() override {
		return new Lion();
	}

};

class America : public Continent { //конкретная фабрика
public:
	Predator* CreatePredator() override {
		return new Wolf();
	}
	Herbivore* CreateHerbivore() override {
		return new Wildebeest();

	}

};

class Eurasia : public Continent { //конкретная фабрика
public:
	Predator* CreatePredator() override {
		return new Tiger();
	}
	Herbivore* CreateHerbivore() override {
		return new Elk();

	}

};


class AnimalWorld { //клиент
	Herbivore* herbivore;
	Predator* predator;
public:
	
	AnimalWorld(Continent* factory) {
		herbivore = factory->CreateHerbivore();
		predator = factory->CreatePredator();
	}
	void MealsHerbivores() {
		herbivore -> eatGrass();
	}

	void NutritionPredators() {
		predator->Eat(*herbivore);
	}
};

int main()
{
	Continent* factory = new Eurasia();
	AnimalWorld* animal = new AnimalWorld(factory);
	animal->MealsHerbivores();
	delete factory;
	delete animal;
   
}

