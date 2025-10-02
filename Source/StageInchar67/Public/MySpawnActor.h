#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnActor.generated.h"

UCLASS()
class STAGEINCHAR67_API AMySpawnActor : public AActor
{
	GENERATED_BODY()

public:
	AMySpawnActor();

protected:
	virtual void BeginPlay() override;

	// === ���� ���� ===
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TArray<TSubclassOf<AActor>> PlatformClassesToSpawn; // ������ �������Ʈ Ŭ������ �����Ϳ��� ����

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 NumberOfPlatformsToSpawn = 5; // ������ �÷����� ����

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnRadius = 1000.0f; // ������ �� �ִ� �ִ� X, Y �ݰ�

	void SpawnPlatforms();
};