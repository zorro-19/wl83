/*
 * Copyright (c) 2021 - 2024 the ThorVG project. All rights reserved.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../../lv_conf_internal.h"
#if LV_USE_THORVG_INTERNAL

#ifndef _TVG_SAVE_MODULE_H_
#define _TVG_SAVE_MODULE_H_

#include "tvgIteratorAccessor.h"

namespace tvg
{

class SaveModule
{
public:
    virtual ~SaveModule() {}

    virtual bool save(Paint *paint, const string &path, bool compress) = 0;
    virtual bool save(Animation *animation, Paint *bg, const string &path, uint32_t quality, uint32_t fps) = 0;
    virtual bool close() = 0;
};

}

#endif //_TVG_SAVE_MODULE_H_

#endif /* LV_USE_THORVG_INTERNAL */

