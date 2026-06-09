# SpartaProject - C++ 기초 과제 (회전발판과 움직이는 장애물)

이 프로젝트는 언리얼 엔진 C++을 활용하여 동적으로 움직이는 장애물과 무작위 퍼즐 요소를 포함한 스테이지를 구현한 과제입니다. 특히 **리플렉션 시스템을 고도화**하여 에디터에서의 수정 사항이 실시간으로 반영되도록 구현하는 데 집중했습니다.

## 🚀 주요 기능

### 1. 필수 구현 기능

#### **회전 장애물 (ASpinner)**
- **Tick 기반 동적 회전**: `Tick(float DeltaTime)` 함수 내에서 `AddActorLocalRotation`을 사용하여 매 프레임 액터를 회전시킵니다.
- **실시간 속도 반영**: 생성자에서 기본값을 설정하고 `BeginPlay`에서의 덮어쓰기를 제거하여, 에디터 디테일 패널에서 수정하는 즉시 회전 속도가 반영됩니다.
- **프레임 독립성 확보**: `DeltaTime`을 적용하여 일정한 회전 속도를 보장합니다.

#### **이동 및 점멸 장애물 (AMovableObject)**
- **왕복 및 순간이동 로직**: 기준점(`StartLocation`)으로부터 특정 범위(`MaxRange`) 내에서 무작위 순간이동을 수행합니다.
- **가시성 토글 (Blink)**: 일정 주기마다 액터를 숨기고 충돌을 비활성화합니다.

#### **실시간 리플렉션 고도화 (Editor Integration)**
- **PostEditChangeProperty 활용**: 에디터에서 `TeleportTime`이나 `ToggleVisibilityTime` 수치를 변경하면, 게임 실행 중에도 `FTimerManager`를 즉시 갱신하여 바뀐 주기가 바로 적용되도록 설계했습니다.
- **데이터 보존**: 기본값을 생성자(`Constructor`)에서 정의하여 에디터에서 설정한 수치가 `BeginPlay` 시점에 초기화되지 않도록 관리합니다.

---

### 2. 도전 구현 기능

#### **타이머 시스템 활용 (FTimerManager)**
- **성능 최적화**: 매 프레임 체크가 필요 없는 가시성 토글과 순간이동 로직은 `Tick` 대신 타이머 핸들을 사용하여 CPU 점유율을 낮췄습니다.
- **동적 주기 갱신**: 에디터 수정 이벤트와 연동하여 타이머를 재설정하는 유연한 구조를 가집니다.

#### **랜덤 퍼즐 생성기 (ASpawnerActor)**
- **동적 스폰**: `UBoxComponent`로 정의된 영역 내에서 `SpawnActor`를 호출하여 장애물을 배치합니다.
- **무작위성 부여**: `FMath::RandRange`와 `FMath::RandBool`을 사용하여 위치, 회전, 클래스 타입을 무작위로 결정해 매번 다른 맵 구성을 제공합니다.

---

## 🛠 클래스 구조 및 설명

| 클래스명 | 상속 | 주요 기능 | 핵심 기술 |
| :--- | :--- | :--- | :--- |
| **ASpinner** | `AActor` | 지속적으로 회전하는 장애물 | `Tick`, `DeltaTime`, `AddActorLocalRotation` |
| **AMovableObject** | `AActor` | 주기적 순간이동 및 점멸 장애물 | `FTimerHandle`, `PostEditChangeProperty`, `Collision Toggle` |
| **ASpawnerActor** | `AActor` | 장애물 무작위 스폰 및 관리 | `UBoxComponent`, `SpawnActor`, `FMath::RandRange` |

---

## 🎨 테마 및 에셋
- **테마**: 황금빛 유적/퍼즐 스테이지
- **주요 에셋**:
  - `SM_Star_B`: 회전하는 별 모양 장애물
  - `SM_Stairs`: 순간이동하는 계단 플랫폼
  - `M_Metal_Gold`: 금속 재질 적용

---

## 💻 개발 환경
- **Engine**: Unreal Engine 5.5.4
- **IDE**: JetBrains Rider
- **Language**: C++

---

### 💡 테스트 방법
1. 프로젝트를 빌드하고 언리얼 에디터를 실행합니다.
2. `ASpawnerActor`를 통해 생성된 장애물들을 확인합니다.
3. 플레이 중 **Details 패널**에서 `RotationSpeed`, `TeleportTime` 등을 변경해 봅니다.
4. 수치가 변경되는 즉시 장애물의 회전 속도나 이동 주기가 바뀌는지 확인합니다.

---
**작성자**: goeun441
**최종 수정일**: 2026-06-09
