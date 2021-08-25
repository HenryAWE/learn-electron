// Author: HenryAWE
// License: The 3-clause BSD License

#ifndef TESTWORLD_EDITOR_PIXELPAINTER_HPP
#define TESTWORLD_EDITOR_PIXELPAINTER_HPP

#include <functional>
#include <map>
#include <vector>
#include <tuple>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "../renderer/texture.hpp"


namespace awe
{
    class Texture;

    class PixelPainter
    {
    public:
        PixelPainter();

        void NewFrame();

        glm::u8vec4 GetColor(
            std::size_t index,
            glm::ivec2 coord
        );

        void Show() noexcept;
        void Hide() noexcept;
        [[nodiscard]]
        constexpr bool IsShow() const noexcept { return m_open; }

    private:
        /* Bitmap data */
        struct BitmapData
        {
            std::string name;
            std::vector<glm::u8vec4> data;
            glm::ivec2 size;
            bool saved = false;
        };

        /* Children */
        void MenuBar();
        void Toolbox();
        void Canvas(std::size_t id);
        void BottomToolbox();

        void MenuBar_File();

        void NewBitmap(const std::string& name, glm::ivec2 size);

        Texture& GetCachedTex(std::size_t id);

        std::function<void()> m_popup;

        bool m_open = true;
        glm::vec4 m_color[2];
        int m_current_tool_id = 0;
        float m_factor = 1.0f;
        std::vector<BitmapData> m_bm_data; // Data of bitmaps
        std::map<std::size_t, Texture> m_cache;
        std::size_t m_current_bm_idx = -1;
    };
}

#endif
