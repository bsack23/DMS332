// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// turn off annoying vscode reordering of include files
// clang-format off
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "BaseAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class DMS332_API UBaseAnimInstance : public UAnimInstance {
  GENERATED_BODY()

public:
  // these are the analogs to the core BP nodes
  virtual void NativeInitializeAnimation() override;
  virtual void NativeUpdateAnimation(float DeltaTime) override;
  // make a pointer to BaseCharacter - forward declared with class keyword
  // BlueprintReadOnly so we can use it in the event graph
  UPROPERTY(BlueprintReadOnly)
  class ABaseCharacter *BaseCharacter;
  // make a movement component - also forward declared
  UPROPERTY(BlueprintReadOnly, Category = Movement)
  class UCharacterMovementComponent *BaseCharacterMovement;
  // plain old variables
  // 1. how fast are we going?
  UPROPERTY(BlueprintReadOnly, Category = Movement)
  float GroundSpeed;
  // 2. are we falling through the air?
  UPROPERTY(BlueprintReadOnly, Category = Movement)
  bool IsFalling;
  
  UPROPERTY(BlueprintReadOnly, Category = "Movement | Character Types")
  ECharacterState CharacterState;
};
