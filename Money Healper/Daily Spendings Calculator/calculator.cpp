#include <iostream>
#include "calculator.h"
#include "savedata.h"

float Calculator::GetDailySpendingLimit(float Income, float SavingsGoal) {
	float ReturnValue = (Income - SavingsGoal) / 365;
	return ReturnValue;
}

void Calculator::ApplyChangeToLimit(Data::DataStruct& CurrentData, float Change) {
	float CalculatedChange = Change / 365;
	CurrentData.DailyLimit += CalculatedChange;
}