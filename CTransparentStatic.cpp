#include "pch.h"
#include "CTransparentStatic.h"
// TransparentStatic.cpp
//#include "TransparentStatic.h"

CTransparentStatic::CTransparentStatic() {}

CTransparentStatic::~CTransparentStatic() {}

BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_PAINT()
END_MESSAGE_MAP()

HBRUSH CTransparentStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CTransparentStatic::OnPaint()
{
    CPaintDC dc(this);

    CString strText;
    GetWindowText(strText);

    CRect rect;
    GetClientRect(rect);

    dc.SetBkMode(TRANSPARENT);
    dc.TextOut(0, 0, strText);
}
