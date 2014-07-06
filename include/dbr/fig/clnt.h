/*
 *  Copyright (C) 2013, 2014 Mark Aylett <mark.aylett@gmail.com>
 *
 *  This file is part of Doobry written by Mark Aylett.
 *
 *  Doobry is free software; you can redistribute it and/or modify it under the terms of the GNU
 *  General Public License as published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  Doobry is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 *  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with this program; if
 *  not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA.
 */
#ifndef DBR_FIG_CLNT_H
#define DBR_FIG_CLNT_H

#include <dbr/elm/pool.h>

#include <stddef.h>

/**
 * @addtogroup Clnt
 * @{
 */

typedef struct FigClnt* DbrClnt;

/**
 * Create client.
 *
 * @param zctx ZeroMQ context.
 *
 * @param uuid Unique session-id.
 *
 * @param mdaddr Address of market-data endpoint.
 *
 * @param traddr Address of trading endpoint.
 *
 * @param tmout Request timeout.
 *
 * @param pool Pool.
 */

DBR_API DbrClnt
dbr_clnt_create(void* zctx, const DbrUuid uuid, const char* mdaddr, const char* traddr,
                DbrMillis tmout, DbrPool pool);

/**
 * No-op if @a clnt is null.
 */

DBR_API void
dbr_clnt_destroy(DbrClnt clnt);

DBR_API void
dbr_clnt_reset(DbrClnt clnt);

DBR_API DbrIden
dbr_clnt_close(DbrClnt clnt);

#define DBR_CLNT_END_REC NULL

static inline struct DbrRec*
dbr_clnt_rec_entry(struct DbrSlNode* node)
{
    return dbr_implof(struct DbrRec, shared_node_, node);
}

/**
 * @return NULL if record does not exist.
 */

DBR_API struct DbrSlNode*
dbr_clnt_find_rec_id(DbrClnt clnt, int type, DbrIden id);

/**
 * Compares #DBR_MNEM_MAX characters of mnem at most.
 *
 * @return NULL if record does not exist.
 */

DBR_API struct DbrSlNode*
dbr_clnt_find_rec_mnem(DbrClnt clnt, int type, const char* mnem);

/**
 * @return first record of requested type.
 */

/**
 * Size is optional.
 */

DBR_API struct DbrSlNode*
dbr_clnt_first_rec(DbrClnt clnt, int type, size_t* size);

DBR_API DbrBool
dbr_clnt_empty_rec(DbrClnt clnt, int type);

DBR_API DbrAccnt
dbr_clnt_accnt(DbrClnt clnt, struct DbrRec* arec);

DBR_API DbrIden
dbr_clnt_logon(DbrClnt clnt, DbrAccnt accnt);

DBR_API DbrIden
dbr_clnt_logoff(DbrClnt clnt, DbrAccnt accnt);

/**
 * Place order.
 * All members of result are set to zero on failure.
 */

DBR_API DbrIden
dbr_clnt_place(DbrClnt clnt, DbrAccnt trader, DbrAccnt giveup, struct DbrRec* crec,
               DbrJd settl_day, const char* ref, int action, DbrTicks ticks, DbrLots lots,
               DbrLots min_lots);

/**
 * Assumes that order already belongs to this side.
 * Reduced lots must not be:
 * - less than executed lots;
 * - less than min lots;
 * - greater than original lots.
 */

DBR_API DbrIden
dbr_clnt_revise_id(DbrClnt clnt, DbrAccnt trader, DbrIden id, DbrLots lots);

DBR_API DbrIden
dbr_clnt_revise_ref(DbrClnt clnt, DbrAccnt trader, const char* ref, DbrLots lots);

DBR_API DbrIden
dbr_clnt_cancel_id(DbrClnt clnt, DbrAccnt trader, DbrIden id);

DBR_API DbrIden
dbr_clnt_cancel_ref(DbrClnt clnt, DbrAccnt trader, const char* ref);

DBR_API DbrIden
dbr_clnt_ack_trade(DbrClnt clnt, DbrAccnt trader, DbrIden id);

DBR_API DbrIden
dbr_clnt_set_timer(DbrClnt clnt, DbrMillis absms);

DBR_API void
dbr_clnt_cancel_timer(DbrClnt clnt, DbrIden id);

#define DBR_CLNT_END_VIEW NULL

static inline struct DbrView*
dbr_clnt_view_entry(struct DbrRbNode* node)
{
    return dbr_implof(struct DbrView, clnt_node_, node);
}

DBR_API struct DbrRbNode*
dbr_clnt_find_view(DbrClnt clnt, DbrIden cid, DbrJd settl_day);

DBR_API struct DbrRbNode*
dbr_clnt_first_view(DbrClnt clnt);

DBR_API struct DbrRbNode*
dbr_clnt_last_view(DbrClnt clnt);

DBR_API DbrBool
dbr_clnt_empty_view(DbrClnt clnt);

DBR_API const unsigned char*
dbr_clnt_uuid(DbrClnt clnt);

DBR_API DbrBool
dbr_clnt_is_closed(DbrClnt clnt);

DBR_API DbrBool
dbr_clnt_is_ready(DbrClnt clnt);

/** @} */

#endif // DBR_FIG_CLNT_H