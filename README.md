# DX9_WorldSkill_Practice_Gyeonggi_01

2020 전국기능경기대회 경기도 문제를 연습하며 만든 DirectX 9 기반 3D 액션 게임입니다. 3D 모델 애니메이션, 전투, 몬스터 웨이브와 보스, 레벨업과 스킬 트리, 미니맵, 데미지 폰트까지 한 판을 플레이할 수 있는 단계까지 구현되어 있습니다.

## 소개

- 저장소 설명: "2020 전국기능경기대회 경기도 문제 연습"
- 커밋은 2020-08-15부터 2020-09-10까지 28건입니다. 본인 계정 별칭 외에 다른 계정의 커밋 1건이 있으나 인원은 저장소에서 확인되지 않습니다.
- 서울디지텍고등학교 기능반(DirectX 게임 제작) 재학 시기에 해당합니다.
- 같은 시기의 `DX9_WorldSkill_Practice_Busan_01`과 엔진 코드(컴포넌트 구조, 애니메이터, 메시 로더)가 거의 같습니다. 이 저장소는 스테이지 흐름과 성장 요소가 더 많이 구현되어 있습니다.

## 조작

| 입력 | 동작 |
|---|---|
| `W` `A` `S` `D` | 카메라 기준 이동 |
| 스페이스 | 점프 |
| 마우스 왼쪽 버튼 | 공격 (두 번째 입력이 이어지면 2연타 콤보) |
| `Left Shift` | 스킬 1: 이동 방향으로 돌진 (이동 중, 쿨타임 4초) |
| `Q` | 스킬 2: 이동 방향으로 도약 (이동 중, 쿨타임 7초) |

## 핵심 구현

### 컴포넌트 구조 (`CGameObject`, `CComponent`, `CObjectManager`)

Unity와 비슷한 구조로 만들었습니다. `CGameObject`는 컴포넌트 목록과 부모/자식 목록을 가지고, 템플릿 함수 `ac<T>()`(AddComponent)와 `gc<T>()`(GetComponent, `dynamic_cast`)로 컴포넌트를 붙이고 꺼냅니다. 컴포넌트는 `Awake`, `Start`, `Update`, `LateUpdate`, `OnDestroy`, `OnCollision` 가상 함수를 구현합니다.

`CObjectManager::Update`의 순서는 다음과 같습니다.

1. 아직 `Start`가 불리지 않은 컴포넌트의 `Start` 호출
2. 활성 오브젝트의 컴포넌트 `Update` 호출
3. 등록된 `CCollider` 쌍을 모두 비교해(반지름 합과 월드 위치 거리 비교의 구 충돌) 겹치면 양쪽 오브젝트의 모든 컴포넌트에 `OnCollision` 호출
4. `LateUpdate` 호출
5. 파괴 표시된 오브젝트 삭제

3D 렌더러 목록을 먼저, 2D 렌더러는 정렬 레이어 순으로 그립니다. `Find`, `Finds`(이름/태그), `GetCollisionObject`(임시 구 콜라이더로 범위 검사), `RayCast`도 제공합니다.

### 메시 시퀀스 애니메이션 (`CAnimator3D`, `CAnimation3D`, `MeshLoader`)

3D 모델은 `.obj` 메시를 프레임마다 한 개씩 불러 재생하는 방식입니다. `MeshLoader`는 DirectX SDK 샘플의 `.obj` 로더 구조를 사용합니다. `AddMesh("PLAYER_IDLE", "Player/Animation/Idle/Idle", "Player", 41)`처럼 `키 (1)`, `키 (2)` ... 이름으로 프레임 메시를 등록하면, `CAnimator3D::AddState(상태명, 키, 프레임 간격, 반복 여부)`가 메시가 없을 때까지 번호를 올려 가며 모아 상태를 만듭니다. `Update`에서 현재 상태의 프레임 메시를 `CMeshRenderer`에 지정합니다. 상태에는 프레임 번호에 콜백을 거는 `AddEvent`가 있어 공격 판정 타이밍(예: 공격 애니메이션 4번째·11번째 프레임)을 애니메이션과 맞춥니다.

### 플레이어 (`CPlayerMovement.cpp`)

애니메이션 상태(IDLE, RUN, ATTACK01, ATTACK02, SKILL01, SKILL02)에 따라 입력의 의미가 달라지는 상태 머신입니다.

- IDLE/RUN: 이동 입력이 있으면 RUN으로, 공격 입력이면 ATTACK01로, 스킬 입력은 쿨타임(`GAME.Skill01Timer`)이 찼을 때 SKILL로 전환
- ATTACK01 진행 중 공격 입력이 한 번 더 있으면 콤보 플래그를 세우고, 애니메이션이 끝날 때(`GetNormalizeTime() >= 0.99`) ATTACK02로 이어감
- 스킬은 `CRigidBody`에 속도를 설정해 돌진·도약을 구현하고 캐릭터를 이동 방향으로 회전

### 지형과 물리 (`CStageMap`, `CRigidBody`)

지형은 두 가지 정보로 판정합니다. 바닥 높이는 맵 메시 기준 `GetFloorY`, 이동 가능 여부는 충돌용 이미지(`MAP_STAGE01_COLISIONMAP`)의 픽셀 색을 `LockRect`로 읽어 판정합니다. 월드 좌표 (x, z)를 10으로 나눠 이미지 좌표로 바꾸고, 마젠타색이면 `Wall`로 처리합니다. `CRigidBody::LateUpdate`는 마찰 감쇠, 중력(5500), 바닥 착지(착지 콜백 `OnLanding`) 처리 후 벽 판정에 걸리면 이전 위치로 되돌립니다.

### 몬스터와 스테이지 (`CEnemy`, `CBoss01`, `CStage01`, `CStage02`)

- `CStage01`: 처치한 몬스터가 없으면 2초 간격 검사에서 5개 스폰 지점을 돌아 가며 `CEnemy01` 8마리와 `CEnemy02` 2마리를 생성합니다. 처치 수가 70에 이르면 보스 `CBoss02`를 생성하고, 보스를 처치하면 `S_STAGECLEAR`로 넘어갑니다.
- `CStage02`: `CEnemy03`, `CEnemy04`를 같은 방식으로 생성하고 처치 수 100에서 `CBoss01`을 생성, 처치하면 게임 클리어로 이어집니다.
- `CBoss01`은 플레이어와의 거리로 전이하는 상태 머신입니다. IDLE에서 거리 2000 이내면 CHASE, CHASE에서 거리 200 이하면 ATTACK_PREPARE, 2500 초과면 다시 IDLE, ATTACK_PREPARE에서 공격 지연 시간이 차면 ATTACK01~03 중 하나를 무작위로 재생하고, 애니메이션 프레임 이벤트(16, 19, 27번째)에서 `Attack()`을 호출합니다. 체력 30000의 보스입니다.
- `CEnemy::OnHit`: 피해를 방어력에 따라 줄여 체력을 깎고, 죽으면 위로 날아가며 사망 애니메이션을 재생합니다. 맞을 때 카메라 흔들림과 짧은 시간 정지(`TimeScale`을 낮췄다 복구)로 타격감을 줍니다. 사망 시 경험치 아이템, 코인, 낮은 확률로 아이템 상자를 떨어뜨립니다.

### 성장과 UI (`CGameManager`, `CSkillTree`, `CPlayerUI`, `CDamageFont`)

`GainExp`로 경험치가 최대치를 넘으면 레벨업(체력 회복, 최대 경험치 x1.1, 스킬 포인트 +3)하고 이펙트를 띄웁니다. 시작 스킬 포인트는 10입니다. `CSkillTree`는 8개 스킬 칸을 가진 창으로, 포인트로 `SkillLevel[8]`을 올립니다. `CPlayerUI`는 체력·경험치 바, 스킬 아이콘과 쿨타임, 콤보, 퀘스트, 미니맵(플레이어·적 표시)을 그리고, `CDamageFont`는 피해량을 띄웁니다. `CScheduleAdmin`은 람다를 큐에 넣어 "지연 후 실행"을 순서대로 처리하는 간단한 스케줄러입니다(보스 사망 후 1.5초 뒤 제거 등).

```cpp
// CBoss01::Update 일부: 거리에 따른 상태 전이
case Enemy_State::IDLE:
    gc<CAnimator3D>()->SetCurrentState("IDLE");
    if (dist < 2000) m_State = Enemy_State::CHASE;
    break;
case Enemy_State::CHASE:
    gc<CAnimator3D>()->SetCurrentState("RUN");
    if (dist <= 200)       m_State = Enemy_State::ATTACK_PREPARE;
    else if (dist > 2500)  m_State = Enemy_State::IDLE;
    break;
```

### 리소스 로딩 (`CMainGame.cpp`)

사운드와 메시·스프라이트 등록 코드를 `std::async` 람다로 감싸 로딩합니다. 씬은 `S_TITLE`, `S_STAGE01`, `S_STAGECLEAR`, `S_STAGE02`, `S_GAMECLEAR`, `S_GAMEOVER`이며 현재 시작 씬은 `S_TITLE`입니다.

## 프로젝트 구조

| 경로 | 설명 |
|---|---|
| `CGameObject`, `CComponent`, `CObjectManager`, `CTransform`, `CCollider`, `CRigidBody` | 컴포넌트 구조, 충돌, 물리 |
| `CAnimator3D`, `CAnimation3D`, `CMeshRenderer`, `MeshLoader` | 3D 메시 애니메이션과 렌더링 |
| `CPlayerMovement`, `CEnemy`, `CEnemy01~04`, `CBoss01`, `CBoss02` | 플레이어, 몬스터, 보스 |
| `CStage01`, `CStage02`, `CStageMap`, `CStageClear`, `CGameClear`, `CGameOver`, `CTitleScene` | 씬과 지형 |
| `CGameManager`, `CSkillTree`, `CPlayerUI`, `CDamageFont`, `CButton`, `CText` | 성장, UI |
| `CScheduleAdmin`, `CEffect`, `CItem`, `CScrollMap` | 스케줄러, 이펙트, 아이템 |
| `CGraphicsManager`, `CCameraManager`, `CInputManager`, `CSceneManager` | 매니저 |
| `Resource/` | 모델, 이펙트, UI, 사운드 |
| `EmptyProject_2010.sln` | Visual Studio 솔루션 (소스는 저장소 최상위) |

## 기술 스택

- C++, DirectX 9, DXUT(저장소에 포함), `std::async`
- Visual Studio 프로젝트 `EmptyProject_2010.sln`: 플랫폼 도구 집합 v141

## 실행 방법

1. Visual Studio(v141 도구 집합)와 DirectX SDK가 필요합니다. 프로젝트가 `DXSDK_DIR` 환경 변수를 참조합니다.
2. `EmptyProject_2010.sln`을 열어 빌드합니다. 리소스는 `Resource/` 폴더에서 상대 경로로 읽습니다.

빌드는 당시 환경 기준입니다.

## 현재 상태

대회 문제 연습용 학습 프로젝트이며 2020-09-10 이후 갱신이 없습니다. `CGameManager`의 `SaveData`/`LoadData`는 비어 있습니다. `Resource/`(모델, 이펙트, 사운드)에는 외부에서 받은 것으로 보이는 에셋이 포함되어 있고 출처는 저장소에 기록되어 있지 않습니다.
