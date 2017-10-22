#pragma once

#include <string>

// Unreal friendly syntax
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class eGuessStatus
{
    InvalidStatus,
    OK,
    NotIsogram,
    NotLowercase,
    WrongLength,
};

class FBullCowGame
{
public:
    FBullCowGame(); // constructor
    
    int getMaxTries() const;
    int getCurrentTry() const;
    int getHiddenWordLength() const;
    bool isGameWon() const;
    eGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 mMyCurrentTry;
    FString mMyHiddenWord;
    bool mbGameIsWon;
    
    bool mIsIsogram(FString) const;
    bool mIsLowercase(FString) const;
};
