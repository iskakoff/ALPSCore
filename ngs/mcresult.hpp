/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 * ALPS Project: Algorithms and Libraries for Physics Simulations                  *
 *                                                                                 *
 * ALPS Libraries                                                                  *
 *                                                                                 *
 * Copyright (C) 2010 - 2011 by Lukas Gamper <gamperl@gmail.com>                   *
 *                           Matthias Troyer <troyer@comp-phys.org>                *
 *                                                                                 *
 * This software is part of the ALPS libraries, published under the ALPS           *
 * Library License; you can use, redistribute it and/or modify it under            *
 * the terms of the license, either version 1 or (at your option) any later        *
 * version.                                                                        *
 *                                                                                 *
 * You should have received a copy of the ALPS Library License along with          *
 * the ALPS Libraries; see the file LICENSE.txt. If not, the license is also       *
 * available from http://alps.comp-phys.org/.                                      *
 *                                                                                 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT       *
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE       *
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,     *
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER     *
 * DEALINGS IN THE SOFTWARE.                                                       *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ALPS_NGS_MCRESULT_HPP
#define ALPS_NGS_MCRESULT_HPP

#include <alps/config.h>
#include <alps/hdf5/hdf5_fwd.hpp>
#include <alps/alea/observable_fwd.hpp>

#ifdef ALPS_HAVE_MPI
    #include <boost/mpi.hpp>
#endif

#include <map>
#include <vector>
#include <iostream>

namespace alps {

    namespace detail {

        class mcresult_impl_base;

    }

    class mcresult;

    mcresult sin(mcresult rhs);
    mcresult cos(mcresult rhs);
    mcresult tan(mcresult rhs);
    mcresult sinh(mcresult rhs);
    mcresult cosh(mcresult rhs);
    mcresult tanh(mcresult rhs);
    mcresult asin(mcresult rhs);
    mcresult acos(mcresult rhs);
    mcresult atan(mcresult rhs);
    mcresult asinh(mcresult rhs);
    mcresult acosh(mcresult rhs);
    mcresult atanh(mcresult rhs);
    mcresult abs(mcresult rhs);
    mcresult sq(mcresult rhs);
    mcresult cb(mcresult rhs);
    mcresult sqrt(mcresult rhs);
    mcresult cbrt(mcresult rhs);
    mcresult exp(mcresult rhs);
    mcresult log(mcresult rhs);

    mcresult pow(mcresult rhs, double exponent);

    class mcresult {

        public:

            friend mcresult sin(mcresult rhs);
            friend mcresult cos(mcresult rhs);
            friend mcresult tan(mcresult rhs);
            friend mcresult sinh(mcresult rhs);
            friend mcresult cosh(mcresult rhs);
            friend mcresult tanh(mcresult rhs);
            friend mcresult asin(mcresult rhs);
            friend mcresult acos(mcresult rhs);
            friend mcresult atan(mcresult rhs);
            friend mcresult asinh(mcresult rhs);
            friend mcresult acosh(mcresult rhs);
            friend mcresult atanh(mcresult rhs);
            friend mcresult abs(mcresult rhs);
            friend mcresult sq(mcresult rhs);
            friend mcresult cb(mcresult rhs);
            friend mcresult sqrt(mcresult rhs);
            friend mcresult cbrt(mcresult rhs);
            friend mcresult exp(mcresult rhs);
            friend mcresult log(mcresult rhs);
            friend mcresult pow(mcresult rhs, double exponent);

            mcresult();
            mcresult(Observable const * obs);
            mcresult(mcresult const & rhs);

            virtual ~mcresult();

            mcresult & operator=(mcresult rhs);

            bool can_rebin() const;
            bool jackknife_valid() const;

            uint64_t count() const;

            uint64_t bin_size() const;
            uint64_t max_bin_number() const;
            std::size_t bin_number() const;

            template <typename T> std::vector<T> const & bins() const;

            template <typename T> T const & mean() const;

            template <typename T> T const & error() const;

            bool has_variance() const;
            template <typename T> T const & variance() const;

            bool has_tau() const;
            template <typename T> T const & tau() const;

            template <typename T> T const & covariance() const;

            void set_bin_size(uint64_t binsize);
            void set_bin_number(uint64_t bin_number);

            void serialize(hdf5::iarchive & ar);
            void serialize(hdf5::oarchive & ar) const;

            void output(std::ostream & os) const;

            #ifdef ALPS_HAVE_MPI
                mcresult reduce(boost::mpi::communicator const & communicator, std::size_t binnumber);
            #endif

            bool operator==(mcresult const & rhs) const;
            bool operator!=(mcresult const & rhs) const;

            mcresult & operator+=(mcresult const & rhs);
            mcresult & operator-=(mcresult const & rhs);
            mcresult & operator*=(mcresult const & rhs);
            mcresult & operator/=(mcresult const & rhs);
            /*
            template <typename T> mcresult & operator+=(T const & rhs);
            template <typename T> mcresult & operator-=(T const & rhs);
            template <typename T> mcresult & operator*=(T const & rhs);
            template <typename T> mcresult & operator/=(T const & rhs);
            */
            mcresult & operator+();
            mcresult & operator-();

        private:

            detail::mcresult_impl_base * impl_;
            static std::map<detail::mcresult_impl_base *, std::size_t> ref_cnt_;

    };

    std::ostream & operator<<(std::ostream & os, mcresult const & result);
/*
    #define ALPS_NGS_MCRESULT_OPERATOR(OPERATOR)                                                       \
        mcresult operator ## OPERATOR(mcresult lhs, mcresult  const & rhs);                            \
        template <typename T> mcresult operator ## OPERATOR(mcresult lhs, T const & rhs);              \
        template <typename T> mcresult operator ## OPERATOR(T const & lhs, mcresult const & rhs);      \
    ALPS_NGS_MCRESULT_OPERATOR(+)
    ALPS_NGS_MCRESULT_OPERATOR(-)
    ALPS_NGS_MCRESULT_OPERATOR(*)
    ALPS_NGS_MCRESULT_OPERATOR(/)
    #undef ALPS_NGS_MCRESULT_OPERATOR
*/
}

#endif