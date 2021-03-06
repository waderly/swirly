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
#ifndef SWIRLY_WEB_TYPES_HPP
#define SWIRLY_WEB_TYPES_HPP

#include <swirly/contrib/http_parser.h>

#include <iostream>

namespace swirly {
inline namespace web {

enum class HttpMethod : int {
    Delete = HTTP_DELETE,
    Get = HTTP_GET,
    Head = HTTP_HEAD,
    Post = HTTP_POST,
    Put = HTTP_PUT,
    Connect = HTTP_CONNECT,
    Options = HTTP_OPTIONS,
    Trace = HTTP_TRACE,
    Copy = HTTP_COPY,
    Lock = HTTP_LOCK,
    MkCol = HTTP_MKCOL,
    Move = HTTP_MOVE,
    PropFind = HTTP_PROPFIND,
    PropPatch = HTTP_PROPPATCH,
    Search = HTTP_SEARCH,
    Unlock = HTTP_UNLOCK,
    Bind = HTTP_BIND,
    Rebind = HTTP_REBIND,
    Unbind = HTTP_UNBIND,
    Acl = HTTP_ACL,
    Report = HTTP_REPORT,
    MkActivity = HTTP_MKACTIVITY,
    Checkout = HTTP_CHECKOUT,
    Merge = HTTP_MERGE,
    MSearch = HTTP_MSEARCH,
    Notify = HTTP_NOTIFY,
    Subscribe = HTTP_SUBSCRIBE,
    Unsubscribe = HTTP_UNSUBSCRIBE,
    Patch = HTTP_PATCH,
    Purge = HTTP_PURGE,
    MkCalendar = HTTP_MKCALENDAR,
    Link = HTTP_LINK,
    Unlink = HTTP_UNLINK,
    Source = HTTP_SOURCE
};

inline const char* enum_string(HttpMethod method) noexcept
{
    return http_method_str(static_cast<http_method>(method));
}

inline std::ostream& operator<<(std::ostream& os, HttpMethod method)
{
    return os << enum_string(method);
}

enum class HttpStatus : int {
    Ok = HTTP_STATUS_OK,
    NoContent = HTTP_STATUS_NO_CONTENT,
    BadRequest = HTTP_STATUS_BAD_REQUEST,
    Unauthorized = HTTP_STATUS_UNAUTHORIZED,
    Forbidden = HTTP_STATUS_FORBIDDEN,
    NotFound = HTTP_STATUS_NOT_FOUND,
    MethodNotAllowed = HTTP_STATUS_METHOD_NOT_ALLOWED,
    InternalServerError = HTTP_STATUS_INTERNAL_SERVER_ERROR,
    ServiceUnavailable = HTTP_STATUS_SERVICE_UNAVAILABLE
};

SWIRLY_API const char* enum_string(HttpStatus status) noexcept;

SWIRLY_API HttpStatus http_status(const std::error_code& ec);

inline const char* http_reason(HttpStatus status) noexcept
{
    return enum_string(status);
}

inline std::ostream& operator<<(std::ostream& os, HttpStatus status)
{
    return os << static_cast<int>(status);
}

enum class HttpType : int { Request = HTTP_REQUEST, Response = HTTP_RESPONSE };

} // namespace web
} // namespace swirly

#endif // SWIRLY_WEB_TYPES_HPP
