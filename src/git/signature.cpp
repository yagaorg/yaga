#include "signature.h"

using namespace std;

namespace yaga_git
{
    signature signature::from_raw(const git_signature* raw_signature)
    {
        return signature(raw_signature);
    }

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

    const string& signature::email() const
    {
        return email_;
    }

    const string& signature::name() const
    {
        return name_;
    }

    const time_with_offset& signature::time() const
    {
        return time_;
    }
}
