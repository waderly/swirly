/*
 * The Restful Matching-Engine.
 * Copyright (C) 2013, 2018 Swirly Cloud Limited.
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
#include "Journ.hxx"

#include <swirly/fin/Exec.hpp>

#include <swirly/util/Config.hpp>

using namespace std;

namespace swirly {
namespace sqlite {
namespace {

constexpr auto BeginSql = "BEGIN TRANSACTION"sv;
constexpr auto CommitSql = "COMMIT TRANSACTION"sv;
constexpr auto RollbackSql = "ROLLBACK TRANSACTION"sv;

constexpr auto InsertMarketSql = //
    "INSERT INTO market_t (id, instr, settl_day, state)" //
    " VALUES (?, ?, ?, ?)"sv;

constexpr auto UpdateMarketSql = //
    "UPDATE Market_t SET state = ?2" //
    " WHERE id = ?1"sv;

constexpr auto InsertExecSql = //
    "INSERT INTO exec_t (market_id, instr, settl_day, id, order_id, accnt, ref," //
    " state_id, side_id, lots, ticks, resd_lots, exec_lots, exec_cost, last_lots," //
    " last_ticks, min_lots, match_id, liqInd_id, cpty, created)" //
    " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"sv;

constexpr auto UpdateExecSql = //
    "UPDATE exec_t SET archive = ?3" //
    " WHERE market_id = ?1 AND id = ?2"sv;

} // namespace

Journ::Journ(const Config& config)
  : db_{openDb(config.get("sqlite_journ", "swirly.db"), SQLITE_OPEN_READWRITE, config)}
  , beginStmt_{prepare(*db_, BeginSql)}
  , commitStmt_{prepare(*db_, CommitSql)}
  , rollbackStmt_{prepare(*db_, RollbackSql)}
  , insertMarketStmt_{prepare(*db_, InsertMarketSql)}
  , updateMarketStmt_{prepare(*db_, UpdateMarketSql)}
  , insertExecStmt_{prepare(*db_, InsertExecSql)}
  , updateExecStmt_{prepare(*db_, UpdateExecSql)}
{
}

Journ::~Journ() noexcept = default;

Journ::Journ(Journ&&) = default;

Journ& Journ::operator=(Journ&&) = default;

void Journ::doBegin()
{
    stepOnce(*beginStmt_);
}

void Journ::doCommit()
{
    stepOnce(*commitStmt_);
}

void Journ::doRollback()
{
    stepOnce(*rollbackStmt_);
}

void Journ::doUpdate(const Msg& msg)
{
    dispatch(msg);
}

void Journ::onReset()
{
    Transactional::reset();
}

void Journ::onCreateMarket(const CreateMarketBody& body)
{
    auto& stmt = *insertMarketStmt_;

    ScopedBind bind{stmt};
    bind(body.id);
    bind(toStringView(body.instr));
    bind(body.settlDay, MaybeNull);
    bind(body.state);

    stepOnce(stmt);
}

void Journ::onUpdateMarket(const UpdateMarketBody& body)
{
    auto& stmt = *updateMarketStmt_;

    ScopedBind bind{stmt};
    bind(body.id);
    bind(body.state);

    stepOnce(stmt);
}

void Journ::onCreateExec(const CreateExecBody& body)
{
    Transaction trans{*this, body.more};
    if (failed()) {
        return;
    }
    auto& stmt = *insertExecStmt_;

    ScopedBind bind{stmt};
    bind(body.marketId);
    bind(toStringView(body.instr));
    bind(body.settlDay, MaybeNull);
    bind(body.id);
    bind(body.orderId, MaybeNull);
    bind(toStringView(body.accnt));
    bind(toStringView(body.ref), MaybeNull);
    bind(body.state);
    bind(body.side);
    bind(body.lots);
    bind(body.ticks);
    bind(body.resdLots);
    bind(body.execLots);
    bind(body.execCost);
    if (body.lastLots > 0_lts) {
        bind(body.lastLots);
        bind(body.lastTicks);
    } else {
        bind(nullptr);
        bind(nullptr);
    }
    bind(body.minLots);
    bind(body.matchId, MaybeNull);
    bind(body.liqInd, MaybeNull);
    bind(toStringView(body.cpty), MaybeNull);
    bind(body.created); // Created.

    stepOnce(stmt);
    trans.commit();
}

void Journ::onArchiveTrade(const ArchiveTradeBody& body)
{
    Transaction trans{*this, body.more};
    if (failed()) {
        return;
    }
    auto& stmt = *updateExecStmt_;

    for (size_t i{0}; i < MaxIds; ++i) {
        const auto id = body.ids[i];
        if (id == 0_id64) {
            break;
        }
        ScopedBind bind{stmt};
        bind(body.marketId);
        bind(id);
        bind(body.modified);

        stepOnce(stmt);
    }
    trans.commit();
}

} // namespace sqlite

unique_ptr<Journ> makeJourn(const Config& config)
{
    return make_unique<sqlite::Journ>(config);
}

} // namespace swirly
