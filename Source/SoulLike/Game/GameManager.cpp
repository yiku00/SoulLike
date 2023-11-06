// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include <random>

UGameManager* UGameManager::GameManagerInstance = nullptr;

UGameManager* UGameManager::GetInstance()
{
    if (!GameManagerInstance)
    {
        GameManagerInstance = NewObject<UGameManager>();
        GameManagerInstance->AddToRoot();  // 가비지 컬렉션으로부터 인스턴스 보호
    }
    return GameManagerInstance;
}

UGameManager::UGameManager()
{
    // 초기화 코드
}

float UGameManager::GetRandomFloatInRange(float Min, float Max)
{
    static std::default_random_engine Generator;
    std::uniform_real_distribution<float> Distribution(Min, Max);
    return Distribution(Generator);
}