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

#ifndef IWL_WIDGET_WIDGET_HPP_
#define IWL_WIDGET_WIDGET_HPP_

#include "../defines.hpp"
#include "../event.hpp"

BEGIN_IWL()

class form;
class graphics;

class widget : private boost::noncopyable
{
    friend form;
private:
    form& m_frm;

protected:
    explicit widget(form& frm);

public:
    virtual ~widget() = 0;

    form& parent_form() const;

    event<widget, void (bool& succeeded)> on_load;
    event<widget, void (graphics& g)> on_paint;

private:
    bool fire_load();
    void fire_paint(graphics& g);
};

inline widget::widget(form& frm)
    : m_frm { frm }
{
}

inline form& widget::parent_form() const
{
    return m_frm;
}

inline bool widget::fire_load()
{
    bool succeeded = true;
    succeeded = true;
    on_load.fire_with_observer(
        [&]() { return succeeded; },
        succeeded);
    return succeeded;
}

inline void widget::fire_paint(graphics& g)
{
    on_paint.fire(g);
}

END_IWL()

#endif // IWL_WIDGET_WIDGET_HPP_