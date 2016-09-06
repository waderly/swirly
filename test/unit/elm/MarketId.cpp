/*
 * The Restful Matching-Engine.
 * Copyright (C) 2013, 2016 Swirly Cloud Limited.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include <swirly/elm/MarketId.hpp>

#include <swirly/ash/String.hpp>

#include <swirly/tea/Test.hpp>

using namespace std;
using namespace swirly;

SWIRLY_TEST_CASE(MarketId)
{
  auto market = MarketId{171_id32, 2492719_jd};
  SWIRLY_CHECK(market.id() == 0xabcdef);
  SWIRLY_CHECK(market.contr() == 171_id32);
  SWIRLY_CHECK(market.settlDay() == 2492719_jd);
  SWIRLY_CHECK(toString(market) == "11259375"s);
}