#include "card.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InitCard(Card *card, int id, const char *name, const char *texturePath,
              int attack, int defense, int hp, float evasion, Vector2 position)
{
    card->id = id;
    card->name = name;
    card->attack = attack;
    card->defense = defense;
    card->hp = hp;
    card->currentHP = hp;
    card->evasionProbability = evasion;
    card->position = position;
    card->isAlive = true;
    
    // Load texture
    card->cardTexture = LoadTexture(texturePath);
    
    // Set card dimensions based on texture
    card->cardWidth = card->cardTexture.width;
    card->cardHeight = card->cardTexture.height;
}

void DrawCard(Card *card)
{
    if (!card->isAlive)
        return;
    
    // Draw card rectangle background
    Rectangle cardRect = {card->position.x, card->position.y, card->cardWidth, card->cardHeight};
    DrawRectangleRec(cardRect, DARKGRAY);
    DrawRectangleLinesEx(cardRect, 3, BLACK);
    
    // Draw card texture
    DrawTexture(card->cardTexture, (int)card->position.x, (int)card->position.y, WHITE);
    
    // Draw card name
    int nameSize = 16;
    DrawText(card->name, (int)card->position.x + 10, (int)card->position.y + 10, nameSize, WHITE);
    
    // Draw stats on card
    int statsSize = 14;
    int startX = (int)card->position.x + 10;
    int startY = (int)card->position.y + card->cardHeight - 90;
    
    // Attack stat
    char attackText[32];
    snprintf(attackText, sizeof(attackText), "ATK: %d", card->attack);
    DrawText(attackText, startX, startY, statsSize, RED);
    
    // Defense stat
    char defenseText[32];
    snprintf(defenseText, sizeof(defenseText), "DEF: %d", card->defense);
    DrawText(defenseText, startX, startY + 20, statsSize, BLUE);
    
    // HP stat
    char hpText[32];
    snprintf(hpText, sizeof(hpText), "HP: %d/%d", card->currentHP, card->hp);
    Color hpColor = card->currentHP > card->hp / 2 ? GREEN : (card->currentHP > 0 ? YELLOW : RED);
    DrawText(hpText, startX, startY + 40, statsSize, hpColor);
    
    // Evasion stat
    char evasionText[32];
    snprintf(evasionText, sizeof(evasionText), "EVA: %.0f%%", card->evasionProbability * 100);
    DrawText(evasionText, startX, startY + 60, statsSize, PURPLE);
    
    // HP bar
    int barWidth = card->cardWidth - 20;
    int barHeight = 8;
    int barX = (int)card->position.x + 10;
    int barY = (int)card->position.y + card->cardHeight - 15;
    
    DrawRectangle(barX, barY, barWidth, barHeight, DARKGRAY);
    float hpPercentage = (float)card->currentHP / card->hp;
    DrawRectangle(barX, barY, (int)(barWidth * hpPercentage), barHeight, hpColor);
    DrawRectangleLinesEx((Rectangle){barX, barY, barWidth, barHeight}, 1, BLACK);
}

void DrawCardExtended(Card *card, bool compact)
{
    if (!card->isAlive)
        return;
    
    if (compact)
    {
        // Compact view - small card display
        Rectangle cardRect = {card->position.x, card->position.y, 100, 120};
        DrawRectangleRec(cardRect, DARKGRAY);
        DrawRectangleLinesEx(cardRect, 2, BLACK);
        
        DrawText(card->name, (int)card->position.x + 5, (int)card->position.y + 5, 12, WHITE);
        
        char stats[64];
        snprintf(stats, sizeof(stats), "ATK:%d DEF:%d\nHP:%d/%d", 
                 card->attack, card->defense, card->currentHP, card->hp);
        DrawText(stats, (int)card->position.x + 5, (int)card->position.y + 25, 10, WHITE);
    }
    else
    {
        // Full view - detailed card display
        DrawCard(card);
    }
}

void TakeDamage(Card *card, int damage)
{
    if (!card->isAlive)
        return;
    
    // Check for evasion
    if (CheckEvasion(card))
    {
        TraceLog(LOG_INFO, "Card %s evaded the attack!", card->name);
        return;
    }
    
    // Apply defense reduction
    int actualDamage = damage - card->defense;
    if (actualDamage < 0)
        actualDamage = 0;
    
    card->currentHP -= actualDamage;
    
    if (card->currentHP <= 0)
    {
        card->currentHP = 0;
        card->isAlive = false;
        TraceLog(LOG_INFO, "Card %s has been defeated!", card->name);
    }
    else
    {
        TraceLog(LOG_INFO, "Card %s took %d damage! HP: %d/%d", card->name, actualDamage, card->currentHP, card->hp);
    }
}

void HealCard(Card *card, int healAmount)
{
    if (!card->isAlive)
        return;
    
    card->currentHP += healAmount;
    if (card->currentHP > card->hp)
        card->currentHP = card->hp;
    
    TraceLog(LOG_INFO, "Card %s healed by %d! HP: %d/%d", card->name, healAmount, card->currentHP, card->hp);
}

bool CheckEvasion(Card *card)
{
    // Generate random number between 0 and 1
    float random = (float)rand() / RAND_MAX;
    return random < card->evasionProbability;
}

void UnloadCard(Card *card)
{
    UnloadTexture(card->cardTexture);
    TraceLog(LOG_INFO, "Card %s unloaded", card->name);
}

void GetCardStats(Card *card, char *buffer, int bufferSize)
{
    snprintf(buffer, bufferSize,
             "Card: %s\nID: %d\nAttack: %d\nDefense: %d\nHP: %d/%d\nEvasion: %.2f%%\nStatus: %s",
             card->name, card->id, card->attack, card->defense, card->currentHP, card->hp,
             card->evasionProbability * 100, card->isAlive ? "Alive" : "Defeated");
}

// ============== DECK AND BATTLE IMPLEMENTATION ==============

void InitDeck(CardDeck *deck, Vector2 position)
{
    deck->cardCount = 0;
    deck->currentCardIndex = 0;
    deck->deckPosition = position;
    
    for (int i = 0; i < MAX_DECK_CARDS; i++)
    {
        deck->cards[i] = NULL;
    }
    
    TraceLog(LOG_INFO, "Deck initialized at position (%.0f, %.0f)", position.x, position.y);
}

bool AddCardToDeck(CardDeck *deck, Card *card)
{
    if (deck->cardCount >= MAX_DECK_CARDS)
    {
        TraceLog(LOG_WARNING, "Cannot add card to deck - deck is full!");
        return false;
    }
    
    deck->cards[deck->cardCount] = card;
    deck->cardCount++;
    
    TraceLog(LOG_INFO, "Card '%s' added to deck. Total cards: %d", card->name, deck->cardCount);
    return true;
}

Card* GetCurrentCard(CardDeck *deck)
{
    if (deck->currentCardIndex >= deck->cardCount)
        return NULL;
    
    return deck->cards[deck->currentCardIndex];
}

bool AdvanceToNextCard(CardDeck *deck)
{
    deck->currentCardIndex++;
    
    while (deck->currentCardIndex < deck->cardCount)
    {
        if (deck->cards[deck->currentCardIndex]->isAlive)
        {
            TraceLog(LOG_INFO, "Advanced to next card: %s", deck->cards[deck->currentCardIndex]->name);
            return true;
        }
        deck->currentCardIndex++;
    }
    
    TraceLog(LOG_INFO, "No more alive cards in deck!");
    return false;
}

bool DeckHasCards(CardDeck *deck)
{
    for (int i = deck->currentCardIndex; i < deck->cardCount; i++)
    {
        if (deck->cards[i]->isAlive)
            return true;
    }
    return false;
}

void InitBattle(Battle *battle, CardDeck *deck1, CardDeck *deck2)
{
    battle->player1Deck = deck1;
    battle->player2Deck = deck2;
    battle->turns = 0;
    battle->isActive = true;
    battle->winner = 0;
    
    TraceLog(LOG_INFO, "Battle initialized! Player 1 vs Player 2");
}

void ProcessAttack(Card *attacker, Card *defender)
{
    if (!attacker->isAlive || !defender->isAlive)
        return;
    
    TraceLog(LOG_INFO, "%s attacks %s for %d damage!", attacker->name, defender->name, attacker->attack);
    TakeDamage(defender, attacker->attack);
}

void ExecuteBattleTurn(Battle *battle)
{
    if (!battle->isActive)
        return;
    
    Card *card1 = GetCurrentCard(battle->player1Deck);
    Card *card2 = GetCurrentCard(battle->player2Deck);
    
    if (!card1 || !card2)
    {
        battle->isActive = false;
        return;
    }
    
    // Both cards attack each other
    ProcessAttack(card1, card2);
    ProcessAttack(card2, card1);
    
    battle->turns++;
    
    // Check if either card died and advance to next card
    if (!card2->isAlive)
    {
        if (!AdvanceToNextCard(battle->player2Deck))
        {
            battle->isActive = false;
            battle->winner = 1;
            TraceLog(LOG_INFO, "Player 1 wins the battle!");
        }
    }
    
    if (!card1->isAlive)
    {
        if (!AdvanceToNextCard(battle->player1Deck))
        {
            battle->isActive = false;
            battle->winner = 2;
            TraceLog(LOG_INFO, "Player 2 wins the battle!");
        }
    }
}

void DrawBattle(Battle *battle)
{
    if (!battle->isActive && battle->winner == 0)
        return;
    
    Card *card1 = GetCurrentCard(battle->player1Deck);
    Card *card2 = GetCurrentCard(battle->player2Deck);
    
    // Draw player 1 side
    if (card1)
    {
        Rectangle deckBox1 = {20, 20, 400, 550};
        DrawRectangleRec(deckBox1, (Color){50, 50, 50, 255});
        DrawRectangleLinesEx(deckBox1, 3, BLUE);
        
        DrawText("PLAYER 1", 30, 30, 20, BLUE);
        
        char deckInfo[64];
        snprintf(deckInfo, sizeof(deckInfo), "Cards left: %d", 
                 battle->player1Deck->cardCount - battle->player1Deck->currentCardIndex);
        DrawText(deckInfo, 30, 60, 16, WHITE);
        
        card1->position = (Vector2){50, 150};
        DrawCard(card1);
    }
    
    // Draw player 2 side
    if (card2)
    {
        Rectangle deckBox2 = {GetScreenWidth() - 420, 20, 400, 550};
        DrawRectangleRec(deckBox2, (Color){50, 50, 50, 255});
        DrawRectangleLinesEx(deckBox2, 3, RED);
        
        DrawText("PLAYER 2", GetScreenWidth() - 410, 30, 20, RED);
        
        char deckInfo[64];
        snprintf(deckInfo, sizeof(deckInfo), "Cards left: %d",
                 battle->player2Deck->cardCount - battle->player2Deck->currentCardIndex);
        DrawText(deckInfo, GetScreenWidth() - 410, 60, 16, WHITE);
        
        card2->position = (Vector2){GetScreenWidth() - 400, 150};
        DrawCard(card2);
    }
    
    // Draw battle info
    char battleInfo[64];
    snprintf(battleInfo, sizeof(battleInfo), "Turn: %d", battle->turns);
    DrawText(battleInfo, GetScreenWidth() / 2 - 30, 20, 20, YELLOW);
    
    if (!battle->isActive && battle->winner > 0)
    {
        const char *winnerText = battle->winner == 1 ? "PLAYER 1 WINS!" : "PLAYER 2 WINS!";
        Color winnerColor = battle->winner == 1 ? BLUE : RED;
        DrawText(winnerText, GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 40, winnerColor);
    }
}

int GetBattleWinner(Battle *battle)
{
    return battle->winner;
}

void UnloadDeck(CardDeck *deck)
{
    for (int i = 0; i < deck->cardCount; i++)
    {
        if (deck->cards[i])
        {
            UnloadCard(deck->cards[i]);
            deck->cards[i] = NULL;
        }
    }
    deck->cardCount = 0;
    deck->currentCardIndex = 0;
    TraceLog(LOG_INFO, "Deck unloaded");
}

void UnloadBattle(Battle *battle)
{
    UnloadDeck(battle->player1Deck);
    UnloadDeck(battle->player2Deck);
    battle->isActive = false;
    battle->winner = 0;
    TraceLog(LOG_INFO, "Battle unloaded");
}

// Helper function to get random value
int GetRandomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}
