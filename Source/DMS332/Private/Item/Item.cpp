// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Item.h"
#include "Components/SphereComponent.h"
#include "Math/UnrealMathUtility.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AItem::AItem() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  ItemMesh =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Component"));
  RootComponent = ItemMesh;

  EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
  EmbersEffect->SetupAttachment(GetRootComponent());

  // create sphere for overlap and attach it to root component
  Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
  Sphere->InitSphereRadius(150.0f);
  Sphere->SetupAttachment(RootComponent);
  // set up a notification for when this component
  // overlaps something
  Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
  Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AItem::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AItem::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  //   float RotationRate = 40.f;
  // RotationRate is now declared and set in Item.h, and can be changed from
  // Blueprint
  AddActorWorldRotation(FRotator(0.f, DeltaTime * RotationRate, 0.f));

  RunningTime += DeltaTime;

  float SineValue = SineAmplitude * FMath::Sin(RunningTime * SineRate);
  //   AddActorWorldOffset(FVector(0.f, 0.f, SineValue));

  // float PerlinValue = 1.f * FMath::PerlinNoise1D(RunningTime);
  // AddActorWorldOffset(FVector(0.f, PerlinValue, SineValue));
}

// our Overlap Begin and end functions
void AItem::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                           class AActor *OtherActor,
                           class UPrimitiveComponent *OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep,
                           const FHitResult &SweepResult) {
  if (OtherActor && (OtherActor != this) && OtherComp) {
    // do something
    // debug message why not?
    if (GEngine) {
      /**  syntax AddOnScreenDebugMessage(index, time to display, color,
                                     text)
                                     */
      /**const FString OtherActorName = OtherActor->GetName();
      GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red,
                                       TEXT("Overlap Begin " + OtherActorName));
                                       */
    }
  }
}

void AItem::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                         class AActor *OtherActor,
                         class UPrimitiveComponent *OtherComp,
                         int32 OtherBodyIndex) {
  if (OtherActor && (OtherActor != this) && OtherComp) {
    // do something
    /**
    GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, TEXT("Overlap End"));
    */
  }
}