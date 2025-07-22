#include "AudioManager.h"


AAudioManager* AAudioManager::Instance = nullptr;

void AAudioManager::BeginPlay()
{
    Super::BeginPlay();
    AAudioManager::Instance = this;
}