// Fill out your copyright notice in the Description page of Project Settings.

// make this header file first - for UE 5.7?
#include "Item/ChangeLevel.h"
#include "Characters/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

// constructor cannot have a return type!
AChangeLevel::AChangeLevel() {
  RotationRate = 0.f;
  SineAmplitude = 0.f;
}
void AChangeLevel::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
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
    UWorld *TheWorld = GetWorld();

    FString CurrentLevel = TheWorld->GetMapName();

    if (CurrentLevel == CurrLevel) {
      UGameplayStatics::OpenLevel(TheWorld, ToLevel);
    } else {
      UGameplayStatics::OpenLevel(TheWorld, CurrLevel);
    }
  }
}