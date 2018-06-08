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
#include "Level.hpp"

#include <swirly/fin/Order.hpp>

namespace swirly {
inline namespace fin {
using namespace std;

static_assert(sizeof(Level) <= 2 * 64, "no greater than specified cache-lines");

Level::Level(const Order& first_order) noexcept
: first_order_{&first_order}
, key_{detail::compose_key(first_order.side(), first_order.ticks())}
, ticks_{first_order.ticks()}
, lots_{first_order.resd_lots()}
, count_{1}
{
}

Level::~Level() = default;

Level::Level(Level&&) = default;

void Level::add_order(const Order& order) noexcept
{
    lots_ += order.resd_lots();
    ++count_;
}

void Level::sub_order(const Order& order) noexcept
{
    lots_ -= order.resd_lots();
    --count_;
}

LevelSet::~LevelSet()
{
    set_.clear_and_dispose([](Level* ptr) { delete ptr; });
}

LevelSet::LevelSet(LevelSet&&) = default;

LevelSet& LevelSet::operator=(LevelSet&&) = default;

LevelSet::Iterator LevelSet::insert(ValuePtr value) noexcept
{
    Iterator it;
    bool inserted;
    tie(it, inserted) = set_.insert(*value);
    if (inserted) {
        // Take ownership if inserted.
        value.release();
    }
    return it;
}

LevelSet::Iterator LevelSet::insert_hint(ConstIterator hint, ValuePtr value) noexcept
{
    auto it = set_.insert(hint, *value);
    // Take ownership.
    value.release();
    return it;
}

LevelSet::Iterator LevelSet::insert_or_replace(ValuePtr value) noexcept
{
    Iterator it;
    bool inserted;
    tie(it, inserted) = set_.insert(*value);
    if (!inserted) {
        // Replace if exists.
        ValuePtr prev{&*it};
        set_.replace_node(it, *value);
        it = Set::s_iterator_to(*value);
    }
    // Take ownership.
    value.release();
    return it;
}

void LevelSet::remove(const Level& level) noexcept
{
    set_.erase_and_dispose(Set::s_iterator_to(level), [](Level* ptr) { delete ptr; });
}

} // namespace fin
} // namespace swirly
