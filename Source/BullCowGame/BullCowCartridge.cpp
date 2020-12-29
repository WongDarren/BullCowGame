// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); // debug line
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    // if the game is over then ClearScreen and SetupGame
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // checking player guess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcome player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess. \nPress enter to continue"));

    // const TCHAR HW[] = TEXT("plums");
    // PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    // PrintLine(TEXT("Character 4 of HW is: %c"), HW[3]);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
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

    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word)
{
    // check each Guess character
    // if they are all unique,
    // return true

    // else return false
    return true;
}