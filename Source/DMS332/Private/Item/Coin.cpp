// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Coin.h"
#include "Characters/BaseCharacter.h"

void ACoin::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                           class AActor *OtherActor,
                           class UPrimitiveComponent *OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep,
                           const FHitResult &SweepResult) {
  // use Super to call version of this func from parent class (Item)
  Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex,
                        bFromSweep, SweepResult);

  // cast from MyCharacter class so we can move the character
  ABaseCharacter *BaseCharacter = Cast<ABaseCharacter>(OtherActor);
  // check for valid Character
  if (BaseCharacter) {
    // increase coin count here
    BaseCharacter->SetCoins();
    // destroy the class instance - bye bye!
    Destroy();
  }
}