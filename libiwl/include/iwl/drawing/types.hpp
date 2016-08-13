// Copyright (c) 2014, Im Kyeong-Hyeon
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef IWL_DRAWING_TYPES_HPP_
#define IWL_DRAWING_TYPES_HPP_

#include "../defines.hpp"

BEGIN_IWL()

struct point
{
    float x, y;
};
inline bool operator ==(const point& lhs, const point& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}
inline bool operator !=(const point& lhs, const point& rhs)
{
    return !(lhs == rhs);
}

struct size
{
    float width, height;
};
inline bool operator ==(const size& lhs, const size& rhs)
{
    return (lhs.width == rhs.width && lhs.height == rhs.height);
}
inline bool operator !=(const size& lhs, const size& rhs)
{
    return !(lhs == rhs);
}

struct rectangle
{
    float x, y;
    float width, height;
};
inline bool operator ==(const rectangle& lhs, const rectangle& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y
        && lhs.width == rhs.width && lhs.height == rhs.height);
}
inline bool operator !=(const rectangle& lhs, const rectangle& rhs)
{
    return !(lhs == rhs);
}

END_IWL()

#endif // IWL_DRAWING_TYPES_HPP_
