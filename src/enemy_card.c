#include "enemy_card.h"
#include "card.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

// ============== ENEMY CARD INITIALIZERS ==============

void InitSoldadoMosquete(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Soldado de Mosquete", "assets/card.png", 8, GetRandomInt(1, 3), 5, 0.05f, position);
    card->role = SOLDADO_MOSQUETE;
    card->team = ENEMY;
    card->ability_used = false;
}

void InitArtilheiroCanhao(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Artilheiro com Canhão", "assets/card.png", 7, GetRandomInt(2, 4), 6, 0.1f, position);
    card->role = ARTILHEIRO_CANHAO;
    card->team = ENEMY;
    card->ability_used = false;
}

void InitAlabardeiro(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Alabardeiro", "assets/card.png", 6, GetRandomInt(4, 7), 11, 0.08f, position);
    card->role = ALABARDEIRO;
    card->team = ENEMY;
    card->ability_used = false;
}

void InitOficialCavalaria(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Oficial de Cavalaria", "assets/card.png", 8, GetRandomInt(2, 5), 7, 0.12f, position);
    card->role = OFICIAL_CAVALARIA;
    card->team = ENEMY;
    card->ability_used = false;
}

void InitEngenheiroNaval(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Engenheiro Naval", "assets/card.png", 3, GetRandomInt(3, 6), 7, 0.15f, position);
    card->role = ENGENHEIRO_NAVAL;
    card->team = ENEMY;
    card->ability_used = false;
}

void InitArcabuzeiro(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Arcabuzeiro", "assets/card.png", 6, GetRandomInt(2, 4), 6, 0.1f, position);
    card->role = ARCABUZEIRO;
    card->team = ENEMY;
    card->ability_used = false;
}

void InitCapitaoGuarda(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Capitão da Guarda", "assets/card.png", 8, GetRandomInt(4, 7), 14, 0.05f, position);
    card->role = CAPITAO_GUARDA;
    card->team = ENEMY;
    card->ability_used = false;
    card->firstAttackImmunity = true;
}

void InitJohanMaurits(Card *card, int id, Vector2 position)
{
    InitCard(card, id, "Johan Maurits van Nassau", "assets/card.png", 9, GetRandomInt(5, 8), 16, 0.08f, position);
    card->role = JOHAN_MAURITS;
    card->team = ENEMY;
    card->ability_used = false;
}

// ============== ENEMY CARD ABILITIES ==============

void AbilitySoldadoMosquete(Card *self, CardDeck *allyDeck)
{
    // Attacks before melee, full damage to first ally
    Card *firstAlly = GetCurrentCard(allyDeck);
    if (firstAlly && !self->ability_used)
    {
        self->ability_used = true;
        TraceLog(LOG_INFO, "%s pre-attacks first ally %s for %d damage!", 
                 self->name, firstAlly->name, self->attack);
        TakeDamage(firstAlly, self->attack);
    }
}

void AbilityArtilheiroCanhao(Card *self, CardDeck *allyDeck)
{
    // Hits both first allies with same total damage (one-time use)
    if (!self->ability_used && allyDeck->cardCount >= 2)
    {
        self->ability_used = true;
        Card *first = allyDeck->cards[allyDeck->currentCardIndex];
        Card *second = (allyDeck->currentCardIndex + 1 < allyDeck->cardCount) ? 
                       allyDeck->cards[allyDeck->currentCardIndex + 1] : NULL;
        
        if (first && second)
        {
            int damagePerTarget = self->attack / 2;
            TraceLog(LOG_INFO, "%s bombards two targets for %d damage each!", 
                     self->name, damagePerTarget);
            TakeDamage(first, damagePerTarget);
            TakeDamage(second, damagePerTarget);
        }
    }
}

void AbilityAlabardeiro(Card *self)
{
    // Reduces first received damage by 50%, then normal defense
    if (!self->ability_used)
    {
        self->ability_used = true;
        self->shieldHP = 999;  // Marker for 50% reduction on next hit
        TraceLog(LOG_INFO, "%s takes stance: First damage reduced by 50%%!", self->name);
    }
}

void AbilityOficialCavalaria(Card *self, CardDeck *enemyDeck)
{
    // Advances 2 positions in deck, first attack after advance deals double damage
    if (!self->ability_used)
    {
        self->ability_used = true;
        enemyDeck->currentCardIndex = (enemyDeck->currentCardIndex + 2 < enemyDeck->cardCount) ?
                                       enemyDeck->currentCardIndex + 2 : enemyDeck->cardCount - 1;
        TraceLog(LOG_INFO, "%s charges forward 2 positions! Next attack: DOUBLE DAMAGE!", self->name);
    }
}

void AbilityEngenheiroNaval(Card *self, CardDeck *enemyDeck)
{
    // On entering combat, repairs 4 HP to ship (one-time)
    // On death, damages ship by 2 HP
    if (!self->ability_used)
    {
        self->ability_used = true;
        TraceLog(LOG_INFO, "%s repairs the ship for 4 HP!", self->name);
        // Ship repair logic would be handled by battle system
    }
}

void AbilityArcabuzeiro(Card *self, Card *target)
{
    // 35% chance to paralyze target for 1 turn
    if ((float)rand() / RAND_MAX < 0.35f)
    {
        target->paralyzeCounter = 1;
        TraceLog(LOG_INFO, "%s shoots %s with paralysis shot! %s is paralyzed and takes +30%% damage!", 
                 self->name, target->name, target->name);
    }
}

void AbilityCapitaoGuarda(Card *self)
{
    // Immune to first attack. After losing immunity, gains +3 ATK permanently
    if (self->firstAttackImmunity)
    {
        TraceLog(LOG_INFO, "%s is immune to this attack! After this, gains +3 ATK!", self->name);
        self->firstAttackImmunity = false;
        self->attack += 3;
    }
}

void AbilityJohanMaurits(Card *self, CardDeck *allyDeck)
{
    // After first hit, reverses enemy deck order (one-time use)
    if (!self->ability_used)
    {
        self->ability_used = true;
        
        // Reverse ally deck order
        for (int i = 0; i < allyDeck->cardCount / 2; i++)
        {
            Card *temp = allyDeck->cards[i];
            allyDeck->cards[i] = allyDeck->cards[allyDeck->cardCount - 1 - i];
            allyDeck->cards[allyDeck->cardCount - 1 - i] = temp;
        }
        
        TraceLog(LOG_INFO, "%s uses ultimate ability: REVERSES ENEMY DECK ORDER!", self->name);
    }
}
