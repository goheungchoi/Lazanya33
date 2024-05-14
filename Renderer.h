#pragma once

using namespace Gdiplus;

struct ScreenExtent {
  int width;
  int height;
};

class Buffer {
 public:
  HDC hdcMem;
  HBITMAP hBitmap;
  std::unique_ptr<Gdiplus::Graphics> graphics;

  Buffer(HDC parentDC, ScreenExtent extent) {
    hdcMem = CreateCompatibleDC(parentDC);
    if (!hdcMem) {
      throw std::runtime_error(
          "Buffer: Unable to create compatible device context!");
    }
    hBitmap = CreateCompatibleBitmap(parentDC, extent.width, extent.height);
    if (!hBitmap) {
      throw std::runtime_error("Buffer: Unable to create compatible bitmap!");
    }
    SelectObject(hdcMem, hBitmap);
    graphics = std::make_unique<Gdiplus::Graphics>(hdcMem);
    if (!graphics.get()) {
      throw std::runtime_error(
          "Buffer: Something went wrong with Gdiplus::Graphics "
          "construction process!");
    }
  }

  ~Buffer() {
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
  }
};

/**
 * @brief 디바이스 컨텍스트를 가져와 그래픽스 오브젝트를 설정한다.
 */
class GDIRenderer {
  // Constructor Input
  HWND _window;
  ScreenExtent _extent;

  // Display device contenxt
  HDC hdc;  // device context handle
  // see;
  // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-paintstruct

  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;

  // Rendering data
  std::unique_ptr<Buffer> backBuffer;

 public:
  /**
   * @brief GDIRenderer 구성자
   * @param window 윈도우 핸들
   * @param extent 스크린 크기 {넓이, 높이}
   */
  GDIRenderer(HWND window, ScreenExtent extent)
      : _window{window}, _extent{extent} {
    // Initialize GDI+
    hdc = GetDC(_window);
    if (!hdc) throw std::runtime_error("hdc init failed!");

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    // Set an off-screen buffer
    backBuffer = std::make_unique<Buffer>(hdc, extent);
  }

  ~GDIRenderer() {
    ReleaseDC(_window, hdc);
    GdiplusShutdown(gdiplusToken);
  }

  // graphics.DrawImage(&image, 120, 10, image.GetWidth(), image.GetHeight());
  Gdiplus::Graphics* GetGraphics() { return backBuffer->graphics.get(); }

  void Clear() {
    PatBlt(backBuffer->hdcMem, 0, 0, _extent.width, _extent.height, WHITENESS);
  }

  void Draw() {
    // When done, bit blt the memroy bitmap to the screen
    BitBlt(hdc, 0, 0, _extent.width, _extent.height, backBuffer->hdcMem, 0, 0,
           SRCCOPY);
  }
};
