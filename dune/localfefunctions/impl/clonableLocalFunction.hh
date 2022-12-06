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
#include <dune/localfefunctions/meta.hh>
namespace Dune {

  template <typename LFImpl>
  class ClonableLocalFunction {
  public:
    LFImpl clone() const {
      return LFImpl(underlying().basis(), underlying().coeffs, underlying().geometry(), Dune::index_constant< LFImpl::id[0]>());
    }

    template <typename OtherType, size_t ID = 0>
    auto rebindClone(OtherType&& t, Dune::index_constant<ID>&& id = Dune::index_constant<0>()) const {
      if constexpr (LFImpl::id[0] == ID)
        return typename LFImpl::template rebind<OtherType>::other(underlying().basis(),
                                                                  convertUnderlying<OtherType>(underlying().coeffs),
                                                                  underlying().geometry(), Dune::index_constant< LFImpl::id[0]>());
      else
        return clone();
    }

  private:
    constexpr LFImpl const& underlying() const  // CRTP
    {
      return static_cast<LFImpl const&>(*this);
    }
  };

}  // namespace Dune
