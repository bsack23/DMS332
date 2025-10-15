// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BaseAnimInstance.h"
#include "Characters/BaseCharacter.h"
// for GetCharacterMovement
#include "GameFramework/CharacterMovementComponent.h"
// for Kismet - see VSizeXY below
#include "Kismet/KismetMathLibrary.h"

// initialize animation - runs once
void UBaseAnimInstance::NativeInitializeAnimation() {
  Super::NativeInitializeAnimation();
  // variables declared in .h
  // cast from Pawn returned by TryGetPawnOwner to Character
  BaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
  if (BaseCharacter) { // if cast is successful
    // get the Character Movement property
    // and set our CharacterMovement
    BaseCharacterMovement = BaseCharacter->GetCharacterMovement();
  }
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaTime) {
  // loop continually updating animations
  Super::NativeUpdateAnimation(DeltaTime);
  if (BaseCharacterMovement) {
    // set our variables from CharacterMovement
    // get the GroundSpeed float from the Velocity property
    GroundSpeed = UKismetMathLibrary::VSizeXY(BaseCharacterMovement->Velocity);
    // get the value of the IsFalling boolean
    IsFalling = BaseCharacterMovement->IsFalling();
  }
}
