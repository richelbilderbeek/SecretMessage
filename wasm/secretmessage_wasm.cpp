// Qt-free port of ribi::sema::MainDialog (secretmessagemaindialog.cpp),
// compiled to WebAssembly with Emscripten for the 'Run' page of the website.
//
// Images are passed as RGBA buffers (4 bytes per pixel, row-major),
// as obtained from an HTML canvas.

#include <algorithm>
#include <cstdint>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

namespace {

bool is_white(const std::uint8_t* rgba) noexcept
{
  const int sum = rgba[0] + rgba[1] + rgba[2];
  return sum / 3 > 127;
}

} // namespace

extern "C" {

// Width of the image created by create_secret_message
EMSCRIPTEN_KEEPALIVE int get_result_width(int original_width, int message_width)
{
  return std::min(original_width, message_width);
}

// Height of the image created by create_secret_message
EMSCRIPTEN_KEEPALIVE int get_result_height(int original_height, int message_height)
{
  return std::min(original_height, message_height);
}

// Hide 'message' in the red channel of 'original'.
// Makes all red values even, except where the message pixel is white.
// 'result' must hold get_result_width * get_result_height * 4 bytes.
EMSCRIPTEN_KEEPALIVE void create_secret_message(
  const std::uint8_t* original, int original_width, int original_height,
  const std::uint8_t* message, int message_width, int message_height,
  std::uint8_t* result
)
{
  const int width = std::min(original_width, message_width);
  const int height = std::min(original_height, message_height);
  const int dx1 = (original_width - width) / 2;
  const int dx2 = (message_width - width) / 2;
  const int dy1 = (original_height - height) / 2;
  const int dy2 = (message_height - height) / 2;
  for (int y = 0; y != height; ++y)
  {
    for (int x = 0; x != width; ++x)
    {
      const std::uint8_t* const p = original + 4 * ((dy1 + y) * original_width + (dx1 + x));
      const std::uint8_t* const m = message + 4 * ((dy2 + y) * message_width + (dx2 + x));
      std::uint8_t* const q = result + 4 * (y * width + x);
      int r = p[0];
      if (r % 2 != 0)
      {
        if (r == 255) { --r; } else { ++r; }
      }
      if (is_white(m)) ++r;
      q[0] = static_cast<std::uint8_t>(r);
      q[1] = p[1];
      q[2] = p[2];
      q[3] = 255;
    }
  }
}

// Extract the message hidden in the red channel:
// odd red value -> white, even red value -> black.
// 'result' must hold width * height * 4 bytes.
EMSCRIPTEN_KEEPALIVE void extract_secret_message(
  const std::uint8_t* image, int width, int height,
  std::uint8_t* result
)
{
  const int n = width * height;
  for (int i = 0; i != n; ++i)
  {
    const std::uint8_t v = (image[4 * i] % 2 == 0) ? 0 : 255;
    result[4 * i + 0] = v;
    result[4 * i + 1] = v;
    result[4 * i + 2] = v;
    result[4 * i + 3] = 255;
  }
}

} // extern "C"
