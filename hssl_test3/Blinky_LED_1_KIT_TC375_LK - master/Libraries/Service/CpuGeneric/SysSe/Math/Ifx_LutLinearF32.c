/**
 * \file Ifx_LutLinearF32.c
 * \brief Linear look-up function
 *
 *
 * \version disabled
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "Ifx_LutLinearF32.h"

/** \brief Look-up table with binary search implementation
 *
 * Value inside table will be linearly interpolated.
 * Value outside table will be linearly extrapolated.
 *
 * \param ml pointer to the multi-segment object
 * \param index
 * \return linear interpolated value */
float32 Ifx_LutLinearF32_searchBin(const Ifx_LutLinearF32 *ml, float32 index)
{
    sint16 imin;
    sint16 imax;
    sint16 imid;

    imin = 0;
    imax = ml->segmentCount - 1;

    if (ml->segments[1].boundary > ml->segments[0].boundary)
    {
        while (imin < imax)
        {
            imid = imin + (imax - imin) / 2;

            if (index > ml->segments[imid].boundary)
            {
                imin = imid + 1;
            }
            else
            {
                imax = imid;
            }
        }
    }
    else
    {
        while (imin < imax)
        {
            imid = imin + (imax - imin) / 2;

            if (index < ml->segments[imid].boundary)
            {
                imin = imid + 1;
            }
            else
            {
                imax = imid;
            }
        }
    }

    return (ml->segments[imin].gain * index) + ml->segments[imin].offset;
}
