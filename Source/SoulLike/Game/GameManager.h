// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameManager.generated.h"

#define DT_PATH "/Game/DataTable/"

/**
 * 
 */

UCLASS()
class SOULLIKE_API UGameManager : public UObject
{
	GENERATED_BODY()
public:
    // �̱��� �ν��Ͻ� ���
    static UGameManager* GetInstance();

    // �������� ���� �޼����
    float GetRandomFloatInRange(float Min, float Max);

private:
    // �̱��� �ν��Ͻ� ����
    static UGameManager* GameManagerInstance;

    // �����ڸ� ������� ����ϴ�.
    UGameManager();
};
