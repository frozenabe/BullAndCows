//
//  main.cpp
//  BullsAndCows learned from Udemy
//
//  Created by Abraham Kim on 10/22/17.
//  Copyright © 2017 Abraham Kim. All rights reserved.
//
#include <iostream>
#include <string>

#include "FBullCowGame.h"

// Unreal friendly syntax
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while(bPlayAgain);
    
    return 0;
}

void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, an awkwardly fun game.\n";
    std::cout << "           }   {           ^__^           " << std::endl;
    std::cout << "           (o o)          (o  o)          " << std::endl;
    std::cout << "   /--------\\ /            \\  /-------\\" << std::endl;
    std::cout << "  / |  BULL |o    Abe Kim   oo| COW  |//   " << std::endl;
    std::cout << " *  |-,-----|                 |------|*   " << std::endl;
    std::cout << "    |       |                 |      |    " << std::endl;
    std::cout << "    ^       ^                 ^      ^    " << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
    std::cout << " letter isogram I am thinking of?\n";
    std::cout << std::endl;

    return;
}

void PlayGame()
{
    BCGame.Reset();
    int MaxTries = BCGame.getMaxTries();
    
    while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= MaxTries)
    {
        std::string Guess = GetValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    return;
}

//Loop till valid guess
std::string GetValidGuess()
{
    FText Guess = "";
    eGuessStatus Status = eGuessStatus::InvalidStatus;
    do
    {
        int32 CurrentTry = BCGame.getCurrentTry();
        std::cout << "Try " << CurrentTry << " of" << BCGame.getMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case eGuessStatus::WrongLength:
                std::cout << "please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
                break;
            case eGuessStatus::NotIsogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            case eGuessStatus::NotLowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
            default:
                break;
        }
    }
    while (Status != eGuessStatus::OK);
    
    return Guess; 
}

bool AskToPlayAgain()
{
    std::cout << "Do you wish to continue with same hidden word (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    (BCGame.isGameWon()) ? std::cout << "You won!\n" : std::cout << "Try again\n";
}
