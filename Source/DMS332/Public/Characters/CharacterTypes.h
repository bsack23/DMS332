#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8 {
  ECS_Unequipped UMETA(DisplayName = "Unequipped"),
  ECS_EquippedRightHanded UMETA(DisplayName = "Equipped Right-Handed"),
  ECS_EquippedLeftHanded UMETA(DisplayName = "Equipped Left-Handed")
};

UENUM(BlueprintType)
enum class EActionState : uint8 {
  EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
  EAS_Swinging UMETA(DisplayName = "Swinging")
};
