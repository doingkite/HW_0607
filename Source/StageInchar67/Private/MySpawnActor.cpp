#include "MySpawnActor.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

AMySpawnActor::AMySpawnActor()
{
	PrimaryActorTick.bCanEverTick = false; // 틱 불필요
}

void AMySpawnActor::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlatforms();
}

void AMySpawnActor::SpawnPlatforms()
{
	UWorld* const World = GetWorld();

	if (!World || PlatformClassesToSpawn.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnPlatforms failed: World or PlatformClassToSpawn is null."));
		return;
	}

	const FVector SpawnCenter = GetActorLocation();

	for (int32 i = 0; i < NumberOfPlatformsToSpawn; ++i)
	{
		// 무작위로 블루프린트 클래스 선택
		const int32 RandomIndex = FMath::RandRange(0, PlatformClassesToSpawn.Num() - 1);
		TSubclassOf<AActor> PlatformClassToSpawn = PlatformClassesToSpawn[RandomIndex];
		// 무작위 X, Y 좌표 계산 (-SpawnRadius ~ +SpawnRadius)
		const float RandomX = FMath::FRandRange(-SpawnRadius, SpawnRadius);
		const float RandomY = FMath::FRandRange(-SpawnRadius, SpawnRadius);

		// 임의의 Z 높이 (예: 100cm ~ 500cm 높이)
		const float SpawnZ = FMath::FRandRange(100.0f, 500.0f);

		const FVector SpawnLocation = FVector(
			SpawnCenter.X + RandomX,
			SpawnCenter.Y + RandomY,
			SpawnCenter.Z + SpawnZ
		);

		const FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// SpawnActor 호출
		World->SpawnActor<AActor>(
			PlatformClassToSpawn,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);
	}
}