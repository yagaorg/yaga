#include "signature.h"

using namespace std;

namespace yaga_git
{
    signature signature::from_raw(const git_signature* raw_signature)
    {
        auto name = string(raw_signature->name);
        auto email = string(raw_signature->email);
        auto time = time_with_offset(raw_signature->when.time, raw_signature->when.offset);

        return signature(name, email, time);
    }

    signature::signature(const string& name, const string& email, const time_with_offset& time)
        : name_(name), email_(email), time_(time)
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
