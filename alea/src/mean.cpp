#include <alps/alea/mean.hpp>
#include <alps/alea/util.hpp>
#include <alps/alea/computed.hpp>

#include <alps/alea/internal/util.hpp>

namespace alps { namespace alea {

template <typename T>
void mean_data<T>::reset()
{
    data_.fill(0);
    count_ = 0;
}

template <typename T>
void mean_data<T>::convert_to_mean()
{
    data_ /= count_;
}

template <typename T>
void mean_data<T>::convert_to_sum()
{
    data_ *= count_;
}

template class mean_data<double>;
template class mean_data<std::complex<double> >;


// We need an explicit copy constructor, as we need to copy the data
template <typename T>
mean_acc<T>::mean_acc(const mean_acc &other)
    : store_(other.store_ ? new mean_data<T>(*other.store_) : nullptr)
    , size_(other.size_)
{ }

template <typename T>
mean_acc<T> &mean_acc<T>::operator=(const mean_acc &other)
{
    store_.reset(other.store_ ? new mean_data<T>(*other.store_) : nullptr);
    size_ = other.size_;
    return *this;
}

template <typename T>
void mean_acc<T>::add(const computed<T> &source, size_t count)
{
    internal::check_valid(*this);
    source.add_to(sink<T>(store_->data().data(), size()));
    store_->count() += count;
}

template <typename T>
void mean_acc<T>::reset()
{
    if (valid())
        store_->reset();
    else
        store_.reset(new mean_data<T>(size_));
}

template <typename T>
mean_result<T> mean_acc<T>::result() const
{
    internal::check_valid(*this);
    mean_result<T> result(*store_);
    result.store_->convert_to_mean();
    return result;
}

template <typename T>
mean_result<T> mean_acc<T>::finalize()
{
    mean_result<T> result;
    finalize_to(result);
    return result;
}

template <typename T>
void mean_acc<T>::finalize_to(mean_result<T> &result)
{
    internal::check_valid(*this);
    result.store_.reset();
    result.store_.swap(store_);
    result.store_->convert_to_mean();
}

template class mean_acc<double>;
template class mean_acc<std::complex<double> >;


// We need an explicit copy constructor, as we need to copy the data
template <typename T>
mean_result<T>::mean_result(const mean_result &other)
    : store_(other.store_ ? new mean_data<T>(*other.store_) : nullptr)
{ }

template <typename T>
mean_result<T> &mean_result<T>::operator=(const mean_result &other)
{
    store_.reset(other.store_ ? new mean_data<T>(*other.store_) : nullptr);
    return *this;
}

template <typename T>
void mean_result<T>::reduce(const reducer &r, bool pre_commit, bool post_commit)
{
    internal::check_valid(*this);
    if (pre_commit) {
        store_->convert_to_sum();
        r.reduce(sink<T>(store_->data().data(), store_->data().rows()));
        r.reduce(sink<size_t>(&store_->count(), 1));
    }
    if (pre_commit && post_commit) {
        r.commit();
    }
    if (post_commit) {
        reducer_setup setup = r.get_setup();
        if (setup.have_result)
            store_->convert_to_mean();
        else
            store_.reset();   // free data
    }
}

template class mean_result<double>;
template class mean_result<std::complex<double> >;


template <typename T>
void serialize(serializer &s, const mean_result<T> &self)
{
    internal::check_valid(self);
    s.write("count", make_adapter(self.count()));
    s.write("mean/value", make_adapter(self.mean()));
}

template void serialize(serializer &, const mean_result<double> &);
template void serialize(serializer &, const mean_result<std::complex<double> > &);

}} /* namespace alps::alea */
