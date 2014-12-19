/*
 *  Copyright (C) 2013, 2014 Swirly Cloud Limited. All rights reserved.
 */
#ifndef SCPP_FIG_SERV_HPP
#define SCPP_FIG_SERV_HPP

#include <scpp/fig/accnt.hpp>
#include <scpp/fig/book.hpp>
#include <scpp/fig/sess.hpp>

#include <scpp/elm/order.hpp>

#include <scpp/ash/except.hpp>
#include <scpp/ash/slnode.hpp>

#include <sc/fig/serv.h>

namespace sc {

/**
 * @addtogroup Serv
 * @{
 */

template <int TypeN>
class ServRecs {
    struct Policy : NodeTraits<ScSlNode> {
        typedef ScRec Entry;
        static Entry*
        entry(Node* node)
        {
            return sc_serv_rec_entry(node);
        }
        static const Entry*
        entry(const Node* node)
        {
            return sc_serv_rec_entry(const_cast<Node*>(node));
        }
    };
    ScServ serv_;
public:
    typedef typename Policy::Entry ValueType;
    typedef typename Policy::Entry* Pointer;
    typedef typename Policy::Entry& Reference;
    typedef const typename Policy::Entry* ConstPointer;
    typedef const typename Policy::Entry& ConstReference;

    typedef ForwardIterator<Policy> Iterator;
    typedef ConstForwardIterator<Policy> ConstIterator;

    typedef std::ptrdiff_t DifferenceType;
    typedef size_t SizeType;

    // Standard typedefs.

    typedef ValueType value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ConstPointer const_pointer;
    typedef ConstReference const_reference;

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;

    typedef DifferenceType difference_type;
    typedef DifferenceType distance_type;
    typedef SizeType size_type;

    explicit
    ServRecs(ScServ serv) noexcept
        : serv_{serv}
    {
    }
    void
    swap(ServRecs& rhs) noexcept
    {
        std::swap(serv_, rhs.serv_);
    }

    // Iterator.

    Iterator
    begin() noexcept
    {
        return sc_serv_first_rec(serv_, TypeN, nullptr);
    }
    ConstIterator
    begin() const noexcept
    {
        return sc_serv_first_rec(serv_, TypeN, nullptr);
    }
    Iterator
    end() noexcept
    {
        return SC_SERV_END_REC;
    }
    ConstIterator
    end() const noexcept
    {
        return SC_SERV_END_REC;
    }
    Iterator
    find(ScIden id) noexcept
    {
        return sc_serv_find_rec_id(serv_, TypeN, id);
    }
    ConstIterator
    find(ScIden id) const noexcept
    {
        return sc_serv_find_rec_id(serv_, TypeN, id);
    }
    Iterator
    find(const char* mnem) noexcept
    {
        return sc_serv_find_rec_mnem(serv_, TypeN, mnem);
    }
    ConstIterator
    find(const char* mnem) const noexcept
    {
        return sc_serv_find_rec_mnem(serv_, TypeN, mnem);
    }

    // Accessor.

    Reference
    front() noexcept
    {
        return *begin();
    }
    ConstReference
    front() const noexcept
    {
        return *begin();
    }
    SizeType
    size() const noexcept
    {
        size_t size;
        sc_serv_first_rec(serv_, TypeN, &size);
        return size;
    }
    SizeType
    max_size() const noexcept
    {
        return std::numeric_limits<SizeType>::max();
    }
    bool
    empty() const noexcept
    {
        return sc_serv_empty_rec(serv_, TypeN) == SC_TRUE;
    }
};

typedef ServRecs<SC_ENTITY_ACCNT> ServAccntRecs;
typedef ServRecs<SC_ENTITY_CONTR> ServContrRecs;

class ServExecs {
    struct Policy : NodeTraits<ScSlNode> {
        typedef ScExec Entry;
        static Entry*
        entry(Node* node)
        {
            return sc_serv_exec_entry(node);
        }
        static const Entry*
        entry(const Node* node)
        {
            return sc_serv_exec_entry(const_cast<Node*>(node));
        }
    };
    ScServ serv_;
public:
    typedef Policy::Entry ValueType;
    typedef Policy::Entry* Pointer;
    typedef Policy::Entry& Reference;
    typedef const Policy::Entry* ConstPointer;
    typedef const Policy::Entry& ConstReference;

    typedef ForwardIterator<Policy> Iterator;
    typedef ConstForwardIterator<Policy> ConstIterator;

    typedef std::ptrdiff_t DifferenceType;
    typedef size_t SizeType;

    // Standard typedefs.

    typedef ValueType value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ConstPointer const_pointer;
    typedef ConstReference const_reference;

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;

    typedef DifferenceType difference_type;
    typedef DifferenceType distance_type;
    typedef SizeType size_type;

    explicit
    ServExecs(ScServ serv) noexcept
        : serv_{serv}
    {
    }
    void
    swap(ServExecs& rhs) noexcept
    {
        std::swap(serv_, rhs.serv_);
    }

    // Iterator.

    Iterator
    begin() noexcept
    {
        return sc_serv_first_exec(serv_);
    }
    ConstIterator
    begin() const noexcept
    {
        return sc_serv_first_exec(serv_);
    }
    Iterator
    end() noexcept
    {
        return nullptr;
    }
    ConstIterator
    end() const noexcept
    {
        return nullptr;
    }

    // Accessor.

    Reference
    front() noexcept
    {
        return *begin();
    }
    ConstReference
    front() const noexcept
    {
        return *begin();
    }
    SizeType
    size() const noexcept
    {
        return std::distance(begin(), end());
    }
    SizeType
    max_size() const noexcept
    {
        return std::numeric_limits<SizeType>::max();
    }
    bool
    empty() const noexcept
    {
        return sc_serv_empty_exec(serv_);
    }
};

class ServPosnups {
    struct Policy : NodeTraits<ScRbNode> {
        typedef ScPosn Entry;
        static Entry*
        entry(Node* node)
        {
            return sc_serv_posnup_entry(node);
        }
        static const Entry*
        entry(const Node* node)
        {
            return sc_serv_posnup_entry(const_cast<Node*>(node));
        }
    };
    ScServ serv_;
public:
    typedef Policy::Entry ValueType;
    typedef Policy::Entry* Pointer;
    typedef Policy::Entry& Reference;
    typedef const Policy::Entry* ConstPointer;
    typedef const Policy::Entry& ConstReference;

    typedef BiDirectionalIterator<Policy> Iterator;
    typedef ConstBiDirectionalIterator<Policy> ConstIterator;
    typedef ReverseBiDirectionalIterator<Policy> ReverseIterator;
    typedef ConstReverseBiDirectionalIterator<Policy> ConstReverseIterator;

    typedef std::ptrdiff_t DifferenceType;
    typedef size_t SizeType;

    // Standard typedefs.

    typedef ValueType value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ConstPointer const_pointer;
    typedef ConstReference const_reference;

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;
    typedef ReverseIterator reverse_iterator;
    typedef ConstReverseIterator const_reverse_iterator;

    typedef DifferenceType difference_type;
    typedef DifferenceType distance_type;
    typedef SizeType size_type;

    explicit
    ServPosnups(ScServ serv) noexcept
    : serv_{serv}
    {
    }
    void
    swap(ServPosnups& rhs) noexcept
    {
        std::swap(serv_, rhs.serv_);
    }

    // Iterator.

    Iterator
    begin() noexcept
    {
        return sc_serv_first_posnup(serv_);
    }
    ConstIterator
    begin() const noexcept
    {
        return sc_serv_first_posnup(serv_);
    }
    Iterator
    end() noexcept
    {
        return SC_SERV_END_POSNUP;
    }
    ConstIterator
    end() const noexcept
    {
        return SC_SERV_END_POSNUP;
    }

    // ReverseIterator.

    ReverseIterator
    rbegin() noexcept
    {
        return sc_serv_last_posnup(serv_);
    }
    ConstReverseIterator
    rbegin() const noexcept
    {
        return sc_serv_last_posnup(serv_);
    }
    ReverseIterator
    rend() noexcept
    {
        return SC_SERV_END_POSNUP;
    }
    ConstReverseIterator
    rend() const noexcept
    {
        return SC_SERV_END_POSNUP;
    }

    // Accessor.

    Reference
    front() noexcept
    {
        return *begin();
    }
    ConstReference
    front() const noexcept
    {
        return *begin();
    }
    Reference
    back() noexcept
    {
        return *rbegin();
    }
    ConstReference
    back() const noexcept
    {
        return *rbegin();
    }
    SizeType
    size() const noexcept
    {
        return std::distance(begin(), end());
    }
    SizeType
    max_size() const noexcept
    {
        return std::numeric_limits<SizeType>::max();
    }
    bool
    empty() const noexcept
    {
        return sc_serv_empty_posnup(serv_);
    }
};

class ServBooks {
    struct Policy : NodeTraits<ScRbNode> {
        typedef ScBook Entry;
        static Entry*
        entry(Node* node)
        {
            return sc_serv_book_entry(node);
        }
        static const Entry*
        entry(const Node* node)
        {
            return sc_serv_book_entry(const_cast<Node*>(node));
        }
    };
    ScServ serv_;
public:
    typedef Policy::Entry ValueType;
    typedef Policy::Entry* Pointer;
    typedef Policy::Entry& Reference;
    typedef const Policy::Entry* ConstPointer;
    typedef const Policy::Entry& ConstReference;

    typedef BiDirectionalIterator<Policy> Iterator;
    typedef ConstBiDirectionalIterator<Policy> ConstIterator;
    typedef ReverseBiDirectionalIterator<Policy> ReverseIterator;
    typedef ConstReverseBiDirectionalIterator<Policy> ConstReverseIterator;

    typedef std::ptrdiff_t DifferenceType;
    typedef size_t SizeType;

    // Standard typedefs.

    typedef ValueType value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ConstPointer const_pointer;
    typedef ConstReference const_reference;

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;
    typedef ReverseIterator reverse_iterator;
    typedef ConstReverseIterator const_reverse_iterator;

    typedef DifferenceType difference_type;
    typedef DifferenceType distance_type;
    typedef SizeType size_type;

    explicit
    ServBooks(ScServ serv) noexcept
    : serv_{serv}
    {
    }
    void
    swap(ServBooks& rhs) noexcept
    {
        std::swap(serv_, rhs.serv_);
    }

    // Iterator.

    Iterator
    begin() noexcept
    {
        return sc_serv_first_book(serv_);
    }
    ConstIterator
    begin() const noexcept
    {
        return sc_serv_first_book(serv_);
    }
    Iterator
    end() noexcept
    {
        return SC_SERV_END_BOOK;
    }
    ConstIterator
    end() const noexcept
    {
        return SC_SERV_END_BOOK;
    }

    // ReverseIterator.

    ReverseIterator
    rbegin() noexcept
    {
        return sc_serv_last_book(serv_);
    }
    ConstReverseIterator
    rbegin() const noexcept
    {
        return sc_serv_last_book(serv_);
    }
    ReverseIterator
    rend() noexcept
    {
        return SC_SERV_END_BOOK;
    }
    ConstReverseIterator
    rend() const noexcept
    {
        return SC_SERV_END_BOOK;
    }

    // Find.

    Iterator
    find(ScIden cid, ScJd settl_day) noexcept
    {
        return sc_serv_find_book(serv_, cid, settl_day);
    }
    ConstIterator
    find(ScIden cid, ScJd settl_day) const noexcept
    {
        return sc_serv_find_book(serv_, cid, settl_day);
    }

    // Accessor.

    Reference
    front() noexcept
    {
        return *begin();
    }
    ConstReference
    front() const noexcept
    {
        return *begin();
    }
    Reference
    back() noexcept
    {
        return *rbegin();
    }
    ConstReference
    back() const noexcept
    {
        return *rbegin();
    }
    SizeType
    size() const noexcept
    {
        return std::distance(begin(), end());
    }
    SizeType
    max_size() const noexcept
    {
        return std::numeric_limits<SizeType>::max();
    }
    bool
    empty() const noexcept
    {
        return sc_serv_empty_book(serv_);
    }
};

class ServBookups {
    struct Policy : NodeTraits<ScRbNode> {
        typedef ScBook Entry;
        static Entry*
        entry(Node* node)
        {
            return sc_serv_bookup_entry(node);
        }
        static const Entry*
        entry(const Node* node)
        {
            return sc_serv_bookup_entry(const_cast<Node*>(node));
        }
    };
    ScServ serv_;
public:
    typedef Policy::Entry ValueType;
    typedef Policy::Entry* Pointer;
    typedef Policy::Entry& Reference;
    typedef const Policy::Entry* ConstPointer;
    typedef const Policy::Entry& ConstReference;

    typedef BiDirectionalIterator<Policy> Iterator;
    typedef ConstBiDirectionalIterator<Policy> ConstIterator;
    typedef ReverseBiDirectionalIterator<Policy> ReverseIterator;
    typedef ConstReverseBiDirectionalIterator<Policy> ConstReverseIterator;

    typedef std::ptrdiff_t DifferenceType;
    typedef size_t SizeType;

    // Standard typedefs.

    typedef ValueType value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef ConstPointer const_pointer;
    typedef ConstReference const_reference;

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;
    typedef ReverseIterator reverse_iterator;
    typedef ConstReverseIterator const_reverse_iterator;

    typedef DifferenceType difference_type;
    typedef DifferenceType distance_type;
    typedef SizeType size_type;

    explicit
    ServBookups(ScServ serv) noexcept
    : serv_{serv}
    {
    }
    void
    swap(ServBookups& rhs) noexcept
    {
        std::swap(serv_, rhs.serv_);
    }

    // Iterator.

    Iterator
    begin() noexcept
    {
        return sc_serv_first_bookup(serv_);
    }
    ConstIterator
    begin() const noexcept
    {
        return sc_serv_first_bookup(serv_);
    }
    Iterator
    end() noexcept
    {
        return SC_SERV_END_BOOKUP;
    }
    ConstIterator
    end() const noexcept
    {
        return SC_SERV_END_BOOKUP;
    }

    // ReverseIterator.

    ReverseIterator
    rbegin() noexcept
    {
        return sc_serv_last_bookup(serv_);
    }
    ConstReverseIterator
    rbegin() const noexcept
    {
        return sc_serv_last_bookup(serv_);
    }
    ReverseIterator
    rend() noexcept
    {
        return SC_SERV_END_BOOKUP;
    }
    ConstReverseIterator
    rend() const noexcept
    {
        return SC_SERV_END_BOOKUP;
    }

    // Accessor.

    Reference
    front() noexcept
    {
        return *begin();
    }
    ConstReference
    front() const noexcept
    {
        return *begin();
    }
    Reference
    back() noexcept
    {
        return *rbegin();
    }
    ConstReference
    back() const noexcept
    {
        return *rbegin();
    }
    SizeType
    size() const noexcept
    {
        return std::distance(begin(), end());
    }
    SizeType
    max_size() const noexcept
    {
        return std::numeric_limits<SizeType>::max();
    }
    bool
    empty() const noexcept
    {
        return sc_serv_empty_bookup(serv_);
    }
};

class Serv {
    ScServ impl_;
public:
    ~Serv() noexcept
    {
        if (impl_)
            sc_serv_destroy(impl_);
    }
    constexpr
    Serv(decltype(nullptr)) noexcept
        : impl_{nullptr}
    {
    }
    Serv(const char* bank, ScJourn journ, ScPool pool)
        : impl_{sc_serv_create(bank, journ, pool)}
    {
        if (!impl_)
            throw_exception();
    }
    operator ScServ() const noexcept
    {
        return impl_;
    }

    // Copy semantics.

    Serv(const Serv&) = delete;

    Serv&
    operator =(const Serv&) = delete;

    // Move semantics.

    Serv(Serv&& rhs) noexcept
        : impl_{nullptr}
    {
        swap(rhs);
    }
    Serv&
    operator =(Serv&& rhs) noexcept
    {
        if (impl_) {
            sc_serv_destroy(impl_);
            impl_ = nullptr;
        }
        swap(rhs);
        return *this;
    }
    void
    swap(Serv& rhs) noexcept
    {
        std::swap(impl_, rhs.impl_);
    }
    void
    load(ScModel model)
    {
        if (!sc_serv_load(impl_, model))
            throw_exception();
    }
    template <int TypeN>
    ServRecs<TypeN>
    recs() const noexcept
    {
        return ServRecs<TypeN>{impl_};
    }
    ServAccntRecs
    arecs() const noexcept
    {
        return ServAccntRecs{impl_};
    }
    ServContrRecs
    crecs() const noexcept
    {
        return ServContrRecs{impl_};
    }
    Accnt
    accnt(ScRec& arec) const
    {
        ScAccnt accnt = sc_serv_accnt(impl_, &arec);
        if (!accnt)
            throw_exception();
        return Accnt{accnt};
    }
    BookRef
    book(ScRec& crec, ScJd settl_day) const
    {
        ScBook* const book = sc_serv_book(impl_, &crec, settl_day);
        if (!book)
            throw_exception();
        return BookRef{*book};
    }
    SessRef
    sess(const ScUuid uuid) const
    {
        ScSess* const sess = sc_serv_sess(impl_, uuid);
        if (!sess)
            throw_exception();
        return SessRef{*sess};
    }
    OrderRef
    place(ScAccnt trader, ScAccnt giveup, ScBook& book, const char* ref, int action,
          ScTicks ticks, ScLots lots, ScLots min_lots)
    {
        ScOrder* const order = sc_serv_place(impl_, trader, giveup, &book, ref, action, ticks,
                                               lots, min_lots);
        if (!order)
            throw_exception();
        return OrderRef{*order};
    }
    OrderRef
    revise(ScAccnt trader, ScIden id, ScLots lots)
    {
        ScOrder* const order = sc_serv_revise_id(impl_, trader, id, lots);
        if (!order)
            throw_exception();
        return OrderRef{*order};
    }
    OrderRef
    revise(ScAccnt trader, const char* ref, ScLots lots)
    {
        ScOrder* const order = sc_serv_revise_ref(impl_, trader, ref, lots);
        if (!order)
            throw_exception();
        return OrderRef{*order};
    }
    OrderRef
    cancel(ScAccnt trader, ScIden id)
    {
        ScOrder* const order = sc_serv_cancel_id(impl_, trader, id);
        if (!order)
            throw_exception();
        return OrderRef{*order};
    }
    OrderRef
    cancel(ScAccnt trader, const char* ref)
    {
        ScOrder* const order = sc_serv_cancel_ref(impl_, trader, ref);
        if (!order)
            throw_exception();
        return OrderRef{*order};
    }
    void
    ack_trade(ScAccnt trader, ScIden id)
    {
        if (!sc_serv_ack_trade(impl_, trader, id))
            throw_exception();
    }
    void
    clear() noexcept
    {
        sc_serv_clear(impl_);
    }
    ServExecs
    execs() const noexcept
    {
        return ServExecs{impl_};
    }
    ServPosnups
    posnups() const noexcept
    {
        return ServPosnups{impl_};
    }
    ServBooks
    books() const noexcept
    {
        return ServBooks{impl_};
    }
    ServBookups
    bookups() const noexcept
    {
        return ServBookups{impl_};
    }
};

/** @} */

} // sc

#endif // SCPP_FIG_SERV_HPP