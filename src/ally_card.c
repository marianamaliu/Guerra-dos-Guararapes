#include "ally_card.h"
#include "card.h"
#include <stdlib.h>
#include <stdio.h>

// ============== ALLY CARD INITIALIZERS ==============

void InitZumbiPalmares(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Zumbi dos Palmares", "assets/card.png", 9, GetRandomInt(2, 5), 10, 0.1f, position);
    card->role = ZUMBI_PALMARES;
    card->team = ALLY;
    card->ability_used = false;
}

void InitGangaZumba(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Ganga Zumba", "assets/card.png", 7, GetRandomInt(3, 6), 11, 0.15f, position);
    card->role = GANGA_ZUMBA;
    card->team = ALLY;
    card->ability_used = false;
    card->shieldHP = 0;
}

void InitCangaceiro(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Cangaceiro", "assets/card.png", 11, GetRandomInt(1, 3), 5, 0.2f, position);
    card->role = CANGACEIRO;
    card->team = ALLY;
    card->ability_used = false;
}

void InitMestreFrevo(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Mestre do Frevo", "assets/card.png", 6, GetRandomInt(2, 4), 5, 0.25f, position);
    card->role = MESTRE_FREVO;
    card->team = ALLY;
    card->ability_used = false;
}

void InitCaboclinho(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Caboclinho", "assets/card.png", 7, GetRandomInt(2, 4), 7, 0.18f, position);
    card->role = CABOCLINHO;
    card->team = ALLY;
    card->ability_used = false;
}

void InitReiMaracatu(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Rei do Maracatu", "assets/card.png", 5, GetRandomInt(3, 6), 12, 0.12f, position);
    card->role = REI_MARACATU;
    card->team = ALLY;
    card->ability_used = false;
}

void InitDamaPaco(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Dama do Paço", "assets/card.png", 3, GetRandomInt(2, 5), 7, 0.3f, position);
    card->role = DAMA_PACO;
    card->team = ALLY;
    card->ability_used = false;
}

void InitHomemMeianoite(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Homem da Meia-Noite", "assets/card.png", 6, GetRandomInt(2, 4), 6, 0.4f, position);
    card->role = HOMEM_MEIA_NOITE;
    card->team = ALLY;
    card->ability_used = false;
}

// ============== ALLY CARD ABILITIES ==============

void AbilityZumbiPalmares(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck)
{
    // First in line, triple damage and ignores shields on first attack
    if (allyDeck->currentCardIndex == 0 && !self->ability_used)
    {
        self->ability_used = true;
        Card *enemy = GetCurrentCard(enemyDeck);
        if (enemy)
        {
            int tripleDamage = self->attack * 3;
            TraceLog(LOG_INFO, "%s uses special ability: TRIPLE DAMAGE (Ignores Shields)! Dealing %d damage", 
                     self->name, tripleDamage);
            
            // Ignore shields
            int tempShield = enemy->shieldHP;
            enemy->shieldHP = 0;
            TakeDamage(enemy, tripleDamage);
            enemy->shieldHP = tempShield;
        }
    }
}

void AbilityGangaZumba(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck)
{
    // Last position, blocks first attack received (one-time use)
    int lastAllyIndex = allyDeck->cardCount - 1;
    
    if (allyDeck->currentCardIndex == lastAllyIndex && !self->ability_used && self->shieldHP == 0)
    {
        self->ability_used = true;
        self->shieldHP = 999;  // Blocks first attack completely
        TraceLog(LOG_INFO, "%s uses ability: Complete block on first attack!", self->name);
    }
}

void AbilityCangaceiro(Card *self, Card *enemy)
{
    // Instakill on enemies with less than 30% HP at odd positions
    if (enemy && (enemy->currentHP < (enemy->hp * 0.3f)))
    {
        enemy->currentHP = 0;
        enemy->isAlive = false;
        TraceLog(LOG_INFO, "%s uses special ability: INSTAKILL on weakened enemy %s!", 
                 self->name, enemy->name);
    }
}

void AbilityMestreFrevo(Card *self, CardDeck *enemyDeck)
{
    // Center position, attacks twice per duel (50% on second hit)
    // This is handled in battle logic - flag that this card can attack twice
    TraceLog(LOG_INFO, "%s can attack twice this turn (50%% damage on second hit)", self->name);
}

void AbilityCaboclinho(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck)
{
    // Between two allies, hits main target + second enemy with 50% damage
    int currentPos = allyDeck->currentCardIndex;
    bool between = (currentPos > 0 && currentPos < allyDeck->cardCount - 1);
    
    if (between)
    {
        Card *mainEnemy = GetCurrentCard(enemyDeck);
        int nextEnemyIndex = enemyDeck->currentCardIndex + 1;
        
        if (mainEnemy)
        {
            TraceLog(LOG_INFO, "%s uses area ability: hits main target + secondary with 50%% damage", 
                     self->name);
            TakeDamage(mainEnemy, self->attack);
            
            if (nextEnemyIndex < enemyDeck->cardCount && enemyDeck->cards[nextEnemyIndex]->isAlive)
            {
                TakeDamage(enemyDeck->cards[nextEnemyIndex], self->attack / 2);
            }
        }
    }
}

void AbilityReiMaracatu(Card *self, CardDeck *allyDeck)
{
    // Position 1 or last, grants 3 HP shield to ally behind (one-time use)
    int lastPos = allyDeck->cardCount - 1;
    
    if ((allyDeck->currentCardIndex == 0 || allyDeck->currentCardIndex == lastPos) && 
        !self->ability_used)
    {
        self->ability_used = true;
        int shieldTargetIndex = allyDeck->currentCardIndex + 1;
        
        if (shieldTargetIndex < allyDeck->cardCount)
        {
            allyDeck->cards[shieldTargetIndex]->shieldHP += 3;
            TraceLog(LOG_INFO, "%s grants 3 HP shield to %s!", 
                     self->name, allyDeck->cards[shieldTargetIndex]->name);
        }
    }
}

void AbilityDamaPaco(Card *self, CardDeck *allyDeck)
{
    // On entering combat, heals 3 HP of adjacent ally (one-time effect)
    if (!self->ability_used)
    {
        self->ability_used = true;
        
        int currentPos = allyDeck->currentCardIndex;
        int adjacentPos = (currentPos > 0) ? currentPos - 1 : currentPos + 1;
        
        if (adjacentPos >= 0 && adjacentPos < allyDeck->cardCount)
        {
            HealCard(allyDeck->cards[adjacentPos], 3);
            TraceLog(LOG_INFO, "%s heals adjacent ally %s for 3 HP!", 
                     self->name, allyDeck->cards[adjacentPos]->name);
        }
    }
}

void AbilityHomemMeianoite(Card *self, Card *attacker, CardDeck *enemyDeck)
{
    // 40% chance of evasion on first attack, counter with 4 fixed damage
    if (!self->ability_used && (float)rand() / RAND_MAX < 0.4f)
    {
        self->ability_used = true;
        TraceLog(LOG_INFO, "%s evades with counter-attack: 4 fixed damage!", self->name);
        TakeDamage(attacker, 4);
    }
}
