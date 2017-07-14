// Copyright(c) 2016 - 2017 Costantino Grana, Federico Bolelli, Lorenzo Baraldi and Roberto Vezzani
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// *Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and / or other materials provided with the distribution.
//
// * Neither the name of YACCLAB nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef YACCLAB_LABELING_ALGORITHMS_H_
#define YACCLAB_LABELING_ALGORITHMS_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <opencv2/core.hpp>

#include "performance_evaluator.h"

#define UPPER_BOUND_8_CONNECTIVITY ((size_t)((img_.rows + 1) / 2) * (size_t)((img_.cols + 1) / 2) + 1);
//#define UPPER_BOUND_4_CONNECTIVITY todo;

class Labeling {
public:
    static cv::Mat1b img_;
    cv::Mat1i img_labels_;
    unsigned nlabels_;
    PerformanceEvaluator perf_;

    Labeling() {}
    virtual ~Labeling() = default;

    virtual unsigned PerformLabeling() { throw std::runtime_error("Average Test not implemented"); }
    virtual unsigned PerformLabelingWithSteps() { throw std::runtime_error("Average Test with Steps not implemented"); }
    virtual unsigned PerformLabelingMem(std::vector<unsigned long>& accesses) { throw std::runtime_error("Memory Test not implemented"); }

    static void SetImg(const cv::Mat1b& img) { img_ = img.clone(); }

private:

    virtual void AllocateMemory() = 0;
    virtual void DeallocateMemory() = 0;
    virtual unsigned FirstScan() { throw std::runtime_error("First Scan not implemented"); }
    virtual unsigned SecondScan(const unsigned& lunique) { throw std::runtime_error("Second Scan not implemented"); }
};

class LabelingMapSingleton {
public:
    std::map<std::string, Labeling*> data_;

    static LabelingMapSingleton& GetInstance();
    static Labeling* GetLabeling(const std::string& s);
    LabelingMapSingleton(LabelingMapSingleton const&) = delete;
    void operator=(LabelingMapSingleton const&) = delete;

private:
    LabelingMapSingleton() {}
    ~LabelingMapSingleton()
    {
        for (std::map<std::string, Labeling*>::iterator it = data_.begin(); it != data_.end(); ++it)
            delete it->second;
    }
};

#endif //YACCLAB_LABELING_ALGORITHMS_H_