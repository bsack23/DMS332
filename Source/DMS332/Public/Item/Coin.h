// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// turn off annoying vscode reordering of include files
// clang-format off
#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Coin.generated.h"

/**
 *
 */
UCLASS()
class DMS332_API ACoin : public AItem {
  GENERATED_BODY()
protected:
  virtual void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult) override;
};
