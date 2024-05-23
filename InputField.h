// ChatGPT Generated
#include "Container.h"

class TextInputField:public Container {
public:
    std::wstring text;  // Stores input from the user
    int x, y;           // Position of the text input field
    int width, height;  // Dimensions of the text input field
    bool focus;         // Whether the text field is currently focused

    TextInputField(int x, int y, int width, int height)
        : Container(x, y, width, height),x(x), y(y), width(width), height(height), focus(false) {}

    void Render(Gdiplus::Graphics& graphics)override {
        using namespace Gdiplus;

        // Draw the background
        //SolidBrush brush(Color(255, 255, 255)); // White background
        //graphics.FillRectangle(&brush, x, y, width, height);

        // Draw the border
        //Pen pen(Color(0, 0, 0)); // Black border
        //graphics.DrawRectangle(&pen, x, y, width, height);

        // Draw the text
        FontFamily fontFamily(L"Threat");
        Font font(&fontFamily, 100, FontStyleRegular, UnitPixel);
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

    void onKeyPress(BYTE key) {
      if (!focus) return;

      // 키보드 상태를 얻어옵니다.
      BYTE keyboardState[256];
      if (!GetKeyboardState(keyboardState)) {
        return; // 키보드 상태를 얻어오지 못했을 경우
      }

      // 키 코드와 키보드 상태를 사용하여 유니코드 문자로 변환합니다.
      WCHAR unicodeChar[3] = { 0 };  // 한글의 경우 최대 2개의 WCHAR가 필요할 수 있습니다.
      int count = ToUnicodeEx(key, 0, keyboardState, unicodeChar, 2, 0, NULL);

      // 실제 문자가 변환되었는지 확인합니다.
      if (count > 0 && unicodeChar[0] != '\0') {
        if (unicodeChar[0] == '\b' && !text.empty()) {
          // 백스페이스 처리
          text.pop_back();
        }
        else {
          // 변환된 문자열을 텍스트에 추가합니다.
          text.append(unicodeChar, count);  // count 만큼의 문자를 추가합니다.
        }
      }
    }

};