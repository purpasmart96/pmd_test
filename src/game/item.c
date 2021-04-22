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

#include "util.h"
#include "common/error.h"
#include "common/exception.h"

#include "game/dungeon.h"
#include "game/pokemon.h"
#include "game/item.h"
#include "game/items/apples.h"
#include "game/items/berries.h"

static const char *item_to_string[] =
{
    "None",
    "Stick",
    "IronThorn",
    "SilverSpike",
    "GoldFang",
    "CacneaSpike",
    "CorsolaTwig",
    "Gravelerock",
    "GeoPebble",
    "GoldThorn",
    "RareFossil",
    "NoSlipCap",
    "YRaySpecs",
    "GaggleSpecs",
    "MobileScarf",
    "HealRibbon",
    "TwistBand",
    "ScopeLens",
    "PatsyBand",
    "NoStickCap",
    "PierceBand",
    "JoyRibbon",
    "XRaySpecs",
    "PersimBand",
    "PowerBand",
    "PechaScarf",
    "Insomniscope",
    "WarpScarf",
    "TightBelt",
    "SneakScarf",
    "GoldRibbon",
    "GoggleSpecs",
    "DietRibbon",
    "TrapScarf",
    "RacketBand",
    "DefScarf",
    "StaminaBand",
    "PlainRibbon",
    "SpecialBand",
    "ZincBand",
    "DetectBand",
    "SpaceGlobe",
    "DodgeScarf",
    "BounceBand",
    "CurveBand",
    "WhiffSpecs",
    "NoAimScope",
    "LockonSpecs",
    "MunchBelt",
    "PassScarf",
    "WeatherBand",
    "FriendBow",
    "BeautyScarf",
    "SunRibbon",
    "LunarRibbon",
    "GoldenMask",
    "AmberTear",
    "IcyFlute",
    "FieryDrum",
    "TerraCymbal",
    "AquaMonica",
    "RockHorn",
    "GrassCornet",
    "SkyMelodica",
    "MiracleChest",
    "WonderChest",
    "IQBooster",
    "HealSeed",
    "OranBerry",
    "SitrusBerry",
    "EyedropSeed",
    "ReviverSeed",
    "BlinkerSeed",
    "DoomSeed",
    "XEyeSeed",
    "LifeSeed",
    "RawstBerry",
    "HungerSeed",
    "QuickSeed",
    "PechaBerry",
    "CheriBerry",
    "TotterSeed",
    "SleepSeed",
    "PlainSeed",
    "WarpSeed",
    "BlastSeed",
    "Ginseng",
    "JoySeed",
    "ChestoBerry",
    "StunSeed",
    "GabiteScale",
    "GoldenSeed",
    "VileSeed",
    "PureSeed",
    "ViolentSeed",
    "VanishSeed",
    "MaxElixir",
    "Protein",
    "Calcium",
    "Iron",
    "Nectar",
    "DropeyeSeed",
    "ReviserSeed",
    "SlipSeed",
    "ViaSeed",
    "Zinc",
    "Apple",
    "BigApple",
    "GrimyFood",
    "HugeApple",
    "GoldenApple",
    "MixElixir",
    "OrenBerry",
    "DoughSeed",
    "WhiteGummi",
    "RedGummi",
    "BlueGummi",
    "GrassGummi",
    "YellowGummi",
    "ClearGummi",
    "OrangeGummi",
    "PinkGummi",
    "BrownGummi",
    "SkyGummi",
    "GoldGummi",
    "GreenGummi",
    "GrayGummi",
    "PurpleGummi",
    "RoyalGummi",
    "BlackGummi",
    "SilverGummi",
    "WonderGummi",
    "Gravelyrock",
    "Upgrade",
    "KingsRock",
    "Thunderstone",
    "Deepseascale",
    "Deepseatooth",
    "SunStone",
    "MoonStone",
    "FireStone",
    "WaterStone",
    "MetalCoat",
    "LeafStone",
    "DragonScale",
    "LinkCable",
    "DubiousDisc",
    "Protector",
    "ReaperCloth",
    "RazorFang",
    "RazorClaw",
    "Electirizer",
    "Magmarizer",
    "OvalStone",
    "DawnStone",
    "ShinyStone",
    "DuskStone",
    "CoronetRock",
    "MossyRock",
    "FrozenRock",
    "GonePebble",
    "WanderGummi",
    "PrizeTicket",
    "SilverTicket",
    "GoldTicket",
    "PrismTicket",
    "MysteryPart",
    "SecretSlab",
    "WonderEgg",
    "Gracidea",
    "SkyGift",
    "Key",
    "Poke",
    "LostLoot",
    "UsedTM",
};


static struct ItemTable
{
    Items type;
    void(*Throw)(struct Bag *, struct PokemonParty *, struct Pokemon_s *, ItemLocation, Items item);
    void(*Use)(struct Bag *, struct PokemonParty *, struct Pokemon_s *, ItemLocation, Items item);
    void(*Drop)(struct Bag *, struct PokemonParty *, struct Pokemon_s *, ItemLocation, Items item);
    void(*Reserved0)();
    void(*Reserved1)();
    void(*Reserved2)();

} item_table[] =
{
    {
        None,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        IronThorn,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SilverSpike,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldFang,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        CacneaSpike,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        CorsolaTwig,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Gravelerock,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GeoPebble,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldThorn,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        RareFossil,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NoSlipCap,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        YRaySpecs,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GaggleSpecs,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MobileScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        HealRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        TwistBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ScopeLens,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PatsyBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NoStickCap,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PierceBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        JoyRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        XRaySpecs,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PersimBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PowerBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PechaScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Insomniscope,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WarpScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        TightBelt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SneakScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoggleSpecs,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DietRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        TrapScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        RacketBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DefScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        StaminaBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PlainRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SpecialBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ZincBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DetectBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SpaceGlobe,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DodgeScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BounceBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        CurveBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WhiffSpecs,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NoAimScope,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        LockonSpecs,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MunchBelt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PassScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WeatherBand,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        FriendBow,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BeautyScarf,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SunRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        LunarRibbon,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldenMask,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        AmberTear,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        IcyFlute,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        FieryDrum,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        TerraCymbal,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        AquaMonica,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        RockHorn,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GrassCornet,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SkyMelodica,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MiracleChest,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WonderChest,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        IQBooster,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        HealSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        OranBerry,
        &OranBerryThrow,
        &OranBerryUse,
        &OranBerryDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        SitrusBerry,
        &SitrusBerryThrow,
        &SitrusBerryUse,
        &SitrusBerryDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        EyedropSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ReviverSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BlinkerSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DoomSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        XEyeSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        LifeSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        RawstBerry,
        &RawstBerryThrow,
        &RawstBerryUse,
        &RawstBerryDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        HungerSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        QuickSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PechaBerry,
        &PechaBerryThrow,
        &PechaBerryUse,
        &PechaBerryDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        CheriBerry,
        &CheriBerryThrow,
        &CheriBerryUse,
        &CheriBerryDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        TotterSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SleepSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PlainSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WarpSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BlastSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Ginseng,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        JoySeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ChestoBerry,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        StunSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GabiteScale,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldenSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        VileSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PureSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ViolentSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        VanishSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MaxElixir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Protein,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Calcium,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Iron,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Nectar,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DropeyeSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ReviserSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SlipSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ViaSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Zinc,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Apple,
        &AppleThrow,
        &AppleUse,
        &AppleDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        BigApple,
        &BigAppleThrow,
        &BigAppleUse,
        &BigAppleDrop,
        NULL,
        NULL,
        NULL,
    },
    {
        GrimyFood,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        HugeApple,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldenApple,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MixElixir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        OrenBerry,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        DoughSeed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WhiteGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        RedGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BlueGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GrassGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        YellowGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        ClearGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        OrangeGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PinkGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BrownGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SkyGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GoldGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GreenGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GrayGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        PurpleGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        RoyalGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        BlackGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SilverGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WonderGummi,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Gravelyrock,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Upgrade,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        KingsRock,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Thunderstone,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Deepseascale,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Deepseatooth,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SunStone,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MoonStone,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        FireStone,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        WaterStone,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        MetalCoat,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        LeafStone,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },

    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        Stick,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};


Bag *Bag_New(bool init)
{
    Bag *bag = malloc(sizeof(*bag));

    if (!bag)
    {
        return NULL;
    }
    else if (init)
    {
        Bag_Init(bag);
    }
    
    return bag;
}

void Bag_Init(Bag *self)
{
    self->capacity = MAX_ITEMS;
    self->items = malloc(sizeof(*self->items) * self->capacity);
    ClearBag(self);
}

void Bag_ShutDown(Bag *self)
{
    free(self->items);
    free(self);
}

void ClearBag(struct Bag *self)
{
    self->size = NO_ITEMS;
    self->real_size = NO_ITEMS;
    for (int i = 0; i < self->capacity; i++)
    {
        Bag_AssignItem(self, i, "None");
    }
}

bool IsBagEmpty(struct Bag *self)
{
    return !self->size;
}

bool IsBagFull(struct Bag *self)
{
    return self->real_size == self->capacity;
}

void RemoveBagIndex(struct Bag *self, int index)
{
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    Bag_AssignItem(self, self->size, "None");
    self->size--;
    self->real_size--;
}

void Bag_CountSortItems(struct Bag *self, int n, int range)
{
    int *count = calloc(1, sizeof(int) * range);

    for (int i = 0; i < self->size - 1; i++)
    {
        count[self->items[i].type]++;
    }
   
    int index = 0;
    for (int i = 0; i < range; i++)
    {
        while (count[i] != 0)
        {
            self->items[index++].type = i;
            count[i]--;
        }
    }

    free(count);
}

void Bag_CountSortItemsDesc(struct Bag *self, int n, int range)
{
    int *count = calloc(1, sizeof(int) * range);

    for (int i = 0; i < self->size; i++)
    {
        count[self->items[i].type]++;
    }

    int k = range - 1;
    for (int i = 0; i < range; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            self->items[k--].type = i;
        }
    }

    free(count);
}

// Insertion sort
void Bag_SortItems(struct Bag *self)
{
    for (int i = 1; i < self->size; i++)
    {
        Item key = self->items[i];
        int j = i - 1;
        while (j >= 0 && self->items[j].type < key.type)
        {
            self->items[j + 1] = self->items[j];
            j--;
        }
        self->items[j + 1] = key;
    }
}

void Bag_DecrementExistingItemInBag(struct Bag *self, int index)
{
    self->items[index].size -= 1;
}

void Bag_IncrementExistingItemInBag(struct Bag *self, int index)
{
    self->items[index].size += 1;
}

// Returns index if it finds the same item type
// If not, it returns -1
int Bag_ItemAlreadyExists(struct Bag *self, Items type)
{
    for (int i = 0; i < self->capacity; i++)
    {
        if (self->items[i].type == type) // Find the same item
        {
            return i;
        }
    }
    return -1;
}

void DisplayBag(struct Bag *self)
{
    printf("\n");
    printf("Displaying Items currently in the bag\n");
    for (int i = 0; i < self->size; i++)
    {
        const int number_of_stacked = self->items[i].size;
        if (number_of_stacked > 1)
        {
            printf("%s(%d)\n", item_to_string[self->items[i].type], number_of_stacked);
        }
        else
        {
            printf("%s\n", item_to_string[self->items[i].type]);
        }
    }
    printf("\n");
}

void AddItemToBagByType(struct Bag *self, Items type)
{
    if (!IsBagFull(self))
    {
        for (int i = 0; i < self->capacity; i++)
        {
            int index = Bag_ItemAlreadyExists(self, type);
            if (index > -1 && type != None)
            {
                Bag_IncrementExistingItemInBag(self, index);
                self->real_size++;
                return;
            }
            else if (self->items[i].type == None) // Find a empty slot
            {
                self->items[i].type = type;
                Bag_AssignItem(self, i, item_to_string[type]);
                if (type != None)
                {
                    self->size++;
                    self->real_size++;
                }
                return;
            }
        }
    }
    else
    {
        printf("Bag is currently full!\n");
        printf("Can't add %s to the bag\n", item_to_string[type]);
        return;
    }
}

void AddItemToBag(struct Bag *self, Item item)
{
    if (!IsBagFull(self))
    {
        for (int i = 0; i < self->capacity; i++)
        {
            int index = Bag_ItemAlreadyExists(self, item.type);
            if (index > -1 && item.type != None)
            {
                Bag_IncrementExistingItemInBag(self, index);
                self->real_size++;
                return;
            }
            else if (self->items[i].type == None) // Find a empty slot
            {
                self->items[i] = item;
                if (item.type != None)
                {
                    self->size++;
                    self->real_size++;
                }
                return;
            }
        }
    }
    else
    {
        printf("Bag is currently full!\n");
        printf("Can't add %s to the bag\n", item_to_string[item.type]);
        return;
    }
}

// String version
void AddItemToBag_(Bag *self, const char *item_name)
{
    if (!IsBagFull(self))
    {
        for (int i = 0; i < self->capacity; i++)
        {
            if (self->items[i].type == None) // Find a empty slot
            {
                Bag_AssignItem(self, i, item_name);
                if (item_name != "None")
                {
                    self->size++;
                    self->real_size++;
                }
                return;
            }
        }
    }
    else
    {
        printf("Can't add %s to the bag\n", item_name);
        printf("Bag is currently full!\n");
        return;
    }
}

void RemoveItemFromBag(Bag *self, Item item)
{
    if (!IsBagEmpty(self))
    {
        for (int i = self->capacity - 1; i >= 0; i--)
        {
            int index = Bag_ItemAlreadyExists(self, item.type);
            if (index > -1 && self->items[i].size > 1)
            {
                Bag_DecrementExistingItemInBag(self, index);
                self->real_size--;
                return;
            }
            else if (self->items[i].type == item.type) // Find the slot that has the item were looking for
            {
                RemoveBagIndex(self, i);
                return;
            }
        }
    }
    else
    {
        printf("Bag is empty!\n");
        return;
    }
}

// String version
bool RemoveItemFromBag_(struct Bag *self, const char *item_name)
{
    if (!IsBagEmpty(self))
    {
        for (int i = self->capacity - 1; i >= 0; i--)
        {
            if (item_to_string[self->items[i].type] == item_name) // Find the slot that has the item were looking for
            {
                RemoveBagIndex(self, i);
                return true;
            }
        }
    }
    else
    {
        printf("Bag is empty!\n");
        return false;
    }

    ERROR("Couldn't find %s!\n", item_name);
    return false;
}

bool RemoveItemFromPokemon(struct Pokemon_s *poke)
{
    if (poke->held_item != None)
    {
        poke->held_item = None;
        return true;
    }
    else
    {
        printf("No item is currently on the pokemon!\n");
        return false;
    }
}


void AddItemToBagFromGround(struct Bag *bag, struct Pokemon_s *poke, Dungeon *dungeon)
{
    int item = GetItemFromTile(dungeon, floorf(poke->position.x), floorf(poke->position.y));

    if (!item)
        return;

    if (!IsBagFull(bag))
    {
        AddItemToBagByType(bag, item);
        RemoveItemFromTile(dungeon, (int)floorf(poke->position.x), (int)floorf(poke->position.y));
    }
    else
    {
        //printf("Can't add %s to the bag\n", item_name);
        printf("Bag is currently full!\n");
    }
    
}

bool RemoveItemFromGround(Dungeon *dungeon, struct Pokemon_s *poke)
{
    int item = GetItemFromTile(dungeon, poke->position.x, poke->position.y);

    if (item != None)
    {
        RemoveItemFromTile(dungeon, (int)floorf(poke->position.x), (int)floorf(poke->position.y));
        return true;
    }
    else
    {
        printf("No item is currently underneath the pokemon!\n");
        return false;
    }
}

bool RemoveItem(struct Bag *bag, struct Pokemon_s *poke, ItemLocation location, const char *item_name)
{
    switch (location)
    {
        case LocationBag:
            return RemoveItemFromBag_(bag, item_name);
        case LocationPokemonLeader:
            return RemoveItemFromPokemon(poke);
        case LocationGround:
            return RemoveItemFromGround(GetDungeonObject(), poke);
        default:
            printf("Couldn't find item %s!\n", item_name);
            return false;
    }
}

// Takes a item from the bag or ground and puts it on the desired team member
// If there is item already on it then swap it and put the current item
// that's on the team member back in the bag
void GiveItemToTeamMember(struct Bag *self, struct Pokemon_s *team_member, Item item)
{
    if (team_member->held_item == None)
    {
        printf("Gave the %s to the Team Member\n", item_to_string[item.type]);
        team_member->held_item = item.type;
        return;
    }
    else if (!IsBagFull(self))
    {
        printf("Put the %s in the bag\n", item_to_string[team_member->held_item]);
        //AddItemToBag(self, *team_member->held_item);
        AddItemToBagByType(self, team_member->held_item);
        printf("Gave the %s to %s\n", item_to_string[item.type], team_member->name);
        team_member->held_item = item.type;
        return;
    }
    else
    {
        // Do nothing
        printf("Cannot give Team Member a item!\n");
        return;
    }

}

// String Version
// Takes a item from the bag or ground and puts it on the desired team member
// If there is item already on it then swap it and put the current item
// that's on the team member back in the bag
void GiveItemToTeamMember_(struct Bag *self, struct Pokemon_s *team_member, const char *item_name)
{
    if (team_member->held_item == None)
    {
        printf("Gave the %s to the Team Member\n", item_name);
        Pokemon_AssignItem(team_member, item_name);
        return;
    }
    else if (!IsBagFull(self))
    {
        printf("Put the %s in the bag\n", item_to_string[team_member->held_item]);
        //AddItemToBag(self, *team_member->held_item);
        AddItemToBagByType(self, team_member->held_item);
        printf("Gave the %s to %s\n", item_name, team_member->name);
        Pokemon_AssignItem(team_member, item_name);
        return;
    }
    else
    {
        // Do nothing
        printf("Cannot give Team Member a item!\n");
        return;
    }

}

// Removes the item from the team member and puts it in the bag
void RemoveItemFromTeamMemberToBag(struct Bag *self, struct Pokemon_s *team_member, Item item)
{
    if (team_member->held_item != None)
    {
        if (!IsBagFull(self))
        {
            RemoveItemFromPokemon(team_member);
            AddItemToBag(self, item);
            return;
        }
        else
        {
            // Do nothing
            printf("Cannot take item from Team Member!\n");
            return;
        }
    }
    else
    {
        printf("There is no item on it!\n");
        return;
    }
}

// String version
// Removes the item from the team member and puts it in the bag
void RemoveItemFromTeamMemberToBag_(struct Bag *self, struct Pokemon_s *team_member, const char *item_name)
{
    if (team_member->held_item != None)
    {
        if (!IsBagFull(self))
        {
            RemoveItemFromPokemon(team_member);
            AddItemToBag_(self, item_name);
            return;
        }
        else
        {
            // Do nothing
            printf("Cannot take item from Team Member!\n");
            return;
        }
    }
    else
    {
        printf("There is no item on it!\n");
        return;
    }
}

void Pokemon_AssignItem(struct Pokemon_s *dst_poke, const char *item_name)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        if (item_to_string[item_table[i].type] == item_name)
        {
            dst_poke->held_item = item_table[i].type;
            //dst_poke->held_item->type  = item_table[i].type;
            //dst_poke->held_item->Throw = item_table[i].Throw;
            //dst_poke->held_item->Use   = item_table[i].Use;
            //dst_poke->held_item->Drop  = item_table[i].Drop;
        }
    }
}

void Bag_AssignItem(struct Bag *bag, int index, const char *item_name)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        if (item_to_string[item_table[i].type] == item_name)
        {
            bag->items[index].size = 1;
            bag->items[index].type  = item_table[i].type;
            bag->items[index].Throw = item_table[i].Throw;
            bag->items[index].Use   = item_table[i].Use;
            bag->items[index].Drop  = item_table[i].Drop;
        }
    }
}

void Bag_AssignItemByType(struct Bag *bag, int index, Items type)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        if (item_table[i].type == type)
        {
            bag->items[index].Throw = item_table[i].Throw;
            bag->items[index].Use   = item_table[i].Use;
            bag->items[index].Drop  = item_table[i].Drop;
        }
    }
}

void UseItem(struct Bag *bag, PokemonParty *party, struct Pokemon_s *user, const char *item_name, ItemLocation location)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        Items enum_item = item_table[i].type;
        if (item_to_string[enum_item] == item_name)
        {
            item_table[i].Use(bag, party, user, location, enum_item);
        }
    }
}

void UseItemFromBag(struct Bag *bag, PokemonParty *party, struct Pokemon_s *user, const char *item_name)
{
    UseItem(bag, party, user, item_name, LocationBag);
}
