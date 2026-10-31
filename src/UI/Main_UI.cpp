// Generated with ImRAD 0.10-WIP
// visit https://github.com/tpecholt/imrad

#include "Main_UI.h"

MainUI mainUI;


void MainUI::Draw(GLFWwindow* window)
{
    /// @dpi-info 94.5116,1
    /// @style Dark
    /// @unit dp
    /// @begin TopWindow
    const float dp = ImRad::GetUserData().dpiScale;
    ImGui::PushFont(nullptr, 20.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xffc0c0c0);
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, 0xff404040);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10*dp, -1*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, { 20*dp, -1*dp });
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10*dp);
    glfwSetWindowTitle(window, "Photo masher UI");
    ImGui::SetNextWindowPos({ 0, 0 });
    int tmpWidth, tmpHeight;
    glfwGetWindowSize(window, &tmpWidth, &tmpHeight);
    ImGui::SetNextWindowSize({ (float)tmpWidth, (float)tmpHeight });
    bool tmpOpen;
    if (ImGui::Begin("Photo masher UI###MainUI", &tmpOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar))
    {
        if (ImGui::IsWindowAppearing())
        {
            glfwSetWindowSize(window, 512*dp, 380*dp);
            glfwSetWindowSizeLimits(window, 0, 0, GLFW_DONT_CARE, GLFW_DONT_CARE);
            glfwSetWindowAttrib(window, GLFW_RESIZABLE, true);
            glfwSetWindowAttrib(window, GLFW_DECORATED, true);
        }
        ImGui::PopStyleVar(4);
        ImGui::PopStyleColor(2);
        ImGui::PopFont();
        DrawPopups();
        ImGui::PushFont(nullptr, 20.f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xffc0c0c0);
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, 0xff404040);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, ImGui::GetStyle().WindowBorderSize);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 10*dp, -1*dp });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, { 20*dp, -1*dp });
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10*dp);
        /// @separator

        /// @begin MenuBar
        if (ImGui::BeginMenuBar())
        {
            /// @separator

            /// @begin MenuIt
            if (ImGui::BeginMenu("Features"))
            {
                /// @separator

                /// @begin MenuIt
                ImGui::Separator();
                ImGui::MenuItem("Preprocessings", "", &Preprocessings);
                /// @end MenuIt

                /// @begin MenuIt
                ImGui::MenuItem("Manual labeling", "", &Manual_Labeling);
                /// @end MenuIt

                /// @begin MenuIt
                ImGui::MenuItem("Assisted labeling", "", &Assisted_Labeling);
                /// @end MenuIt

                /// @separator
                ImGui::EndMenu();
            }
            /// @end MenuIt

            /// @separator
            ImGui::EndMenuBar();
        }
        /// @end MenuBar

        /// @begin Text
        ImRad::Spacing(-1);
        ImGui::PushFont(nullptr, 20.f);
        ImGui::PushStyleColor(ImGuiCol_Text, 0xffffffff);
        ImGui::AlignTextToFramePadding();
        ImGui::PushTextWrapPos(0);
        ImGui::TextUnformatted("Input address");
        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();
        ImGui::PopFont();
        /// @end Text

        /// @begin CustomWidget
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        Draw_Spacing1(ImRad::CustomWidgetArgs("Spacing1", { 43*dp, 0 }));
        /// @end CustomWidget

        /// @begin Input
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, 0xff808080);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 3*dp);
        ImGui::SetNextItemWidth(150*dp);
        ImGui::InputText("##Input_Address", &Input_Address, 0);
        if (ImGui::IsItemActive())
            ImRad::GetUserData().imeType = ImRad::ImeText;
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        /// @end Input

        /// @begin CustomWidget
        ImRad::Spacing(-1);
        Draw_Spacing2(ImRad::CustomWidgetArgs("Spacing2", { 0, 0 }));
        /// @end CustomWidget

        /// @begin Text
        ImGui::PushFont(nullptr, 20.f);
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Output address");
        ImGui::PopFont();
        /// @end Text

        /// @begin CustomWidget
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        Draw_Spacing3(ImRad::CustomWidgetArgs("Spacing3", { 30*dp, 0 }));
        /// @end CustomWidget

        /// @begin Input
        ImGui::SameLine(0, 1 * ImGui::GetStyle().ItemSpacing.x);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, 0xff808080);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 3*dp);
        ImGui::SetNextItemWidth(150*dp);
        ImGui::InputText("##Output_Address", &Output_Address, 0);
        if (ImGui::IsItemActive())
            ImRad::GetUserData().imeType = ImRad::ImeText;
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        /// @end Input

        /// @begin Button
        ImGui::PushStyleColor(ImGuiCol_Border, 0xff404040);
        ImGui::PushStyleColor(ImGuiCol_Button, 0xff808080);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, 0xffc0c0c0);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, 0xff808080);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10*dp);
        ImGui::Button("Save", { 0, 0 });
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        if (ImGui::IsItemClicked())
            Save_Button_Clicked();
        /// @end Button

        /// @separator
    }
    ImGui::End();
    ImGui::PopStyleVar(4);
    ImGui::PopStyleColor(2);
    ImGui::PopFont();
    /// @end TopWindow
}

void MainUI::DrawPopups()
{
    // TODO: Draw dependent popups here
}

void MainUI::CustomWidget_Draw(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing1(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing2(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing3(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Save_Button_Clicked()
{
}

void MainUI::Draw_Spacing1(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing2(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing3(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing1(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing2(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing3(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing1(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing2(const ImRad::CustomWidgetArgs& args)
{
}

void MainUI::Draw_Spacing3(const ImRad::CustomWidgetArgs& args)
{
}
