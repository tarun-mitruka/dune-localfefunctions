/*
 * This file is part of the Ikarus distribution (https://github.com/ikarus-project/ikarus).
 * Copyright (c) 2022. The Ikarus developers.
 *
 * This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#pragma once
#include <dune/localfefunctions/expressions/unaryExpr.hh>
//#include <ikarus/utils/linearAlgebraHelper.hh>
namespace Dune {

  template <typename E1>
  class NegateExpr : public UnaryExpr<NegateExpr, E1> {
  public:
    using Base = UnaryExpr<NegateExpr, E1>;
    using Base::Base;
    using Traits                   = LocalFunctionTraits<NegateExpr>;
    using ctype                    = typename Traits::ctype;
    static constexpr int valueSize = Traits::valueSize;
    using LinearAlgebra = typename Base::E1Raw::LinearAlgebra;

    template <size_t ID_ = 0>
    static constexpr int orderID = Base::E1Raw::template orderID<ID_>;

    template <typename LFArgs>
    auto evaluateValueOfExpression(const LFArgs& lfArgs) const {
      return Dune::eval(-evaluateFunctionImpl(this->m(), lfArgs));
    }

    template <int DerivativeOrder, typename LFArgs>
    auto evaluateDerivativeOfExpression(const LFArgs& lfArgs) const {
      return Dune::eval(-evaluateDerivativeImpl(this->m(), lfArgs));
    }
  };

  template <typename E1>
  struct LocalFunctionTraits<NegateExpr<E1>> : public LocalFunctionTraits<std::remove_cvref_t<E1>> {};

  template <typename E1>
  requires IsLocalFunction<E1>
  constexpr auto operator-(E1&& u) { return NegateExpr<E1>(std::forward<E1>(u)); }

}  // namespace Dune
