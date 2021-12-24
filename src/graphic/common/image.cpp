// Author: HenryAWE
// License: The 3-clause BSD License

#include "image.hpp"
#include <stb_image.h>
#include <stb_image_write.h>


namespace awe::graphic::common
{
    namespace detailed
    {
        ImageBase::~ImageBase() noexcept
        {
            Release();
        }

        bool ImageBase::LoadFile(const char* file, int desired_channels, int* channel)
        {
            stbi_set_flip_vertically_on_load(true);
            glm::ivec2 size(0);
            void* tmp = stbi_load(file, &size[0], &size[1], channel, desired_channels);
            if(!tmp)
            {
                return false;
            }

            Release();
            m_raw_data = tmp;
            m_size = size;

            return true;
        }
        bool ImageBase::LoadMemory(
            const void* mem,
            std::size_t length,
            int desired_channels,
            int* channel
        ) {
            glm::ivec2 size(0);
            stbi_uc* tmp = stbi_load_from_memory(
                static_cast<const stbi_uc*>(mem),
                static_cast<int>(length),
                &size[0], &size[1], channel, desired_channels
            );
            if(!tmp)
            {
                return false;
            }

            Release();
            m_raw_data = tmp;
            m_size = size;

            return true;
        }
        void ImageBase::Release() noexcept
        {
            stbi_image_free(m_raw_data);
            m_raw_data = nullptr;
            m_size = glm::ivec2(0);
        }
    }
}
