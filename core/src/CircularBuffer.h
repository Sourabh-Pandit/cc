/*
 * Copyright (C) 2007-2016 Frank Mertens.
 *
 * Distribution and use is allowed under the terms of the zlib license
 * (see cc/LICENSE-zlib).
 *
 */

#pragma once

#include <cc/assert>
#include <cc/Array>

namespace cc {

/** \class CircularBuffer CircularBuffer.h cc/CircularBuffer
  * \ingroup container
  * \brief Circular buffer data container
  */
template<class T>
class CircularBuffer: public Object
{
public:
    /// Item type
    typedef T Item;

    /** Create a new circular buffer
      * \param capacity max number of items storable in the circular buffer
      * \return new object instance
      */
    inline static Ref<CircularBuffer> create(int capacity)
    {
        return new CircularBuffer(size);
    }

    /// Maximum number of items storable in the circular buffer
    inline int capacity() const { return size_; }

    /// Current number of items stored in the circular buffer
    inline int count() const { return fill_; }

    /** Check if index is within range
      * \param i item index
      * \return true if i is a valid index
      */
    inline bool has(int i) const { return (0 <= i) && (i < fill_); }

    /** Access item at index i (readonly)
      * \param i item index
      * \return low-level reference
      */
    inline const T& at(int i) const { return front(i); }

    /** Insert a new item at the end of the circular buffer
      * \param item item value
      */
    void pushBack(const T& item, int = 0)
    {
        CC_ASSERT(fill_ != size_);
        ++head_;
        if (head_ >= size_) head_ = 0;
        ++fill_;
        buf_->at(head_) = item;
    }

    /** Add a new item to the head of the queue
      * \param item item value
      */
    void pushFront(const T& item, int = 0)
    {
        CC_ASSERT(fill_ < size_);
        buf_->at(tail_) = item;
        --tail_;
        if (tail_ < 0) tail_ = size_ - 1;
        ++fill_;
    }

    /** Remove an item from the head of the queue
      * \param item optionally return the item value
      * \return item value
      */
    T popFront(T* item)
    {
        CC_ASSERT(fill_ > 0);
        ++tail_;
        if (tail_ >= size_) tail_ = 0;
        --fill_;
        return *item = buf_->at(tail_);
    }

    /** Remove an item from the end of the queue
      * \param item optionally return the item value
      * \return item value
      */
    T popBack(T* item)
    {
        CC_ASSERT(fill_ > 0);
        *item = buf_->at(head_);
        --head_;
        if (head_ < 0) head_ = size_ - 1;
        --fill_;
        return *item;
    }

    /** Remove the last item from the queue
      * \return item value
      */
    inline T popBack() { T item; return popBack(&item); }

    /** Remove the first item from the queue
      * \return item value
      */
    inline T popFront() { T item; return popFront(&item); }

    /// \copydoc pushBack(const T &)
    inline void push(const T &item) { pushBack(item); }

    /// \copydoc popFront(T *item)
    inline T pop(T* item) { return popFront(item); }

    /// \copydoc popFront()
    inline T pop() { return popFront(); }

    /// Return the an item from the front
    inline T back(int i = 0) const
    {
        CC_ASSERT((0 <= i) && (i < fill_));
        i = -i;
        i += head_;
        if (i < 0) i += size_;
        return buf_->at(i);
    }

    /// Return the an item from the end
    inline T front(int i = 0) const
    {
        CC_ASSERT((0 <= i) && (i < fill_));
        i += tail_ + 1;
        if (i >= size_) i -= size_;
        return buf_->at(i);
    }

    /// Reset the circular buffer to an empty state
    inline void deplete()
    {
        fill_ = 0;
        head_ = size_ - 1;
        tail_ = size_ - 1;
    }

private:
    CircularBuffer(int size):
        fill_(0),
        size_(size),
        head_(size_-1),
        tail_(size_-1),
        buf_(Array<T>::create(size_))
    {}

    ~CircularBuffer()
    {}

    int fill_;
    int size_;
    int head_;
    int tail_;
    Ref< Array<T> > buf_;
};

} // namespace cc
