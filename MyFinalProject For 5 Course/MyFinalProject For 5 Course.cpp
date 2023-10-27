#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "osama.h"



using namespace std;


enum enTurn { Computer, Player, pPlayer2 };
enum enChoice_X_O { X, O };
enum enOperatorType { Addition = 1, Subtract, Multipli, Divine, MixOp };
enum enQuestionLevel { EasyLevel = 1, MideumLevel, HardLevel, Mix };
enum enSPS_Choices { Stone = 1, Paper = 2, Scissor = 3 };
enum enSPS_Winner { Player1 = 1, Player2, COMPUTER, NO_Winner };
enum enSPS_GameEnemy { EPlayer2 = 2, ECOMPUTER = 1 , Back = 3};
struct strQuestion {

	short FirstNumber; short SecondNumber;
	short RightAnswer;
	enOperatorType OpType;
	enQuestionLevel QuestionLevel;
	short UserAnswer;
	bool AnswerResult;
};
struct strQuizz {

	short NumberOf_WrongAnswers = 0; short NumberOf_RightAnswers = 0;
	enOperatorType OpType;
	enQuestionLevel QuestionLevel;
	short NumberOfQuestions;
	vector <strQuestion> vQuestionList;
	bool isPass;
};
struct strRoundInfo_SPS {

	enSPS_Choices Player1Choice, Player2Choice, COMPUTER_CHOICE;

	short RoundNumber;

	enSPS_Winner RoundWinner;
	string WinnerName;

};
struct strSPSGameInfo {

	short DrawTimes = 0, COMPUTER_WonTimes = 0, Player1_WonTimes = 0, Player2_WonTimes = 0;

	short GameRounds;

	enSPS_Winner FinalWinner;
	string FinalWinner_Name;

	enSPS_GameEnemy GameEnemy;
};
struct str_TicTacToe {

	char Place[9] = { '1','2','3','4','5','6','7','8','9' };

	char ComputerChoice; char Player_Choice; char Player2_Choice;
	enTurn Turn;
	enChoice_X_O X_O_Letter;
	enSPS_Winner Winner;
	bool IsWin;

};


string GetQuestionLevelName(enQuestionLevel QuestionLevel) {

	string arr[3] = { "Easy" , "Miduem" , "Hard" };
	return arr[QuestionLevel - 1];

}

short ReadOnlyNumbers_InRange_Short_Version(string Message, short From, short To) {

	short Number;
	cout << Message;
	cin >> Number;

	while (cin.fail() || (Number < From || Number > To)) {

		cin.clear();
		cout << "\nPlease ,Be Sure it's A Number ," + Message;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> Number;
	}

	return Number;
}

short ReadOnlyNumbers_Short_Version(string Message) {

	short Number;
	cout << Message;
	cin >> Number;

	while (cin.fail()) {

		cin.clear();

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nPlease ,Be Sure it's A Number ," + Message;
		cin >> Number;
	}

	return Number;
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

int GetRandomNumber(int From, int To)
{
	return  rand() % (To - From + 1) + From;
}

short ReadOnlyNumbers_InRange_Short_Version(string, short, short);

void ResetScreen() {

	system("color 0F");
	system("cls");
}

short ReadOnlyNumbers_Short_Version(string);

short Read_NumberOfQuestions() {

	return  ReadOnlyNumbers_InRange_Short_Version("Please How Many Questions Do You Want ? | From [ 1 To 10 ]    |~", 1, 10);
}

enQuestionLevel Read_QuestionLevel() {

	return (enQuestionLevel)ReadOnlyNumbers_InRange_Short_Version("Please Select Which you want about Questions Level:| [1]-Easy | [2]-Mid | [3]-Hard  | [4]-Mix  |~", 1, 4);
}

enOperatorType Read_OperationType() {

	return (enOperatorType)ReadOnlyNumbers_InRange_Short_Version("Please Choose The Operator:| [1]-Addition | [2]-Subtract | [3]-Multiply | [4]-Divine | [5]-Mix  |~", 1, 5);
}

short SimpleCalculator(short &FirstNumber, short &SecondNumber, enOperatorType &OpType) {

	switch (OpType) {

	case enOperatorType::Addition:
		return (FirstNumber + SecondNumber);

	case enOperatorType::Subtract:
		return (FirstNumber - SecondNumber);

	case enOperatorType::Multipli:
		return (FirstNumber * SecondNumber);

	case enOperatorType::Divine:
		return (FirstNumber / SecondNumber);
	}
}

strQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperatorType OpType) {

	strQuestion QuestionList;

	

	if (QuestionLevel == enQuestionLevel::Mix) {
		QuestionLevel = (enQuestionLevel)GetRandomNumber(1, 3);
	}

	if (OpType == enOperatorType::MixOp) {
		OpType = (enOperatorType)GetRandomNumber(1, 4);
	}

	QuestionList.OpType = OpType;
	QuestionList.QuestionLevel = QuestionLevel;

	switch (QuestionLevel) {


	case enQuestionLevel::EasyLevel:
		QuestionList.FirstNumber = GetRandomNumber(0, 9);
		QuestionList.SecondNumber = GetRandomNumber(0, 9);

		break;


	case enQuestionLevel::MideumLevel:
		QuestionList.FirstNumber = GetRandomNumber(10, 50);
		QuestionList.SecondNumber = GetRandomNumber(10, 50);

		break;


	case enQuestionLevel::HardLevel:
		QuestionList.FirstNumber = GetRandomNumber(50, 100);
		QuestionList.SecondNumber = GetRandomNumber(50, 100);

		break;
	}

	QuestionList.RightAnswer = (SimpleCalculator(QuestionList.FirstNumber, QuestionList.SecondNumber, QuestionList.OpType));
	return QuestionList;
}

void GenerateQuizzQuestions(strQuizz& Quizz) {

	for (int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
		Quizz.vQuestionList.push_back(GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType));

	
}

char Get_OpTypeSympol(enOperatorType &OpType) {

	char OpTypeSympol[4] = { '+','-','*','/' };

	return OpTypeSympol[OpType - 1];
}

void ShowTheQuestion(strQuizz &Quizz, short &QuestionNumber) {

	cout << "Question [" << (QuestionNumber + 1) << "\\" << Quizz.NumberOfQuestions << "]"; cout << "  - "  << "\n\n";
	cout << Quizz.vQuestionList[QuestionNumber].FirstNumber << "\n\n";
	cout << Quizz.vQuestionList[QuestionNumber].SecondNumber << "  " << Get_OpTypeSympol(Quizz.vQuestionList[QuestionNumber].OpType) << endl;
	cout << "_______________________\n";
}

string Get_QuestionLevelName(enQuestionLevel &QuestionLevel) {
	string Quest_Level[4] = { "Easy level","Mudieum Level","Hard Level","Mixed Level" };

	return Quest_Level[QuestionLevel - 1];
}

void SetScreenColour(bool);

void Correct_UserAnswer(strQuizz& Quizz, short &QuestionNumber) {

	if (Quizz.vQuestionList[QuestionNumber].UserAnswer == Quizz.vQuestionList[QuestionNumber].RightAnswer) {

		Quizz.vQuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOf_RightAnswers++;

		cout << "Right Answer :-) \n";
	}
	else {

		Quizz.vQuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOf_WrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is = { " << Quizz.vQuestionList[QuestionNumber].RightAnswer << " }\n";
	}

	SetScreenColour(Quizz.vQuestionList[QuestionNumber].AnswerResult);

}

void AskAndCorrect_QuestionsListAnswers(strQuizz& Quizz) {

	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {

		ShowTheQuestion(Quizz, QuestionNumber);

		Quizz.vQuestionList[QuestionNumber].UserAnswer = ReadOnlyNumbers_Short_Version("");

		Correct_UserAnswer(Quizz, QuestionNumber); cout << endl;

	}
	Quizz.isPass = (Quizz.NumberOf_RightAnswers >= Quizz.NumberOf_WrongAnswers);
}

void SetScreenColour(bool Result) {

	switch (Result) {

	case true:
		system("color 2F");
		break;

	case false:
		system("color 4F");
		break;
	}
}

string Get_OperationType_Name(enOperatorType &OpType) {
	string Operation_Names[5] = { "Addition","Subtract","Multiply","Divine","Mix Operations" };
	return Operation_Names[OpType - 1];
}

string GetFinalResultText(strQuizz &Quizz) {

	switch (Quizz.isPass) {

	case true:
		return "Pass :-)";

	case false:
		return "Fail :-(";
	}
}

void Show_FinalResults(strQuizz &Quizz) {
	cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";

	cout << "          Final Result Is " << GetFinalResultText(Quizz) << "\n";

	cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n";

	cout << "| Number Of Questions     : { " << Quizz.NumberOfQuestions << " }\n";
	cout << "| Questions Level         : { " << Get_QuestionLevelName(Quizz.QuestionLevel) << " }\n";
	cout << "| Operation Type          : { " << Get_OperationType_Name(Quizz.OpType) << " }\n";
	cout << "| Number Of Right Answers : { " << Quizz.NumberOf_RightAnswers << " }\n";
	cout << "| Number Of Wrong Answers : { " << Quizz.NumberOf_WrongAnswers << " }\n";
	cout << "_______________________________________________________\n";


	SetScreenColour(Quizz.isPass);
}
void Play_MathGame() {

	strQuizz Quizz;

	Quizz.NumberOfQuestions = Read_NumberOfQuestions(); cout << endl;
	Quizz.QuestionLevel = Read_QuestionLevel(); cout << endl;
	Quizz.OpType = Read_OperationType(); cout << endl;

	GenerateQuizzQuestions(Quizz);

	AskAndCorrect_QuestionsListAnswers(Quizz);
	Show_FinalResults(Quizz);
}

char DoUserNeed_ToPlayAgain() {
	char PlayAgain;
	cout << "Press [Y] To Play Again! | Or Press Any Key To Finish |~";
	cin >> PlayAgain;

	return PlayAgain;
}

void PlayLauncher(void);

void Start_MathGame() {

	char PlayAgain = 'Y';

	do {
		ResetScreen();

		Play_MathGame();

		PlayAgain = DoUserNeed_ToPlayAgain();

		if (PlayAgain == 'Y' || 'y')
		{
			ResetScreen();
			PlayLauncher();
		}

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

void ShowGameOverScreen()
{
	cout << Tabs(2) <<
		"__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e  O v e r  +++ \n"; 
		cout << Tabs(2) <<
		"__________________________________________________________\n\n";

}

void ShowFinalGameResults_VsCOMPUTER(strSPSGameInfo GameResults)
{
	cout << Tabs(2) << "_____________________ [ Game Results ] _____________________\n\n"; 
cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1_WonTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.COMPUTER_WonTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.FinalWinner_Name << endl;
	cout << Tabs(2) << "____________________________________________________________\n";

	SetScreenColour(GameResults.FinalWinner);
}

void ShowFinalGameResults_VsPlayer2(strSPSGameInfo GameResults)
{
	cout << Tabs(2) << "_____________________ [ Game Results ] _____________________\n\n";
	cout << Tabs(2) << "Game Rounds          : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player{1} won times  : " << GameResults.Player1_WonTimes << endl;
	cout << Tabs(2) << "Player{2} won times  : " << GameResults.Player2_WonTimes << endl;
	cout << Tabs(2) << "Draw times           : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner         : " << GameResults.FinalWinner_Name << endl;
	cout << Tabs(2) << "____________________________________________________________\n";

	SetScreenColour(GameResults.FinalWinner);
}

short ReadNumberOfRounds() {
	return ReadOnlyNumbers_InRange_Short_Version("Please ,Enter Number Of Game Rounds ,Do You Need ?   |~", 1, 10);
}

enSPS_Choices ReadPlayer1_Choice() {
	return (enSPS_Choices)ReadOnlyNumbers_InRange_Short_Version("Player1 Choice : {  [1]:Stone | [2]:Paper | [3]:Scissor  }  |~", 1, 3);
}

enSPS_Choices ReadPlayer2_Choice() {
	return (enSPS_Choices)ReadOnlyNumbers_InRange_Short_Version("Player2 Choice : {  [1]:Stone | [2]:Paper | [3]:Scissor  }  |~", 1, 3);
}

enSPS_Choices GetCOMPUTER_CHOICE() {
	return (enSPS_Choices)GetRandomNumber(1, 3);
}

enSPS_Winner WhoWonTheRound_SPS_VsCOMPUTER(strRoundInfo_SPS RoundInfo) {

	if (RoundInfo.Player1Choice == RoundInfo.COMPUTER_CHOICE)
		return enSPS_Winner::NO_Winner;

	switch (RoundInfo.Player1Choice)
	{

		case enSPS_Choices::Stone:
		{
			if (RoundInfo.COMPUTER_CHOICE == enSPS_Choices::Paper)
				return enSPS_Winner::COMPUTER;

			break;
		}

		case enSPS_Choices::Paper:
		{
			if (RoundInfo.COMPUTER_CHOICE == enSPS_Choices::Scissor)
				return enSPS_Winner::COMPUTER;

			break;
		}

		case enSPS_Choices::Scissor:
		{
			if (RoundInfo.COMPUTER_CHOICE == enSPS_Choices::Stone)
				return enSPS_Winner::COMPUTER;
		}

			
	}
	return enSPS_Winner::Player1;
}

enSPS_Winner WhoWonTheRound_SPS_VsPlayer2(strRoundInfo_SPS RoundInfo) {

	if (RoundInfo.Player1Choice == RoundInfo.Player2Choice)
		return enSPS_Winner::NO_Winner;

	switch (RoundInfo.Player1Choice)
	{

	case enSPS_Choices::Stone:
	{
		if (RoundInfo.Player2Choice == enSPS_Choices::Paper)
			return enSPS_Winner::Player2;

		break;
	}

	case enSPS_Choices::Paper:
	{
		if (RoundInfo.Player2Choice == enSPS_Choices::Scissor)
			return enSPS_Winner::Player2;

		break;
	}

	case enSPS_Choices::Scissor:
	{
		if (RoundInfo.Player2Choice == enSPS_Choices::Stone)
			return enSPS_Winner::Player2;
	}

	
	}
	return enSPS_Winner::Player1;
}

string Get_WinnerName(enSPS_Winner Winner) {

	string WinnerName[4] = { "Player 1","Player 2","COMPUTER","NO WINNER" };
	return WinnerName[Winner - 1];
} 

string Get_ChoiceName(enSPS_Choices Choice) {

	string ChoicesName[3] = { "Stone","Paper","Scissor" };
	return ChoicesName[Choice - 1];
}

enSPS_Winner Get_FinalWinner(strSPSGameInfo GameInfo) {

	if (GameInfo.COMPUTER_WonTimes == GameInfo.Player1_WonTimes || GameInfo.Player1_WonTimes == GameInfo.Player2_WonTimes)
		return enSPS_Winner::NO_Winner;
	else
	{
		if (GameInfo.COMPUTER_WonTimes > GameInfo.Player1_WonTimes) {
			if (GameInfo.COMPUTER_WonTimes > GameInfo.Player2_WonTimes) {
				return enSPS_Winner::COMPUTER;
			}
			else
				return enSPS_Winner::Player2;
		}

		else {
			if (GameInfo.Player1_WonTimes > GameInfo.Player2_WonTimes)
				return enSPS_Winner::Player1;
			else
				return enSPS_Winner::Player2;
		}
	}
}

void SetScreenColour_SPSGame(enSPS_Winner Winner) {
	switch (Winner)
	{
	case Player1:
		system("color 2F");
		break;
	case Player2:
		system("color 3F");
		break;
	case COMPUTER:
		system("color 4F");
		break;
	case NO_Winner:
		system("color 6F");
		break;
	}
}

void PrintSPS_RoundResults_VsCOM(strRoundInfo_SPS RoundInfo) {

	printf("\n_________________ Round [ %d ] _________________\n\n", RoundInfo.RoundNumber);
	cout << setw(17) << "Player1 Choice " << ':' << Get_ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << setw(17) << "COMPUTER CHOICE " << ':' << Get_ChoiceName(RoundInfo.COMPUTER_CHOICE) << endl;
	cout << setw(17) << "Round Winner " << ':' << Get_WinnerName(RoundInfo.RoundWinner) << endl;
	printf("________________________________________________\n\n");

	SetScreenColour_SPSGame(RoundInfo.RoundWinner);
}

void PrintSPS_RoundResults_VsPlayer2(strRoundInfo_SPS RoundInfo) {

	printf("\n_________________ Round [ %d ] _________________\n\n", RoundInfo.RoundNumber);
	cout << setw(17) << "Player1 Choice " << ':' << Get_ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << setw(17) << "Player2 Choice " << ':' << Get_ChoiceName(RoundInfo.Player2Choice) << endl;
	cout << setw(17) << "Round Winner " << ':' << Get_WinnerName(RoundInfo.RoundWinner) << endl;
	printf("________________________________________________\n\n");

	SetScreenColour_SPSGame(RoundInfo.RoundWinner);
}

strSPSGameInfo Fill_SPSGameInfo_WithData(short Player1_WonTimes,short DrawTimes ,short NumberOfRounds,short Player2_WonTimes=0, short COMPUTER_WonTimes = 0) {

	strSPSGameInfo GameInfo;

	GameInfo.GameRounds = NumberOfRounds;
	GameInfo.Player1_WonTimes = Player1_WonTimes;
	GameInfo.Player2_WonTimes = Player2_WonTimes;
	GameInfo.COMPUTER_WonTimes = COMPUTER_WonTimes;
	GameInfo.DrawTimes = DrawTimes;
	GameInfo.FinalWinner = Get_FinalWinner(GameInfo);
	GameInfo.FinalWinner_Name = Get_WinnerName(GameInfo.FinalWinner);

	return GameInfo;
}

strSPSGameInfo Play_SPSGame_Player2(short NumberOfRounds) {

	short DrawTimes = 0, Player2_WonTimes = 0, Player1_WonTimes = 0;
	
	strRoundInfo_SPS RoundInfo;
	for (short GameRound = 1; GameRound <= NumberOfRounds; GameRound++) {

		printf("Round [ %d ] Begins \n\n", GameRound);

		RoundInfo.RoundNumber = NumberOfRounds;
		RoundInfo.Player1Choice = ReadPlayer1_Choice();
		RoundInfo.Player2Choice = ReadPlayer2_Choice();
		RoundInfo.RoundWinner = WhoWonTheRound_SPS_VsPlayer2(RoundInfo);
		RoundInfo.WinnerName = Get_WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enSPS_Winner::NO_Winner)
			DrawTimes++;
		else if (RoundInfo.RoundWinner == enSPS_Winner::Player1)
			Player1_WonTimes++;
		else
			Player2_WonTimes++;

		PrintSPS_RoundResults_VsPlayer2(RoundInfo);
	}

	return Fill_SPSGameInfo_WithData(Player1_WonTimes,DrawTimes,NumberOfRounds,Player2_WonTimes);


}

strSPSGameInfo Play_SPSGame_COM(short NumberOfRounds) {

	short DrawTimes = 0, COMPUTER_WonTimes = 0, Player1_WonTimes = 0;

	strRoundInfo_SPS RoundInfo;
	for (short GameRound = 1; GameRound <= NumberOfRounds; GameRound++) {

		printf("Round [ %d ] Begins\n\n", GameRound);

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1_Choice();
		RoundInfo.COMPUTER_CHOICE = GetCOMPUTER_CHOICE();
		RoundInfo.RoundWinner = WhoWonTheRound_SPS_VsCOMPUTER(RoundInfo);
		RoundInfo.WinnerName = Get_WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enSPS_Winner::NO_Winner)
			DrawTimes++;
		else if (RoundInfo.RoundWinner == enSPS_Winner::Player1)
			Player1_WonTimes++;
		else
			COMPUTER_WonTimes++;

		PrintSPS_RoundResults_VsCOM(RoundInfo);
	}

	return Fill_SPSGameInfo_WithData(Player1_WonTimes, DrawTimes, NumberOfRounds,0,COMPUTER_WonTimes);

}
void Show_SPS_GameModes() {

	cout << NextLine(5) << Tabs(4) << "_____________________________________________________________" << endl;
	cout << Tabs(4)                << "|                                                           |" << endl;
	cout << Tabs(4)                << "|                         Game Modes                        |" << endl;
	cout << Tabs(4)                << "|___________________________________________________________|" << endl;
	cout << Tabs(4)                << "|                                                           |" << endl;
	cout << Tabs(4)                << "|          1 - [     V S   C O M P U T E R     ]            |" << endl;
	cout << Tabs(4)                << "|___________________________________________________________|" << endl;
	cout << Tabs(4)                << "|                                                           |" << endl;
	cout << Tabs(4)                << "|          2 - [   V S    P L  A Y E R  { 2 }   ]           |" << endl;
	cout << Tabs(4)                << "|___________________________________________________________|" << endl;
	cout << Tabs(4)                << "|                                                           |" << endl;
	cout << Tabs(4)                << "|          3 - [          B  A  C  K          ]             |" << endl;
	cout << Tabs(4)                << "|___________________________________________________________|" << "\n\n";
}

enSPS_GameEnemy AskPlayerWhat_SPSGameMode() {

	Show_SPS_GameModes();
	return (enSPS_GameEnemy)ReadOnlyNumbers_InRange_Short_Version("\t\t\t\t[ I Choose ? ]  |~", 1, 3);
}

void PlayGameMode(strSPSGameInfo &GameInfo) {
	

	GameInfo.GameEnemy = AskPlayerWhat_SPSGameMode();


		

	ResetScreen();

	short NumberOf_GameRounds;

	switch (GameInfo.GameEnemy)
	{
	case enSPS_GameEnemy::ECOMPUTER:
	{
		 NumberOf_GameRounds = ReadNumberOfRounds();
		GameInfo = Play_SPSGame_COM(NumberOf_GameRounds);
		ShowGameOverScreen();
		ShowFinalGameResults_VsCOMPUTER(GameInfo);
		break;
	}

	case enSPS_GameEnemy::EPlayer2:
	{
		 NumberOf_GameRounds = ReadNumberOfRounds();
		GameInfo = Play_SPSGame_Player2(NumberOf_GameRounds);
		ShowGameOverScreen();
		ShowFinalGameResults_VsPlayer2(GameInfo);
		break;
	}

	case enSPS_GameEnemy::Back: {

		break;
	}
	
	}
}

void Start_SPSGame() {

	strSPSGameInfo GameInfo;
	


	char PlayAgain = 'Y';

	do {
		ResetScreen();


		if (GameInfo.GameEnemy == enSPS_GameEnemy::Back)
		{
			PlayLauncher();
			break;
		}



		PlayGameMode(GameInfo);
		cout << NextLine(1) << Tabs(2);
		
		if (GameInfo.GameEnemy != enSPS_GameEnemy::Back)
			 PlayAgain = DoUserNeed_ToPlayAgain();

		
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

void FillMatrixArrayWithMultilplys(short Osama[10][10]) {

	for (short i = 0; i < 10; i++) {

		for (short j = 0; j < 10; j++) {

			Osama[i][j] = ((i + 1) * (j + 1));
		}
	}
}

#include <Windows.h>

void SetColour(short Colour_Code) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Colour_Code);
}

void PrintTableHeader()
{
	SetColour(12);
	cout << "\n\n\t\t\t Multipliaction Table From 1 to 10\n\n";
	cout << "\t";
	SetColour(10);
	for (int i = 1; i <= 10; i++)
	{
		Sleep(10); cout << i << "\t";
	}
	cout << "\n___________________________________________________________________________________\n";
	
}

string ColumSperator(int i)
{
	if (i < 10)
		return "   |";
	else
		return "  |";
}



void PrintMultiplicationTable(short Osama[10][10])
{
	PrintTableHeader();

	for (int i = 0; i < 10; i++) {
		SetColour(11);
		printf(" %d", (i + 1)); cout << ColumSperator(i + 1);

		for (int j = 0; j < 10; j++) {

			SetColour(9);
			Sleep(10);  printf("\t%0*d ", 2, Osama[i][j]);
		}
		cout << endl;
	}

}

void MultiplicationTable() {

	short MultiAolication[10][10];
	char PlayAgain = ' ';

	do {

		ResetScreen();

		if (PlayAgain != ' ')
			PlayLauncher();

		FillMatrixArrayWithMultilplys(MultiAolication);

		PrintMultiplicationTable(MultiAolication); cout << "\n\n";

		PlayAgain = DoUserNeed_ToPlayAgain();

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

enum enScreenColour { Red, Green, Blue, Yellow };

void XO_Logo() {

	cout << Tabs(2) << "---------------------------------" << NextLine(1);
	cout << Tabs(2) << "|         X O    G A M E        |" << NextLine(1);
	cout << Tabs(2) << "---------------------------------" << NextLine(1);
}

void ShowXO_Screen(char Place[9]) {

	cout << NextLine(3);

	
	XO_Logo();


	printf("\t\t\t     |     |     \n");
	printf("\t\t\t  %c  |  %c  |  %c \n", Place[0], Place[1], Place[2]);

	printf("\t\t\t_____|_____|_____\n");
	printf("\t\t\t     |     |     \n");

	printf("\t\t\t  %c  |  %c  |  %c \n", Place[3], Place[4], Place[5]);

	printf("\t\t\t_____|_____|_____\n");
	printf("\t\t\t     |     |     \n");

	printf("\t\t\t  %c  |  %c  |  %c \n", Place[6], Place[7], Place[8]);

	printf("\t\t\t     |     |     \n\n");



}

void PrintWinnerNameOfXO(enSPS_Winner Winner) {

	cout << "\n\t\t\t T H E   W I N N E R   I S  { - " << Get_WinnerName(Winner) << " - }";
}

bool IsSlotAvailable(char GameSlots[9], char Choice) {

	for (short i = 0; i < 9; i++) {

		if (GameSlots[i] == Choice)
			return true;
	}



	return false;
}

char GetComputerChoice(str_TicTacToe& TicTacToe) {

	char ComputerChoice = 'Y';

	cout << "\n\n\t\t\t\t\t < C O M P U T E R    T U R N  >";

	do {


		Sleep(300);
		ComputerChoice = (char)GetRandomNumber(1, 9) + 48;

	} while (!IsSlotAvailable(TicTacToe.Place, ComputerChoice));

	return ComputerChoice;

}

char ReadPlayer1Choice(str_TicTacToe& TicTacToe) {

	char Player1Choice = 'Y';

	do {
		ResetScreen();
		ShowXO_Screen(TicTacToe.Place);

		Player1Choice = (char)ReadOnlyNumbers_InRange_Short_Version("\n\n\t\t\t\t\t < Player { 1 }  Turn ", 1, 9) + 48;

	} while (!IsSlotAvailable(TicTacToe.Place, Player1Choice));

	return Player1Choice;
}

char ReadPlayer2Choice(str_TicTacToe& TicTacToe) {

	char Player2_Choice = 'Y';

	do {

		ResetScreen();
		ShowXO_Screen(TicTacToe.Place);

		Player2_Choice = ReadOnlyNumbers_InRange_Short_Version("\n\n\t\t\t\t\t < Player { 2 }  Turn ", 1, 9) + 48;

	} while (!IsSlotAvailable(TicTacToe.Place, Player2_Choice));

	return Player2_Choice;
}

short Turn_ToPlay(str_TicTacToe& TicTacToe) {

	switch (TicTacToe.Turn)
	{
	case enTurn::Computer:
		return GetComputerChoice(TicTacToe);
		break;

	case enTurn::Player:
		return ReadPlayer1Choice(TicTacToe);
		break;

	case enTurn::pPlayer2:
		return ReadPlayer2Choice(TicTacToe);

	}

}

bool Win(char GameSlots[9]) {


	for (short i = 0; i < 9; i += 3) {
		if ((GameSlots[i] == GameSlots[i + 2]) && (GameSlots[i] == GameSlots[i + 1]))
			return true;
	}

	for (short j = 0; j < 3; j++) {
		if ((GameSlots[j] == GameSlots[j + 3]) && (GameSlots[j] == GameSlots[j + 6]))
			return true;
	}

	if ((GameSlots[0] == GameSlots[4]) && (GameSlots[0] == GameSlots[8]))
		return true;

	if ((GameSlots[2] == GameSlots[4]) && (GameSlots[2] == GameSlots[6]))
		return true;

	
	return false;
}

enTurn ChangeTurn_Vs_Computer(enTurn Turn) {

	switch (Turn)
	{
	case Computer:
		return enTurn::Player;
	case Player:
		return enTurn::Computer;

	}

}

enTurn ChangeTurn_Vs_Player2(enTurn Turn) {

	switch (Turn)
	{
	case pPlayer2:
		return enTurn::Player;
	case Player:
		return enTurn::pPlayer2;

	}

}

void SetGameSlot(str_TicTacToe& TicTacToe) {

	switch (TicTacToe.X_O_Letter)
	{
	case X:
		TicTacToe.Place[Turn_ToPlay(TicTacToe) - 1 - 48] = 'X';
		break;
	case O:
		TicTacToe.Place[Turn_ToPlay(TicTacToe) - 1 - 48] = 'O';

	}
}

enChoice_X_O ChangeLetter(enChoice_X_O& Choice) {

	switch (Choice)
	{
	case enChoice_X_O::X:
		return enChoice_X_O::O;

	case enChoice_X_O::O:
		return enChoice_X_O::X;
	}


}

void SetColourScreen(enScreenColour Colour) {

	switch (Colour)
	{
	case Yellow:
		system("color 6E");
		break;
	case Red:
		system("color 4F");
		break;
	case Green:
		system("color 2F");
		break;
	case Blue:
		system("color 1F");
		break;

	}
}

void SetWinnerColour(enSPS_Winner Winner) {

	switch (Winner)
	{

	case enSPS_Winner::NO_Winner:
		SetColourScreen(enScreenColour::Yellow);
		break;

	case enSPS_Winner::COMPUTER:
		SetColourScreen(enScreenColour::Red);
		break;
	case enSPS_Winner::Player1:
		SetColourScreen(enScreenColour::Green);
		break;
	case enSPS_Winner::Player2:
		SetColourScreen(enScreenColour::Blue);
		break;


	}

}

enSPS_Winner TheWinnerInXO(enTurn Turn) {

	switch (Turn)
	{
	case Computer:
		return enSPS_Winner::COMPUTER;

	case Player:
		return enSPS_Winner::Player1;

	case pPlayer2:
		return enSPS_Winner::Player2;

	default:
		return enSPS_Winner::NO_Winner;
	}

}

void Run_XOGame_Vs_Computer() {

	str_TicTacToe TicTacToe;

	TicTacToe.Turn = (enTurn)GetRandomNumber(0, 1);
	TicTacToe.X_O_Letter = (enChoice_X_O)GetRandomNumber(0, 1);

	for (short Rounds = 1; Rounds <= 9; Rounds++) {

		TicTacToe.Turn = ChangeTurn_Vs_Computer(TicTacToe.Turn);

		ResetScreen();

		ShowXO_Screen(TicTacToe.Place);

		SetGameSlot(TicTacToe);

		TicTacToe.X_O_Letter = ChangeLetter(TicTacToe.X_O_Letter);

		TicTacToe.IsWin = Win(TicTacToe.Place);

		if (TicTacToe.IsWin) {

			TicTacToe.Winner = TheWinnerInXO(TicTacToe.Turn);

			ResetScreen();
			ShowXO_Screen(TicTacToe.Place);

			SetWinnerColour(TicTacToe.Winner);

			break;
		}

	}

	if (TicTacToe.IsWin == false) {

		TicTacToe.Winner = enSPS_Winner::NO_Winner;

		ResetScreen();
		ShowXO_Screen(TicTacToe.Place);

		SetWinnerColour(enSPS_Winner::NO_Winner);
	}

	PrintWinnerNameOfXO(TicTacToe.Winner);

}

void Run_XOGame_Vs_Player2() {

	str_TicTacToe TicTacToe;

	TicTacToe.Turn = (enTurn)GetRandomNumber(1, 2);
	TicTacToe.X_O_Letter = (enChoice_X_O)GetRandomNumber(0, 1);

	for (short Rounds = 1; Rounds <= 9; Rounds++) {

		TicTacToe.Turn = ChangeTurn_Vs_Player2(TicTacToe.Turn);

		ResetScreen();

		ShowXO_Screen(TicTacToe.Place);

		SetGameSlot(TicTacToe);

		TicTacToe.X_O_Letter = ChangeLetter(TicTacToe.X_O_Letter);

		TicTacToe.IsWin = Win(TicTacToe.Place);
		if (TicTacToe.IsWin) {

			TicTacToe.Winner = TheWinnerInXO(TicTacToe.Turn);

			ResetScreen();
			ShowXO_Screen(TicTacToe.Place);

			SetWinnerColour(TicTacToe.Winner);

			break;
		}

	}

	if (TicTacToe.IsWin == false) {

		TicTacToe.Winner = enSPS_Winner::NO_Winner;

		ResetScreen();
		ShowXO_Screen(TicTacToe.Place);

		SetWinnerColour(enSPS_Winner::NO_Winner);
	}

	PrintWinnerNameOfXO(TicTacToe.Winner);

}

void Run_XOGame() {




	char PlayAgain = 'Y';


	do {

		ResetScreen();


		enSPS_GameEnemy Enemy = AskPlayerWhat_SPSGameMode();



		if (Enemy == enSPS_GameEnemy::Back)
		{
			ResetScreen();
			PlayLauncher();
			break;
		}


		switch (Enemy)
		{
		case EPlayer2:
			Run_XOGame_Vs_Player2();
			break;

		case ECOMPUTER:
			Run_XOGame_Vs_Computer();

		}

		cout <<"\a" << NextLine(2) << Tabs(4);

		PlayAgain = DoUserNeed_ToPlayAgain();

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}






enum enGames { SPS = 1, MathGame = 2 , XO_Game , MultiTable};

struct strLauncher {

	enGames SelectedGame;
};

enGames ReadGameChoice() {

	return (enGames)ReadOnlyNumbers_InRange_Short_Version("\t\t\t\tI Choose |~", 1, 4);
}

void Run_SelectedGame(strLauncher Launcher) {


	

	switch (Launcher.SelectedGame)
	{
	case enGames::SPS: {
		Start_SPSGame();
		break;
	}

	case enGames::MathGame: {
		Start_MathGame();
		break;
	}

	case enGames::XO_Game: {
		Run_XOGame();
		break;
	}

	case enGames::MultiTable: {
		MultiplicationTable();
		break;
	}
	}
}

void Show_LauncherGames() {

	cout << "Made With Love By [ Osama Thabit ]";
	cout << NextLine(5);
	cout << Tabs(4) << "________________________________________________________________" << endl;
	cout << Tabs(4) << "|          |                                                   |" << endl;
	cout << Tabs(4) << "|  Number  |            G A M E S   L I S T                    |" << endl;
	cout << Tabs(4) << "|__________|___________________________________________________|" << endl;
	cout << Tabs(4) << "|          |                                                   |" << endl;
	cout << Tabs(4) << "|     1    |       [     Stone  , Paper , Scissor     ]        |" << endl;
	cout << Tabs(4) << "|__________|___________________________________________________|" << endl;
	cout << Tabs(4) << "|          |                                                   |" << endl;
	cout << Tabs(4) << "|     2    |          [     M A T H   G A M E     ]            |" << endl;
	cout << Tabs(4) << "|__________|___________________________________________________|" << endl;
	cout << Tabs(4) << "|          |                                                   |" << endl;
	cout << Tabs(4) << "|     3    |         [     T I C   T A C   T O E     ]         |" << endl;
	cout << Tabs(4) << "|__________|___________________________________________________|" << endl;
	cout << Tabs(4) << "|          |                                                   |" << endl;
	cout << Tabs(4) << "|     4    |  [   M U L T I P L I C A T I O N   T A B L E   ]  |" << endl;
	cout << Tabs(4) << "|__________|___________________________________________________|" << "\n\n";
}

void PlayLauncher() {

	strLauncher Launcher;

	Show_LauncherGames();

	Launcher.SelectedGame = ReadGameChoice();

	Run_SelectedGame(Launcher);

}


int main(void) {

	srand((unsigned)time(NULL));
	
	PlayLauncher();
	
	return 0;
}


