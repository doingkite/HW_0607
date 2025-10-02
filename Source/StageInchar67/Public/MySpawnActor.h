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

	// === 스폰 설정 ===
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TArray<TSubclassOf<AActor>> PlatformClassesToSpawn; // 스폰할 블루프린트 클래스를 에디터에서 지정

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 NumberOfPlatformsToSpawn = 5; // 스폰할 플랫폼의 개수

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnRadius = 1000.0f; // 스폰될 수 있는 최대 X, Y 반경

	void SpawnPlatforms();
};