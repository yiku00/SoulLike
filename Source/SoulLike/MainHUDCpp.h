// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include "MainHUDCpp.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API UMainHUDCpp : public UUserWidget
{
	GENERATED_BODY()

protected:
	class ASoulLikeCharacter* OwningPawn;
protected:
	virtual void NativeConstruct();
	virtual void BeginDestroy();
	virtual void NativeTick(const FGeometry& MyGeometry,float dt);
public:

};
