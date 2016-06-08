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
#ifndef SWIRLY_ELM_TRANSACTIONAL_HPP
#define SWIRLY_ELM_TRANSACTIONAL_HPP

#include <swirly/elm/Rec.hpp>

#include <swirly/ash/Types.hpp>

using namespace std;

namespace swirly {

/**
 * @addtogroup IO
 * @{
 */

class SWIRLY_API Transactional {
 public:
  Transactional() noexcept = default;
  virtual ~Transactional() noexcept;

  // Copy.
  constexpr Transactional(const Transactional&) noexcept = default;
  Transactional& operator=(const Transactional&) noexcept = default;

  // Move.
  constexpr Transactional(Transactional&&) noexcept = default;
  Transactional& operator=(Transactional&&) noexcept = default;

  auto failed() const noexcept { return state_ == Failed; }

  /**
   * Begin transaction.
   */
  void tryBegin()
  {
    if (state_ == None) {
      state_ = Active;
      doBegin();
    }
  }

  /**
   * Commit transaction.
   */
  void tryCommit()
  {
    if (state_ == Active) {
      state_ = None;
      doCommit();
    }
  }

  /**
   * Rollback transaction.
   */
  void tryRollback() noexcept;

  /**
   * Reset transaction.
   */
  void reset() noexcept;

 protected:
  virtual void doBegin() = 0;

  virtual void doCommit() = 0;

  virtual void doRollback() = 0;

 private:
  enum { None, Active, Failed } state_{None};
};

class Transaction {
 public:
  Transaction(Transactional& target, More more) : target_(target), more_{more}
  {
    if (more == More::Yes) {
      target_.tryBegin();
    }
  }
  explicit Transaction(Transactional& target) : target_(target), more_{More::No}
  {
    target_.tryBegin();
  }
  ~Transaction() noexcept
  {
    if (more_ == More::No) {
      target_.reset();
    } else if (!done_) {
      target_.tryRollback();
    }
  }
  // Copy.
  Transaction(const Transaction&) = delete;
  Transaction& operator=(const Transaction&) = delete;

  // Move.
  Transaction(Transaction&&) = delete;
  Transaction& operator=(Transaction&&) = delete;

  void commit()
  {
    if (more_ == More::No) {
      target_.tryCommit();
    }
    done_ = true;
  }

 private:
  Transactional& target_;
  More more_;
  bool done_{false};
};

/** @} */

} // swirly

#endif // SWIRLY_ELM_TRANSACTIONAL_HPP
