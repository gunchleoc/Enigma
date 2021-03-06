/*
 * Copyright (C) 2002 Daniel Heck
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef ECL_ALIST_HH
#define ECL_ALIST_HH

// This file defines STL-like associative lists similar to those found in Lisp
// dialects, but with a C++-ish look and feel. They can be used as a std::map
// replacement when linear searches aren't expensive.

#include <string>
#include <list>
#include <utility>

namespace ecl {

template <class KEY, class VAL>
class AssocList : public std::list<std::pair<KEY, VAL> > {
public:
    typedef KEY key_type;
    typedef std::pair<KEY, VAL> value_type;
    typedef typename std::list<value_type>::iterator iterator;
    typedef typename std::list<value_type>::const_iterator const_iterator;

    iterator find(const key_type &key) {
        for (auto i = this->begin(); i != this->end(); ++i)
            if (i->first == key)
                return i;
        return this->end();
    }

    const_iterator find(const key_type &key) const {
        for (auto i = this->begin(); i != this->end(); ++i)
            if (i->first == key)
                return i;
        return this->end();
    }

    VAL &operator[](const key_type &key) {
        auto i = find(key);
        if (i == this->end())
            i = this->insert(this->end(), make_pair(key, VAL()));
        return i->second;
    }

    void remove_key(const key_type &key) {
        auto i = find(key);
        if (i != this->end())
            this->erase(i);
    }
};

}  // namespace ecl

#endif
