#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {	Reset(); }	//default construct 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,9}, {6,14}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];

}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "hotel";
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if ( ! IsIsogram(Guess))		//if (false)  // if the guess isn`t an isogram(����ٸ����ĺ������̷�������� ex)sadf)    // return error
	{
		return EGuessStatus::Not_Isogram;	 // TODO write function
	}
	else if ( ! IsLowercase(Guess))	// if the guess isn`t all lowercase(�ҹ���)		// return error
	{
		return EGuessStatus::Not_Lowercase;		 // TODO write function
	}	
	else if (Guess.length() != GetHiddenWordLength())	// if the guess length is wrong			// return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else	// otherwise		// return ok
	{
		return EGuessStatus::OK;
	}
		
}


// ��ȿ�� ������ �޾ƿ;� �Ѵ�. increments turn, returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	//setup a return variable 
	FBullCowCount BullCowCount;

	//loop through all letter in the guess
	int32 WordLenght = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) {
		
		// compare letter against the hidden word
		for (int32 GChar = 0; GChar < WordLenght; GChar++){
			
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]){
				
				//if they`re in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;   // incriment bulls
				}
				else {
					BullCowCount.Cows++; //else 	// incriment cow   //Must be Cow
				}

				
			}
		}
	}

	if(BullCowCount.Bulls == WordLenght){
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//�Է°��� ���ų�, �ѱ���¥���� isogram���� ���϶�. //treat 0 and 1 letter word as isogram
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;	// setup our map  // // map<key�ڷ���, value�ڷ���> ������ 
	
	for (auto Letter : Word)		// for all letters of the word  // ������ ��� �ܾ ����Ͽ� �ݺ�	//������� for ��		
	{
		
		Letter = tolower(Letter);	//handle mixed case  //tolower()�� c�� ���̺귯�� �Լ� -> ���״�� �ҹ��ڷ� �ٲ��� 
		
		if (LetterSeen[Letter]) {	//if the letter is in the map : LetterSeen���� ���ǵ� �ʿ� �迭 ������ 	/-->/ ���� map�� ���ڰ� �ִٸ�		// if the letters in the map
			
			return false;	//we do not have an isogram		//�츮�� isogram�� ����		// we Do Not have isogram
		
		}else{			 // �׷��� �ʴٸ�						// otherwise
			LetterSeen[Letter] = true;			// add letter to the map as seen
		}
		
	}
	return true;	// for example in case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if ( ! islower(Letter))		// ���� �ҹ��� �ƴҶ�	//islower() �� C ���̺귯�� �Լ�
		{
			return false;
		}
		
	}
	return true;
}

