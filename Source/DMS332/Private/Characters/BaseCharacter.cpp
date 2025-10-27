// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
// headers for camera and arm
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// headers for input stuff
// make sure that EnhancedInput is added to DMS332.Build.cs before this include
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
// for GetCharacterMovement() below
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Create a camera boom (pulls in towards the player if there is a collision)
  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
  SpringArm->SetupAttachment(GetRootComponent());
  SpringArm->TargetArmLength =
      400.0f; // The camera follows at this distance behind the character

  // Create a follow camera
  ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
  ViewCamera->SetupAttachment(SpringArm);
  // different from Bird class
  SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the
  // controller
  ViewCamera->bUsePawnControlRotation = false; // Camera does not
  // rotate relative to arm
  /**
   * from CharacterMovementComponent.h
   * If true, smoothly rotate the Character toward the Controller's desired
   * rotation (typically Controller->ControlRotation), using RotationRate as the
   * rate of rotation change. Overridden by OrientRotationToMovement. Normally
   * you will want to make sure that other settings are cleared, such as
   * bUseControllerRotationYaw on the Character.
   */
  GetCharacterMovement()->bUseControllerDesiredRotation = true;
  GetCharacterMovement()->bIgnoreBaseRotation = true;
  GetCharacterMovement()->bOrientRotationToMovement = true;
  // Character moves in the direction of input...
  GetCharacterMovement()->RotationRate =
      FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
  // set slow walk speed for this particular animation
  GetCharacterMovement()->MaxWalkSpeed = 150.0;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay() {
  Super::BeginPlay();
  // Add Input Mapping Context - named CharacterMappingContext
  if (APlayerController *PlayerController =
          Cast<APlayerController>(GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(CharacterMappingContext, 0);
    }
    // from Pawn.h: if true, this Pawn's pitch (yaw) will be updated to match
    // the Controller's ControlRotation pitch (yaw), if controlled by a
    // PlayerController.
    // pitch is up/down
    bUseControllerRotationPitch = true;
    // yaw is right/left
    // set to false so we can pan around character
    bUseControllerRotationYaw = false;
  }
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ABaseCharacter::Move(const FInputActionValue &Value) {
  // use the direction keys (w a s d) AND the mouse orientation
  const FVector2D MovementVector = Value.Get<FVector2d>();
  const FRotator Rotation = Controller->GetControlRotation();
  const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
  const FVector ForwardDirection =
      FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
  AddMovementInput(ForwardDirection, MovementVector.Y);
  const FVector RightDirection =
      FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
  AddMovementInput(RightDirection, MovementVector.X);
}

void ABaseCharacter::Look(const FInputActionValue &Value) {
  // input from mouse's x & y is 2D - make a vector
  const FVector2D LookAxisValue = Value.Get<FVector2D>();
  // check for valid controller
  if (GetController()) { // check for valid controller
    // turn / look left-right
    AddControllerYawInput(LookAxisValue.X);
    // turn / look up-down
    AddControllerPitchInput(LookAxisValue.Y);
  }
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  // Set up action bindings
  if (UEnhancedInputComponent *EnhancedInputComponent =
          Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
    EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered,
                                       this, &ABaseCharacter::Move);
    EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered,
                                       this, &ABaseCharacter::Look);
    //  jumping
    // note that the Jump and StopJumping functions are defined in the
    // Character parent class, not our BaseCharacter
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
                                       &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
                                       this, &ACharacter::StopJumping);
    // end jumping
    // sprinting
    EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started,
                                       this, &ABaseCharacter::BeginSprint);
    EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed,
                                       this, &ABaseCharacter::EndSprint);
    // end sprinting
    EnhancedInputComponent->BindAction(SwingAction, ETriggerEvent::Triggered,
                                       this, &ABaseCharacter::Swing);
  }
}

void ABaseCharacter::BeginSprint() {
  GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ABaseCharacter::EndSprint() {
  GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void ABaseCharacter::Swing() {
  if (CharacterState == ECharacterState::ECS_Unequipped)
    return;
  // Make a local AnimInstance pointer for our character's mesh
  UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
  // check for successful instance and presence of a montage
  if (AnimInstance && SwingMontage) {
    // play the montage
    AnimInstance->Montage_Play(SwingMontage);
    // local variable to choose a random int
    int32 Selection = FMath::RandRange(0, 1);
    // make an empty FName to hold a SectionName
    FName SectionName = FName();
    // assign value depending on Selection
    switch (Selection) {
    case 0:
      SectionName = FName("Swing1");
      break;
    case 1:
      SectionName = FName("Swing2");
      break;
    default:
      SectionName = FName("Swing1");
    }
    // jump to the selected montage section
    AnimInstance->Montage_JumpToSection(SectionName, SwingMontage);
  }
}