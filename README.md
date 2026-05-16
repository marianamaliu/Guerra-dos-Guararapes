# ⚔️ Guerra dos Guararapes

Um jogo de estratégia em tempo real baseado na histórica Batalha dos Guararapes (1648), combinando mecânicas de cartas, ordenação visual e batalha por turnos.

## 📖 Visão Geral do Jogo

- **Vibe Recifense**: História e Recife Antigo / Batalha dos Guararapes
- **Contexto**: Um Recife alternativo, século XVII. Os holandeses retornam com uma frota reforçada para retomar o que perderam. O povo pernambucano convoca seus maiores ícones — do folclore, do carnaval, da resistência — para defender a terra mais uma vez.
- **Objetivo**: Destruir a caravela holandesa antes que o exército invasor atravesse a praia e tome o Forte das Cinco Pontas.
- **Mecânica Principal**: O jogador organiza sua fila de batalha usando Merge Sort para posicionar os personagens estrategicamente e vencer os duelos.

## 🏗️ Estrutura de Dados

### Estrutura Principal
- **Lista duplamente encadeada**: Representa a fila de batalha
- **Justificativa**: 
  - Inserção e remoção eficiente em qualquer posição
  - Reposicionamento durante Merge Sort sem cópia de dados
  - Travessia nos dois sentidos para animações
  - Mecânica de duelo sequencial (carta do topo vs carta do topo)

### Algoritmo de Ordenação
- **Merge Sort iterativo** sobre lista encadeada
- **Justificativa Técnica**: 
  - Mais adequado para listas ligadas (sem acesso aleatório)
  - Complexidade O(n log n) garantida
  - Estável (mantém ordem relativa de elementos iguais)
- **Justificativa de Jogo**: 
  - Cada passo do merge reposiciona fisicamente os soldados na tela
  - Algoritmo é visível e interativo

## 📁 Estrutura de Pastas

```
Guerra-dos-Guararapes/
├── include/                    # Headers (.h) - Definições de tipos e interfaces
│   ├── card.h                 # Sistema base de cartas (Card, CardDeck, Battle)
│   ├── ally_card.h            # Heróis aliados e suas habilidades
│   ├── enemy_card.h           # Inimigos e suas habilidades
│   ├── scene.h                # Gerenciamento de cenas/mapas
│   ├── game.h                 # Enums e constantes gerais (GameScreen, Team)
│   ├── enemy.h                # Sistema de entidades (personagens antigos)
│   ├── gameInitScreen.h       # Inicialização de telas do menu
│   ├── gameInitEntities.h     # Inicialização de entidades
│   └── gameInitTimer.h        # Sistema de timer/pontuação
│
├── src/                        # Implementação (.c)
│   ├── card.c                 # Implementação do sistema de cartas e batalha
│   ├── ally_card.c            # Implementação de heróis aliados
│   ├── enemy_card.c           # Implementação de inimigos
│   ├── scene.c                # Carregamento e renderização de cenas
│   ├── gameInitScreens.c      # Implementação de telas (menu, gameplay, etc)
│   ├── gameInitEntities.c     # Inicialização de entidades
│   ├── home.c                 # Tela inicial/lobby
│   ├── enemy.c                # Sistema de entidades antigo
│   ├── card.c                 # (Arquivo vazio - será removido)
│   └── scene.c                # (Arquivo vazio - será removido)
│
├── assets/                     # Recursos multimídia
│   ├── image.png              # Textura padrão de menu
│   ├── island.animated.gif    # Mapa de gameplay
│   ├── tela_ganhou.png        # Tela de vitória
│   ├── tela_perdeu.png        # Tela de derrota
│   └── card.png               # Textura de cartas
│
├── main.c                      # Arquivo principal - loop do jogo
├── main_ant.c                  # Versão antiga (backup)
├── Makefile                    # Configuração de compilação
├── README.md                   # Este arquivo
└── .gitignore                  # Arquivos ignorados pelo git
```

## 🎮 Componentes Principais

### 1. **Sistema de Cartas** (`card.h` / `card.c`)

#### Estrutura Card
```c
typedef struct {
    // Identidade
    int id;
    const char *name;
    Texture2D cardTexture;
    
    // Atributos de combate
    int attack;        // Dano causado
    int defense;       // Redução de dano recebido
    int hp;            // Pontos de vida totais
    float evasionProbability;  // 0.0 a 1.0 (probabilidade de esquivar)
    
    // Posição e visual
    Vector2 position;
    int cardWidth, cardHeight;
    
    // Estado
    int currentHP;
    bool isAlive;
    
    // Sistema de habilidades
    CardRole role;
    Team team;
    bool ability_used;
    int paralyzeCounter;
    int shieldHP;
    bool firstAttackImmunity;
} Card;
```

#### Estrutura CardDeck
```c
typedef struct {
    Card *cards[MAX_DECK_CARDS];    // Array de até 20 cartas
    int cardCount;                  // Número de cartas adicionadas
    int currentCardIndex;           // Índice da carta em combate
    Vector2 deckPosition;
} CardDeck;
```

#### Estrutura Battle
```c
typedef struct {
    CardDeck *player1Deck;
    CardDeck *player2Deck;
    int turns;
    bool isActive;
    int winner;  // 0 = em andamento, 1 = jogador 1, 2 = jogador 2
} Battle;
```

### 2. **Heróis Aliados** (`ally_card.h` / `ally_card.c`)

8 heróis com habilidades únicas:

| Herói | ATK | HP | Habilidade Especial |
|-------|-----|----|--------------------|
| 🧟 Zumbi dos Palmares | 9 | 10 | Primeiro da fila: ataque triplo ignora escudos |
| 👑 Ganga Zumba | 7 | 11 | Última posição: bloqueia 1º ataque (uso único) |
| 🤠 Cangaceiro | 11 | 5 | Instakill em inimigos < 30% HP (posição ímpar) |
| 🎭 Mestre do Frevo | 6 | 5 | Centro: ataca 2x por duel (2º hit = 50% dano) |
| 👨 Caboclinho | 7 | 7 | Entre dois aliados: atinge alvo + segundo inimigo |
| 🎺 Rei do Maracatu | 5 | 12 | Pos 1 ou última: escudo 3 HP ao aliado atrás |
| 👸 Dama do Paço | 3 | 7 | Ao entrar: cura 3 HP do aliado adjacente |
| 🌙 Homem da Meia-Noite | 6 | 6 | 40% esquiva + contra-ataque 4 dano fixo |

### 3. **Inimigos** (`enemy_card.h` / `enemy_card.c`)

8 inimigos com habilidades únicas:

| Inimigo | ATK | HP | Habilidade Especial |
|---------|-----|----|--------------------|
| 🔫 Soldado de Mosquete | 8 | 5 | Pré-ataque dano total ao 1º aliado |
| 🎯 Artilheiro com Canhão | 7 | 6 | Bombarda dois primeiros (uso único) |
| 🔱 Alabardeiro | 6 | 11 | Reduz 50% dano do 1º ataque |
| 🐴 Oficial de Cavalaria | 8 | 7 | Avança 2 posições, ataque dobrado |
| 🔧 Engenheiro Naval | 3 | 7 | Repara caravela 4 HP / danifica 2 ao morrer |
| 🏹 Arcabuzeiro | 6 | 6 | 35% paralysar (alvo toma +30% dano) |
| 👨‍💼 Capitão da Guarda | 8 | 14 | Imune ao 1º ataque, ganha +3 ATK |
| 👑 Johan Maurits (Boss) | 9 | 16 | Após 1º golpe: inverte ordem da fila inimiga |

### 4. **Sistema de Telas** (`gameInitScreen.h` / `gameInitScreens.c`)

Estados do jogo:
- **MENU**: Tela inicial com opção ENTER para jogar
- **LORE**: Introdução da história
- **GAMEPLAY**: Batalha principal em tempo real
- **WINNING**: Tela de vitória
- **LOSING**: Tela de derrota

Cada tela chama `DrawScene()` para renderizar o fundo com scaling automático.

### 5. **Sistema de Cenas** (`scene.h` / `scene.c`)

- Carrega texturas para cada tela
- Calcula escala e offset para centralizar na tela
- Suporta múltiplas resoluções automaticamente
- `addScenes()`: Carrega todas as 5 texturas (índices 0-4)
- `DrawScene()`: Renderiza e atualiza posicionamento

## 🎯 Enums Principais

```c
// Times em batalha
typedef enum { ALLY, ENEMY } Team;

// Estados do jogo
typedef enum GameScreen {
    MENU = 0,
    LORE = 1,
    GAMEPLAY = 2,
    WINNING = 3,
    LOSING = 4
} GameScreen;

// Papéis/Classes de cartas
typedef enum {
    // Aliados
    ZUMBI_PALMARES, GANGA_ZUMBA, CANGACEIRO, MESTRE_FREVO,
    CABOCLINHO, REI_MARACATU, DAMA_PACO, HOMEM_MEIA_NOITE,
    // Inimigos
    SOLDADO_MOSQUETE, ARTILHEIRO_CANHAO, ALABARDEIRO, OFICIAL_CAVALARIA,
    ENGENHEIRO_NAVAL, ARCABUZEIRO, CAPITAO_GUARDA, JOHAN_MAURITS,
    ROLE_NONE
} CardRole;
```

## 🚀 Como Compilar e Rodar

### Pré-requisitos
- GCC (compilador C)
- Raylib instalado em `/opt/homebrew/` (macOS) ou `/usr/` (Linux)

### Compilação
```bash
cd /home/arthur/AED/jogo/Guerra-dos-Guararapes
make clean    # Limpa arquivos antigos
make          # Compila
./guararapes.exe  # Executa
```

### Usando o Makefile
O Makefile está configurado para:
- Compilar todos os arquivos `.c` em `src/`
- Incluir headers de `include/`
- Linkar com Raylib
- Padrão C99

## 📚 Funções Principais

### Inicialização
```c
void InitCard(Card *card, int id, const char *name, const char *texturePath,
              int attack, int defense, int hp, float evasion, Vector2 position);

void InitDeck(CardDeck *deck, Vector2 position);
bool AddCardToDeck(CardDeck *deck, Card *card);

void InitBattle(Battle *battle, CardDeck *deck1, CardDeck *deck2);
```

### Batalha
```c
void ExecuteBattleTurn(Battle *battle);  // Executa um turno completo
void ProcessAttack(Card *attacker, Card *defender);
void DrawBattle(Battle *battle);
int GetBattleWinner(Battle *battle);
```

### Heróis Aliados
```c
void InitZumbiPalmares(Card *card, int id, Vector2 position);
void InitGangaZumba(Card *card, int id, Vector2 position);
// ... (7 mais)

void AbilityZumbiPalmares(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck);
// ... (habilidades)
```

### Inimigos
```c
void InitSoldadoMosquete(Card *card, int id, Vector2 position);
void InitArtilheiroCanhao(Card *card, int id, Vector2 position);
// ... (6 mais)

void AbilitySoldadoMosquete(Card *self, CardDeck *allyDeck);
// ... (habilidades)
```

## 🎨 Fluxo do Jogo

```
[MENU] ← ENTER
  ↓
[LORE] ← Intro da história
  ↓
[GAMEPLAY] ← Loop de batalha
  ↓ (Vitória)
[WINNING] ← Score final
  ↓ ENTER
[MENU]

  ↓ (Derrota)
[LOSING] ← Mostrar inimigo vencedor
  ↓ ENTER
[MENU]
```

## 🔧 Como Adicionar Novos Heróis

### 1. Adicionar ao enum (card.h)
```c
typedef enum {
    // ... heróis existentes
    MEU_NOVO_HEROI,
    // ...
} CardRole;
```

### 2. Criar inicializador (ally_card.c)
```c
void InitMeuNovoHeroi(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Nome", "assets/card.png", 
             10, 5, 20, 0.15f, position);
    card->role = MEU_NOVO_HEROI;
    card->team = ALLY;
    card->ability_used = false;
}
```

### 3. Criar habilidade (ally_card.c)
```c
void AbilityMeuNovoHeroi(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck)
{
    // Implementar lógica especial
    TraceLog(LOG_INFO, "%s usa habilidade especial!", self->name);
}
```

### 4. Declarar no header (ally_card.h)
```c
void InitMeuNovoHeroi(Card *card, int id, Vector2 position);
void AbilityMeuNovoHeroi(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck);
```

## 🐛 Debugging

### Logs
O jogo usa `TraceLog()` do Raylib para debug:
```c
TraceLog(LOG_INFO, "Mensagem de informação");
TraceLog(LOG_WARNING, "Aviso");
TraceLog(LOG_ERROR, "Erro");
```

### Terminal
Todos os logs aparecem no terminal durante execução.

## 📝 Notas de Desenvolvimento

- **Cards atuais**: 16 heróis (8 aliados + 8 inimigos)
- **Sistema de habilidades**: Cada herói tem até 3-4 habilidades únicas
- **Atributos dinâmicos**: Stats faltando são gerados aleatoriamente
- **Máximo de cartas por deck**: 20 (MAX_DECK_CARDS)
- **Turno de batalha**: Ambas cartas atacam simultaneamente

## 🎯 Próximas Etapas

- [ ] Implementar Merge Sort visual na interface
- [ ] Sistema de pontuação e ranking
- [ ] Mais tipos de inimigos
- [ ] Powerups durante batalha
- [ ] Multiplayer
- [ ] Animações de ataque

---

**Desenvolvido em C com Raylib** 🎮
