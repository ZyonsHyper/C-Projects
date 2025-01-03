#pragma once
#include "savedata.h"

namespace Calculator {
	float GetDailySpendingLimit(float Income, float SavingsGoal);
	void ApplyChangeToLimit(Data::DataStruct& CurrentData, float Change);
}