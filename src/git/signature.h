#ifndef YAGA_GIT_SIGNATURE_H
#define YAGA_GIT_SIGNATURE_H

#include <stx/string_view.hpp>

#include <git2.h>

#include "types.h"

namespace yaga_git
{
    struct signature
    {
        signature(const std::string& name, const std::string& email, const time_with_offset& time);
        signature(const git_signature* signature_raw);

        const stx::string_view& email() const;
        const stx::string_view& name() const;
        const time_with_offset& time() const;

      private:
        stx::string_view name_;
        stx::string_view email_;
        time_with_offset time_;
    };
}

#endif
