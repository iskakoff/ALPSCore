/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 * ALPS Project: Algorithms and Libraries for Physics Simulations                  *
 *                                                                                 *
 * ALPS Libraries                                                                  *
 *                                                                                 *
 * Copyright (C) 2010 - 2012 by Andreas Hehn <hehn@phys.ethz.ch>                   *
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

#ifndef __ALPS_BLASMACROS_H__
#define __ALPS_BLASMACROS_H__

#include <boost/numeric/bindings/blas.hpp>
#include <vector>

// provide overloads for types where blas can be used        
    
namespace alps {
    namespace numeric {
    
    #define IMPLEMENT_FOR_REAL_BLAS_TYPES(F) F(float) F(double)
    
    #define IMPLEMENT_FOR_COMPLEX_BLAS_TYPES(F) \
    F(std::complex<float>) \
    F(std::complex<double>)
    
    #define IMPLEMENT_FOR_ALL_BLAS_TYPES(F) \
    IMPLEMENT_FOR_REAL_BLAS_TYPES(F) \
    IMPLEMENT_FOR_COMPLEX_BLAS_TYPES(F) 
    } // namespave numeric
} // namespace alps
    
#endif // __ALPS_BLASMACROS_H__