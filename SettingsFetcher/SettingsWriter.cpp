#include "SettingsWriter.h"

#include <ostream>
#include <vector>
#include <string>

#define WRITE_PRIZEWEIGHT(setting) out << #setting << "=" << static_cast<int>(m_Settings.PrizeWeights.setting) << std::endl
#define WRITE_SHIP_SETTING(setting) out << #setting << "=" << static_cast<int>(m_Settings.ShipSettings[ship].setting) << std::endl
#define WRITE_SETTING(setting) out << #setting << "=" << static_cast<int>(m_Settings.setting) << std::endl

namespace continuum {

SettingsWriter::SettingsWriter(const ClientSettings& settings) 
    : m_Settings(settings)
{

}

void SettingsWriter::Write(std::ostream& out) {
    for (int i = 0; i < 8; ++i)
        WriteShipSettings(out, i);

    out << std::endl << "[Spectator]" << std::endl;

    WRITE_SETTING(HideFlags);
    WRITE_SETTING(NoXRadar);

    out << std::endl << "[Bullet]" << std::endl;

    WRITE_SETTING(ExactDamage);
    out << "BulletDamageLevel=" << static_cast<int>(m_Settings.BulletDamageLevel / 1000) << std::endl;
    out << "BulletDamageUpgrade=" << static_cast<int>(m_Settings.BulletDamageUpgrade / 1000) << std::endl;
    WRITE_SETTING(BulletAliveTime);

    out << std::endl << "[Misc]" << std::endl;

    WRITE_SETTING(SlowFrameRate);
    WRITE_SETTING(MaxTimerDrift);
    WRITE_SETTING(DisableScreenshot);
    WRITE_SETTING(WarpPointDelay);
    WRITE_SETTING(DecoyAliveTime);
    WRITE_SETTING(SafetyLimit);
    WRITE_SETTING(FrequencyShift);
    WRITE_SETTING(NearDeathLevel);
    WRITE_SETTING(ActivateAppShutdownTime);
    WRITE_SETTING(SendPositionDelay);
    WRITE_SETTING(BounceFactor);
    WRITE_SETTING(TickerDelay);
    WRITE_SETTING(WarpRadiusLimit);
    WRITE_SETTING(ExtraPositionData);
    WRITE_SETTING(SlowFrameCheck);
    WRITE_SETTING(AllowSavedShips);
    WRITE_SETTING(VictoryMusic);
    WRITE_SETTING(AntiWarpSettleDelay);

    out << std::endl << "[Latency]" << std::endl;

    WRITE_SETTING(SendRoutePercent);
    WRITE_SETTING(ClientSlowPacketTime);
    WRITE_SETTING(S2CNoDataKickoutDelay);
    WRITE_SETTING(ClientSlowPacketSampleSize);

    out << std::endl << "[Soccer]" << std::endl;
    
    WRITE_SETTING(DisableBallKilling);
    WRITE_SETTING(DisableWallPass);
    WRITE_SETTING(PassDelay);
    WRITE_SETTING(BallBlankDelay);
    WRITE_SETTING(BallBounce);
    WRITE_SETTING(AllowBombs);
    WRITE_SETTING(AllowGuns);
    WRITE_SETTING(Mode);
    WRITE_SETTING(UseFlagger);
    WRITE_SETTING(BallLocation);

    out << std::endl << "[Spawn]" << std::endl;

    for (int i = 0; i < 4; ++i)
        WriteSpawnSettings(out, i);

    out << std::endl << "[Bomb]" << std::endl;

    out << "BombDamageLevel=" << static_cast<int>(m_Settings.BombDamageLevel / 1000) << std::endl;
    WRITE_SETTING(BombAliveTime);
    WRITE_SETTING(BombExplodeDelay);
    WRITE_SETTING(BombExplodePixels);
    WRITE_SETTING(JitterTime);
    WRITE_SETTING(ProximityDistance);
    WRITE_SETTING(EBombShutdownTime);
    WRITE_SETTING(EBombDamagePercent);
    WRITE_SETTING(BBombDamagePercent);
    WRITE_SETTING(BombSafety);

    out << std::endl << "[Mine]" << std::endl;

    WRITE_SETTING(MineAliveTime);
    out << "TeamMaxMines=" << std::abs(static_cast<int>(m_Settings.TeamMaxMines)) << std::endl;

    out << std::endl << "[Shrapnel]" << std::endl;

    out << "InactiveShrapDamage=" << static_cast<int>(m_Settings.InactiveShrapDamage / 1000) << std::endl;
    WRITE_SETTING(ShrapnelSpeed);
    WRITE_SETTING(Random);
    WRITE_SETTING(ShrapnelDamagePercent);

    out << std::endl << "[Burst]" << std::endl;

    out << "BurstDamageLevel=" << static_cast<int>(m_Settings.BurstDamageLevel / 1000) << std::endl;

    out << std::endl << "[Toggle]" << std::endl;

    WRITE_SETTING(AntiWarpPixels);

    out << std::endl << "[Prize]" << std::endl;

    WRITE_SETTING(DeathPrizeTime);
    WRITE_SETTING(EngineShutdownTime);
    WRITE_SETTING(PrizeFactor);
    WRITE_SETTING(PrizeDelay);
    WRITE_SETTING(MinimumVirtual);
    WRITE_SETTING(UpgradeVirtual);
    WRITE_SETTING(PrizeMaxExist);
    WRITE_SETTING(PrizeMinExist);
    WRITE_SETTING(PrizeNegativeFactor);
    WRITE_SETTING(MultiPrizeCount);
    WRITE_SETTING(TakePrizeReliable);
    WRITE_SETTING(PrizeHideCount);

    out << std::endl << "[Flag]" << std::endl;

    WRITE_SETTING(FlagDropDelay);
    WRITE_SETTING(EnterGameFlaggingDelay);
    WRITE_SETTING(FlaggerOnRadar);
    WRITE_SETTING(FlaggerKillMultiplier);
    WRITE_SETTING(FlagBlankDelay);
    WRITE_SETTING(NoDataFlagDropDelay);
    WRITE_SETTING(FlagDropResetReward);
    WRITE_SETTING(FlaggerFireCostPercent);
    WRITE_SETTING(FlaggerDamagePercent);
    WRITE_SETTING(FlaggerBombFireDelay);
    WRITE_SETTING(FlaggerThrustAdjustment);
    WRITE_SETTING(FlaggerSpeedAdjustment);
    WRITE_SETTING(CarryFlags);
    WRITE_SETTING(FlaggerGunUpgrade);
    WRITE_SETTING(FlaggerBombUpgrade);

    out << std::endl << "[Radar]" << std::endl;

    WRITE_SETTING(MapZoomFactor);
    WRITE_SETTING(RadarNeutralSize);
    WRITE_SETTING(RadarMode);

    out << std::endl << "[Team]" << std::endl;

    WRITE_SETTING(MaxFrequency);
    WRITE_SETTING(MaxPerTeam);
    WRITE_SETTING(MaxPerPrivateTeam);

    out << std::endl << "[Kill]" << std::endl;

    WRITE_SETTING(EnterDelay);
    WRITE_SETTING(BountyIncreaseForKill);
    WRITE_SETTING(MaxBonus);
    WRITE_SETTING(MaxPenalty);
    WRITE_SETTING(RewardBase);

    out << std::endl << "[Repel]" << std::endl;

    WRITE_SETTING(RepelSpeed);
    WRITE_SETTING(RepelTime);
    WRITE_SETTING(RepelDistance);

    out << std::endl << "[Message]" << std::endl;

    WRITE_SETTING(MessageReliable);
    WRITE_SETTING(AllowAudioMessages);

    out << std::endl << "[Wormhole]" << std::endl;

    WRITE_SETTING(SwitchTime);
    WRITE_SETTING(GravityBombs);

    out << std::endl << "[Brick]" << std::endl;

    WRITE_SETTING(BrickTime);

    out << std::endl << "[Rocket]" << std::endl;

    WRITE_SETTING(RocketThrust);
    WRITE_SETTING(RocketSpeed);

    out << std::endl << "[Door]" << std::endl;

    WRITE_SETTING(DoorDelay);
    WRITE_SETTING(DoorMode);

    out << std::endl << "[PrizeWeight]" << std::endl;

    WRITE_PRIZEWEIGHT(QuickCharge);
    WRITE_PRIZEWEIGHT(Energy);
    WRITE_PRIZEWEIGHT(Rotation);
    WRITE_PRIZEWEIGHT(Stealth);
    WRITE_PRIZEWEIGHT(Cloak);
    WRITE_PRIZEWEIGHT(XRadar);
    WRITE_PRIZEWEIGHT(Warp);
    WRITE_PRIZEWEIGHT(Gun);
    WRITE_PRIZEWEIGHT(Bomb);
    WRITE_PRIZEWEIGHT(BouncingBullets);
    WRITE_PRIZEWEIGHT(Thruster);
    WRITE_PRIZEWEIGHT(TopSpeed);
    WRITE_PRIZEWEIGHT(Recharge);
    WRITE_PRIZEWEIGHT(Glue);
    WRITE_PRIZEWEIGHT(MultiFire);
    WRITE_PRIZEWEIGHT(Proximity);
    WRITE_PRIZEWEIGHT(AllWeapons);
    WRITE_PRIZEWEIGHT(Shields);
    WRITE_PRIZEWEIGHT(Shrapnel);
    WRITE_PRIZEWEIGHT(AntiWarp);
    WRITE_PRIZEWEIGHT(Repel);
    WRITE_PRIZEWEIGHT(Burst);
    WRITE_PRIZEWEIGHT(Decoy);
    WRITE_PRIZEWEIGHT(Thor);
    WRITE_PRIZEWEIGHT(MultiPrize);
    WRITE_PRIZEWEIGHT(Brick);
    WRITE_PRIZEWEIGHT(Rocket);
    WRITE_PRIZEWEIGHT(Portal);
}

void SettingsWriter::WriteShipSettings(std::ostream& out, int ship) {
    static const std::vector<std::string> ShipNames = { 
        "Warbird", "Javelin", "Spider", "Leviathan", "Terrier", "Weasel", "Lancaster", "Shark"
    };

    if (ship != 0)
        out << std::endl;

    out << "[" << ShipNames[ship] << "]" << std::endl;

    WRITE_SHIP_SETTING(SuperTime);
    WRITE_SHIP_SETTING(ShieldsTime);
    WRITE_SHIP_SETTING(Gravity);
    WRITE_SHIP_SETTING(GravityTopSpeed);
    WRITE_SHIP_SETTING(BulletFireEnergy);
    WRITE_SHIP_SETTING(MultiFireEnergy);
    WRITE_SHIP_SETTING(BombFireEnergy);
    WRITE_SHIP_SETTING(BombFireEnergyUpgrade);
    WRITE_SHIP_SETTING(LandmineFireEnergy);
    WRITE_SHIP_SETTING(LandmineFireEnergyUpgrade);
    WRITE_SHIP_SETTING(BulletSpeed);
    WRITE_SHIP_SETTING(BombSpeed);
    WRITE_SHIP_SETTING(SeeBombLevel);
    WRITE_SHIP_SETTING(DisableFastShooting);
    WRITE_SHIP_SETTING(Radius);
    WRITE_SHIP_SETTING(MultiFireAngle);
    WRITE_SHIP_SETTING(CloakEnergy);
    WRITE_SHIP_SETTING(StealthEnergy);
    WRITE_SHIP_SETTING(AntiWarpEnergy);
    WRITE_SHIP_SETTING(XRadarEnergy);
    WRITE_SHIP_SETTING(MaximumRotation);
    WRITE_SHIP_SETTING(MaximumThrust);
    WRITE_SHIP_SETTING(MaximumSpeed);
    WRITE_SHIP_SETTING(MaximumRecharge);
    WRITE_SHIP_SETTING(MaximumEnergy);
    WRITE_SHIP_SETTING(InitialRotation);
    WRITE_SHIP_SETTING(InitialThrust);
    WRITE_SHIP_SETTING(InitialSpeed);
    WRITE_SHIP_SETTING(InitialRecharge);
    WRITE_SHIP_SETTING(InitialEnergy);
    WRITE_SHIP_SETTING(UpgradeRotation);
    WRITE_SHIP_SETTING(UpgradeThrust);
    WRITE_SHIP_SETTING(UpgradeSpeed);
    WRITE_SHIP_SETTING(UpgradeRecharge);
    WRITE_SHIP_SETTING(UpgradeEnergy);
    WRITE_SHIP_SETTING(AfterburnerEnergy);
    WRITE_SHIP_SETTING(BombThrust);
    WRITE_SHIP_SETTING(BurstSpeed);
    WRITE_SHIP_SETTING(TurretThrustPenalty);
    WRITE_SHIP_SETTING(TurretSpeedPenalty);
    WRITE_SHIP_SETTING(BulletFireDelay);
    WRITE_SHIP_SETTING(MultiFireDelay);
    WRITE_SHIP_SETTING(BombFireDelay);
    WRITE_SHIP_SETTING(LandmineFireDelay);
    WRITE_SHIP_SETTING(RocketTime);
    WRITE_SHIP_SETTING(InitialBounty);
    WRITE_SHIP_SETTING(DamageFactor);
    WRITE_SHIP_SETTING(PrizeShareLimit);
    WRITE_SHIP_SETTING(AttachBounty);
    WRITE_SHIP_SETTING(SoccerBallFriction);
    WRITE_SHIP_SETTING(SoccerBallProximity);
    WRITE_SHIP_SETTING(SoccerThrowTime);
    WRITE_SHIP_SETTING(SoccerBallSpeed);
    WRITE_SHIP_SETTING(TurretLimit);
    WRITE_SHIP_SETTING(BurstShrapnel);
    WRITE_SHIP_SETTING(MaxMines);
    WRITE_SHIP_SETTING(RepelMax);
    WRITE_SHIP_SETTING(BurstMax);
    WRITE_SHIP_SETTING(DecoyMax);
    WRITE_SHIP_SETTING(ThorMax);
    WRITE_SHIP_SETTING(BrickMax);
    WRITE_SHIP_SETTING(PortalMax);
    WRITE_SHIP_SETTING(RocketMax);
    WRITE_SHIP_SETTING(InitialRepel);
    WRITE_SHIP_SETTING(InitialBurst);
    WRITE_SHIP_SETTING(InitialBrick);
    WRITE_SHIP_SETTING(InitialRocket);
    WRITE_SHIP_SETTING(InitialThor);
    WRITE_SHIP_SETTING(InitialDecoy);
    WRITE_SHIP_SETTING(InitialPortal);
    WRITE_SHIP_SETTING(BombBounceCount);
    WRITE_SHIP_SETTING(ShrapnelMax);
    WRITE_SHIP_SETTING(ShrapnelRate);
    WRITE_SHIP_SETTING(CloakStatus);
    WRITE_SHIP_SETTING(StealthStatus);
    WRITE_SHIP_SETTING(XRadarStatus);
    WRITE_SHIP_SETTING(AntiWarpStatus);
    WRITE_SHIP_SETTING(InitialGuns);
    WRITE_SHIP_SETTING(MaxGuns);
    WRITE_SHIP_SETTING(InitialBombs);
    WRITE_SHIP_SETTING(MaxBombs);
    WRITE_SHIP_SETTING(DoubleBarrel);
    WRITE_SHIP_SETTING(EmpBomb);
    WRITE_SHIP_SETTING(SeeMines);
}

void SettingsWriter::WriteSpawnSettings(std::ostream& out, int freq) {
    std::string team = "Team" + std::to_string(freq);
    out << team + "-Radius" << "=" << std::abs(static_cast<int>(m_Settings.SpawnSettings[freq].Radius)) << std::endl;
    out << team + "-X" << "=" << static_cast<int>(m_Settings.SpawnSettings[freq].X) << std::endl;
    out << team + "-Y" << "=" << static_cast<int>(m_Settings.SpawnSettings[freq].Y) << std::endl;
}

}
