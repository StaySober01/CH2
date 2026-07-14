# 커밋 순서로 배우는 Dungeon Escape Text RPG

이 문서는 이 프로젝트가 커밋마다 어떻게 성장했는지를 따라가며 C++의 기초 문법과 객체 지향 개념을 설명한다. 완성된 코드만 한꺼번에 보면 클래스와 파일이 많아 복잡해 보이지만, 실제 개발 순서는 **입력과 출력 → 반복과 조건 → 클래스 → 상속과 다형성 → 컨테이너 → 기능별 객체 분리**로 자연스럽게 확장된다.

## 먼저 알아둘 프로젝트 구조

- `main.cpp`: 프로그램 시작점과 전체 게임 진행을 담당한다.
- `player.h`, `Player.cpp`: 모든 플레이어 직업이 공유하는 상태와 행동을 정의한다.
- `Warrior`, `Magician`, `Thief`, `Archer`: `Player`를 상속한 직업 클래스다.
- `Monster`와 `Slime`, `Zombie`, `Skeleton`: 몬스터의 공통 부분과 종류별 차이를 표현한다.
- `Item`: 전투에서 얻는 아이템 한 개를 표현한다.
- `Inventory.h`: 어떤 자료형이든 보관할 수 있는 `Inventory<T>` 템플릿과 동적 배열을 정의한다.
- `PotionRecipe`: 포션 레시피 한 개를 표현한다.
- `AlchemyWorkshop`: 여러 레시피를 보관하고 검색한다.
- `CH2.vcxproj`, `CH2.vcxproj.filters`: Visual Studio가 어떤 소스 파일을 빌드하고 솔루션 탐색기에 어떻게 보여 줄지 기록한다.

헤더 파일(`.h`)에는 주로 클래스의 **선언**, 소스 파일(`.cpp`)에는 함수의 **구현**을 둔다. `#include`는 다른 파일에 선언된 이름을 현재 파일에서 사용할 수 있게 가져오는 지시문이다.

---

## 0. Initial commit (`0dc2e03`)

첫 커밋에는 `.gitignore`, `.gitattributes`, `README.md`만 있다. 아직 게임 코드는 없으며, 저장소의 기본 규칙을 준비한 단계다.

- `.gitignore`: 빌드 결과물과 Visual Studio 임시 파일처럼 Git에 저장할 필요가 없는 파일을 지정한다.
- `.gitattributes`: Git이 파일을 다루는 방식을 설정한다.
- `README.md`: 프로젝트 소개를 적는 문서다.

여기서 배울 점은 **소스 코드뿐 아니라 개발 환경을 관리하는 파일도 프로젝트의 일부**라는 것이다.

---

## 1. 캐릭터 생성 화면 (`0bd2c7c`)

첫 번째 실제 기능은 이름과 능력치를 입력받아 캐릭터 정보를 출력하는 것이다.

### 입력, 변수, 객체

`main.cpp`에서 다음과 같은 변수를 만든다.

```cpp
std::string name;
int hp;
int mp;
int attack;
int defence;
```

`std::string`은 문자열, `int`는 정수를 저장한다. `std::cin`은 키보드 입력을 받고 `std::cout`은 콘솔에 글자를 출력한다.

```cpp
std::cin >> name;
std::cin >> hp >> mp;
```

입력이 끝나면 `Player` 객체를 만든다.

```cpp
Player player(name, hp, mp, attack, defence);
player.printStats();
```

`Player(...)` 생성자는 전달받은 값을 객체 내부에 저장하고, `printStats()`는 그 값을 출력한다. 객체는 관련된 **데이터와 기능을 한 묶음으로 만든 것**이라고 생각하면 된다.

### `struct Stat`과 `class Player`

초기 `player.h`의 `Stat` 구조체는 네 능력치를 묶는다.

```cpp
struct Stat {
    int HP;
    int MP;
    int Attack;
    int Defence;
};
```

`Player`의 `name`과 `stat`은 `private`이므로 클래스 바깥에서 직접 수정할 수 없다. 대신 `printStats()`, `setHP()` 같은 공개 함수로 접근한다. 이것이 **캡슐화**의 시작이다. 객체 내부 상태를 아무 곳에서나 바꾸지 못하게 하고, 정해진 통로를 사용하게 만든다.

`printStats() const`의 마지막 `const`는 이 함수가 플레이어 상태를 변경하지 않는다는 약속이다.

---

## 2. 입력 유효성 검사 (`c41c1ba`)

사용자가 너무 낮은 능력치를 입력하면 다시 입력하게 만들었다.

```cpp
while (true) {
    std::cin >> hp >> mp;

    if (hp >= 50 && mp >= 50) {
        break;
    }
}
```

- `while (true)`: 끝없이 반복한다.
- `if`: 조건이 참일 때만 내부 코드를 실행한다.
- `&&`: 두 조건이 모두 참이어야 한다.
- `break`: 가장 가까운 반복문을 즉시 끝낸다.

즉, HP와 MP가 모두 기준을 만족할 때만 반복문을 빠져나간다.

이 커밋에는 공격력과 방어력 안내는 20 이상이라고 되어 있지만 실제 조건은 50 이상을 검사하는 불일치가 있었다. 다음 단계에서 조건이 20 이상으로 수정된다. 작은 숫자 하나도 프로그램 규칙을 바꾸므로 **화면 안내와 실제 조건을 함께 확인하는 습관**이 중요하다.

또한 이 시점에는 문자 입력처럼 `std::cin` 자체가 실패하는 경우를 처리하지 않는다. 숫자의 범위와 입력 성공 여부는 서로 다른 문제이며, 뒤 커밋에서 `cin.clear()`와 `cin.ignore()`를 사용해 보완한다.

---

## 3. 스탯 관리 메뉴 (`0afb87a`)

캐릭터에게 포션을 지급하고, 사용자가 메뉴를 반복해서 선택할 수 있게 했다.

> 현재 진행본에서는 `< Character Upgrade >` 메뉴 루프 전체가 주석 처리되어 있다. 아래 내용은 해당 커밋에서 어떤 반복문과 포션 기능을 학습했는지 설명하는 기록이다. 포션은 지금도 지급되지만 실제 아이템으로 인벤토리에 들어가며 전투 중 사용할 수 있다.

### 상태를 기억하는 멤버 변수

`Player`에 현재 포션 수를 저장하는 변수가 추가됐다.

```cpp
int curHpPotion = 0;
int curMpPotion = 0;
```

`GainHpPotion()`은 개수를 늘리고, `UseHpPotion()`은 포션이 있을 때 HP를 20 회복한 뒤 개수를 하나 줄인다. 포션이 없다면 `return`으로 함수를 일찍 끝낸다.

```cpp
if (curHpPotion <= 0) {
    std::cout << "You don't have Hp potion.\n";
    return;
}
```

### 메뉴와 `switch`

`switch`는 하나의 값에 따라 여러 행동 중 하나를 고를 때 유용하다.

```cpp
switch (choose) {
case 1:
    player.UseHpPotion();
    break;
case 0:
    isGameStart = true;
    break;
}
```

`isGameStart`는 참/거짓을 저장하는 `bool` 변수다. 값이 `false`인 동안 메뉴를 반복하고, 0을 선택하면 `true`가 되어 반복이 끝난다.

당시 범위 검사는 `choose < 0 && choose > 5`였는데, 하나의 수가 동시에 0보다 작고 5보다 클 수는 없다. 범위 밖을 검사하려면 `choose < 0 || choose > 5`처럼 **둘 중 하나**를 뜻하는 `||`를 사용해야 한다. 이 오류는 Step 4에서 고쳐진다.

---

## 4. `Player` 클래스와 직업 선택 (`891eb18`)

이 단계는 프로젝트 구조가 크게 바뀌는 지점이다. 하나뿐이던 플레이어를 전사, 마법사, 도적, 궁수로 확장한다.

### 선언과 구현 분리

길어진 `Player` 코드를 `player.h`와 `Player.cpp`로 나눴다.

- 헤더: 어떤 멤버와 함수가 있는지 알린다.
- 소스: 각 함수가 실제로 무엇을 하는지 작성한다.

이렇게 나누면 `main.cpp`는 플레이어의 내부 구현을 전부 알지 않아도 공개된 함수만 사용할 수 있다.

### 상속

각 직업은 공통 능력치를 다시 만들지 않고 `Player`를 상속한다.

```cpp
class Warrior : public Player {
public:
    Warrior(const std::string& name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
};
```

`Warrior : public Player`는 “Warrior는 Player의 한 종류”라는 뜻이다. `Player`의 `protected` 멤버는 외부에서는 접근할 수 없지만 자식 클래스에서는 사용할 수 있다. 그래서 전사 생성자는 기본 플레이어를 먼저 만든 뒤 HP를 30 높인다.

```cpp
Warrior::Warrior(...)
    : Player(name, hp, mp, power, defence) {
    job = "Warrior";
    this->hp += 30;
}
```

콜론 뒤의 `Player(...)`는 부모 클래스 생성자를 호출하는 **멤버 초기화 목록**이다.

### 가상 함수와 다형성

`Player`의 공격은 다음처럼 선언된다.

```cpp
class Monster;
virtual void attack(Monster* monster) = 0;
```

`class Monster;`는 뒤에서 정의될 클래스를 먼저 이름만 알려주는 전방 선언이다. `= 0`이 붙은 순수 가상 함수는 부모가 공통 공격을 정하지 않고 각 직업이 반드시 자기 공격을 구현하게 한다. 이런 `Player`는 직접 객체로 만들 수 없는 **추상 클래스**가 된다.

`main.cpp`는 실제 직업과 관계없이 `Player*` 하나로 캐릭터를 다룬다.

```cpp
Player* player = nullptr;
player = new Warrior(name, hp, mp, power, defence);
player->attack(&monster);
```

포인터의 자료형은 `Player*`지만 실제 객체가 `Warrior`라면 전사의 `attack(Monster*)`가 실행된다. 전사와 마법사는 한 번 공격하고, 궁수는 3회, 도적은 5회로 데미지를 나누어 적용한다. 각 타격의 계산 결과가 0 이하라면 최소 데미지 1을 적용한다. 같은 호출이 실제 객체에 따라 다르게 동작하는 것이 **다형성**이다.

`new`로 만든 객체는 사용 후 `delete`해야 한다. 부모 포인터로 자식 객체를 안전하게 삭제하기 위해 `Player`에는 가상 소멸자 `virtual ~Player()`가 있다. 현재 코드는 이 수동 메모리 관리 방식을 연습하고 있으며, 현대 C++에서는 `std::unique_ptr`로 더 안전하게 표현할 수 있다.

---

## 5. `Monster` 클래스와 1:1 전투 (`d15053a`)

플레이어와 싸울 `Monster`가 추가되고, 전투 규칙이 별도 함수로 분리됐다.

### 데미지 계산 함수

```cpp
int calculateDamage(int power, int defence) {
    int damage = power - defence;
    return damage > 0 ? damage : 1;
}
```

이 공통 함수는 몬스터가 플레이어를 공격할 때 공격력에서 방어력을 빼고, 결과가 0 이하라면 최소 1의 피해를 주는 데 사용한다. 플레이어 공격은 각 직업의 `attack(Monster*)`가 직업별 계산식으로 처리한다. `조건 ? 참일 때 값 : 거짓일 때 값`은 간단한 `if/else`를 값 하나로 표현하는 **삼항 연산자**다.

### 참조와 포인터

```cpp
void battle(Player* player, Monster& monster)
```

- `Player*`: 플레이어 객체의 주소를 받으며 멤버 접근에 `->`를 쓴다.
- `Monster&`: 몬스터 객체의 별명인 참조를 받으며 멤버 접근에 `.`을 쓴다.

둘 다 원본 객체를 대상으로 하므로 함수 안에서 바뀐 HP가 함수 밖에도 유지된다. 객체를 복사해 받았다면 복사본만 바뀌었을 것이다.

전투는 양쪽 HP가 모두 0보다 큰 동안 반복된다. 플레이어 공격 후 몬스터가 죽었는지 먼저 확인하여, 죽은 몬스터가 다시 공격하지 못하게 `break`한다. 이후 몬스터 턴을 처리하고 반복 조건으로 돌아간다.

### 입력 스트림 복구

직업 선택에서는 숫자가 아닌 입력도 다루기 시작한다.

```cpp
if (std::cin >> jobChoice && jobChoice >= 1 && jobChoice <= 4) {
    break;
}

std::cin.clear();
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

잘못된 형식이 들어오면 `std::cin`은 실패 상태가 된다. `clear()`는 실패 상태를 해제하고, `ignore()`는 입력 줄에 남은 잘못된 문자를 버린다. 둘 중 하나만 하면 다음 입력도 계속 실패할 수 있다.

---

## 6. 인벤토리와 아이템 드롭 (`b75f77c`)

전투 승리 보상이 실제 인벤토리에 저장되고, 게임이 메인 메뉴를 중심으로 계속 실행된다.

### 간단한 데이터에는 `struct`

```cpp
struct Item {
    std::string name;
    int price;

    void PrintInfo() const;
};
```

`Item`은 이름과 가격을 묶은 작은 자료형이다. `class`와 `struct`는 거의 같지만, `struct`의 멤버는 기본적으로 `public`이다. 단순한 데이터 묶음에는 `struct`가 읽기 편하다.

### 초기 구현: 크기가 변하는 배열 `std::vector`

```cpp
class Player {
    std::vector<Item> inventory;
};
```

`std::vector`는 실행 중 원소 수가 달라질 수 있는 컨테이너다. 이 단계에서는 `Player`가 `std::vector<Item>`을 직접 소유했다. `push_back()`으로 아이템을 뒤에 추가하고, `size()`로 개수를 확인하며, `empty()`로 비었는지 검사했다.

```cpp
if (inventory.size() < Player::MAX_INVENTORY_SIZE) {
    inventory.push_back(droppedItem);
}
```

`Player::MAX_INVENTORY_SIZE`는 `constexpr`로 선언되어 실행 중 변하지 않는 상수임을 나타낸다. 당시에는 벡터 자체에 더 들어갈 수 있지만, `Player::addItem()`이 게임 규칙으로 최대 10개를 제한했다. 현재 코드는 뒤에서 설명할 `Inventory<Item>`으로 교체되어 용량 제한을 컨테이너가 직접 관리한다.

`Player::getInventory()`는 `const` 참조를 반환한다. 복사 비용을 피하면서도 외부 함수가 인벤토리를 직접 수정하지 못하게 하는 좋은 읽기 전용 접근 방식이다.

범위 기반 `for`문도 등장한다.

```cpp
for (const Item& item : inventory) {
    item.PrintInfo();
}
```

인벤토리의 모든 아이템을 처음부터 끝까지 하나씩 읽는다.

### 상태의 수명

`inventory`는 `battle()`의 지역 변수가 아니라 게임이 끝날 때까지 살아 있는 `Player` 객체의 멤버다. 전투 함수 안에 만들었다면 전투가 끝날 때마다 사라진다. 여러 메뉴 방문과 전투 사이에 유지되어야 하는 데이터는 그것을 사용하는 함수보다 **더 오래 살아 있는 객체**가 소유해야 한다.

`clearScreen()`과 `pauseScreen()`은 각각 Windows의 `cls`, `pause` 명령을 실행해 콘솔 화면 흐름을 정돈한다. `std::system()`과 이 명령들은 운영체제 의존적이므로 이 프로젝트는 Windows 콘솔을 전제로 한다.

---

## 7. 포션 제작소 기본 기능 (`cf71da9`)

이 커밋은 몬스터 종류를 늘리고 포션 레시피 조회 기능을 추가한다. 이제 상속과 객체 합성이 양쪽에서 사용된다.

### 몬스터 상속 구조

`Monster`는 공통 능력치뿐 아니라 드롭 아이템 이름과 가격, 보상 경험치도 가진다. `Slime`, `Zombie`, `Skeleton`은 생성자에서 서로 다른 값을 부모에게 전달한다.

```cpp
Slime::Slime()
    : Monster("Slime", 30, 20, 10, "Slime Jelly", 30, 30) {}
```

전투에서 승리하면 몬스터의 `expReward`를 `Player::gainExp()`에 전달한다. 경험치가 `maxExp` 이상이면 레벨과 능력치를 올리고 경험치를 0으로 초기화한다. 다음 레벨에 필요한 경험치는 50씩 증가한다.

각 자식 클래스는 `attack(Monster*)`를 `override`하여 서로 다른 공격 횟수와 데미지 계산을 적용한다. `enterDungeon()`은 사용자가 고른 몬스터를 지역 객체로 만든 뒤 모두 같은 `battle(Player*, Monster&)` 함수에 전달한다. `Monster&`가 자식 객체도 받을 수 있고 가상 함수가 실제 몬스터의 공격을 선택하기 때문에 전투 코드를 복사할 필요가 없다.

### 레시피와 제작소의 관계

`PotionRecipe`는 레시피 한 개를 나타내고 `AlchemyWorkshop`은 여러 레시피를 `std::vector<PotionRecipe>`로 소유한다.

```cpp
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;
};
```

이 관계는 상속이 아니다. 제작소가 레시피의 한 종류인 것이 아니라 레시피들을 **가지고 있는 것**이므로 객체 합성(composition)이다.

제작소 생성자의 초기화 목록에서 세 레시피를 한 번에 채운다. `ShowAllRecipes()`는 전부 순회하고, `SearchByName()`은 같은 이름을 찾으면 출력 후 `return`한다. `SearchByIngredient()`는 모든 레시피를 확인해야 하므로 찾은 뒤에도 반복을 계속하고 `foundCount`를 증가시킨다.

```cpp
bool PotionRecipe::ContainsIngredient(const std::string& ingredient) const {
    return firstIngredient == ingredient || secondIngredient == ingredient;
}
```

“이 레시피가 재료를 포함하는가?”라는 판단을 `PotionRecipe` 안에 둔 덕분에 제작소는 재료 필드의 세부 구조를 덜 알아도 된다. 데이터와 그 데이터를 판단하는 기능을 가까이 두는 객체 지향 설계다.

### `std::getline`과 `std::ws`

```cpp
std::getline(std::cin >> std::ws, searchText);
```

`operator >>`로 메뉴 숫자를 읽으면 줄바꿈 문자가 입력 버퍼에 남을 수 있다. `std::ws`는 앞쪽 공백과 줄바꿈을 먼저 소비하고, `getline()`은 공백이 포함된 `Clear Water` 같은 한 줄 전체를 읽는다.

### 현재 게임의 전체 흐름

1. 이름과 초기 능력치를 입력한다.
2. 직업을 선택하고 직업별 보너스를 받는다.
3. HP 포션 5개와 MP 포션 5개를 인벤토리로 받는다.
4. 기존 능력치 강화 메뉴는 주석 처리되어 바로 메인 메뉴로 이동한다.
5. 메인 메뉴에서 던전, 인벤토리, 포션 제작소 중 하나를 고른다.
6. 던전에서는 매 턴 공격 또는 아이템 사용을 선택한다.
7. 전투에서 승리하면 경험치와 드롭 아이템을 얻는다.
8. 종료를 선택할 때까지 메인 메뉴를 반복한다.
9. 마지막에 동적으로 생성한 플레이어를 `delete`한다.

---

## 8. 전투 중 포션 사용

플레이어 턴마다 곧바로 공격하던 구조를 메뉴 선택 방식으로 바꿨다.

```text
--- Player Turn ---
1. Attack
2. Use Item
Choose:
```

`Use Item`을 선택하면 같은 이름과 가격을 가진 아이템을 한 줄로 묶어 보여 준다.

```text
[ Inventory ]
1. HP Potion x 5 (50G)
2. MP Potion x 5 (50G)
0. Back
Choose item:
```

`0`을 입력하면 턴을 소비하지 않고 `Attack / Use Item` 선택으로 돌아간다. 잘못된 번호나 숫자가 아닌 입력도 아이템 인덱스로 사용하지 않고 다시 선택하게 한다.

HP 포션과 MP 포션은 각각 50을 회복하지만 `std::min()`으로 최대 HP와 MP를 넘지 않게 제한한다.

```cpp
player->setHP(std::min(player->getHP() + 50, player->getMaxHP()));
player->setMP(std::min(player->getMP() + 50, player->getMaxMP()));
```

선택한 포션은 회복 처리 후 인벤토리에서 한 개만 제거한다. 그래서 `HP Potion x 5`를 한 번 사용하면 다음 출력은 `HP Potion x 4`가 된다. 포션 사용도 플레이어의 한 턴이므로 그 뒤에는 살아 있는 몬스터가 공격한다.

---

## 9. 도전 STEP 5: `Inventory<T>` 직접 구현

기존 `std::vector<Item>` 대신 [Inventory.h](Inventory.h)의 `Inventory<T>`가 아이템 저장 공간을 직접 관리한다. 템플릿을 사용했기 때문에 `Item` 이외의 자료형도 같은 컨테이너에 보관할 수 있다.

```cpp
template<typename T>
class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;
};
```

### 템플릿 코드를 헤더에 작성하는 이유

컴파일러는 `Inventory<Item>`처럼 실제 자료형이 정해지는 지점에서 템플릿 코드를 이용해 구체적인 클래스를 만든다. 따라서 선언만 헤더에 두고 구현을 일반 `.cpp`로 분리하면 필요한 구현을 찾지 못할 수 있다. 현재 프로젝트는 템플릿 선언과 구현을 모두 `Inventory.h`에 둔다.

### 생성자와 소멸자의 동적 메모리 관리

생성자는 지정된 용량만큼 배열을 만들고 현재 아이템 수를 0으로 시작한다.

```cpp
explicit Inventory(int capacity = 10)
    : pItems_(nullptr), capacity_(capacity > 0 ? capacity : 1), size_(0) {
    pItems_ = new T[capacity_];
}
```

`new[]`로 만든 배열은 반드시 `delete[]`로 해제해야 한다. 소멸자가 이 작업을 담당하므로 `Inventory` 객체의 수명이 끝날 때 저장 공간도 정리된다.

```cpp
~Inventory() {
    delete[] pItems_;
}
```

### 아이템 추가와 삭제

`AddItem()`은 공간이 가득 차면 `Resize(capacity_ * 2)`를 호출한다. `Resize()`는 더 큰 배열을 할당하고 기존 아이템을 복사한 뒤 기존 배열을 해제하므로, 아이템을 잃지 않고 용량을 두 배로 늘릴 수 있다.

`SortItems()`는 `std::sort`와 `compareByPrice()`를 사용해 현재 아이템을 가격이 낮은 순서로 정렬한다.

`RemoveLastItem()`은 마지막 원소를 제거하고 `size_`를 하나 줄인다. 전투에서는 사용자가 중간 위치의 포션을 선택할 수도 있으므로 보조 함수 `RemoveItem(index)`도 구현했다. 이 함수는 인덱스 범위를 검사하고 뒤쪽 원소를 한 칸씩 앞으로 옮긴 다음 `RemoveLastItem()`을 호출한다.

```cpp
for (int moveIndex = index; moveIndex < size_ - 1; ++moveIndex) {
    pItems_[moveIndex] = pItems_[moveIndex + 1];
}

return RemoveLastItem();
```

`GetItem()`은 잘못된 인덱스라면 `nullptr`를 반환한다. 호출하는 쪽은 포인터가 유효한지 확인한 뒤 아이템에 접근하므로 배열 범위를 벗어나지 않는다.

### 깊은 복사와 Rule of Three

`pItems_` 주소만 복사하는 얕은 복사를 사용하면 두 인벤토리가 같은 배열을 가리킨다. 한 객체가 소멸하면서 배열을 해제하면 다른 객체의 포인터가 무효가 되고, 나중에 같은 메모리를 두 번 해제할 수도 있다.

복사 생성자는 새로운 배열을 할당하고 기존 아이템을 하나씩 복사한다.

```cpp
Inventory(const Inventory& other)
    : pItems_(new T[other.capacity_]),
      capacity_(other.capacity_),
      size_(other.size_) {
    for (int index = 0; index < size_; ++index) {
        pItems_[index] = other.pItems_[index];
    }
}
```

복사 대입 연산자도 자기 자신을 대입하는 경우를 먼저 확인하고, 새 배열에 복사한 뒤 기존 배열을 해제한다. 현재 `Inventory<T>`는 소멸자, 복사 생성자, 복사 대입 연산자를 모두 직접 구현했으므로 **Rule of Three**를 만족한다.

### `Player`와의 연결

`Player`는 이제 표준 벡터 대신 직접 만든 인벤토리를 멤버로 소유한다.

```cpp
Inventory<Item> inventory;
```

`Player::addItem()`과 `removeItem()`은 각각 `Inventory<Item>::AddItem()`과 `RemoveItem()`에 작업을 전달한다. 메인 메뉴의 인벤토리 출력은 `PrintAllItems()`, 현재 개수는 `GetSize()`, 현재 용량은 `GetCapacity()`를 사용한다. 인벤토리는 가득 차면 자동 확장되며, 수명은 여전히 `Player` 객체와 같으므로 메뉴나 전투가 끝나도 아이템이 유지된다.

---

## 현재 코드를 읽는 추천 순서

1. `main.cpp`의 `main()`만 읽으며 게임의 큰 흐름을 파악한다.
2. `Inventory.h`에서 템플릿과 동적 배열의 생성·복사·해제를 확인한다.
3. `player.h`와 `Player.cpp`에서 `Inventory<Item>`이 플레이어에게 연결되는 방식을 본다.
4. 네 직업의 헤더와 소스를 비교해 달라지는 부분만 찾는다.
5. `Monster.h`, `Monster.cpp`와 세 몬스터를 같은 방식으로 비교한다.
6. `battle()`, `useBattleItem()`, `enterDungeon()`, `printInventory()`를 따라 데이터가 어떻게 전달되는지 본다.
7. `PotionRecipe`와 `AlchemyWorkshop`을 읽으며 “레시피 한 개”와 “레시피 관리자”의 책임 차이를 본다.

## 입문자가 직접 해 볼 연습

- `Goblin` 클래스를 추가하고 고블린만의 능력치, 드롭 아이템, 공격 문장을 정한다.
- `Inventory<Item>`의 생성자 인자로 최대 크기를 바꾸고 꽉 찼을 때의 동작을 확인한다.
- `Inventory<int>`를 만든 뒤 복사 생성자와 복사 대입 연산자가 깊은 복사를 하는지 확인한다.
- 포션 레시피를 하나 추가한 뒤 이름 검색과 재료 검색이 모두 되는지 확인한다.
- 전투에서 HP가 음수가 되지 않도록 `setHP()` 또는 피해 처리 함수를 개선한다.
- `new`/`delete`를 `std::unique_ptr<Player>`로 바꿔 자동 메모리 관리를 연습한다.
- 반복되는 숫자 입력 검사를 하나의 함수로 분리한다.

## 읽으면서 발견할 수 있는 개선점

현재 코드는 학습 단계가 잘 드러나지만 다음 개선 여지도 있다.

- `getHp()`와 `getHP()`, `setHp()`와 `setHP()`가 중복되어 이름을 하나로 통일할 수 있다.
- 플레이어에는 `takeDamage()`가 있지만 전투는 `setHP()`로 직접 HP를 계산한다. 피해 규칙을 한 함수로 모으면 변경하기 쉽다.
- 숫자가 아닌 초기 HP, MP, Power, Defence 입력은 아직 스트림 복구 처리가 없다.
- 레시피 검색은 대소문자와 앞뒤 공백이 정확히 같아야 성공한다.
- `AlchemyWorkshop.cpp`의 검색 실패 문구 하나는 현재 문자 인코딩이 깨져 있으므로 올바른 문자열로 고칠 필요가 있다.
- `main.cpp`가 많은 흐름을 담당한다. 프로젝트가 더 커지면 게임 진행을 관리하는 `Game` 클래스로 나눌 수 있다.

이 개선점들은 현재 코드가 나쁘다는 뜻이 아니다. 기능을 한 단계씩 완성한 뒤 중복과 책임을 다시 정리하는 **리팩터링 후보**이며, 다음 학습 주제로 삼기 좋은 지점들이다.
