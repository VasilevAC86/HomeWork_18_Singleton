# include <iostream>
#include <exception>
#include<string>

class Apple {
public:
	// Статический метод для доступа к единственному объекту класса
	static Apple& Instance() {
		// Локальная статическая переменная метода instance, хранящая единственный экземпляр класса (Синглтон Меерса)
		static Apple instance; 
		return instance;
	}
	// Геттер оставшейся питательной ценности
	float Remainder()const { return remainder_; }
	// Геттер оставшегося времени до сгнивания
	int Time_capasity()const { return time_capasity_; }
	// Метод уменьшения питательной способности яблока
	float Pop_Remainder(int time) { // Каждый день состояние яблока ухудшается на 12,5 %
		remainder_ -= (12.5 * time); 
		if (remainder_ > 0)
			return remainder_;
		return remainder_ = 0;
	} 
	// Метод уменьшения времени до полного сгнивания яблока
	int Pop_Time(int time) { 
		time_capasity_ -= time; 
		if (time_capasity_ > 0)
			return time_capasity_;
		return time_capasity_ = 0;
	} 
private:
	float remainder_; // Оставшаяся питательная ценность
	int time_capasity_; // Оставшееся врямя до сгнивания
	// Приватный конструктор для создания только одного экземпляра класса
	// 100.0 - полностью целое яблоко (на 100 %), 8 дней - время полного сгнивания яблока
	Apple(): remainder_(100.0), time_capasity_(8) {}
};

int main() {
	Apple& apple = Apple::Instance(); // Создаём единственный экземпляр яблока
	std::cout << "Source state of the apple:" << std::endl
		<< "Nutritional value = \033[92m" << apple.Remainder() << " %\033[0m" << std::endl
		<< "Time until complete rotting = \033[92m" << apple.Time_capasity() << "\033[0m" << std::endl << std::endl
		<< "\033[93mEnter time in days -> \033[0m";
	int time; // Переменная для хранения дней, введённых пользователем	
	std::string text; // Переменная для хранения дней, введённых пользователем в формате строки для обработки исключением	
	std::cin >> text;
	// Обработка исключения, если пользователь вводит что-то не то
	try {		
		if ((text.at(0) < 48 || text.at(0) > 56) || text.size() > 1)
			throw std::exception("\n\033[91mInput error! The entered value is not a number from 0 to 8!\033[0m\n");
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		bool key = false;
		while (!key) {
			std::cout << "Enter time in days one again -> ";
			std::cin >> text;			
			if ((text.at(0) < 48 || text.at(0) > 56) || text.size() > 1) 
				key = false;							
			else
				key = true;			
		}
	}
	time = stoi(text);
	int time_capasity = apple.Pop_Time(time); // Переменная для хранения остатка дней до полного сгнивания
	std::cout << std::endl;
	if (time_capasity)
		std::cout << "Time until complete rotting = \033[92m" << time_capasity << "\033[0m" << std::endl
		<< "Nutritional value = \033[92m" << apple.Pop_Remainder(time) << " %\033[0m" << std::endl;
	else
		std::cout << "\033[92mThe apple is completely rotten!\033[0m" << std::endl;
	
	return 0;
}