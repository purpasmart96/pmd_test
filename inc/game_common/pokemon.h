// Copyright(c) 2015 Purpasmart
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _POKEMON_MANAGER_H_
#define _POKEMON_MANAGER_H_

#include "util.h"
#include "common/vec.h"


typedef enum Sex
{
    Male,
    Female,
    GenderLess,
} Sex;


typedef enum AbilityTypes
{
    NoAbility,
    Stench, Drizzle, SpeedBoost, BattleArmor, Sturdy, Damp, Limber, SandVeil, Static,
    VoltAbsorb, WaterAbsorb, Oblivious, CloudNine, Compoundeyes, Insomnia, ColorChange, Immunity, FlashFire,
    ShieldDust, OwnTempo, SuctionCups, Intimidate, ShadowTag, RoughSkin, WonderGuard, Levitate, EffectSpore,
    Synchronize, ClearBody, NaturalCure, Lightningrod, SereneGrace, SwiftSwim, Chlorophyll,
    Illuminate, Trace, HugePower, PoisonPoint, InnerFocus, MagmaArmor, WaterVeil, MagnetPull,
    Soundproof, RainDish, SandStream, Pressure, ThickFat, EarlyBird, FlameBody, RunAway, KeenEye, HyperCutter,
    Pickup, Truant, Hustle, CuteCharm, Plus, Minus, Forecast, StickyHold, ShedSkin, Guts, MarvelScale,
    LiquidOoze, Overgrow, Blaze, Torrent, Swarm, RockHead, Drought, ArenaTrap, VitalSpirit, WhiteSmoke,
    PurePower, ShellArmor, AirLock, TangledFeet, MotorDrive, Rivalry, Steadfast, SnowCloak, Gluttony,
    AngerPoint, Unburden, Heatproof, Simple, DrySkin, Download, IronFist, PoisonHeal, Adaptability,
    SkillLink, Hydration, SolarPower, QuickFeet, Normalize, Sniper, MagicGuard, NoGuard, Stall, Technician,
    LeafGuard, Klutz, MoldBreaker, SuperLuck, Aftermath, Anticipation, Forewarn, Unaware,
    TintedLens, Filter, SlowStart, Scrappy, StormDrain, IceBody, SolidRock, SnowWarning, HoneyGather,
    Frisk, Reckless, Multitype, FlowerGift, BadDreams, Pickpocket, SheerForce, Contrary, Unnerve,
    Defiant, Defeatist, CursedBody, Healer, FriendGuard, WeakArmor, HeavyMetal, LightMetal, Multiscale,
    ToxicBoost, FlareBoost, Harvest, Telepathy, Moody, Overcoat, PoisonTouch, Regenerator, BigPecks,
    SandRush, WonderSkin, Analytic, Illusion, Imposter, Infiltrator, Mummy, Moxie, Justified, Rattled,
    MagicBounce, SapSipper, Prankster, SandForce, IronBarbs, ZenMode, VictoryStar, Turboblaze, Teravolt,
    AromaVeil, FlowerVeil, CheekPouch, Protean, FurCoat, Magician, Bulletproof, Competitive, StrongJaw,
    Refrigerate, SweetVeil, StanceChange, GaleWings, MegaLauncher, GrassPelt, Symbiosis, ToughClaws,
    Pixilate, Gooey, Aerilate, ParentalBond, DarkAura, FairyAura, AuraBreak, PrimordialSea, DesolateLand,
    DeltaStream,
} AbilityTypes;

typedef enum Type
{
    TypeNone,
    Normal,
    Fighting,
    Flying,
    Poison,
    Ground,
    Rock,
    Bug,
    Ghost,
    Steel,
    Fire,
    Water,
    Grass,
    Electric,
    Psychc,
    Ice,
    Dragon,
    Dark,
    Fairy,
} Type;

typedef enum Species
{
    Bulbasaur = 1,
    Ivysaur,
    Venusaur,
    Charmander,
    Charmeleon,
    Charizard,
    Squirtle,
    Wartortle,
    Blastoise,
    Caterpie,
    Metapod,
    Butterfree,
    Weedle,
    Kakuna,
    Beedrill,
    Pidgey,
    Pidgeotto,
    Pidgeot,
    Rattata,
    Raticate,
    Spearow,
    Fearow,
    Ekans,
    Arbok,
    Pikachu,
    Raichu,
    Sandshrew,
    Sandslash,
    Nidoran_f,
    Nidorina,
    Nidoqueen,
    Nidoran_m,
    Nidorino,
    Nidoking,
    Clefairy,
    Clefable,
    Vulpix,
    Ninetales,
    Jigglypuff,
    Wigglytuff,
    Zubat,
    Golbat,
    Oddish,
    Gloom,
    Vileplume,
    Paras,
    Parasect,
    Venonat,
    Venomoth,
    Diglett,
    Dugtrio,
    Meowth,
    Persian,
    Psyduck,
    Golduck,
    Mankey,
    Primeape,
    Growlithe,
    Arcanine,
    Poliwag,
    Poliwhirl,
    Poliwrath,
    Abra,
    Kadabra,
    Alakazam,
    Machop,
    Machoke,
    Machamp,
    Bellsprout,
    Weepinbell,
    Victreebel,
    Tentacool,
    Tentacruel,
    Geodude,
    Graveler,
    Golem,
    Ponyta,
    Rapidash,
    Slowpoke,
    Slowbro,
    Magnemite,
    Magneton,
    Farfetchd,
    Doduo,
    Dodrio,
    Seel,
    Dewgong,
    Grimer,
    Muk,
    Shellder, Cloyster, Gastly,
    Haunter, Gengar, Onix,
    Drowzee, Hypno, Krabby,
    Kingler, Voltorb, Electrode,
    Exeggcute, Exeggutor, Cubone,
    Marowak, Hitmonlee, Hitmonchan,
    Lickitung, Koffing, Weezing, Rhyhorn, Rhydon, Chansey, Tangela, Kangaskhan,
    Horsea, Seadra, Goldeen, Seaking, Staryu, Starmie, Mr_Mime, Scyther, Jynx, Electabuzz, Magmar, Pinsir, Tauros, Magikarp, Gyarados, Lapras, Ditto,
    Eevee, Vaporeon, Jolteon, Flareon, Porygon, Omanyte, Omastar, Kabuto, Kabutops, Aerodactyl, Snorlax, Articuno, Zapdos, Moltres, Dratini, Dragonair, Dragonite, Mewtwo, Mew, Chikorita, Bayleef, Meganium,
    Cyndaquil, Quilava, Typhlosion, Totodile, Croconaw, Feraligatr, Sentret, Furret, Hoothoot, Noctowl, Ledyba, Ledian, Spinarak, Ariados, Crobat, Chinchou, Lanturn, Pichu, Cleffa, Igglybuff, Togepi, Togetic,
    Natu, Xatu, Mareep, Flaaffy, Ampharos, Bellossom, Marill, Azumarill, Sudowoodo, Politoed, Hoppip, Skiploom, Jumpluff, Aipom, Sunkern, Sunflora, Yanma, Wooper, Quagsire, Espeon, Umbreon, Murkrow, Slowking,
    Misdreavus, Unown, Wobbuffet, Girafarig, Pineco, Forretress, Dunsparce, Gligar, Steelix, Snubbull, Granbull, Qwilfish, Scizor, Shuckle, Heracross, Sneasel, Teddiursa, Ursaring, Slugma, Magcargo,
    Swinub, Piloswine, Corsola, Remoraid, Octillery, Delibird, Mantine, Skarmory, Houndour, Houndoom, Kingdra, Phanpy, Donphan, Porygon2, Stantler, Smeargle, Tyrogue, Hitmontop, Smoochum, Elekid, Magby,
    Miltank, Blissey, Raikou, Entei, Suicune, Larvitar, Pupitar, Tyranitar, Lugia, Ho_Oh, Celebi, Treecko, Grovyle, Sceptile, Torchic, Combusken, Blaziken, Mudkip, Marshtomp, Swampert, Poochyena, Mightyena,
    Zigzagoon, Linoone, Wurmple, Silcoon, Beautifly, Cascoon, Dustox, Lotad, Lombre, Ludicolo, Seedot, Nuzleaf, Shiftry, Taillow, Swellow, Wingull, Pelipper, Ralts, Kirlia, Gardevoir, Surskit, Masquerain,
    Shroomish, Breloom, Slakoth, Vigoroth, Slaking, Nincada, Ninjask, Shedinja, Whismur, Loudred, Exploud, Makuhita, Hariyama, Azurill, Nosepass, Skitty, Delcatty, Sableye, Mawile, Aron, Lairon, Aggron,
    Meditite, Medicham, Electrike, Manectric, Plusle, Minun, Volbeat, Illumise, Roselia, Gulpin, Swalot, Carvanha, Sharpedo, Wailmer, Wailord, Numel, Camerupt, Torkoal, Spoink, Grumpig, Spinda,
    Trapinch, Vibrava, Flygon, Cacnea, Cacturne, Swablu, Altaria, Zangoose, Seviper, Lunatone, Solrock, Barboach, Whiscash, Corphish, Crawdaunt, Baltoy, Claydol, Lileep, Cradily, Anorith, Armaldo,
    Feebas, Milotic, Castform, Kecleon, Shuppet, Banette, Duskull, Dusclops, Tropius, Chimecho, Absol, Wynaut, Snorunt, Glalie, Spheal, Sealeo, Walrein, Clamperl, Huntail, Gorebyss, Relicanth, Luvdisc,
    Bagon, Shelgon, Salamence, Beldum, Metang, Metagross, Regirock, Regice, Registeel, Latias, Latios, Kyogre, Groudon, Rayquaza, Jirachi, Deoxys, Turtwig, Grotle, Torterra, Chimchar, Monferno, Infernape,
    Piplup, Prinplup, Empoleon, Starly, Staravia, Staraptor, Bidoof, Bibarel, Kricketot, Kricketune, Shinx, Luxio, Luxray, Budew, Roserade, Cranidos, Rampardos, Shieldon, Bastiodon, Burmy, Wormadam, Mothim,
    Combee, Vespiquen, Pachirisu, Buizel, Floatzel, Cherubi, Cherrim, Shellos, Gastrodon, Ambipom, Drifloon, Drifblim, Buneary, Lopunny, Mismagius, Honchkrow, Glameow, Purugly, Chingling, Stunky, Skuntank,
    Bronzor, Bronzong, Bonsly, Mime, Happiny, Chatot, Spiritomb, Gible, Gabite, Garchomp, Munchlax, Riolu, Lucario, Hippopotas, Hippowdon, Skorupi, Drapion, Croagunk, Toxicroak, Carnivine, Finneon, Lumineon,
    Mantyke, Snover, Abomasnow, Weavile, Magnezone, Lickilicky, Rhyperior, Tangrowth, Electivire, Magmortar, Togekiss, Yanmega, Leafeon, Glaceon, Gliscor, Mamoswine, Porygon_Z, Gallade, Probopass, Dusknoir,
    Froslass, Rotom, Uxie, Mesprit, Azelf, Dialga, Palkia, Heatran, Regigigas, Giratina, Cresselia, Phione, Manaphy, Darkrai, Shaymin, Arceus, Victini, Snivy, Servine, Serperior, Tepig, Pignite, Emboar,
    Oshawott, Dewott, Samurott, Patrat, Watchog, Lillipup, Herdier, Stoutland, Purrloin, Liepard, Pansage, Simisage, Pansear, Simisear, Panpour, Simipour, Munna, Musharna, Pidove, Tranquill, Unfezant,
    Blitzle, Zebstrika, Roggenrola, Boldore, Gigalith, Woobat, Swoobat, Drilbur, Excadrill, Audino, Timburr, Gurdurr, Conkeldurr, Tympole, Palpitoad, Seismitoad, Throh, Sawk, Sewaddle, Swadloon, Leavanny,
    Venipede, Whirlipede, Scolipede, Cottonee, Whimsicott, Petilil, Lilligant, Basculin, Sandile, Krokorok, Krookodile, Darumaka, Darmanitan, Maractus, Dwebble, Crustle, Scraggy, Scrafty, Sigilyph,
    Yamask, Cofagrigus, Tirtouga, Carracosta, Archen, Archeops, Trubbish, Garbodor, Zorua, Zoroark, Minccino, Cinccino, Gothita, Gothorita, Gothitelle, Solosis, Duosion, Reuniclus, Ducklett, Swanna,
    Vanillite, Vanillish, Vanilluxe, Deerling, Sawsbuck, Emolga, Karrablast, Escavalier, Foongus, Amoonguss, Frillish, Jellicent, Alomomola, Joltik, Galvantula, Ferroseed, Ferrothorn, Klink, Klang, Klinklang,
    Tynamo, Eelektrik, Eelektross, Elgyem, Beheeyem, Litwick, Lampent, Chandelure, Axew, Fraxure, Haxorus, Cubchoo, Beartic, Cryogonal, Shelmet, Accelgor, Stunfisk, Mienfoo, Mienshao, Druddigon, Golett, Golurk,
    Pawniard, Bisharp, Bouffalant, Rufflet, Braviary, Vullaby, Mandibuzz, Heatmor, Durant, Deino, Zweilous, Hydreigon, Larvesta, Volcarona, Cobalion, Terrakion, Virizion, Tornadus, Thundurus, Reshiram, Zekrom,
    Landorus, Kyurem, Keldeo, Meloetta, Genesect, Chespin, Quilladin, Chesnaught, Fennekin, Braixen, Delphox, Froakie, Frogadier, Greninja, Bunnelby, Diggersby, Fletchling, Fletchinder, Talonflame,
    Scatterbug, Spewpa, Vivillon, Litleo, Pyroar, Flabébé, Floette, Florges, Skiddo, Gogoat, Pancham, Pangoro, Furfrou, Espurr, Meowstic, Honedge, Doublade, Aegislash, Spritzee, Aromatisse, Swirlix, Slurpuff,
    Inkay, Malamar, Binacle, Barbaracle, Skrelp, Dragalge, Clauncher, Clawitzer, Helioptile, Heliolisk, Tyrunt, Tyrantrum, Amaura, Aurorus, Sylveon, Hawlucha, Dedenne, Carbink, Goomy, Sliggoo, Goodra, Klefki,
    Phantump, Trevenant, Pumpkaboo, Gourgeist, Bergmite, Avalugg, Noibat, Noivern, Xerneas, Yveltal, Zygarde, Diancie, Hoopa, Volcanion,
} Species;

typedef struct Ability
{
    AbilityTypes ability_enum;
    char *name;
    char *description;
} Ability;

union ivec2;

typedef struct Pokemon_s
{
    char name[16];
    Species species;
    Type primary_type;
    Type sub_type;
    Ability ability;
    Sex sex;
    u64 exp;
    int level;
    int current_hp;
    int max_hp;
    u8 attack;
    u8 sp_attack;
    u8 defense;
    u8 sp_defense;
    u8 speed;

    struct Item *held_item;
    struct MoveSet *moves;
    struct DungeonStatus *status;
    ivec2 position;
} Pokemon_t;

typedef struct PokemonParty
{
    struct Pokemon_s **members;
    int capacity;
    int size;
} PokemonParty;

PokemonParty *PokemonParty_New(int capacity);

Pokemon_t *Pokemon_New(const char *name, Species species, Type primary_type, Type sub_type, AbilityTypes ability, Sex sex, int level, int max_hp);

void AddPartyMember(PokemonParty *party, Pokemon_t *member);
Ability GetAbilityFromTable(AbilityTypes ability_name);
void SetPokemonName(Pokemon_t *pokemon, const char *name);
char *GetPokemonName(Pokemon_t *pokemon);
void SetPokemonAbility(Pokemon_t *pokemon, AbilityTypes ability_name);
AbilityTypes GetPokemonAbility(Pokemon_t *team_member);
Pokemon_t *GetCurrentLeader();

#endif
