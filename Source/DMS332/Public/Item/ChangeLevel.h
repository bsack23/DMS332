// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// clang-format off

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "ChangeLevel.generated.h"

/**
 *
 */
UCLASS()
class DMS332_API AChangeLevel : public AItem {
  GENERATED_BODY()
  // Make a constructor because we wanna set default values in cpp
  AChangeLevel();
protected:
  virtual void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult) override;

 // properties so we can assign different levels in BP child class
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Parameters")
FName CurrLevel;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Parameters")
FName ToLevel;
};
