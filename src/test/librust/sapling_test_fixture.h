// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2021 The IBA Coin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef IBACoin_SAPLING_TEST_FIXTURE_H
#define IBACoin_SAPLING_TEST_FIXTURE_H

#include "test/test_ibacoin.h"

/**
 * Testing setup that configures a complete environment for Sapling testing.
 */
struct SaplingTestingSetup : public TestingSetup {
    SaplingTestingSetup();
    ~SaplingTestingSetup();
};


#endif //IBACoin_SAPLING_TEST_FIXTURE_H
