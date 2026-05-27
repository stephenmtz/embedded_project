#pragma once 

#include <librealsense2/rs.hpp>  
#include <cstdint>  
#include <functional> 
#include <string>

namespace Realsense { 

    struct ColorFrame
    {
        const uint8_t* data; // BGR8 pixel buffer
        int height; 
        int width; 
        int stride; 
    };
    
    using FrameCallback = std::function<void(const ColorFrame&)>;

    class ColorStreamer {
        public: 
            explicit ColorStreamer(int width, int height, int fps=30); 
            ~ColorStreamer();

            ColorStreamer(const ColorStreamer&) = delete; 
            ColorStreamer& operator = (const ColorStreamer&) = delete; 

            void setFrameCallBack(FrameCallback cb); 

            void start(); 
            void stop();

            bool isRunning const();

        private: 
            rs2::config config_; 
            rs2::pipeline pipeline_; 
            FrameCallback callback_; 
            bool running_; 
            
            int width_; 
            int height_; 
            int fps_; 
    
    }

    CameraConfig loadConfig(const std::string& path);

} // namespace Realsense 
