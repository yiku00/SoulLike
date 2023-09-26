// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UGameManager : public UObject
{
	GENERATED_BODY()
public:
    // 싱글턴 인스턴스 얻기
    static UGameManager* GetInstance();

    // 여러분의 범용 메서드들
    float GetRandomFloatInRange(float Min, float Max);

private:
    // 싱글턴 인스턴스 저장
    static UGameManager* GameManagerInstance;

    // 생성자를 비공개로 만듭니다.
    UGameManager();
};
