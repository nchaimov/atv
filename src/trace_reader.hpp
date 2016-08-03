#ifndef TRACE_READER_HPP
#define TRACE_READER_HPP

#include <vector>
#include <list>
#include <cstdlib>
#include <otf2/otf2.h>
#include <stdexcept>
#include "status.hpp"
#include "callbacks.hpp"

class TraceReader {

    public:
    using locations_t = std::vector<uint64_t>;

    private:
    inline static void check_status(const OTF2_ErrorCode status, const std::string & msg) {
        const char * errname = OTF2_Error_GetName(status);
        const char * errdesc = OTF2_Error_GetDescription(status);
        if(status != OTF2_SUCCESS) {
            throw std::runtime_error(msg + ": " + errname + ": " + errdesc);
        }
    };

    template<typename T>
    inline static void check_ptr(const T* ptr, const std::string & msg) {
        if(ptr == nullptr) {
            throw std::runtime_error(msg + ": Null pointer");    
        }
    };

    const std::string anchor;
    OTF2_Reader * reader;
    locations_t locations;

    Callbacks * callbacks;

    public:
    TraceReader(std::string & filename, const locations_t & locations, Callbacks * callbacks);
    virtual ~TraceReader();
    ATVStatus read_traces();

};

#endif // TRACE_READER_HPP
