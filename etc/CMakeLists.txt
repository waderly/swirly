# The Restful Matching-Engine.
# Copyright (C) 2013, 2018 Swirly Cloud Limited.
#
# This program is free software; you can redistribute it and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if
# not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

configure_file(swirlyd.conf.in "${PROJECT_BINARY_DIR}/etc/swirlyd.conf")
configure_file(swirlyd.service.in "${PROJECT_BINARY_DIR}/etc/swirlyd.service")
configure_file(swirlyd.service.conf.in "${PROJECT_BINARY_DIR}/etc/swirlyd.service.conf")

install(FILES
  "${PROJECT_BINARY_DIR}/etc/swirlyd.conf"
  "${PROJECT_BINARY_DIR}/etc/swirlyd.service"
  "${PROJECT_BINARY_DIR}/etc/swirlyd.service.conf"
  DESTINATION etc
  COMPONENT config
)

add_subdirectory(cmake)
add_subdirectory(fbs)
add_subdirectory(sql)
