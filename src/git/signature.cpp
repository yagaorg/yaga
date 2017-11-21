#include "signature.h"

namespace yaga_git
{
    signature::signature(
        const std::string& name,
        const std::string& email,
        const time_with_offset& time)
        : name_(name), email_(email), time_(time)
    {
    }

    signature::signature(const git_signature* raw_signature)
        : name_(raw_signature->name),
          email_(raw_signature->email),
          time_(raw_signature->when.time, raw_signature->when.offset)
    {
    }

    const stx::string_view& signature::email() const
    {
        return email_;
    }

    const stx::string_view& signature::name() const
    {
        return name_;
    }

    const time_with_offset& signature::time() const
    {
        return time_;
    }
}
