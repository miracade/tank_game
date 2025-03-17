#pragma once

enum class TileType { kNone, kDirt, kToughDirt, kStone, kToughStone, kCount };

struct TileTypeAttributes {
  bool is_solid;
  int toughness;
  Vec2i sprite_offset;
};

static constexpr EnumMap<TileType, TileTypeAttributes> kTileTypeAttributes{
    {TileType::kNone, TileTypeAttributes{false, 0, {0, 0}}},
    {TileType::kDirt, TileTypeAttributes{true, 1, {0, 7}}},
    {TileType::kToughDirt, TileTypeAttributes{true, 3, {1, 7}}},
    {TileType::kStone, TileTypeAttributes{true, 6, {2, 6}}},
    {TileType::kToughStone, TileTypeAttributes{true, 8, {3, 6}}},
};

enum class LootType {
  kNone,
  kCoal1 = 4,
  kCoal2,
  kCoal3,
  kCoal4,
  kCopper1,
  kCopper2,
  kCopper3,
  kCopper4,
  kIron1,
  kIron2,
  kIron3,
  kIron4,
  kBronze1,
  kBronze2,
  kBronze3,
  kBronze4,
  kGold1,
  kGold2,
  kGold3,
  kGold4,
  kCount,
};

struct LootTypeAttributes {
  int toughness;
  int dropped_item;
  int dropped_item_count;
  Vec2i sprite_offset;
};

static constexpr EnumMap<LootType, LootTypeAttributes> kLootTypeAttributes{
    {LootType::kNone, {0, {}, 0, {0, 0}}},
    {LootType::kCoal1, {1, {}, 1, {0, 0}}},
    {LootType::kCoal2, {2, {}, 2, {1, 0}}},
    {LootType::kCoal3, {3, {}, 3, {2, 0}}},
    {LootType::kCoal4, {4, {}, 4, {3, 0}}},
    {LootType::kBronze1, {1, {}, 1, {0, 1}}},
    {LootType::kBronze2, {2, {}, 2, {1, 1}}},
    {LootType::kBronze3, {3, {}, 3, {2, 1}}},
    {LootType::kBronze4, {4, {}, 4, {3, 1}}},
    {LootType::kIron1, {1, {}, 1, {0, 2}}},
    {LootType::kIron2, {2, {}, 2, {1, 2}}},
    {LootType::kIron3, {3, {}, 3, {2, 2}}},
    {LootType::kIron4, {4, {}, 4, {3, 2}}},
    {LootType::kGold1, {1, {}, 1, {0, 3}}},
    {LootType::kGold2, {2, {}, 2, {1, 3}}},
    {LootType::kGold3, {3, {}, 3, {2, 3}}},
    {LootType::kGold4, {4, {}, 4, {3, 3}}},
    {LootType::kCopper1, {1, {}, 1, {0, 4}}},
    {LootType::kCopper2, {2, {}, 2, {1, 4}}},
    {LootType::kCopper3, {3, {}, 3, {2, 4}}},
    {LootType::kCopper4, {4, {}, 4, {3, 4}}},
};

inline constexpr Vec2i kTileSize{32, 32};

struct Tile {
  TileType tile_type;
  LootType loot_type;
};
