#pragma once

namespace Data {
	struct DataStruct
	{
		float YearlyIncome;
		float SavingsGoal;
		float SpentMoney;
		float CurrentSavings;
		int CurrentDay;
		float DailyLimit;
		float LeftToSpend;
		float Rollover;
		float NextDay;
	};

	bool CheckData();
	bool WriteData(auto DataToWrite, int LineNumber);
	auto ReadData();
}