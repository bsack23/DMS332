// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// clang-format off
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DMSSaveGame.generated.h"

/**
 *
 */
UCLASS()
class DMS332_API UDMSSaveGame : public USaveGame {
  GENERATED_BODY()
  public:
  //  we need to be able to write to this, too?
  UPROPERTY(BlueprintReadWrite)
  FTransform PlayerTransform;
};
