/*
 * odict.h
 *
 *  Created on: 2013/10/27
 *      Author: mugwort_rc
 */

#ifndef ODICT_H_
#define ODICT_H_

#include <memory>
#include <stdexcept>

#include <QList>
#include <QMap>

#include <boost/range/algorithm_ext/erase.hpp>

#include "pypp.hpp"

namespace markdown{

/*!
 * A dictionary that keeps its keys in the order in which they're inserted.
 *
 * Copied from Django's SortedDict with some modifications.
 *
 */
template <class T>
class OrderedDict
{
public:
    typedef T ValueType;
    typedef QList<ValueType> Sequence;
    typedef QPair<QString, ValueType> Pair;
    typedef QList<Pair> Pairs;

public:
    OrderedDict() :
        _dict(), _keyOrder()
    {}
    OrderedDict(const OrderedDict &copy) :
        _dict(copy._dict), _keyOrder(copy._keyOrder)
    {}
    OrderedDict &operator =(const OrderedDict &rhs)
    {
        this->_dict     = rhs._dict;
        this->_keyOrder = rhs._keyOrder;
        return *this;
    }

    /*!
     * Returns the value of the item at the given zero-based index.
     */
    ValueType &at(int i)
    {
        if ( i < 0 ) {
            i = this->_dict.size() + i;
        }
        return this->_dict[this->_keyOrder.at(i)];
    }
    const ValueType at(int i) const
    {
        if ( i < 0 ) {
            i = this->_dict.size() + i;
        }
        return this->_dict[this->_keyOrder.at(i)];
    }
    const ValueType operator [](int i) const
    {
        if ( i < 0 ) {
            i = this->_dict.size() + i;
        }
        return this->_dict[this->_keyOrder.at(i)];
    }
    ValueType &operator [](const QString &key)
    {
        if ( ! this->exists(key) ) {
            this->append(key, ValueType());
        }
        return this->_dict[key];
    }
    const ValueType &operator [](const QString &key) const
    {
        return this->_dict[key];
    }
    bool exists(const QString &key)
    {
        return this->_dict.contains(key);
    }
    /*!
     * Return the index of a given key.
     */
    int index(const QString &key)
    {
        if ( ! this->_keyOrder.contains(key) ) {
            return -1;
        }
        return this->_keyOrder.indexOf(key);
    }
    int size(void) const
    {
        return this->_dict.size();
    }
    void clear(void)
    {
        this->_dict.clear();
        this->_keyOrder.clear();
    }

    void append(const QString &key, const ValueType &val)
    {
        if ( this->index(key) == -1 ) {
            this->_keyOrder.push_back(key);
        }
        this->_dict[key] = val;
    }
    /*!
     * Insert by key location.
     */
    void add(const QString &key, const ValueType &val, const QString &location)
    {
        int i = this->index_for_location(location);
        if ( i < 0 ) {
            this->append(key, val);
        } else {
            this->insert(i, key, val);
        }
    }
    /*!
     * Inserts the key, value pair before the item with the given index.
     */
    void insert(int index, const QString &key, const ValueType &val)
    {
        if ( this->exists(key) ) {
            boost::range::remove_erase(this->_keyOrder, key);
        }
        if ( index < 0 ) {
            index = this->_dict.size() + index;
        }
        if ( index < 0 ) {
            throw pypp::IndexError();
        }
        this->_keyOrder.insert(std::min(index, this->_keyOrder.size()), key);
        this->append(key, val);
    }
    /*!
     * Change location of an existing item.
     */
    void link(const QString &key, const QString &location)
    {
        int n = this->index(key);
        if ( n < 0 ) {
            n = this->_dict.size() + n;
        }
        int counter = 0;
        boost::range::remove_erase_if(this->_keyOrder, [&](const QString &) -> bool{ bool result = counter == n; ++counter; return result;  });
        try {
            int i = this->index_for_location(location);
            if ( i < 0 ) {
                this->_keyOrder.push_back(key);
            } else {
                this->_keyOrder.insert(std::min(i, this->_keyOrder.size()), key);
            }
        } catch (const std::invalid_argument &) {
            //! restore to prevent data loss and reraise
        }

    }

    Sequence toList(void) const
    {
        Sequence result;
        for ( const QString &key : this->_keyOrder ) {
            result.push_back(this->_dict[key]);
        }
        return result;
    }

    QStringList keys() const
    {
        return this->_keyOrder;
    }
    Sequence values() const
    {
        return this->toList();
    }
    Pairs items() const
    {
        Pairs result;
        for ( const QString &key : this->_keyOrder ) {
            result.append(qMakePair(key, this->_dict[key]));
        }
        return result;
    }


private:
    /*!
     * Return index or None for a given location.
     */
    int index_for_location(const QString &location)
    {
        int i = 0;
        if ( location == "_begin" ) {
            i = 0;
        } else if ( location == "_end" ) {
            i = -1;
        } else if ( location.startsWith("<") || location.startsWith(">") ) {
            i = this->index(location.mid(1));
            if ( location.startsWith(">") ) {
                if ( i >= this->_dict.size() ) {
                    //! last item
                    i = -1;
                } else {
                    i = i + 1;
                }
            }
        } else {
            throw std::invalid_argument("Not a valid location: \"" + location.toStdString() + "\". Location key "
                                        "must start with a \">\" or \"<\".");
        }
        return i;
    }

private:
    QMap<QString, ValueType> _dict;
    QStringList _keyOrder;

};

} // end of namespace markdown

#endif /* ODICT_H_ */
