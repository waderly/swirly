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
#ifndef SWIRLY_SYS_EPOLL_HPP
#define SWIRLY_SYS_EPOLL_HPP

#include <swirly/sys/Error.hpp>
#include <swirly/sys/Handle.hpp>

#include <sys/epoll.h>

namespace swirly {
inline namespace sys {
namespace os {

inline FileHandle epoll_create(int size, std::error_code& ec) noexcept
{
    const auto ret = ::epoll_create(size);
    if (ret < 0) {
        ec = make_error(errno);
    }
    return ret;
}

inline FileHandle epoll_create(int size)
{
    const auto fd = ::epoll_create(size);
    if (fd < 0) {
        throw std::system_error{make_error(errno), "epoll_create"};
    }
    return fd;
}

inline int epoll_ctl(int epfd, int op, int fd, epoll_event event, std::error_code& ec) noexcept
{
    const auto ret = ::epoll_ctl(epfd, op, fd, &event);
    if (ret < 0) {
        ec = make_error(errno);
    }
    return ret;
}

inline void epoll_ctl(int epfd, int op, int fd, epoll_event event)
{
    const auto ret = ::epoll_ctl(epfd, op, fd, &event);
    if (ret < 0) {
        throw std::system_error{make_error(errno), "epoll_ctl"};
    }
}

inline int epoll_wait(int epfd, epoll_event* events, int maxevents, int timeout,
                      std::error_code& ec) noexcept
{
    const auto ret = ::epoll_wait(epfd, events, maxevents, timeout);
    if (ret < 0) {
        ec = make_error(errno);
    }
    return ret;
}

inline int epoll_wait(int epfd, epoll_event* events, int maxevents, int timeout)
{
    const auto ret = ::epoll_wait(epfd, events, maxevents, timeout);
    if (ret < 0) {
        throw std::system_error{make_error(errno), "epoll_wait"};
    }
    return ret;
}

} // namespace os
} // namespace sys
} // namespace swirly

#endif // SWIRLY_SYS_EPOLL_HPP
