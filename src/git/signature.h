#ifndef YAGA_GIT_SIGNATURE_H
#define YAGA_GIT_SIGNATURE_H

#include <string>

#include <git2.h>

#include "types.h"

namespace yaga_git
{
    struct signature
    {
        static signature from_raw(const git_signature* signature_raw);

        explicit signature(const git_signature* signature_raw);
        signature(const std::string& name, const std::string& email, const time_with_offset& time);

        const std::string& email() const;
        const std::string& name() const;
        const time_with_offset& time() const;

      private:
        std::string name_;
        std::string email_;
        time_with_offset time_;
    };
}

#endif
