// Copyright(c) <2015> <Purpasmart>
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

#include "game_common/dungeon_manager.h"
#include "game_common/pokemon_manager.h"
#include "game_common/item_manager.h"
#include "game_common/items/apples.h"

static const char *item_string[] =
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

static Items ItemStringToEnum(const char *item_name)
{
    if (item_name == "None")
    {
        return None;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "IronThorn")
    {
        return IronThorn;
    }
    else if (item_name == "SilverSpike")
    {
        return SilverSpike;
    }
    else if (item_name == "GoldFang")
    {
        return GoldFang;
    }
    else if (item_name == "CacneaSpike")
    {
        return CacneaSpike;
    }
    else if (item_name == "CorsolaTwig")
    {
        return CorsolaTwig;
    }
    else if (item_name == "Gravelerock")
    {
        return Gravelerock;
    }
    else if (item_name == "GeoPebble")
    {
        return GeoPebble;
    }
    else if (item_name == "GoldThorn")
    {
        return GoldThorn;
    }
    else if (item_name == "RareFossil")
    {
        return RareFossil;
    }
    else if (item_name == "NoSlipCap")
    {
        return NoSlipCap;
    }
    else if (item_name == "YRaySpecs")
    {
        return YRaySpecs;
    }
    else if (item_name == "GaggleSpecs")
    {
        return GaggleSpecs;
    }
    else if (item_name == "MobileScarf")
    {
        return MobileScarf;
    }
    else if (item_name == "HealRibbon")
    {
        return HealRibbon;
    }
    else if (item_name == "TwistBand")
    {
        return TwistBand;
    }
    else if (item_name == "ScopeLens")
    {
        return ScopeLens;
    }
    else if (item_name == "PatsyBand")
    {
        return PatsyBand;
    }
    else if (item_name == "NoStickCap")
    {
        return NoStickCap;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else if (item_name == "Stick")
    {
        return Stick;
    }
    else
    {
        return None;
    }
}

static struct ItemTable
{
    Items name;
    void(*Throw)(struct Bag *, struct PokemonParty *, struct Pokemon *, ItemLocation);
    void(*Use)(struct Bag *, struct PokemonParty *, struct Pokemon *, ItemLocation);
    void(*Drop)(struct Bag *, struct PokemonParty *, struct Pokemon *, ItemLocation);
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
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        SitrusBerry,
        NULL,
        NULL,
        NULL,
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
        NULL,
        NULL,
        NULL,
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
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        CheriBerry,
        NULL,
        NULL,
        NULL,
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


struct Bag *CreateBag(int capacity)
{
    struct Bag *bag = malloc(sizeof(*bag));
    //bag->capacity = capacity;
    //bag->items = (Item*)calloc(bag->capacity, sizeof(Item));
    ClearBag(bag);
    return bag;
}

/*
struct Bag *ResizeBag(Bag *self, int capacity)
{
    self->capacity = capacity;
    self->items = (Item*)realloc(self->items, self->capacity);

    if (!self->items)
    {
        return NULL;
    }
    else
    {
        return self;
    }
}
*/

void DestroyBag(struct Bag *self)
{
    //free(self->items);
    free(self);
}

void ClearBag(struct Bag *self)
{
    self->size = NO_ITEMS;
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        AssignItem(self->items[i], "None");
    }
}

bool IsBagEmpty(struct Bag *self)
{
    return !self->size;
}

bool IsBagFull(struct Bag *self)
{
    return self->size == MAX_ITEMS;
}

static void RenameNullItems(struct Bag *self)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (self->items[i].name == None) // Find a NULL slot
        {
            AssignItem(self->items[i], "None");
            return;
        }
    }
}

void RemoveBagIndex(struct Bag *self, int index)
{
    if ((index < 0) || (index >= self->size))
    {
        return;
    }

    //self->size--;
    for (int i = index; i < self->size; i++)
    {
        self->items[i] = self->items[i + 1];
        self->size--;
    }
}

void DisplayBag(struct Bag *self)
{
    printf("\n");
    printf("Displaying Items currently in the bag\n");
    for (int i = 0; i < self->size; i++)
    {
        printf("%s\n", item_string[self->items[i].name]);
    }
    printf("\n");
}

void AddItemToBag(struct Bag *self, Item item)
{
    if (!IsBagFull(self))
    {
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (self->items[i].name == None) // Find a empty slot
            {
                self->items[i] = item;
                self->size++;
                return;
            }
        }
    }
    else
    {
        printf("Bag is currently full!\n");
        printf("Can't add %s to the bag\n", item_string[item.name]);
        return;
    }
}

// String version
void AddItemToBag_(struct Bag *self, const char *item_name)
{
    if (!IsBagFull(self))
    {
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (self->items[i].name == None) // Find a empty slot
            {
                //AssignItem(self->items[i], item_name);
                AssignItemToBag(self, i, item_name);
                self->size++;
                return;
            }
        }
    }
    else
    {
        printf("Bag is currently full!\n");
        printf("Can't add %s to the bag\n", item_name);
        return;
    }
}

void RemoveItemFromBag(struct Bag *self, Item item)
{
    if (!IsBagEmpty(self))
    {
        for (int i = MAX_ITEMS - 1; i >= 0; i--)
        {
            if (self->items[i].name == item.name) // Find the slot that has the item were looking for
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
void RemoveItemFromBag_(struct Bag *self, const char *item_name)
{
    if (!IsBagEmpty(self))
    {
        for (int i = MAX_ITEMS - 1; i >= 0; i--)
        {
            if (item_string[self->items[i].name] == item_name) // Find the slot that has the item were looking for
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

void RemoveItemFromPokemon(Pokemon *poke)
{
    AssignItem(*poke->held_item, "None");
}

void RemoveItemFromGround(DungeonState *dungeon)
{
    //poke->held_item = None;
}

void RemoveItem(struct Bag *bag, Pokemon *poke, ItemLocation location, const char *item_name)
{
    if (location == LocationBag)
    {
        RemoveItemFromBag_(bag, item_name);
    }
    else if (location == LocationPokemonLeader)
    {
        RemoveItemFromPokemon(poke);
    }

}

// Takes a item from the bag or ground and puts it on the desired team member
// If there is item already on it then swap it and put the current item
// that's on the team member back in the bag
void GiveItemToTeamMember(struct Bag *self, Pokemon *team_member, Item item)
{
    if (team_member->held_item->name == None)
    {
        printf("Gave the %s to the Team Member\n", item_string[item.name]);
        team_member->held_item = &item;
        return;
    }
    else if (!IsBagFull(self))
    {
        printf("Put the %s in the bag\n", item_string[team_member->held_item->name]);
        AddItemToBag(self, *team_member->held_item);
        printf("Gave the %s to %s\n", item_string[item.name], team_member->name);
        team_member->held_item = &item;
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
void GiveItemToTeamMember_(struct Bag *self, Pokemon *team_member, const char *item_name)
{
    if (team_member->held_item->name == None)
    {
        printf("Gave the %s to the Team Member\n", item_name);
        AssignItem(*team_member->held_item, item_name);
        return;
    }
    else if (!IsBagFull(self))
    {
        printf("Put the %s in the bag\n", item_string[team_member->held_item->name]);
        AddItemToBag(self, *team_member->held_item);
        printf("Gave the %s to %s\n", item_name, team_member->name);
        AssignItem(*team_member->held_item, item_name);
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
void RemoveItemFromTeamMemberToBag(struct Bag *self, Pokemon *team_member, Item item)
{
    if (team_member->held_item->name != None)
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
void RemoveItemFromTeamMemberToBag_(struct Bag *self, Pokemon *team_member, const char *item_name)
{
    if (team_member->held_item->name != None)
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

void AssignItem(struct Item item, const char *item_name)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        if (item_string[item_table[i].name] == item_name)
        {
            item.name  = item_table[i].name;
            item.Throw = item_table[i].Throw;
            item.Use   = item_table[i].Use;
            item.Drop  = item_table[i].Drop;
        }
    }
}

void AssignItemToBag(struct Bag *bag, int index, const char *item_name)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        if (item_string[item_table[i].name] == item_name)
        {
            bag->items[index].name  = item_table[i].name;
            bag->items[index].Throw = item_table[i].Throw;
            bag->items[index].Use   = item_table[i].Use;
            bag->items[index].Drop  = item_table[i].Drop;
        }
    }
}

void UseItem(struct Bag *bag, PokemonParty *party, Pokemon *user, const char *item_name, ItemLocation location)
{
    for (int i = 0; i < ARRAY_SIZE(item_table); i++)
    {
        if (item_string[item_table[i].name] == item_name)
        {
            item_table[i].Use(bag, party, user, location);
        }
    }
}

void UseItemFromBag(struct Bag *bag, PokemonParty *party, Pokemon *user, const char *item_name)
{
    UseItem(bag, party, user, item_name, LocationBag);
}
