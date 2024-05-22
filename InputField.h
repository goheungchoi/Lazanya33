// ChatGPT Generated

class TextInputField {
public:
    std::wstring text;  // Stores input from the user
    int x, y;           // Position of the text input field
    int width, height;  // Dimensions of the text input field
    bool focus;         // Whether the text field is currently focused

    TextInputField(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height), focus(false) {}

    void draw(Gdiplus::Graphics& graphics) {
        using namespace Gdiplus;

        // Draw the background
        SolidBrush brush(Color(255, 255, 255)); // White background
        graphics.FillRectangle(&brush, x, y, width, height);

        // Draw the border
        Pen pen(Color(0, 0, 0)); // Black border
        graphics.DrawRectangle(&pen, x, y, width, height);

        // Draw the text
        FontFamily fontFamily(L"Arial");
        Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);
        PointF origin((REAL)x + 2, (REAL)y + 2); // Small padding from the border
        SolidBrush textBrush(Color(0, 0, 0)); // Black text
        graphics.DrawString(text.c_str(), -1, &font, origin, &textBrush);

        // Draw the cursor if focused
        if (focus) {
            //int textWidth = (int)graphics.MeasureString(text.c_str(), -1, &font, origin, nullptr).Width;
            //graphics.DrawLine(&pen, x + 2 + textWidth, y + 2, x + 2 + textWidth, y + height - 4);
        }
    }

    void onClick(int mouseX, int mouseY) {
        // Check if the click is within the text field's bounds
        focus = (mouseX > x && mouseX < x + width && mouseY > y && mouseY < y + height);
    }

    void onKeyPress(WPARAM wParam) {
        if (!focus) return;

        switch (wParam) {
            case VK_BACK:
                if (!text.empty()) text.pop_back();
                break;
            default:
                if (wParam >= 0x20 && wParam <= 0x7E) { // Printable characters
                    text += static_cast<wchar_t>(wParam);
                }
                break;
        }
    }
};