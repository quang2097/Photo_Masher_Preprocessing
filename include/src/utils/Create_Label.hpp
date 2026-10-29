#pragma once
#ifndef CREATE_LABELS
#define CREATE_LABELS
#include <string>
#include <filesystem>
#include <vector>
namespace utils{
    namespace create_label{
        enum Create_Label_Type{
            ROTATE_PHOTO, FLIP_PHOTO
        };

        enum Dataset_Format{
            COCO, COCO_Segmentation, COCO_MMDetection, CreateML, PaliGemma, 
            Florence_2_Object_Detection, YOLO26, YOLOv8, YOLOv5, SAM_2,
            Pascal_VOC, YOLO_Darknet, YOLOv3_Keras, YOLOv4_PyTorch, Scaled_YOLOv4, 
            YOLOv6, YOLOv5, YOLOv7, YOLOv8, YOLOv9, 
            YOLOv11, YOLOv12, YOLO26, Tensorflow_Object_Detection, RetinaNet_Keras, 
            Tensorflow_TFRecord, Server_Benchmark, Multi_Label_Classification, OpenAI_Clip_Classification
        };

        struct Pair{
            int first;
            int second;

            // Constructor
            Pair(const int FIRST, const int SECOND){
                first = FIRST;
                second = SECOND;
            }
        };
    };

    namespace resize_photo{
        std::vector<std::string> create_label(const std::vector<std::string> INPUT, 
                                                const create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                const create_label::Pair RESOLUTIONS_VERTICAL,
                                                const create_label::Dataset_Format FORMAT);
    };
};
#endif