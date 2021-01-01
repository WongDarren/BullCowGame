// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &PlayerInput) // When the player hits enter
{

    // if the game is over then ClearScreen and SetupGame
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // checking player guess
    {
        ProcessGuess(PlayerInput);
    }
}

// ++++++++++++++++++++++++++++++++++++++++
// |              Setup Game              |
// ++++++++++++++++++++++++++++++++++++++++
void UBullCowCartridge::SetupGame()
{
    // Welcome player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    // PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); // debug line
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess. \nPress enter to continue"));

    // const TCHAR HW[] = TEXT("plums");
    // PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    // PrintLine(TEXT("Character 4 of HW is: %c"), HW[3]);
}

// ++++++++++++++++++++++++++++++++++++++++
// |                End Game              |
// ++++++++++++++++++++++++++++++++++++++++
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

// ++++++++++++++++++++++++++++++++++++++++
// |           Process Guess              |
// ++++++++++++++++++++++++++++++++++++++++
void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (HiddenWord == Guess)
    {
        PrintLine(TEXT("YOU WIN"));
        EndGame();
        return;
    }

    if (HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again!\nYou have %i lives remaining"), Lives);
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    --Lives;
    PrintLine(TEXT("You have lost a life."));

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left."));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    // Show the player bulls and cows
    FBullsCowsCount Score = GetBullsCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

// ++++++++++++++++++++++++++++++++++++++++
// |          Check if isogram            |
// ++++++++++++++++++++++++++++++++++++++++
bool UBullCowCartridge::IsIsogram(const FString &Word) const
{

    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
                return false;
        }
    }

    return true;
}

// ++++++++++++++++++++++++++++++++++++++++
// |          Get valid words             |
// ++++++++++++++++++++++++++++++++++++++++
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8)
            if (IsIsogram(Word))
                ValidWords.Emplace(Word);
    }

    return ValidWords;
}

// ++++++++++++++++++++++++++++++++++++++++
// |         Get Bulls and Cows           |
// ++++++++++++++++++++++++++++++++++++++++
FBullsCowsCount UBullCowCartridge::GetBullsCows(const FString &PlayerGuess) const
{

    FBullsCowsCount Count;

    for (int32 i = 0; i < PlayerGuess.Len(); i++)
    {
        if (HiddenWord[i] == PlayerGuess[i])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 j = 0; j < HiddenWord.Len(); j++)
        {
            if (PlayerGuess[i] == HiddenWord[j])
            {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}