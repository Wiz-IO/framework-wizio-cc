#ifndef RADIO_INSTANCE_HPP_
#define RADIO_INSTANCE_HPP_

#include <stdint.h>
#include <non_copyable.hpp>
#include "ieee_ot_radio.h"

typedef struct otInstance
{
} otInstance;

extern uint64_t gInstanceRaw[];

#define OT_DEFINE_ALIGNED_VAR(name, size, align_type) \
    align_type name[(((size) + (sizeof(align_type) - 1)) / sizeof(align_type))]

class Instance : public otInstance, private NonCopyable
{
public:
    Radio mRadio;

    Instance(void) : mRadio(*this)
    {
    }

    static Instance &Get(void)
    {
        void *instance = &gInstanceRaw;
        return *static_cast<Instance *>(instance);
    }
};

OT_DEFINE_ALIGNED_VAR(gInstanceRaw, sizeof(Instance), uint64_t);

#endif // RADIO_INSTANCE_HPP_