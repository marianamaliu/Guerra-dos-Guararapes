#ifndef ENEMY_CARD_H
#define ENEMY_CARD_H

#include "card.h"

/**
 * Enemy Card Initializers - Each creates a card with specific stats and role
 */

void InitSoldadoMosquete(Card *card, int id, Vector2 position);
void InitArtilheiroCanhao(Card *card, int id, Vector2 position);
void InitAlabardeiro(Card *card, int id, Vector2 position);
void InitOficialCavalaria(Card *card, int id, Vector2 position);
void InitEngenheiroNaval(Card *card, int id, Vector2 position);
void InitArcabuzeiro(Card *card, int id, Vector2 position);
void InitCapitaoGuarda(Card *card, int id, Vector2 position);
void InitJohanMaurits(Card *card, int id, Vector2 position);

/**
 * Enemy Card Abilities - Called during battle phases
 */

// Soldado de Mosquete: Attacks before melee, full damage to first ally
void AbilitySoldadoMosquete(Card *self, CardDeck *allyDeck);

// Artilheiro com Canhão: Hits both first allies with same total damage (one-time use)
void AbilityArtilheiroCanhao(Card *self, CardDeck *allyDeck);

// Alabardeiro: Reduces first received damage by 50%, then normal defense
void AbilityAlabardeiro(Card *self);

// Oficial de Cavalaria: Advances 2 positions, first attack after advance deals double damage
void AbilityOficialCavalaria(Card *self, CardDeck *enemyDeck);

// Engenheiro Naval: On entering combat, repairs 4 HP to ship (one-time). Losing him damages ship
void AbilityEngenheiroNaval(Card *self, CardDeck *enemyDeck);

// Arcabuzeiro: 35% chance to paralyze target for 1 turn (target takes +30% damage while paralyzed)
void AbilityArcabuzeiro(Card *self, Card *target);

// Capitão da Guarda: Immune to first attack. After losing immunity, gains +3 ATK permanently
void AbilityCapitaoGuarda(Card *self);

// Johan Maurits van Nassau (Boss): After first hit, reverses enemy deck order (one-time use)
void AbilityJohanMaurits(Card *self, CardDeck *allyDeck);

#endif
