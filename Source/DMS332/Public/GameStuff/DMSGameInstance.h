// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// clang-format off
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DMSGameInstance.generated.h"

/**
 *
 */
UCLASS()
class DMS332_API UDMSGameInstance : public UGameInstance {
  GENERATED_BODY()

protected:
  UPROPERTY(BlueprintReadWrite)
  int32 Coins;
};
