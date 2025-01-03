#include <iostream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <algorithm>
#include <cctype>

#include "savedata.h"
#include "calculator.h"

std::string line;
std::string ChosenOption;
Data::DataStruct DataStruct;
bool Running = false;

void PostStartLoop() {
	Running = true;
}

void MainLoop() {
	
	if (DataStruct.CurrentDay == 0) {
		DataStruct.LeftToSpend = DataStruct.DailyLimit;
		DataStruct.CurrentDay = 1;
	}

	while (Running)
	{
		system("cls"); //Again probably a bad idea :b
		std::cout << "It is day " << DataStruct.CurrentDay << " and you have $" << DataStruct.LeftToSpend << " left to spend.\n";

		std::cout << "Pick a option to continue: \n";

		std::cout << "[1] End the current day and start a new one \n";
		std::cout << "[2] Log a expense \n";
		std::cout << "[3] Add to savings \n";

		std::getline(std::cin, ChosenOption);

		if (ChosenOption == "1") {
			//Start a new day
			DataStruct.Rollover = (DataStruct.DailyLimit - DataStruct.SpentMoney);
			std::cout << DataStruct.Rollover;
			DataStruct.CurrentDay += 1;
			DataStruct.SpentMoney = 0.0;
			DataStruct.LeftToSpend = DataStruct.NextDay;

			if (DataStruct.Rollover >= 0)
			{
				DataStruct.NextDay = DataStruct.DailyLimit + DataStruct.Rollover;
				std::cout << "Rollover has been applied to the next day!\n";
			}
			else {
				std::cout << "You went negitive for the day. Would you like to take this into account in the future to make up for it?\n";
				std::cout << "[y/n]\n";
				std::getline(std::cin, line);

				std::transform(line.begin(), line.end(), line.begin(),
					[](unsigned char c) { return std::tolower(c); });

				if (line == "y") {
					Calculator::ApplyChangeToLimit(DataStruct, DataStruct.Rollover);
				}
				else {
					std::cout << "Rollover will not be added.\n";
				}
			}
			std::cout << "A new day has been started\n";
		}
		else if (ChosenOption == "2") {
			//Log a expense
			float Expense;
			std::cout << "How much money would you like to log. (To add money use a negitive number): $";

			std::getline(std::cin, line);

			Expense = std::stof(line);

			DataStruct.SpentMoney = Expense;
			DataStruct.LeftToSpend -= Expense;

			std::cout << "\n $" << Expense << " has been logged!";
		}
		else if (ChosenOption == "3") {
			//Add to savings
			float SavingsChange;

			std::cout << "Your current savings are $" << DataStruct.CurrentSavings << ". \n";
			std::cout << "How much would you like to add or remove (Remove is a negitive number): ";
			std::getline(std::cin, line);

			SavingsChange = std::stof(line);

			DataStruct.CurrentSavings += SavingsChange;
		}
		else {
			MainLoop();
			break;
		}

		Sleep(500);
	}
	
}

void StartLoop() {
	DataStruct.CurrentDay = 0; //Set the current day to 0 because its your first time using the app

	std::cout << "Welcome to Laynes Money Helper. First before we begin I need to ask you a few questuions.\n";

	std::cout << "What is your after tax yearly income: \n";

	std::getline(std::cin, line);

	DataStruct.YearlyIncome = std::stof(line);

	std::cout << "What is your savings goal for this year: \n";

	std::getline(std::cin, line);

	DataStruct.SavingsGoal = std::stof(line);

	DataStruct.DailyLimit = std::ceil(Calculator::GetDailySpendingLimit(DataStruct.YearlyIncome, DataStruct.SavingsGoal) * 100) / 100;

	std::cout << "Taking all of this into account you have $" << DataStruct.DailyLimit << " to spend per day.\n";

	Sleep(5000);

	system("cls"); //I think this is a bad idea to use system calls but I cant think of another way right now
}

int main() {
	//First we want to check for save data
	/*bool Outcome = Data::CheckData();
	if (Outcome == false) {
		//Data was found and we are good to go into daily spendings
		std::cout << "Save data found we are good to continue!\n";
	}
	else {
		//The save data was not found so we need to ask some questions
		std::cout << "Data not found\n";
	}*/

	//Second we want to get their daily income so we can calculate their daily spendings
	

	StartLoop();

	PostStartLoop();


	MainLoop();
	//std::cout << Calculator::GetDailySpendingLimit(AfterTaxIncome);

	return 1;
}