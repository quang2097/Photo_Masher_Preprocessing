#pragma once
#include "GuiLite.h"

class CCalculatorWnd : public c_wnd {
public:
    virtual void V_WND_MSGP_MAP() override;
    
    // Message handler callbacks for button clicks
    void OnAddClick(int control_id, c_wnd* p_wnd);
    void OnSubClick(int control_id, c_wnd* p_wnd);
    void OnMulClick(int control_id, c_wnd* p_wnd);
    void OnDivClick(int control_id, c_wnd* p_wnd);

private:
    c_edit m_editNum1;
    c_edit m_editNum2;
    c_label m_lblResult;
    c_button m_btnAdd;
    c_button m_btnSub;
    c_button m_btnMul;
    c_button m_btnDiv;
};

// Function exposed to main.cpp to start the calculator screen
void RunCalculatorUI();