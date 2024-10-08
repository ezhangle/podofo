/**
 * SPDX-FileCopyrightText: (C) 2007 Dominik Seichter <domseichter@web.de>
 * SPDX-FileCopyrightText: (C) 2020 Francesco Pretto <ceztko@gmail.com>
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef PDF_CMAP_ENCODING_H
#define PDF_CMAP_ENCODING_H

#include "PdfEncodingMap.h"

namespace PoDoFo
{
    struct PODOFO_API PdfCIDSystemInfo final
    {
        PdfString Registry;
        PdfString Ordering;
        int Supplement = 0;
    };

    class PODOFO_API PdfCMapEncoding final : public PdfEncodingMapBase
    {
        friend class PdfEncodingMapFactory;

    public:
        /** Construct a PdfCMapEncoding from a map
         */
        PdfCMapEncoding(PdfCharCodeMap&& map);
        PdfCMapEncoding(PdfCharCodeMap&& map, const PdfName& name, const PdfCIDSystemInfo& info, PdfWModeKind wMode);

        static PdfCMapEncoding Parse(const std::string_view& filepath);
        static PdfCMapEncoding Parse(InputStreamDevice& device);

    private:
        PdfCMapEncoding(PdfCharCodeMap&& map, const PdfName& name,
            const PdfCIDSystemInfo& info, int wmode, const PdfEncodingLimits& limits);

    public:
        bool HasLigaturesSupport() const override;
        const PdfEncodingLimits& GetLimits() const override;
        int GetWModeRaw() const override;
        PdfWModeKind GetWMode() const;

    public:
        const PdfName& GetName() const { return m_Name; }
        const PdfCIDSystemInfo& GetCIDSystemInfo() const { return m_CIDSystemInfo; }

    private:
        PdfName m_Name;
        PdfCIDSystemInfo m_CIDSystemInfo;
        int m_WMode;
        PdfEncodingLimits m_Limits;
    };
}

#endif // PDF_CMAP_ENCODING_H
