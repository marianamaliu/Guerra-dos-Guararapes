#ifndef ALLY_CARD_H
#define ALLY_CARD_H

#include "card.h"

/**
 * Ally Card Initializers - Each creates a card with specific stats and role
 */

void InitZumbiPalmares(Card *card, int id, Vector2 position);
void InitGangaZumba(Card *card, int id, Vector2 position);
void InitCangaceiro(Card *card, int id, Vector2 position);
void InitMestreFrevo(Card *card, int id, Vector2 position);
void InitCaboclinho(Card *card, int id, Vector2 position);
void InitReiMaracatu(Card *card, int id, Vector2 position);
void InitDamaPaco(Card *card, int id, Vector2 position);
void InitHomemMeianoite(Card *card, int id, Vector2 position);

/**
 * Ally Card Abilities - Called during battle phases
 */

// Zumbi dos Palmares: First in line, triple damage and ignores shields on first attack
void AbilityZumbiPalmares(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck);

// Ganga Zumba: Last position, blocks first attack received (one-time use)
void AbilityGangaZumba(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck);

// Cangaceiro: Instakill on enemies with less than 30% HP at odd positions
void AbilityCangaceiro(Card *self, Card *enemy);

// Mestre do Frevo: Center position, attacks twice per duel (50% on second hit)
void AbilityMestreFrevo(Card *self, CardDeck *enemyDeck);

// Caboclinho: Between two allies, hits main target + second enemy with 50% damage
void AbilityCaboclinho(Card *self, CardDeck *allyDeck, CardDeck *enemyDeck);

// Rei do Maracatu: Position 1 or last, grants 3 HP shield to ally behind (one-time use)
void AbilityReiMaracatu(Card *self, CardDeck *allyDeck);

// Dama do Paço: On entering combat, heals 3 HP of adjacent ally (one-time effect)
void AbilityDamaPaco(Card *self, CardDeck *allyDeck);

// Homem da Meia-Noite: 40% evasion on first attack, counter with 4 fixed damage
void AbilityHomemMeianoite(Card *self, Card *attacker, CardDeck *enemyDeck);

#endif
