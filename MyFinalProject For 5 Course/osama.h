#pragma once



#include <iostream>
#include <string>
using namespace std;


namespace legend
{


	int GetRandomNumber(int From, int To)
	{
		return  rand() % (To - From + 1) + From;
	}





	namespace ReadNumber {

		short ReadNumber_short_Version(string Message) {

			short Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail()) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " \n|Be Sure To Enter A Number ~" + Message;
				cin >> Number;

			}

			return Number;
		}
		float ReadNumber_float_Version(string Message) {

			float Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail()) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " \n|Be Sure To Enter A Number ~" + Message;
				cin >> Number;

			}

			return Number;
		}
		int ReadNumber(string Message) {

			int Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail()) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " \n|Be Sure To Enter A Number ~" + Message;
				cin >> Number;

			}

			return Number;
		}
		bool ReadNumber_bool_Version(string Message) {

			bool Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number < 0 || Number>1)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " \n|Be Sure To Enter A Number ~" + Message;
				cin >> Number;

			}

			return Number;
		}
	}


	namespace ReadNumber_InRange {

		int ReadNumber_InRange(string Message, int From, int To) {

			int Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number<From || Number>To)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Number Between [ %d and %d ] ~", From, To);
				cout << Message;
				cin >> Number;

			}

			return Number;
		}
		float ReadNumber_InRange_float_Ver(string Message, float From, float To) {

			float Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number<From || Number>To)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Number Between [ %.3f and %.3f ] ~", From, To);
				cout << Message;
				cin >> Number;

			}

			return Number;
		}
		short ReadNumber_InRange_short_Ver(string Message, short From, short To) {

			short Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number<From || Number>To)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Number Between [ %d and %d ] ~", From, To);
				cout << Message;
				cin >> Number;

			}

			return Number;
		}

	}


	namespace ReadPositiveNumbers {

		short ReadPositiveNumber_short_Ver(string Message) {

			short Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number < 0)) {


				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Positive Number ~");
				cout << Message;

			}

			return Number;
		}
		float ReadPositiveNumber_float_Ver(string Message) {

			float Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number < 0)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Positive Number ~");
				cout << Message;
				cin >> Number;

			}

			return Number;
		}
		int ReadPositiveNumber(string Message) {

			int Number = 0;
			cout << Message;

			cin >> Number;


			while (cin.fail() || (Number < 0)) {

				cin.clear();

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				printf("\n|Be Sure To Enter A Positive Number ~");
				cout << Message;
				cin >> Number;

			}

			return Number;
		}
	}


	namespace Arrays {

		void FillArray_WithRandomNumbers(int Array[100], short& arrLength)
		{
			arrLength = legend::ReadNumber_InRange::ReadNumber_InRange_short_Ver("How Many Elements Do You Want ,From [ 1 to 100 ] ?    |~ ", 1, 100);

			for (int i = 0; i < arrLength; i++)
			{
				Array[i] = legend::GetRandomNumber(1, 100);
			}
		}
		void FillArray_WithRandomNumbers(short Array[100], short& arrLength)
		{
			arrLength = legend::ReadNumber_InRange::ReadNumber_InRange_short_Ver("How Many Elements Do You Want ,From [ 1 to 100 ] ?    |~ ", 1, 100);

			for (int i = 0; i < arrLength; i++)
			{
				Array[i] = legend::GetRandomNumber(1, 100);
			}
		}
		void FillArray_WithRandomNumbers_WithoutRead(short Array[100], short& arrLength)
		{

			for (int i = 0; i < arrLength; i++)
			{
				Array[i] = legend::GetRandomNumber(1, 100);
			}
		}
		short FindNumberPosition_InArray(int arr[100], short arrLength, short SearchFor)
		{
			for (int i = 0; i < arrLength; i++)
			{
				if (arr[i] == SearchFor)
					return i;
			}

			return -1;
		}
		bool IsNumberInArray(int arr[100], short arrLength, short NumberToCheck)
		{
			return (FindNumberPosition_InArray(arr, arrLength, NumberToCheck) != -1);
		}
		void AddArrayElement_InArray(int NumberToAdd, int ArrayDistination[100], short& arrDistinationLength)
		{
			arrDistinationLength++;
			ArrayDistination[arrDistinationLength - 1] = NumberToAdd;
		}
		void InputUserNumbers_InArray(int arr[100], short& arrLength)
		{
			bool AddMore;

			do
			{
				AddArrayElement_InArray(legend::ReadNumber::ReadNumber("Please enter a Number ? | "), arr, arrLength);

				AddMore = legend::ReadNumber::ReadNumber_bool_Version("\nDo you want to add more numbers ?  [0]:No | [1]:Yes ? ~ "); cout << endl;
			} while (AddMore);
		}
		void CopyArray(int SourceArray[100], int ArrayDistination[100], short arrSourceLength, short& arrDistinationLength)
		{
			for (int i = 0; i < arrSourceLength; i++)
			{
				AddArrayElement_InArray(SourceArray[i], ArrayDistination, arrDistinationLength);
			}
		}
		void PrintArray(int Arr[100], short arrLength)
		{
			for (int i = 0; i < arrLength; i++)
			{
				cout << Arr[i] << " ";
			}
			cout << endl;
		}
		void PrintArray(short Arr[100], short& arrLength)
		{
			for (int i = 0; i < arrLength; i++)
			{
				cout << Arr[i] << " ";
			}
			cout << endl;
		}
		void ReadArray(int arr[100], short& arrLength)
		{

			arrLength = legend::ReadPositiveNumbers::ReadPositiveNumber_short_Ver("Enter Number Of Elements :\n");

			cout << "\nEnter array elements :\n";

			for (int i = 0; i < arrLength; i++)
			{
				arr[i] = legend::ReadNumber::ReadNumber("Element [" + to_string(i + 1) + "]:");
			}
		}
	}


	

	int ReverseNumber(int Number)
	{
		short Remainder = 0; int ReversedNumber = 0;
		while (Number > 0)
		{
			Remainder = (Number % 10);
			Number /= 10;

			ReversedNumber = ReversedNumber * 10 + Remainder;
		}

		return ReversedNumber;
	}
	bool Check_IsPrimeNumber(int Number)
	{

		for (int i = 2; i <= ceil(Number / 2); i++)
		{
			if (Number % i == 0)
				return false;
		}

		return true;
	}
	bool Check_IsPerfectNumber(int Number)
	{
		int Sum = 0;
		for (int i = 1; i <= ceil(Number / 2); i++)
		{
			if (Number % i == 0)
			{
				Sum += i;
			}
		}

		return (Number == Sum);
	}
	bool Check_IsPalindromeNumber(int Number)
	{
		return (Number == ReverseNumber(Number));
	}



	enum enCharType { CapitalLetter, SmallLetter, SpecialCharacter, Digit };
	char GetRandomCharacter(enCharType CharType)
	{
		switch (CharType)
		{

		case enCharType::SmallLetter:
		{
			return char(legend::GetRandomNumber(97, 122));
			break;
		}
		case enCharType::CapitalLetter:
		{
			return char(GetRandomNumber(65, 90));
			break;
		}
		case enCharType::SpecialCharacter:
		{
			return char(GetRandomNumber(33, 47));
			break;
		}
		case enCharType::Digit:
		{
			return char(GetRandomNumber(48, 57));
			break;
		}

		}
	}

	string NextLine(short NumberOfLinesToStepUp) {

		string NextLine = "";
		for (short NextLines = 1; NextLines <= NumberOfLinesToStepUp; NextLines++)
			NextLine += "\n";

		return NextLine;

	}

	string Tabs(short NumberOfTabs) {

		string OrderedTabs = "";

		for (short i = 1; i <= NumberOfTabs; i++)
			OrderedTabs += "\t";

		return OrderedTabs;
	}


	void Swap(int& FirstNumber, int& SecondNumber)
	{
		int Temp = FirstNumber;
		FirstNumber = SecondNumber;
		SecondNumber = Temp;
	}
	void Swap(short& FirstNumber, short& SecondNumber)
	{
		int Temp = FirstNumber;
		FirstNumber = SecondNumber;
		SecondNumber = Temp;
	}


	string ReadString(string Message)
	{
		string Word = "";

		cout << Message;
		getline(cin, Word);

		return Word;
	}




}


