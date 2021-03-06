/*
 * Copyright (C) 1998-2017 ALPS Collaboration. See COPYRIGHT.TXT
 * All rights reserved. Use is subject to license terms. See LICENSE.TXT
 * For use in publications, see ACKNOWLEDGE.TXT
 */

#ifndef ALPSCORE_GF_TENSORVIEW_H
#define ALPSCORE_GF_TENSORVIEW_H



#include <vector>
#include <array>
#include "data_storage.hpp"
#include "view.hpp"

namespace alps {
  namespace numerics {
    namespace detail {

       /**
        * @brief TensorView class. Provide interface for tensor to operate with raw data
        *
        * @tparam T - stored data type
        */
      template<typename T>
      class data_view {
      private:
        /// raw buffer storage
        view<T> data_slice_;
        /// data offset
        size_t offset_;
        /// data size
        size_t size_;
      public:
        /// Construct view of the whole DataStorage
        data_view(data_storage<T> & storage) : data_slice_(storage), offset_(0), size_(storage.size()) {}
        template<typename S>
        data_view(const data_storage<S> & storage, size_t size = 0, size_t offset = 0) : data_slice_(storage.data().data(), size), offset_(offset), size_(size) {}
        /// Construct subview of specified size for DataStorage starting from offset point
        data_view(data_storage<T> & storage, size_t size, size_t offset = 0) : data_slice_(storage), offset_(offset), size_(size) {}
        /// Move-construction of subview of specified size for another View starting from offset point
        data_view(data_view<T> && storage, size_t size, size_t offset) : data_slice_(storage.data_slice_), offset_(offset + storage.offset_), size_(size) {}
        /// Copy-construction of subview of specified size for another View starting from offset point
        data_view(const data_view<T> & storage, size_t size, size_t offset) : data_slice_(storage.data_slice_), offset_(offset + storage.offset_), size_(size) {}
        /// Create view for the raw buffer
        data_view(T*data, size_t size) : data_slice_(data, size), offset_(0), size_(size){}
        /// Copy constructor
        data_view(const data_view<T> & storage) = default;

        template<typename S>
        data_view(const data_view<S>& storage, size_t size = 0, size_t offset = 0) :
          data_slice_(&storage.data()[0], storage.size()) {};


        /// Move constructor
        data_view(data_view<T> && storage) = default;

        /// Copy assignment
        data_view<T>& operator=(const data_view<T>& rhs) = default;
        /// Move assignment
        data_view<T>& operator=(data_view<T>&& rhs) = default;

        /// @return reference to the data at point i
        T& data(size_t i) {return data_slice_.data(i + offset_);};
        /// @return const-reference to the data at point i
        const T& data(size_t i) const {return data_slice_.data(i + offset_);};
        /// bracket operators
        inline T  operator()(size_t i) const {return data_slice_.data(i + offset_);};
        inline T& operator()(size_t i) {return data_slice_.data(i + offset_);};
        /// @return buffer size
        size_t size() const {return size_;}
        /// @return offset from the buffer beginning
        size_t offset() const {return offset_;}
        /// @return pointer to the raw buffer
        T* data() {return data_slice_.data() + offset_;}
        /// @return const pointer to the raw buffer
        const T* data() const {return data_slice_.data() + offset_;}

        /// DataView comparison
        template<typename T2>
        bool operator==(const data_view<T2>& r) const {
          return size() == r.size() && std::equal(r.data(), r.data() + r.size(), data());
        }

        /// Comparison against DataStorage
        template<typename T2>
        bool operator==(const data_storage<T2>& r) const {
          return size() == r.size() && std::equal(r.data().begin(), r.data().end(), data());
        }
      };
    }
  }
}
#endif //ALPSCORE_GF_TENSORVIEW_H
