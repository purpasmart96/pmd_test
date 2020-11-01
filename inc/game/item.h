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


#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

#include "util.h"
#include "common/vec.h"

#define NO_ITEMS 0
#define MAX_ITEMS 48
#define NEXT_SLOT i + 1

typedef enum Items
{
    None,
    Stick,
    IronThorn,
    SilverSpike,
    GoldFang,
    CacneaSpike,
    CorsolaTwig,
    Gravelerock,
    GeoPebble,
    GoldThorn,
    RareFossil,
    NoSlipCap,
    YRaySpecs,
    GaggleSpecs,
    MobileScarf,
    HealRibbon,
    TwistBand,
    ScopeLens,
    PatsyBand,
    NoStickCap,
    PierceBand,
    JoyRibbon,
    XRaySpecs,
    PersimBand,
    PowerBand,
    PechaScarf,
    Insomniscope,
    WarpScarf,
    TightBelt,
    SneakScarf,
    GoldRibbon,
    GoggleSpecs,
    DietRibbon,
    TrapScarf,
    RacketBand,
    DefScarf,
    StaminaBand,
    PlainRibbon,
    SpecialBand,
    ZincBand,
    DetectBand,
    SpaceGlobe,
    DodgeScarf,
    BounceBand,
    CurveBand,
    WhiffSpecs,
    NoAimScope,
    LockonSpecs,
    MunchBelt,
    PassScarf,
    WeatherBand,
    FriendBow,
    BeautyScarf,
    SunRibbon,
    LunarRibbon,
    GoldenMask,
    AmberTear,
    IcyFlute,
    FieryDrum,
    TerraCymbal,
    AquaMonica,
    RockHorn,
    GrassCornet,
    SkyMelodica,
    MiracleChest,
    WonderChest,
    IQBooster,
    HealSeed,
    OranBerry,
    SitrusBerry,
    EyedropSeed,
    ReviverSeed,
    BlinkerSeed,
    DoomSeed,
    XEyeSeed,
    LifeSeed,
    RawstBerry,
    HungerSeed,
    QuickSeed,
    PechaBerry,
    CheriBerry,
    TotterSeed,
    SleepSeed,
    PlainSeed,
    WarpSeed,
    BlastSeed,
    Ginseng,
    JoySeed,
    ChestoBerry,
    StunSeed,
    GabiteScale,
    GoldenSeed,
    VileSeed,
    PureSeed,
    ViolentSeed,
    VanishSeed,
    MaxElixir,
    Protein,
    Calcium,
    Iron,
    Nectar,
    DropeyeSeed,
    ReviserSeed,
    SlipSeed,
    ViaSeed,
    Zinc,
    Apple,
    BigApple,
    GrimyFood,
    HugeApple,
    GoldenApple,
    MixElixir,
    OrenBerry,
    DoughSeed,
    WhiteGummi,
    RedGummi,
    BlueGummi,
    GrassGummi,
    YellowGummi,
    ClearGummi,
    OrangeGummi,
    PinkGummi,
    BrownGummi,
    SkyGummi,
    GoldGummi,
    GreenGummi,
    GrayGummi,
    PurpleGummi,
    RoyalGummi,
    BlackGummi,
    SilverGummi,
    WonderGummi,
    Gravelyrock,
    Upgrade,
    KingsRock,
    Thunderstone,
    Deepseascale,
    Deepseatooth,
    SunStone,
    MoonStone,
    FireStone,
    WaterStone,
    MetalCoat,
    LeafStone,
    DragonScale,
    LinkCable,
    DubiousDisc,
    Protector,
    ReaperCloth,
    RazorFang,
    RazorClaw,
    Electirizer,
    Magmarizer,
    OvalStone,
    DawnStone,
    ShinyStone,
    DuskStone,
    CoronetRock,
    MossyRock,
    FrozenRock,
    GonePebble,
    WanderGummi,
    PrizeTicket,
    SilverTicket,
    GoldTicket,
    PrismTicket,
    MysteryPart,
    SecretSlab,
    WonderEgg,
    Gracidea,
    SkyGift,
    Key,
    Poke,
    LostLoot,
    UsedTM,
    /*
    188 = FocusPunchTM,
    189 = DragonClawTM,
    190 = WaterPulseTM,
    191 = CalmMindTM,
    192 = RoarTM,
    193 = ToxicTM,
    194 = HailTM,
    195 = BulkUpTM,
    196 = BulletSeedTM,
    197 = HiddenPowerTM
    198 = unk13,
    199 = TauntTM
    200 = IceBeamTM
    201 = BlizzardTM
    202 = HyperBeamTM
    203 = LightScreenTM
    204 = ProtectTM
    205 = unk14,
    206 = GigaDrainTM
    207 = SafeguardTM
    208 = FrustrationTM
    209 = SolarBeamTM
    210 = IronTailTM
    211 = ThunderboltTM
    212 = ThunderTM
    213 = EarthquakeTM
    214 = ReturnTM
    215 = DigTM
    216 = Psychic
    217 = ShadowBallTM
    218 = BrickBreakTM
    219 = unk15,
    220 = ReflectTM
    221 = ShockWave
    222 = FlamethrowerTM
    223 = SludgeBombTM
    225 = FireBlastTM
    227 = AerialAceTM
    228 = TormentTM
    229 = FacadeTM
    230 = SecretPowerTM
    231 = RestTM
    232 = AttractTM
    233 = ThiefTM
    234 = SteelWingTM
    235 = SkillSwapTM
    237 = OverheatTM
    238 = RoostTM
    239 = FocusBlastTM
    240 = EnergyBallTM
    241 = FalseSwipeTM
    242 = BrineTM
    243 = FlingTM
    244 = ChargeBeamTM
    245 = EndureTM
    246 = DragonPulseTM
    247 = DrainPunchTM
    248 = WillOWispTM
    249 = SilverWindTM
    250 = EmbargoTM
    251 = ExplosionTM
    252 = ShadowClawTM
    253 = PaybackTM
    254 = RecycleTM
    255 = GigaImpactTM
    256 = RockPolishTM
    257 = WideSlashTM
    260 = VacuumCutTM
    261 = DiveTM
    262 = FlashTM
    263 = StoneEdgeTM
    264 = AvalancheTM
    265 = ThunderWaveTM
    266 = GyroBallTM
    267 = SwordsDanceTM
    268 = StealthRockTM
    269 = PsychUpTM
    270 = CaptivateTM
    271 = DarkPulseTM
    272 = RockSlideTM
    273 = XScissorTM
    274 = SleepTalkTM
    275 = NaturalGiftTM
    276 = PoisonJabTM
    277 = DreamEaterTM
    278 = GrassKnotTM
    279 = SwaggerTM
    280 = PluckTM
    281 = UTurnTM
    282 = SubstituteTM
    283 = FlashCannonTM
    284 = TrickRoomTM
    285 = CutTM
    286 = FlyTM
    287 = SurfTM
    288 = StrengthTM
    289 = DefogTM
    290 = RockSmashTM
    291 = WaterfallTM
    292 = RockClimbTM
    301 = HailOrb
    302 = SunnyOrb
    303 = RainyOrb
    304 = EvasionOrb
    305 = SandyOrb
    306 = RockyOrb
    307 = SnatchOrb
    308 = SeeTrapOrb
    309 = MugOrb
    310 = ReboundOrb
    311 = LobOrb
    312 = SwitcherOrb
    313 = BlowbackOrb
    314 = WarpOrb
    315 = TransferOrb
    316 = SlowOrb
    317 = QuickOrb
    318 = LuminousOrb
    319 = PetrifyOrb
    320 = StayawayOrb
    321 = PounceOrb
    322 = TrawlOrb
    323 = CleanseOrb
    325 = DecoyOrb
    326 = SlumberOrb
    327 = TotterOrb
    328 = TwoEdgeOrb
    329 = Silence Orb
    330 = Escape Orb
    331 = Scanner Orb
    332 = RadarOrb
    333 = DroughtOrb
    334 = TrapbustOrb
    335 = RollcallOrb
    336 = InvisifyOrb
    337 = OneShotOrb
    338 = IdentifyOrb
    340 = ShockerOrb
    341 = SizebustOrb
    342 = OneRoomOrb
    343 = FillInOrb
    344 = TrapperOrb
    346 = Itemizer Orb
    347 = HurlOrb
    348 = MobileOrb
    350 = StairsOrb
    351 = LongtossOrb
    352 = PierceOrb
    354 = SpurnOrb
    355 = FoeHoldOrb
    356 = AllMachOrb
    357 = FoeFearOrb
    358 = AllHitOrb
    359 = FoeSealOrb
    362 = LinkBox
    364 = GorgeousBox0
    365 = GorgeousBox1
    366 = GorgeousBox2
    367 = HeavyBox0
    368 = HeavyBox1
    369 = HeavyBox2
    370 = ShinyBox0
    371 = ShinyBox1
    372 = ShinyBox2
    373 = NiftyBox3
    374 = NiftyBox0
    375 = NiftyBox1
    376 = DaintyBox0
    377 = DaintyBox1
    378 = DaintyBox2
    379 = GlitteryBox0
    380 = GlitteryBox1
    381 = GlitteryBox2
    382 = PrettyBox0
    383 = PrettyBox1
    384 = PrettyBox2
    385 = DeluxeBox0
    386 = DeluxeBox1
    387 = DeluxeBox2
    388 = LightBox0
    389 = LightBox1
    390 = LightBox2
    391 = CuteBox0
    392 = CuteBox1
    393 = CuteBox2
    394 = HardBox0
    395 = HardBox1
    396 = HardBox2
    397 = SinisterBox0
    398 = SinisterBox1
    399 = SinisterBox2

    SilverBow
    429 = BrownBow
    430 = RedBow
    431 = PinkBow
    432 = OrangeBow
    433 = YellowBow
    434 = LimeBow
    435 = GreenBow
    436 = Viridian Bow
    437 = Minty Bow
    438 = Sky Blue Bow
    439 = Blue Bow
    440 = Cobalt Bow
    441 = Purple Bow
    442 = Violet Bow
    443 = Fuchsia Bow
    444 = Prism Ruff
    445 = Aqua Collar
    446 = Volt Collar
    447 = Fire Collar
    448 = Light Collar
    449 = Dusk Collar
    450 = Virid Collar
    451 = Icy Collar
    452 = Pep Sash
    453 = Counter Ruff
    454 = Victory Belt
    455 = Power Bangle
    456 = Thundershard
    457 = Fallen Star
    458 = Fluff Dust
    459 = Egg Shard
    460 = Heroic Medal
    461 = Chic Shard
    462 = Yellow Jewel
    463 = Red Jewel
    464 = Blue Jewel
    465 = Laugh Dust
    466 = Guard Sand
    467 = Purple Jewel
    468 = White Jewel
    469 = Brave Dust
    470 = Heal Dew
    471 = Marine Cache
    472 = Freeze Veil
    473 = Thunder Veil
    474 = Fire Veil
    475 = Havoc Robe
    476 = Life Ring
    477 = Bolt Fang
    478 = Flare Fang
    479 = Aqua Mantle
    480 = Silver Veil
    481 = Rainbow Veil
    482 = Chrono Veil
    483 = Rock Sash
    484 = Ice Sash
    485 = Steel Sash
    486 = Heart Brooch
    487 = Eon Veil
    488 = Seabed Veil
    489 = Terra Ring
    490 = SkyHigh Veil
    491 = Wish Mantle
    492 = Revive Robe
    493 = Shadow Veil
    494 = Plasma Veil
    495 = Edify Robe
    496 = Charity Robe
    497 = Hope Robe
    498 = Time Shield
    499 = Air Blade
    500 = Searing Ring
    501 = Ancient Ring
    502 = Nether Veil
    503 = Lunar Veil
    504 = Tidal Cape
    505 = Eclipse Robe
    506 = White Silk
    507 = Normal Dust
    508 = White Gem
    509 = Joy Globe
    510 = Red Silk
    511 = Fire Dust
    512 = Fiery Gem
    513 = Fiery Globe
    514 = Blue Silk
    515 = Water Dust
    516 = Aqua Gem
    517 = Aqua Globe
    518 = Grass Silk
    519 = Grass Dust
    520 = Grass Gem
    521 = Soothe Globe
    522 = Yellow Silk
    523 = Thunder Dust
    524 = Thunder Gem
    525 = Volt Globe
    526 = Clear Silk
    527 = Icy Dust
    528 = Icy Gem
    529 = Icy Globe
    530 = Orange Silk
    531 = Courage Dust
    532 = Fight Gem
    533 = PowerGlobe
    534 = PinkSilk
    535 = PoisonDust
    536 = PoisonGem
    537 = PoisonGlobe
    538 = BrownSilk
    539 = GroundDust
    540 = EarthGem
    541 = TerraGlobe
    542 = SkySilk
    543 = SkyDust
    544 = SkyGem
    545 = SkyGlobe
    546 = GoldSilk
    547 = Psyche Dust
    548 = Psyche Gem
    549 = Psyche Globe
    550 = Green Silk
    551 = Wonder Dust
    552 = Guard Gem
    553 = Defend Globe
    554 = Gray Silk
    555 = Rock Dust
    556 = Stone Gem
    557 = Rock Globe
    558 = Purple Silk
    559 = Shady Dust
    560 = Shadow Gem
    561 = Nether Globe
    562 = Royal Silk
    563 = Dragon Dust
    564 = Dragon Gem
    565 = Dragon Globe
    566 = Black Silk
    567 = Dark Dust
    568 = Dark Gem
    569 = Dusk Globe
    570 = Iron Silk
    571 = Steel Dust
    572 = Metal Gem
    573 = Steel Globe
    574 = Bulba - Claw
    575 = Bulba - Fang
    576 = Grass - Guard
    577 = Leafy Tie
    578 = Ivy - Claw
    579 = Ivy - Fang
    580 = Ivy - Crest
    581 = Plant Torc
    582 = Venus - Claw
    583 = Venus - Fang
    584 = Venus - Seal
    585 = Solar Sash
    586 = Char - Claw
    587 = Char - Fang
    588 = Fiery Heart
    589 = Heat Armlet
    590 = Charme - Claw
    591 = Charme - Fang
    592 = Charme - Crest
    593 = Kindle Scarf
    594 = Chariz - Claw
    595 = Chariz - Fang
    596 = Chariz - Seal
    597 = Flame Bangle
    598 = Squirt - Foam
    599 = Squirt - Card
    600 = Water - Guard
    601 = Aqua Tie
    602 = Wartor - Claw
    603 = Wartor - Fang
    604 = Wartor - Crest
    605 = BubbleBangle
    606 = Blasto - Claw
    607 = Blasto - Card
    608 = Blasto - Seal
    609 = Hydro Band
    610 = Pichu Hair
    611 = Pichu Card
    612 = Express Tag
    613 = Shocker Cape
    614 = Pikachu Hair
    615 = Pikachu Card
    616 = Volt Charm
    617 = Volt Torc
    618 = Raichu Hair
    619 = Raichu Card
    620 = Raichu Crest
    621 = Zapper Scarf
    622 = Meowth Claw
    623 = Meowth Fang
    624 = Coin Charm
    625 = Bling Ruff
    626 = Persian Claw
    627 = Persian Fang
    628 = Insight Rock
    629 = Noble Scarf
    630 = Chiko - Claw
    631 = Chiko - Card
    632 = Dawn Jewel
    633 = Fresh Bow
    634 = Bayleef Claw
    635 = Bayleef Card
    636 = Bayleef Seal
    637 = Spice Bow
    638 = Megani - Claw
    639 = Megani - Card
    640 = Shiny Charm
    641 = Bright Veil
    642 = Cynda - Hair
    643 = Cynda - Claw
    644 = Blazing Rock
    645 = Storm Sash
    646 = Quila - Hair
    647 = Quila - Card
    648 = Quila - Crest
    649 = Volcano Torc
    650 = Typhlo - Gasp
    651 = Typhlo - Fang
    652 = Typhlo - Seal
    653 = Blast Bangle
    654 = Totodi - Dew
    655 = Totodi - Fang
    656 = Water Heart
    657 = Wash Bow
    658 = Croco - Fang
    659 = Croco - Card
    660 = Swirl Rock
    661 = Anger Scarf
    662 = Feral - Claw
    663 = Feral - Fang
    664 = Feral - Crest
    665 = Hydro Jaw
    666 = Treeck - Thorn
    667 = Treeck - Card
    668 = Forest Ore
    669 = Guard Ring
    670 = Grovy - Shoot
    671 = Grovy - Card
    672 = Jungle - Tag
    673 = Grass Blade
    674 = Scept - Claw
    675 = Scept - Card
    676 = Scept - Seal
    677 = Drain Bangle
    678 = Torchic Hair
    679 = Torchic Card
    680 = Hot Pebble
    681 = Fire Cape
    682 = Combus - Sweat
    683 = Combus - Claw
    684 = Charge Tag
    685 = Gutsy Band
    686 = Blazi - Claw
    687 = Blazi - Card
    688 = Blazi - Seal
    689 = Blaze Torc
    690 = Mudkip Mud
    691 = Mudkip Card
    692 = Mud Jewel
    693 = Speed Scarf
    694 = Marsh - Mud
    695 = Marsh - Card
    696 = Marsh - Crest
    697 = Marsh Torc
    698 = Swamp - Mud
    699 = Swamp - Card
    700 = Swamp - Seal
    701 = Swamp Bangle
    702 = Skitty Fang
    703 = Skitty Card
    704 = Smile Pebble
    705 = Heal Pendant
    706 = Delcat - Hair
    707 = Delcat - Fang
    708 = Prim Pebble
    709 = Guard Collar
    710 = Lucky Leaf
    711 = Turtwig Card
    712 = Sprout Rock
    713 = Leafy Hat
    714 = Grotle Twig
    715 = Grotle Claw
    716 = Grotle Crest
    717 = Woody Scarf
    718 = Tort - Claw
    719 = Tort - Horn
    720 = Tort - Seal
    721 = Forest Torc
    722 = Chim - Hair
    723 = Chim - Fang
    724 = Nimble Charm
    725 = Ember Cap
    726 = Monfer - Hair
    727 = Monfer - Fang
    728 = Monfer - Crest
    729 = Burst Sash
    730 = Infern - Hair
    731 = Infern - Fang
    732 = Infern - Seal
    733 = Blazing Ruff
    734 = Piplup Foam
    735 = Piplup Card
    736 = Sea Ore
    737 = Water Cape
    738 = Prin - Foam
    739 = Prin - Card
    740 = Prin - Crest
    741 = Aqua Blade
    742 = Empol - Claw
    743 = Empol - Horn
    744 = Empol - Seal
    745 = Marine Crown
    746 = Munch - Drool
    747 = Munch - Claw
    748 = Tummy Charm
    749 = Glutton Cape
    750 = Snorlax Gasp
    751 = Snorlax Fang
    752 = Valor Charm
    753 = Glee Scarf
    754 = Scyther Fang
    755 = Scyther Card
    756 = Ambush Rock
    757 = Strike Ruff
    758 = Scizor Wing
    759 = Scizor Card
    760 = Steel Charm
    761 = Red Armlet
    762 = Lapras Song
    763 = Lapras Card
    764 = Wavy Charm
    765 = Mystic Scarf
    766 = Eevee Tail
    767 = Eevee Card
    768 = Evolve Charm
    769 = Eevee
    770 = Cleffa Dew
    771 = Cleffa Card
    772 = Starry Ore
    773 = Comet Ring
    774 = Clef - Claw
    775 = Clef - Fang
    776 = Moon Jewel
    777 = Moon Scarf
    778 = Clefa - Claw
    779 = Clefa - Card
    780 = Moon Rock
    781 = Fairy Bow
    782 = Iggly - Dew
    783 = Iggly - Card
    784 = Bouncy Charm
    785 = Pretty Bow
    786 = Jiggly - Song
    787 = Jiggly - Card
    788 = Slumber Rock
    789 = Snooze Ring
    790 = Wiggly - Hair
    791 = Wiggly - Card
    792 = Buddy Rock
    793 = Friend Torc
    794 = Togepi Dew
    795 = Togepi Card
    796 = Pure Heart
    797 = Angel Scarf
    798 = Togetic Wing
    799 = Togetic Card
    800 = Happy Rock
    801 = Luck Brooch
    802 = Togek - Wing
    803 = Togek - Card
    804 = Ovation Rock
    805 = Glitter Robe
    806 = Sneasel Claw
    807 = Sneasel Card
    808 = Dusk Jewel
    809 = Cruel Ring
    810 = Weavile Claw
    811 = Weavile Fang
    812 = Vile Tag
    813 = Ruin Armlet
    814 = Teddi - Claw
    815 = Teddi - Card
    816 = Honey Rock
    817 = Heal Scarf
    818 = Ursa - Claw
    819 = Ursa - Fang
    820 = Calming Rock
    821 = Hiber Scarf
    822 = Tyro - Sweat
    823 = Tyro - Card
    824 = Muscle Charm
    825 = Tyrogue
    826 = Smooch - Song
    827 = Smooch - Card
    828 = Kiss Charm
    829 = Heart Tiara
    830 = Jynx Song
    831 = Jynx Card
    832 = Frozen Ore
    833 = Ruin Scarf
    834 = Elekid Claw
    835 = Elekid Card
    836 = Jolt Charm
    837 = Current Ring
    838 = Electa - Claw
    839 = Electa - Fang
    840 = Charge Seal
    841 = Volt Bangle
    842 = Electi - Claw
    843 = Electi - Card
    844 = Voltaic Rock
    845 = Voltaic Band
    846 = Magby Claw
    847 = Magby Card
    848 = Ember Jewel
    849 = Coal Ring
    850 = Magmar Claw
    851 = Magmar Card
    852 = Erupt Ore
    853 = Magma Scarf
    854 = Magmor - Claw
    855 = Magmor - Card
    856 = Vulcan Rock
    857 = Burning Torc
    858 = Azuri - Dew
    859 = Azuri - Card
    860 = Fount Charm
    861 = Water Float
    862 = Marill Dew
    863 = Marill Card
    864 = Surfer Rock
    865 = Brine Scarf
    866 = Azuma - Dew
    867 = Azuma - Card
    868 = Stream Charm
    869 = Dotted Scarf
    870 = Plusle Tail
    871 = Plusle Card
    872 = Cheer Rock
    873 = Pulse Bow
    874 = Minun Tail
    875 = Minun Card
    876 = Volt Heart
    877 = Spark Tie
    878 = Cast - Dew
    879 = Cast - Card
    880 = Cloud Rock
    881 = Weather Cape
    882 = Wynaut Tail
    883 = Wynaut Card
    884 = Grin Charm
    885 = Cheery Scarf
    886 = Wobbu - Sweat
    887 = Wobbu - Card
    888 = Endure Rock
    889 = Suffer Scarf
    890 = Bidoof Tooth
    891 = Bidoof Card
    892 = Fall Charm
    893 = Stolid Scarf
    894 = Biba - Tooth
    895 = Biba - Card
    896 = River Charm
    897 = Dam Scarf
    898 = Shinx Claw
    899 = Shinx Fang
    900 = Flash Tag
    901 = Energy Scarf
    902 = Luxio Claw
    903 = Luxio Fang
    904 = Spark Tag
    905 = Spark Scarf
    906 = Luxray Claw
    907 = Luxray Fang
    908 = Glare Tag
    909 = Glare Sash
    910 = Pachi - Tooth
    911 = Pachi - Card
    912 = Rouse Charm
    913 = Miracle Bow
    914 = Buizel Fang
    915 = Buizel Card
    916 = Swimmer Rock
    917 = Screw Torc
    918 = Float - Fang
    919 = Float - Card
    920 = Rescue Rock
    921 = Float Aid
    922 = Drifloo - Gasp
    923 = Drifloo - Card
    924 = Wind Heart
    925 = Draft Ring
    926 = Drifbli - Gasp
    927 = Drifbli - Card
    928 = Easy Charm
    929 = Breeze Scarf
    930 = Cherubi Seed
    931 = Cherubi Card
    932 = Cute Ore
    933 = Charm Bow
    934 = Cherrim Dew
    935 = Cherrim Card
    936 = Sweet Aroma
    937 = Petal Dress
    938 = Bonsly Dew
    939 = Bonsly Card
    940 = Arid Tag
    941 = Teary Cape
    942 = Sudo - Sweat
    943 = Sudo - Card
    944 = Drain Rock
    945 = Fake Torc
    946 = Junior Beam
    947 = Junior Card
    948 = Mimic Pebble
    949 = Copy Mask
    950 = Mime Key
    951 = Mime Card
    952 = Bulwark Rock
    953 = Barrier Bow
    954 = Happiny Dew
    955 = Happiny Card
    956 = Play Tag
    957 = Nurture Cape
    958 = Chansey Song
    959 = Chansey Card
    960 = Lucky Charm
    961 = Lucky Scarf
    962 = Blissey Song
    963 = Blissey Card
    964 = Amity Rock
    965 = Faith Ring
    966 = Gible Fang
    967 = Gible Card
    968 = Dragon Jewel
    969 = Dragon Tie
    970 = Gabite Claw
    971 = Gabite Fang
    972 = Star Rock
    973 = Meteor Torc
    974 = Gar - Claw
    975 = Gar - Fang
    976 = Speed Tag
    977 = Mach Scarf
    978 = Riolu Tail
    979 = Riolu Card
    980 = Valiant Rock
    981 = Emit Ring
    982 = Lucario Fang
    983 = Lucario Card
    984 = Pledge Rock
    985 = Ravage Ring
    986 = Mantyke Beam
    987 = Mantyke Card
    988 = Waft Rock
    989 = Ocean Bow
    990 = Mantine Foam
    991 = Mantine Card
    992 = Sunset Rock
    993 = Horizon Bow
    994 = Phione Song
    995 = Phione Card
    996 = Wave Jewel
    997 = Ripple Cape
    998 = Vulpix Tail
    999 = Vulpix Card
    1000 = Vulpix Tag
    1001 = Glowing Bow
    1002 = Nine - Hair
    1003 = Nine - Card
    1004 = Nine - Seal
    1005 = Afire Collar
    1006 = Phanpy Claw
    1007 = Phanpy Card
    1008 = Phanpy Tag
    1009 = Value Ruff
    1010 = Donphan Fang
    1011 = Donphan Card
    1012 = Don - Crest
    1013 = Armor Scarf
    1014 = Cater - Belt
    1015 = Defense Bow
    1016 = Glittery Bow
    1017 = Weedle Bow
    1018 = Kakuna Scarf
    1019 = Charge Scarf
    1020 = Pidgey Bow
    1021 = Pidgeo - Scarf
    1022 = Pidgeot Torc
    1023 = Ratta - Scarf
    1024 = Overcome Bow
    1025 = Quirky Bow
    1026 = Wing Scarf
    1027 = Leash Bow
    1028 = Shock Ruff
    1029 = Sand - Scarf
    1030 = Sandy Torc
    1031 = Pointy Scarf
    1032 = Return Scarf
    1033 = Impact Torc
    1034 = Halve Scarf
    1035 = Thorny Scarf
    1036 = King Sash
    1037 = Dodge Bow
    1038 = Absorb Scarf
    1039 = Odd Bow
    1040 = Guard Hat
    1041 = Aroma Scarf
    1042 = Moving Scarf
    1043 = Firm Hat
    1044 = Gaze Goggles
    1045 = Venomoth Bow
    1046 = Diglett Hat
    1047 = Dugtrio Bow
    1048 = Psyduck Hat
    1049 = Paddle Scarf
    1050 = Mankey Torc
    1051 = Nullify Belt
    1052 = Growl - Scarf
    1053 = Legend Bow
    1054 = Damp Bow
    1055 = Poli - Bow
    1056 = Bold Belt
    1057 = Predict Torc
    1058 = Psychic Torc
    1059 = Sparkle Ruff
    1060 = Impish Band
    1061 = Strong Belt
    1062 = Machamp Belt
    1063 = Bell - Bow
    1064 = Digest Scarf
    1065 = Victree - Torc
    1066 = Tangle Bow
    1067 = Tenta - Cape
    1068 = Geodude Torc
    1069 = Rocky Torc
    1070 = Rugged Sash
    1071 = Heated Bow
    1072 = Sunlight Bow
    1073 = Slowpoke Hat
    1074 = Slow - Scarf
    1075 = Magne - Torc
    1076 = Magneton Bow
    1077 = Bullseye Bow
    1078 = Buddy Torc
    1079 = Fight Torc
    1080 = Gentle Bow
    1081 = North Torc
    1082 = Grimy Scarf
    1083 = Slimy Bow
    1084 = Shell - Torc
    1085 = Cover Armor
    1086 = Gastly Veil
    1087 = Slip Scarf
    1088 = Sunglasses
    1089 = Trust Brooch
    1090 = Drowzee Tie
    1091 = Dream Coin
    1092 = Krabby Bow
    1093 = Super Sash
    1094 = Ball Scarf
    1095 = Electro - Bow
    1096 = Repel Scarf
    1097 = Exeggu - Sash
    1098 = Cubone Scarf
    1099 = Marowak Torc
    1100 = Licky Scarf
    1101 = Koffing Bow
    1102 = Weez - Scarf
    1103 = Solid Shield
    1104 = Pierce Drill
    1105 = Sticky Bow
    1106 = Kang - Apron
    1107 = Horsea Bow
    1108 = Swirl Scarf
    1109 = Goldeen Bow
    1110 = Seaking Bow
    1111 = Recover Torc
    1112 = Starmie Belt
    1113 = Pinsir Sash
    1114 = Rushing Bow
    1115 = Magikarp Bow
    1116 = Tempest Sash
    1117 = Ditto Torc
    1118 = AI Brooch
    1119 = Spike Brooch
    1120 = Aged Scarf
    1121 = Kabuto Hat
    1122 = Kabu - Torc
    1123 = Old Brooch
    1124 = Dragon Sash
    1125 = Aloft Mantle
    1126 = Mirage Cape
    1127 = Sentret Ruff
    1128 = Body Collar
    1129 = Expose Specs
    1130 = Noctowl Torc
    1131 = Morning Bow
    1132 = Ledian Bow
    1133 = Spina - Scarf
    1134 = Ariados Bow
    1135 = Slash Bow
    1136 = Shine Torc
    1137 = Lanturn Bow
    1138 = Lively Scarf
    1139 = Xatu Bow
    1140 = Wool Bow
    1141 = Fluffy Scarf
    1142 = Sacred Scarf
    1143 = Bright Tiara
    1144 = Rain Crown
    1145 = Zephyr Bow
    1146 = Skip - Scarf
    1147 = Cotton Torc
    1148 = Revenge Ruff
    1149 = Hasty Bow
    1150 = Sun Scarf
    1151 = Chitin Bow
    1152 = Wooper Bow
    1153 = Quag - Torc
    1154 = Murkrow Hat
    1155 = King Cap
    1156 = Misdrea - Cape
    1157 = Cryptic Sash
    1158 = Reverse Bow
    1159 = Robust Bow
    1160 = Dense Poncho
    1161 = Escape Scarf
    1162 = Takeoff Ruff
    1163 = Quartz Torc
    1164 = Snub - Cape
    1165 = Stern Sash
    1166 = Qwilfish Bow
    1167 = Shuckle Bow
    1168 = Horn Torc
    1169 = Lava Bow
    1170 = Torrid Scarf
    1171 = Frigid Bow
    1172 = Frost Torc
    1173 = Eager Brooch
    1174 = Reach Bow
    1175 = Psy Bow
    1176 = Snow Brooch
    1177 = Skar - Cape
    1178 = Dark Choker
    1179 = Pit Fang
    1180 = Tornado Bow
    1181 = Virtual Bow
    1182 = Delusion Bow
    1183 = Paint Scarf
    1184 = Milky Scarf
    1185 = Larvitar Bow
    1186 = Pupita - Scarf
    1187 = Crash Claw
    1188 = Pooch - Collar
    1189 = Dark Fang
    1190 = Merry Scarf
    1191 = Linoone Ruff
    1192 = Wurmple Bow
    1193 = Tough Scarf
    1194 = Vivid Silk
    1195 = Guard Bow
    1196 = Dustox Bow
    1197 = Kelp Hat
    1198 = Jolly Scarf
    1199 = Ludicolo Hat
    1200 = Seedot Hat
    1201 = Nuzleaf Bow
    1202 = Shiftry Belt
    1203 = Taillow Bow
    1204 = Midair Scarf
    1205 = Wingull Bow
    1206 = Stock Scarf
    1207 = Sensing Hat
    1208 = Magical Bow
    1209 = Caring Scarf
    1210 = Bliss Scarf
    1211 = Blocking Bow
    1212 = Mobile Bow
    1213 = Thwart Bow
    1214 = Slak - Scarf
    1215 = Vigor Sash
    1216 = Lazy Ruff
    1217 = Novice Scarf
    1218 = Ninja Ruff
    1219 = Awe Mantle
    1220 = Good Earring
    1221 = Nice Bangle
    1222 = Great Torc
    1223 = Makuhit - Belt
    1224 = Thrust Belt
    1225 = Nose - Torc
    1226 = Sable - Scope
    1227 = Deceit Mask
    1228 = Iron Torc
    1229 = Metal Bangle
    1230 = Iron Helmet
    1231 = Intuit Bow
    1232 = Ponder Sash
    1233 = Punish Torc
    1234 = Protect Mask
    1235 = Neon Scarf
    1236 = Evening Bow
    1237 = Thorned Torc
    1238 = Gulpin Bow
    1239 = Swalot Belt
    1240 = Carva - Sash
    1241 = Vicious Bow
    1242 = Spout Scarf
    1243 = Huge Bow
    1244 = Numel Bow
    1245 = Erupt Scarf
    1246 = Sooty Sash
    1247 = Spring Bow
    1248 = Scheme Scarf
    1249 = Hula Bow
    1250 = Desert Bow
    1251 = Vibra Scarf
    1252 = Red Glasses
    1253 = Desert Sash
    1254 = Cacturne Hat
    1255 = Tuft Bow
    1256 = Cloud Ruff
    1257 = Strong Sash
    1258 = Seviper Bow
    1259 = Lunaton - Torc
    1260 = Solrock Bow
    1261 = Soak Scarf
    1262 = Whiscash Bow
    1263 = Bossy Scarf
    1264 = Cower Sash
    1265 = Bal - Brooch
    1266 = Claydol Torc
    1267 = Bind Scarf
    1268 = Cradily Bow
    1269 = Guard Claw
    1270 = Rigid Cape
    1271 = Admire Scarf
    1272 = Grace Scarf
    1273 = Kecleon Torc
    1274 = Shuppet Cape
    1275 = Ominous Torc
    1276 = Duskull Ruff
    1277 = Illusion Bow
    1278 = Tropius Bow
    1279 = Chime - Scarf
    1280 = Perish Torc
    1281 = Chilly Hat
    1282 = Hail Scarf
    1283 = Sleet Bow
    1284 = Safe Scarf
    1285 = Walrein Torc
    1286 = Clam - Brooch
    1287 = Deep Torc
    1288 = Gore - Scarf
    1289 = Reli - Torc
    1290 = Luvdisc Torc
    1291 = Crag Helmet
    1292 = Outlast Bow
    1293 = Sala - Cape
    1294 = Beldum Torc
    1295 = Metang Scarf
    1296 = Meta - Torc
    1297 = Starly Bow
    1298 = Regret Torc
    1299 = Guts Sash
    1300 = Still Bow
    1301 = Kricke - Torc
    1302 = Budew Scarf
    1303 = Bouquet Cape
    1304 = Hard Helmet
    1305 = Skull Helmet
    1306 = Rebound Bow
    1307 = Block Brooch
    1308 = Straw Cape
    1309 = Worma - Bow
    1310 = Mothim Bow
    1311 = Nectar Bow
    1312 = Vespi - Torc
    1313 = Awake Bow
    1314 = Gastro - Torc
    1315 = Ambipom Bow
    1316 = Defrost Ruff
    1317 = Allure Coat
    1318 = Magic Hat
    1319 = Honch - Cape
    1320 = Glameow Bow
    1321 = Scary Belt
    1322 = Ching - Torc
    1323 = Stinky Scarf
    1324 = Stench Sash
    1325 = Image Brooch
    1326 = Mirror Torc
    1327 = Chatot Scarf
    1328 = Thick Scarf
    1329 = Grit Veil
    1330 = Skorupi Bow
    1331 = Dust Scarf
    1332 = CroaTorc
    1333 = ToxiBelt
    1334 = CarniBow
    1335 = SwimBow
    1336 = LumiTorc
    1337 = SnowyTorc
    1338 = FrozenCape
    1339 = BuilderSash
    1340 = FlabbyBelt
    1341 = RhyperiTorc
    1342 = ClingingBow
    1343 = YanmegaBow
    1344 = GliscorCape
    1345 = GlacierCape
    1346 = BestScarf
    1347 = GallantTorc
    1348 = ProboHat
    1349 = UnluckySash
    1350 = FroslassBow
    1351 = PurifyVeil
    */

} Items;

typedef enum ItemLocation
{
    LocationBag,
    LocationPokemonLeader,
    LocationPokemonTeamateOne,
    LocationPokemonTeamateTwo,
    LocationPokemonTeamateThree,
    LocationPokemonTeamateFour,
    LocationPokemonTeamateFive,
    LocationPokemonTeamateSix,
    LocationPokemonTeamateSeven,
    LocationGround,
} ItemLocation;

typedef struct Item
{
    Items type;
    void(*Throw)(struct Bag *, struct PokemonParty *, struct Pokemon_s *, ItemLocation, Items item);
    void(*Use)(struct Bag *, struct PokemonParty *, struct Pokemon_s *, ItemLocation, Items item);
    void(*Drop)(struct Bag *, struct PokemonParty *, struct Pokemon_s *, ItemLocation, Items item);
    void(*Reserved0)();
    void(*Reserved1)();
    void(*Reserved2)();
    ivec2 position;
    int size; // internal amount
} Item;

typedef struct Bag
{
    struct Item *items;
    u32 size; // does not contain dupe items
    u32 real_size; // contains dupe items
    u32 capacity;
} Bag;

typedef struct Dungeon Dungeon;

Bag *Bag_New(bool init);
void Bag_Init(Bag *self);
void Bag_ShutDown(Bag *self);

void ClearBag(struct Bag *self);
bool IsBagEmpty(struct Bag *self);
bool IsBagFull(struct Bag *self);
void DisplayBag(struct Bag *self);
void Bag_SortItems(struct Bag *self);
void Bag_DecrementExistingItemInBag(Bag *self, int index);
void Bag_IncrementExistingItemInBag(Bag *self, int index);
int Bag_ItemAlreadyExists(Bag * self, Items type);
void Bag_CountSortItemsDesc(struct Bag *self, int n, int range);
//void AddEmptySlots(struct Bag *self);
//void UpdateBag(struct Bag *self);
void GiveItemToTeamMember(struct Bag *self, struct Pokemon_s *team_member, struct Item item);
void GiveItemToTeamMember_(struct Bag *self, struct Pokemon_s *team_member, const char *item_name);
void AddItemToBagByType(struct Bag *self, Items type);
void AddItemToBag(struct Bag *self, struct Item item);
// String version
void AddItemToBag_(Bag *self, const char *item_name);
void RemoveItemFromBag(Bag *self, struct Item item);
// String version
bool RemoveItemFromBag_(struct Bag *self, const char *item_name);
void RemoveItemFromTeamMemberToBag(struct Bag *self, struct Pokemon_s *team_member, struct Item item);

void RemoveItemFromTeamMemberToBag_(struct Bag *self, struct Pokemon_s *team_member, const char *item_name);
void AddItemToBagFromGround(Bag * bag, struct Pokemon_s *poke, Dungeon *dungeon);
bool RemoveItemFromGround(Dungeon *dungeon, struct Pokemon_s *poke);
bool RemoveItem(struct Bag *bag, struct Pokemon_s *poke, enum ItemLocation location, const char *item_name);

void Pokemon_AssignItem(struct Pokemon_s *dst_poke, const char *item_name);
void Bag_AssignItem(struct Bag *bag, int index, const char *item_name);
void Bag_AssignItemByType(struct Bag *bag, int index, Items type);

void UseItem(struct Bag *bag, struct PokemonParty *party, struct Pokemon_s *user, const char *item_name, ItemLocation location);
void UseItemFromBag(struct Bag *bag, struct PokemonParty *party, struct Pokemon_s *user, const char *item_name);


#endif
