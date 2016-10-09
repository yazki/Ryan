/*  This is console executable, that makes use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all user interaction.
	For game logic see the BullCowGame class
*/

#include <iostream>
#include <string>  //sting과 관련된 것 포함 시킴
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;		   // 언리얼 표준에 맞게 int를 int32로

void PrintIntro(); //게임 소개 함수 정의
void PlayGame();
FText GetValidGuess(); //플레이어 추측 함수 정의 그리고 컨트롤 + R 로 함수나 변수 선언된거 모든 코드에 쉽게 변환 가능하다.
bool AskToPlayAgain();  //다시 플레이 할꺼냐 말꺼냐를 물어볼려고 하는 것이니까 불리언 사용
void PrintGameSummary(); //게임 서머리

FBullCowGame BCGame; //첫번째 Instantiate a new game //FBullCowGame 이라는 헤더의 Class를 BCGame이라고 정의 

//프로그램의 실제 실행 지점.
int main() {

	bool bplayAgain = false; //While에 넣어서 반복문 설정 하기 위한 불리언 선언

	do	{
	      PrintIntro(); // 게임 소개 함수 호출
	      PlayGame();
		  bplayAgain = AskToPlayAgain();
	} 
	while (bplayAgain);

	return 0;
}


// 게임 소개 함수 선언
void PrintIntro() {
	std::cout << std::endl << std::endl;
	std::cout << "⊂_\n";
	std::cout << " ＼＼   Λ＿Λ\n";
	std::cout << "   ＼ ＼('ㅅ')  두둠칫\n";
	std::cout << "       >  ⌒、\n";
	std::cout << "      /   へ ＼\n";
	std::cout << "     /   /  ＼ ＼\n";
	std::cout << "    /   ノ    ＼ _つ\n";
	std::cout << "   /  / 두둠칫\n";
	std::cout << "  /  / |\n";
	std::cout << " ((  ＼\n";
	std::cout << "  | | 、＼\n";
	std::cout << "  | |  ＼⌒)\n";
	std::cout << "  | |   ) /\n";
	std::cout << "(`ノ)　L/\n";
	std::cout << std::endl << "\n재밌는 단어 연상 <<Bulls and Cows>> 게임에 오신걸 환영합니다!!^^!\n" << std::endl;
	std::cout << "제가 생각하는 [" << BCGame.GetHiddenWordLength() << "] 글자의 단어는 무엇일까요? ㅇㅅㅇ\n" << std::endl;
	std::cout << "참고로 반복되는 글자(EX: aaa 나 aab와 같은)는 아닙니다\n";
	return;
}


//  플레이어 추측 함수 5번 반복
void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries(); //위에 정의한 BCGame이라는 곳에 GetMaxTries라는 변수로 대입
	
	std::cout << "최대 "<< MaxTries <<"회 까지 시도 가능 합니다."<< std::endl;
	
	//loop for the number of turns asking for guesses
	//is not won and there are still tries remaining
	while ( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){	// 앞에 !는 Not 임 &&는 and고
		FText Guess = GetValidGuess();
		
		
		//Submit valid guess to the game,and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		//print number of bulls and cows
		std::cout << "황소 = " << BullCowCount.Bulls;
		std::cout << "젖소 = " << BullCowCount.Cows << "\n\n";

	}

	PrintGameSummary();		// Summarise game end
	return;
}


// loop continually until the user gives a valid guess
// 플레이어의 추측 함수 
FText GetValidGuess()
{
	FText Guess = "";   //string 변수 Guess 선언
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do{
		//get a guess from the player 
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		
		std::cout << "\n현재 [" << MaxTries << "]번 중 [" << CurrentTry << "]번째 시도입니다.\n" << std::endl;
		std::cout << "추측한 단어를 입력해 주세요~ :";
		std::getline(std::cin, Guess);   //***cin >> Guess; ****cin을 사용하면 스페이스바로 띄운 걸 읽지 못한다. 때문에 대체하는 것으로 getline()을 사용할 것이다. 
	
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)	{
		case EGuessStatus::Wrong_Length:
			std::cout << "잘못되었습니다. 올바른 " << BCGame.GetHiddenWordLength() << "글자의 단어를 입력하세요.\n\n";
			break;
		
		case EGuessStatus::Not_Isogram:
			std::cout << "반복 없는 단어를 입력하세요.\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "소문자만 입력하세요.\n\n";
			break;

		default : 
			// assume the guess is valid 
			break;
			 }
	} while (Status != EGuessStatus::OK);  //keep looping until we get no errors
	return Guess;		//String 함수는 변수 값 반환해야만 한다. 그래서 문자열 변수 Guess 반환 해 준다.
}

bool AskToPlayAgain(){  //마우스 오른쪽 퀵 액션에서 함 쩐당!

	std::cout << "다시 플레이 하실래요 ㅇㅅㅇ?  [Y 또는 Yes / N 또는 No] 입력해 주세요\n"; 
	FText Response = "";
	std::getline(std::cin, Response);
    std::cout << std::endl;

	return  (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "축하합니다 당신이 이겼어요 -ㅂ-\n";
	}

	else
	{
		std::cout << "운이 나빴어요ㅋㅋㅋㅋ. 다음엔 이길 수 있을거에요 ㅇㅅㅇㅋㅋㅋㅋ\n";
	}
}
