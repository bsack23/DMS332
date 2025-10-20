// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Utensils/Utensil.h"

// need to include header for BaseCharacter because we're attaching
// this to a socket on its skeletal mesh
#include "Characters/BaseCharacter.h"

AUtensil::AUtensil() {
  // collision presets set to NoCollision to avoid strange motion ...
  ItemMesh->SetCollisionProfileName(FName("NoCollision"));
  // change radius of Sphere to match the mesh size
  Sphere->InitSphereRadius(40.0f);
}

void AUtensil::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult) {
  // use Super to call version of this func from parent class (Item)
  Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex,
                        bFromSweep, SweepResult);
  // cast from MyCharacter class so we can attach this to its socket
  ABaseCharacter *BaseCharacter = Cast<ABaseCharacter>(OtherActor);
  // check for valid Character
  if (BaseCharacter) {
    // assign transform rules for attachment
    FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,
                                             TRUE);
    // do the attachment
    ItemMesh->AttachToComponent(BaseCharacter->GetMesh(), TransformRules,
                                FName("RightHandSocket"));
    // Stop the rotation
    RotationRate = 0;
  }
}

void AUtensil::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                            class AActor *OtherActor,
                            class UPrimitiveComponent *OtherComp,
                            int32 OtherBodyIndex) {
  Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}