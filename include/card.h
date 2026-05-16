#ifndef CARD_H
#define CARD_H

#include "raylib.h"

#define MAX_DECK_CARDS 20

// Enums for card classification
typedef enum {
    ALLY,
    ENEMY
} Team;

typedef enum {
    // Ally roles
    ZUMBI_PALMARES,
    GANGA_ZUMBA,
    CANGACEIRO,
    MESTRE_FREVO,
    CABOCLINHO,
    REI_MARACATU,
    DAMA_PACO,
    HOMEM_MEIA_NOITE,
    
    // Enemy roles
    SOLDADO_MOSQUETE,
    ARTILHEIRO_CANHAO,
    ALABARDEIRO,
    OFICIAL_CAVALARIA,
    ENGENHEIRO_NAVAL,
    ARCABUZEIRO,
    CAPITAO_GUARDA,
    JOHAN_MAURITS,
    
    ROLE_NONE
} CardRole;

// Card structure with game attributes
typedef struct {
    // Card identity
    int id;
    const char *name;
    Texture2D cardTexture;
    
    // Combat attributes
    int attack;
    int defense;
    int hp;
    float evasionProbability;  // 0.0 to 1.0 (0% to 100%)
    
    // Position and visual
    Vector2 position;
    int cardWidth;
    int cardHeight;
    
    // State
    int currentHP;
    bool isAlive;
    
    // Role and team
    CardRole role;
    Team team;
    
    // Ability management
    bool ability_used;
    int paralyzeCounter;  // For paralysis effects
    int shieldHP;  // Shield value
    bool firstAttackImmunity;  // For captain
    
} Card;

// Deck structure for battle system
typedef struct {
    Card *cards[MAX_DECK_CARDS];
    int cardCount;
    int currentCardIndex;  // Index of the card currently fighting
    Vector2 deckPosition;
} CardDeck;

// Battle state
typedef struct {
    CardDeck *player1Deck;
    CardDeck *player2Deck;
    int turns;
    bool isActive;
    int winner;  // 0 = no winner, 1 = player1 won, 2 = player2 won
} Battle;

/**
 * @brief Initialize a card with base attributes
 * @param card Pointer to the card structure
 * @param id Unique card identifier
 * @param name Card name
 * @param texturePath Path to card texture asset
 * @param attack Attack stat
 * @param defense Defense stat
 * @param hp Health points
 * @param evasion Evasion probability (0.0 to 1.0)
 * @param position Starting position on screen
 */
void InitCard(Card *card, int id, const char *name, const char *texturePath, 
              int attack, int defense, int hp, float evasion, Vector2 position);

/**
 * @brief Draw card on screen with all attributes displayed
 * @param card Pointer to the card
 */
void DrawCard(Card *card);

/**
 * @brief Draw card with custom display mode (full card or compact)
 * @param card Pointer to the card
 * @param compact If true, draws minimal info; if false, draws full stats
 */
void DrawCardExtended(Card *card, bool compact);

/**
 * @brief Take damage to the card
 * @param card Pointer to the card
 * @param damage Amount of damage
 */
void TakeDamage(Card *card, int damage);

/**
 * @brief Heal the card
 * @param card Pointer to the card
 * @param healAmount Amount to heal
 */
void HealCard(Card *card, int healAmount);

/**
 * @brief Check if card should evade an attack based on probability
 * @param card Pointer to the card
 * @return true if attack is evaded, false otherwise
 */
bool CheckEvasion(Card *card);

/**
 * @brief Unload card texture from memory
 * @param card Pointer to the card
 */
void UnloadCard(Card *card);

/**
 * @brief Get card statistics as a formatted string
 * @param card Pointer to the card
 * @param buffer Output buffer for stats string
 * @param bufferSize Size of the buffer
 */
void GetCardStats(Card *card, char *buffer, int bufferSize);

// ============== DECK AND BATTLE FUNCTIONS ==============

/**
 * @brief Initialize a card deck
 * @param deck Pointer to the deck
 * @param position Position to draw the deck on screen
 */
void InitDeck(CardDeck *deck, Vector2 position);

/**
 * @brief Add a card to the deck
 * @param deck Pointer to the deck
 * @param card Pointer to the card to add
 * @return true if added successfully, false if deck is full
 */
bool AddCardToDeck(CardDeck *deck, Card *card);

/**
 * @brief Get the currently fighting card from the deck
 * @param deck Pointer to the deck
 * @return Pointer to the current card, or NULL if deck is empty
 */
Card* GetCurrentCard(CardDeck *deck);

/**
 * @brief Get the next available card after the current one dies
 * @param deck Pointer to the deck
 * @return true if a valid card was found and set, false if no more cards
 */
bool AdvanceToNextCard(CardDeck *deck);

/**
 * @brief Check if deck has any alive cards
 * @param deck Pointer to the deck
 * @return true if deck has alive cards, false if all are dead
 */
bool DeckHasCards(CardDeck *deck);

/**
 * @brief Initialize a battle with two decks
 * @param battle Pointer to battle structure
 * @param deck1 First player deck
 * @param deck2 Second player deck
 */
void InitBattle(Battle *battle, CardDeck *deck1, CardDeck *deck2);

/**
 * @brief Execute one turn of battle (both cards attack)
 * @param battle Pointer to the battle structure
 */
void ExecuteBattleTurn(Battle *battle);

/**
 * @brief Process attack from attacker to defender
 * @param attacker Card attacking
 * @param defender Card defending
 */
void ProcessAttack(Card *attacker, Card *defender);

/**
 * @brief Draw the battle state on screen
 * @param battle Pointer to the battle structure
 */
void DrawBattle(Battle *battle);

/**
 * @brief Get the battle winner (0 = ongoing, 1 = deck1 wins, 2 = deck2 wins)
 * @param battle Pointer to the battle structure
 * @return Winner ID or 0 if battle is still ongoing
 */
int GetBattleWinner(Battle *battle);

/**
 * @brief Unload all cards from a deck
 * @param deck Pointer to the deck
 */
void UnloadDeck(CardDeck *deck);

/**
 * @brief Unload battle resources
 * @param battle Pointer to the battle structure
 */
void UnloadBattle(Battle *battle);

int GetRandomInt(int min, int max);

#endif