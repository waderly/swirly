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
#include "Order.hxx"

#include <QJsonObject>

namespace swirly {
namespace ui {

Order::Order(const QString& accnt, Id64 market_id, const Instr& instr, QDate settl_date, Id64 id,
             const QString& ref, State state, Side side, Lots lots, Ticks ticks, Lots resd_lots,
             Lots exec_lots, Cost exec_cost, Lots last_lots, Ticks last_ticks, Lots min_lots,
             const QDateTime& created, const QDateTime& modified)
: accnt_{accnt}
, market_id_{market_id}
, instr_{instr}
, settl_date_{settl_date}
, id_{id}
, ref_{ref}
, state_{state}
, side_{side}
, lots_{lots}
, ticks_{ticks}
, resd_lots_{resd_lots}
, exec_lots_{exec_lots}
, exec_cost_{exec_cost}
, last_lots_{last_lots}
, last_ticks_{last_ticks}
, min_lots_{min_lots}
, created_{created}
, modified_{modified}
{
}

Order Order::from_json(const Instr& instr, const QJsonObject& obj)
{
    using swirly::ui::from_json;
    return Order{from_json<QString>(obj["accnt"]),
                 from_json<Id64>(obj["market_id"]),
                 instr,
                 from_json<QDate>(obj["settl_date"]),
                 from_json<Id64>(obj["id"]),
                 from_json<QString>(obj["ref"]),
                 from_json<State>(obj["state"]),
                 from_json<Side>(obj["side"]),
                 from_json<Lots>(obj["lots"]),
                 from_json<Ticks>(obj["ticks"]),
                 from_json<Lots>(obj["resd_lots"]),
                 from_json<Lots>(obj["exec_lots"]),
                 from_json<Cost>(obj["exec_cost"]),
                 from_json<Lots>(obj["last_lots"]),
                 from_json<Ticks>(obj["last_ticks"]),
                 from_json<Lots>(obj["min_lots"]),
                 from_json<QDateTime>(obj["created"]),
                 from_json<QDateTime>(obj["modified"])};
}

QDebug operator<<(QDebug debug, const Order& order)
{
    debug.nospace() << "Order{accnt=" << order.accnt()      //
                    << ",market_id=" << order.market_id()   //
                    << ",instr=" << order.instr()           //
                    << ",settl_date=" << order.settl_date() //
                    << ",id=" << order.id()                 //
                    << ",ref=" << order.ref()               //
                    << ",state=" << order.state()           //
                    << ",side=" << order.side()             //
                    << ",lots=" << order.lots()             //
                    << ",ticks=" << order.ticks()           //
                    << ",resd_lots=" << order.resd_lots()   //
                    << ",exec_lots=" << order.exec_lots()   //
                    << ",exec_cost=" << order.exec_cost()   //
                    << ",last_lots=" << order.last_lots()   //
                    << ",last_ticks=" << order.last_ticks() //
                    << ",min_lots=" << order.min_lots()     //
                    << ",created=" << order.created()       //
                    << ",modified=" << order.modified()     //
                    << '}';
    return debug;
}

} // namespace ui
} // namespace swirly
