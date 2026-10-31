// Generated with ImRAD 0.10-WIP
// visit https://github.com/tpecholt/imrad

#pragma once
#include <GLFW/glfw3.h>
#include <imrad.h>


class MainUI
{
public:
    /// @begin interface
    void Draw(GLFWwindow* window);

    std::string value1;
    std::string value2;
    std::string value3;
    std::string Input_Address;
    std::string value4;
    bool Preprocessings = false;
    bool Manual_Labeling = false;
    bool Assisted_Labeling = false;
    std::string value5;
    bool Spacing_Visible = false;
    std::string Output_Address;
    /// @end interface

private:
    /// @begin impl
    void DrawPopups();
    void CustomWidget_Draw(const ImRad::CustomWidgetArgs& args);
    void Draw_Spacing1(const ImRad::CustomWidgetArgs& args);
    void Draw_Spacing2(const ImRad::CustomWidgetArgs& args);
    void Draw_Spacing3(const ImRad::CustomWidgetArgs& args);
    void Save_Button_Clicked();

    /// @end impl
};

extern MainUI mainUI;
