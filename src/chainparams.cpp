// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The IBA Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "tinyformat.h"
#include "utilstrencodings.h"

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

void CChainParams::UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    assert(IsRegTestNet()); // only available for regtest
    assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
    consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "All life on Earth harbours genetic material";
    const CScript genesisOutputScript = CScript() << ParseHex("04c10e83b2713ccf322a7dbd62da5815ac7c10bd055814ce121ba72607d572b8810c02c05b2aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c4") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints = {
    {0, uint256S("0000008d996b1f00a049507aa5e625d13bf12bb2e9ff486691790713b2e22884")},
    {1, uint256S("00000cacd8c4ad930e9bdfaaee8987f8ce4cf419eae8cf8bc3f8599afeab0bb1")},
    {348, uint256S("0000001c5b4a375327682fa016006be9b29e3733f39475e84757ed03f9b22f6e")},
    {1611, uint256S("778f023ce5c5330f34c5bd3f1a169a64205794e156de8a2ecab3f46da88415b9")},
    {2176, uint256S("30165934d45f08737c319e19712704b8ff9eeef45f1bb4f01ecfee394d90030e")},
    {3001, uint256S("34cd1a330d35ea314b07696ef8c511bd4efff41a89e47d2cc2b64d0e8df06378")},
    {4461, uint256S("f34936bfe28e3f1ff4c547b9ad8a19c5bb8a272b8652272465f99f095e9554cc")},
    {5323, uint256S("44a1066b62cc9e70b6095bc7111cf689be0ce0a614c5537a27bcd20796406fd0")},
    {6738, uint256S("a2f92904a33079a90dd6d90e82381962faf57873d7c7426f61855b89d867071c")},
    {7607, uint256S("98a675f84af4fd8a356781288b84eef2fb2684c138d219ade927c0eccc46d07b")},
    {9140, uint256S("cb4119ed0ff6709640bdfcd302389b675cceea6b740c024d30267da1b9ec5b6a")},
    {10909, uint256S("3ce941abe25fc5b11ae1ef6249d591599f7a122d381c94e10051972fa6ffaa0d")},
    
};

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1629874110, // * UNIX timestamp of last checkpoint block
    21383,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet = {
    {0, uint256S("0x")},

};

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1627545600,
    0,
    3000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest = {{0, uint256S("0x001")}};
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1628492400, 360164, 0x1e0ffff0, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000008d996b1f00a049507aa5e625d13bf12bb2e9ff486691790713b2e22884"));
        assert(genesis.hashMerkleRoot == uint256S("0x9a39c4e9515fd585faa1d7d172a85564b417c508ee1e549a1f2b49345e693cd0"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // IBACoin starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 100000000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 60;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 2 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;


        // spork keys
        consensus.strSporkPubKey = "045ecd94feacdecb37759825645a8447b23c4301bd9f02a07cc9589dccb9062b3d3bb0e4222948f90d1ff602413f683c90f3bb3c849d6ab1fdfb30c044a83a875a";
        consensus.strSporkPubKeyOld = "045ecd94feacdecb37759825645a8447b23c4301bd9f02a07cc9589dccb9062b3d3bb0e4222948f90d1ff602413f683c90f3bb3c849d6ab1fdfb30c044a83a875a";
        consensus.nTime_EnforceNewSporkKey = 1628568000;    //!> Tuesday, 10 August 2021 4:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1628748000;     //!> Thursday, 12 August 2021 6:00:00 AM GMT


        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 1;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 1100;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight          = 1300;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock =
                uint256S("0x");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock =
                uint256S("0x");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock =
                uint256S("0x");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x2a;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xd4;
        pchMessageStart[3] = 0xc1;
        nDefaultPort = 14022;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("51.222.65.208", "51.222.65.208", true); 
        vSeeds.emplace_back("2607:5300:120:121::208", "2607:5300:120:121::208", true); 
        vSeeds.emplace_back("51.222.65.209", "51.222.65.209", true); 
        vSeeds.emplace_back("2607:5300:120:121::209", "2607:5300:120:121::209", true); 
        vSeeds.emplace_back("51.222.65.210", "51.222.65.210", true); 
        vSeeds.emplace_back("2607:5300:120:121::210", "2607:5300:120:121::210", true); 
        vSeeds.emplace_back("51.222.65.211", "51.222.65.211", true); 
        vSeeds.emplace_back("2607:5300:120:121::211", "2607:5300:120:121::211", true); 
        vSeeds.emplace_back("51.222.65.213", "51.222.65.213", true); 
        vSeeds.emplace_back("2607:5300:120:121::213", "2607:5300:120:121::213", true); 
        vSeeds.emplace_back("51.222.65.214", "51.222.65.214", true); 
        vSeeds.emplace_back("2607:5300:120:121::214", "2607:5300:120:121::214", true); 
        vSeeds.emplace_back("51.222.65.215", "51.222.65.215", true); 
        vSeeds.emplace_back("2607:5300:120:121::215", "2607:5300:120:121::215", true); 
        vSeeds.emplace_back("51.222.65.216", "51.222.65.216", true); 
        vSeeds.emplace_back("2607:5300:120:121::216", "2607:5300:120:121::216", true); 
        vSeeds.emplace_back("51.222.65.217", "51.222.65.217", true); 
        vSeeds.emplace_back("2607:5300:120:121::217", "2607:5300:120:121::217", true); 
        vSeeds.emplace_back("51.222.65.218", "51.222.65.218", true); 
        vSeeds.emplace_back("2607:5300:120:121::218", "2607:5300:120:121::218", true); 
        vSeeds.emplace_back("51.222.65.219", "51.222.65.219", true); 
        vSeeds.emplace_back("2607:5300:120:121::219", "2607:5300:120:121::219", true); 
        vSeeds.emplace_back("51.222.65.220", "51.222.65.220", true); 
        vSeeds.emplace_back("2607:5300:120:121::220", "2607:5300:120:121::220", true); 
        vSeeds.emplace_back("51.222.65.221", "51.222.65.221", true); 
        vSeeds.emplace_back("2607:5300:120:121::221", "2607:5300:120:121::221", true); 
        vSeeds.emplace_back("51.222.65.222", "51.222.65.222", true); 
        vSeeds.emplace_back("2607:5300:120:121::222", "2607:5300:120:121::222", true); 
        vSeeds.emplace_back("51.222.65.223", "51.222.65.223", true); 
        vSeeds.emplace_back("2607:5300:120:121::223", "2607:5300:120:121::223", true); 



        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 103);		// starting with 'i'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 23);     // starting with 'A'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x02, 0x2D, 0x25, 0x33};
        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0x21, 0x31, 0x2B};
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x77};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ps";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "ibaks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-main";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviews";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};

/**
 * Testnet (v5)
 */
class CTestNetParams : public CChainParams
{
public:
    CTestNetParams()
    {
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
      //  assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
      //  assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // IBACoin starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 20000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 60;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 2 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;

        // spork keys
        consensus.strSporkPubKey = "04677c34726c491117265f4b1c83cef085684f36c8df5a97a3a42fc499316d0c4e63959c9eca0dba239d9aaaf72011afffeb3ef9f51b9017811dec686e412eb504";
        consensus.strSporkPubKeyOld = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.nTime_EnforceNewSporkKey = 1608512400;    //!> December 21, 2020 01:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1614560400;     //!> March 1, 2021 01:00:00 AM GMT


        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 1;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 1100;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 1300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight          = 1300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x5a;
        nDefaultPort = 11012;

        // nodes with support for servicebits filtering should be at the top
       /* vSeeds.emplace_back(""fuzzbawls.pw", "ibacoin-testnet.seed.fuzzbawls.pw", true);
        vSeeds.emplace_back(""fuzzbawls.pw", "ibacoin-testnet.seed.fuzzbawls.pw", true);*/

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet IBA addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c'
        // Testnet ibacoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet ibacoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet ibacoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "ibaktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams
{
public:
    CRegTestParams()
    {
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
   //     assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
    //    assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // IBACoin starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 300;
        consensus.vUpgrades[Consensus::UPGRADE_V5_2].nActivationHeight          = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51476;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ibacoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ibacoin script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet ibacoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet ibacoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet ibacoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "ibaktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params()
{
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    globalChainParams->UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
