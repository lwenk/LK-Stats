#pragma once

#include "mc/server/ServerPlayer.h"
#include "mc/world/actor/ActorDamageSource.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/effect/MobEffectInstance.h"
#include "mc/world/item/ItemStackBase.h"

namespace stats {
namespace event {
namespace player {
void onJoin(Player& player);
void onLeft(ServerPlayer& player);
void onTakeItem(Player& player, ItemStack& item);
void onDropItem(Player* player, ItemStack const& item);
void onDied(Player& player, ActorDamageSource const& source);
void onKillMob(Player& player, Mob& mob);
void onTakenDamage(Player* player, float damage, float afterDamage);
void onDealtDamage(Mob* mob, Player* player, float damage, float afterDamage);
void onCraftedItem();
void onItemHurtAndBroken(Player* player, ItemStackBase* item, int deltaDamage);
void onUsedItem(Player* player, ItemStackBase& instance, ItemUseMethod itemUseMethod, bool consumeItem);
void onEffectAdded(Player* player, MobEffectInstance const& effect);
void onStartSleep(Player* player);
void onBlockUsingShield(Player* player, float damage);
void onOpenTrading(Player* player);
void onJump(Player& player);
void onMove();
void onChangeContainerWith(
    Player&          player,
    std::string      blockType,
    int              slot,
    ItemStack const& oldItem,
    ItemStack const& newItem
);
} // namespace player
} // namespace event
} // namespace stats