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

      // Ű���� ���¸� ���ɴϴ�.
      BYTE keyboardState[256];
      if (!GetKeyboardState(keyboardState)) {
        return; // Ű���� ���¸� ������ ������ ���
      }

      // Ű �ڵ�� Ű���� ���¸� ����Ͽ� �����ڵ� ���ڷ� ��ȯ�մϴ�.
      WCHAR unicodeChar[3] = { 0 };  // �ѱ��� ��� �ִ� 2���� WCHAR�� �ʿ��� �� �ֽ��ϴ�.
      int count = ToUnicodeEx(key, 0, keyboardState, unicodeChar, 2, 0, NULL);

      // ���� ���ڰ� ��ȯ�Ǿ����� Ȯ���մϴ�.
      if (count > 0 && unicodeChar[0] != '\0') {
        if (unicodeChar[0] == '\b' && !text.empty()) {
          // �齺���̽� ó��
          text.pop_back();
        }
        else {
          // ��ȯ�� ���ڿ��� �ؽ�Ʈ�� �߰��մϴ�.
          text.append(unicodeChar, count);  // count ��ŭ�� ���ڸ� �߰��մϴ�.
        }
      }
    }

};