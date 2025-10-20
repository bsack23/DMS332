// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/LightSwitch.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitch::ALightSwitch() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;
  // set default light intensity
  DesiredIntensity = 3000.0f;
  // FLinearColor is RGB as 3 floats
  NewLightColor = FLinearColor(1.f, 0.f, 1.f);
  // Make new PointLight component
  PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
  //   set the color and intensity
  PointLight->Intensity = DesiredIntensity;
  PointLight->SetLightColor(NewLightColor);
  // make it the root
  RootComponent = PointLight;

  // Start with visibility false (light off)
  PointLight->SetVisibility(false);
  // make a sphere component
  Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
  // set the initial size and attach it to the light
  Sphere->InitSphereRadius(150.0f);
  Sphere->SetupAttachment(RootComponent);

  Sphere->OnComponentBeginOverlap.AddDynamic(
      this, &ALightSwitch::OnOverlapBegin); // set up a notification for
                                            // when this component
                                            // overlaps something
  Sphere->OnComponentEndOverlap.AddDynamic(
      this,
      &ALightSwitch::OnOverlapEnd); // set up a notification for when
                                    // this component stops
                                    // overlapping something
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void ALightSwitch::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// our functions
void ALightSwitch::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                                  class AActor *OtherActor,
                                  class UPrimitiveComponent *OtherComp,
                                  int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult &SweepResult) {
  if (OtherActor && (OtherActor != this) && OtherComp) {
    // turn light on
    PointLight->SetVisibility(true);
    // debug message why not?
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
                                     TEXT("Overlap Begin"));
  }
}

void ALightSwitch::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                                class AActor *OtherActor,
                                class UPrimitiveComponent *OtherComp,
                                int32 OtherBodyIndex) {
  if (OtherActor && (OtherActor != this) && OtherComp) {
    // turn light off
    PointLight->SetVisibility(false);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
  }
}