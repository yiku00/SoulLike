// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include <random>

UGameManager* UGameManager::GameManagerInstance = nullptr;

UGameManager* UGameManager::GetInstance()
{
    if (!GameManagerInstance)
    {
        GameManagerInstance = NewObject<UGameManager>();
        GameManagerInstance->AddToRoot();  // ������ �÷������κ��� �ν��Ͻ� ��ȣ
    }
    return GameManagerInstance;
}

UGameManager::UGameManager()
{
    // �ʱ�ȭ �ڵ�
}

float UGameManager::GetRandomFloatInRange(float Min, float Max)
{
    static std::default_random_engine Generator;
    std::uniform_real_distribution<float> Distribution(Min, Max);
    return Distribution(Generator);
}