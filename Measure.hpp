#pragma once

#include "IDataStorage.hpp"
#include "IEncoder.hpp"
#include <memory>
#include <iostream>

struct DataStoreMeasurement{
std::string component;
int64_t duration;
};


struct EncodeDataMeasurement{
    std::string buffer;
    int64_t duration;
};

struct EncodeDataMeasurement callMeasureEncoderStep(std::shared_ptr<IEncoder> encoder, std::shared_ptr<IDataStructure> data);
int64_t callMesureStoreDataStep(std::shared_ptr<IDataStorage> dataStorage, const int event, const std::string component, const std::string buffer);
void saveTimespan(int64_t encodingTimespan, int64_t storeTimespan, std::shared_ptr<std::fstream> handle);