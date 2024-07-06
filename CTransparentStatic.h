// TransparentStatic.h
#pragma once

class CTransparentStatic : public CStatic
{
public:
    CTransparentStatic();
    virtual ~CTransparentStatic();

protected:
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
};

