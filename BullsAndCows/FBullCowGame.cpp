#include "FBullCowGame.h"
#include <map>

#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()
{
    Reset();
}

int32 FBullCowGame::getCurrentTry() const
{
    return mMyCurrentTry;
}
int32 FBullCowGame::getHiddenWordLength() const
{
    return static_cast<unsigned>(mMyHiddenWord.length());
    
}
bool FBullCowGame::isGameWon() const
{
    return mbGameIsWon;
    
}

int32 FBullCowGame::getMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
    return WordLengthToMaxTries[static_cast<unsigned>(mMyHiddenWord.length())];
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    mMyHiddenWord = HIDDEN_WORD;
    
    mMyCurrentTry = 1;
    mbGameIsWon = false;
    return;
}

eGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!mIsIsogram(Guess))
    {
        return eGuessStatus::NotIsogram;
    }
    else if (!mIsLowercase(Guess))
    {
        return eGuessStatus::NotLowercase;
    }
    else if (Guess.length() != getHiddenWordLength())
    {
        return eGuessStatus::WrongLength;
    }
    else
    {
        return eGuessStatus::OK;
    }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    mMyCurrentTry += 1;
    FBullCowCount BullCowCount;
    int32 WordLength = static_cast<unsigned>(mMyHiddenWord.length());
    
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar += 1)
    {
        for (int32 GChar = 0; GChar < WordLength; GChar += 1)
        {
            if (Guess[GChar] == mMyHiddenWord[MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls += 1;
                }
                else
                {
                    BullCowCount.Cows += 1;
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength)
    {
        mbGameIsWon = true;
    }
    else
    {
        mbGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::mIsIsogram(FString Word) const
{
    if (Word.length() <= 1)
    {
        return true;
    }
    
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter])
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::mIsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}
