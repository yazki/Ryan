#pragma once
#include <string>

using FString = std::string;  //�𸮾� �ڵ忡 �ͼ������� ���� �ٲٴ� �۾�
using int32 = int;

//all values initialize to 0 
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:

	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; //TODO Make more Rich return Value

	void Reset();  //TODO Make more Rich return Value
	
	
    //SomeNewType SubmitValidGuess() 
	//->1. Provid a method for counting bulls & cows, and increasing try turn #number  //2. ��ȿ�� ������ �����Ѵ�->�Լ� �����ϱ�
	FBullCowCount SubmitValidGuess(FString);



//Please try and ignore this and focus on the interface above 
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};