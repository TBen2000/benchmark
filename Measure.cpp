#include "Measure.hpp"
#include <sstream>
#include <fstream>

struct EncodeDataMeasurement callMeasureEncoderStep(std::shared_ptr<IEncoder> encoder, std::shared_ptr<IDataStructure> data)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::string buffer = encoder->encode(data);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    // saveTimespan(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), "Encode");

    struct EncodeDataMeasurement ret;
    ret.buffer = buffer;
    ret.duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    return ret;
}

int64_t callMesureStoreDataStep(std::shared_ptr<IDataStorage> dataStorage, const int event, const std::string component, const std::string buffer)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    dataStorage->store(event, component, buffer);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    // saveTimespan(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(), "Store");
    //  TextToFileEncode.csv
    //  TextToSQLiteStore.csv
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void saveTimespan(int64_t encodingTimespan, int64_t storeTimespan, std::shared_ptr<std::fstream> handle)
{
    if (handle->is_open() == false)
        throw std::runtime_error("Output file is closed");

    std::stringstream textStream;

    // get length of file:
    handle->seekg(0, handle->end);
    int length = handle->tellg();
    handle->seekg(0, handle->beg);

    if (length == 0)
    {
        textStream << "encoding time in microseconds,storing time in microseconds"
                   << std::endl;
    }
    textStream << encodingTimespan << "," << storeTimespan << std::endl;
    std::string text = textStream.str();

    handle->write(text.c_str(), text.size());
}
